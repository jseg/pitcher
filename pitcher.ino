

#define EI_NOTEXTERNAL
#include <EnableInterrupt.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TimerFive.h>
#include <Key.h>          //installs w/ Keypad.h
#include <Keypad.h>       //version 3.1.1
#include <EEPROM.h>       //version 2.0 (built-in)
#include <PID_v1.h>       //version 1.1.1
#include <Encoder.h>      //version 1.4
#include <Automaton.h>    //version 1.0.1
#include "pins.h"
#include "settings.h"

//////////////////////////////////////
//Program Objects And Global Variables
//////////////////////////////////////
//LCD
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
bool newStep = true; 

//Keypad

//Documentation: https://playground.arduino.cc/Code/Keypad
//Further (and better) documentation in the "Dynamic Keypad" example
const byte ROWS = 4; //four rows
const byte COLS = 5; //five columns

char keys[ROWS][COLS] = { //key map
    {'1','2','3','a','b'},
    {'4','5','6','c','d'},
    {'7','8','9','e','f'},
    {'*','0','#','g','h'}
};

bool edit = false;
byte rowPins[ROWS] = {31, 32, 33, 34}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {35, 36, 37, 38, 39}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );//instantiate keypad object

//Encoders
//Documentation: https://www.pjrc.com/teensy/td_libs_Encoder.html
volatile int springPos;     //value of spring encoder
int pitchPos;
int yawPos;
int lastSpringPos;
bool springDir = true;             //true for up, false for down
Encoder EncPitch(PITCH_A, PITCH_B); //instantiate pitch encoder, uses INT0 and INT1
Encoder EncYaw(YAW_A, YAW_B); ////instantiate pitch encoder, uses INT4 and INT5

//Motor Control Values 
bool pitchEn, yawEn, springEn;            //Enable booleans for PID loops
int pitchSet = 0, yawSet = 0, springSet = 0;  //Motor Setpoints
int pitchSpeed = 0, yawSpeed = 0, springSpeed = 0;
bool atSetPoint = false;
int currentPreset = 5;

//State Machines
//There are four global machine states "Loading", "Aiming", "Firing", and "Main". "Loading", 
//"Aiming", and "Firing" are binary and mutually exclusive; if one is true the others are false. 
//"Main" is a step sequence that defines 
Atm_step Main;
Atm_bit Loading;
Atm_bit Aiming;
Atm_bit Firing;

//Serial Command Line object 
//Documentation:https://github.com/tinkerspy/Automaton/wiki/The-command-machine
Atm_command cmd;  //This object is the primary way to control the machine during development     
char cmd_buffer[80];   // input buffer
enum { CMD_HIGH, CMD_LOW, CMD_READ, CMD_AREAD, CMD_AWRITE, //enum for switchcase in callback
       CMD_MODE_INPUT, CMD_MODE_OUTPUT, CMD_MODE_PULLUP, CMD_LOAD, CMD_NUMKEY, CMD_EEPROMSETUP, CMD_PITCH, CMD_YAW, CMD_SPRING, CMD_HOME, CMD_PID, CMD_MOVE, CMD_STATE, CMD_SERIAL };
const char cmdlist[] = //must be in the same order as enum
      "high low read aread awrite mode_input mode_output mode_pullup load numkey eepromsetup pitch yaw spring home pid move state serial"; 
      
//Objects related to the Ball Loading Sequence
//"LED" state machine reference: https://github.com/tinkerspy/Automaton/wiki/The-led-machine
//"Digital state machine reference: https://github.com/tinkerspy/Automaton/wiki/The-digital-machine
//"Step state machine reference: 
Atm_step loadSq;
Atm_led ballLift; //Controlls the ball lift arm motor
Atm_led newBall; //Controlls the "Latch" signal to call for a new ball from the hopper
Atm_digital ballReady; //Microswitch to signal that a ball is ready to load
Atm_digital loadSense; //Mircoswitch under the loading arm depressed and high at idle
Atm_timer springLoad;

//Objects related to Firing Sequence
Atm_step fireSq;
Atm_timer moving;
Atm_led fireSol;
Atm_led doorSol;
Atm_led sound;


//Objects related to the Home Sequence
//"Timer" state machine reference: https://github.com/tinkerspy/Automaton/wiki/The-timer-machine
Atm_timer yawHome;   //controlls the amount of time the motors run during homing
Atm_timer pitchHome;
Atm_timer springHome;

//Temporary Timer Object
Atm_timer printEncoders;







/////////////////////////////////
//Setup
/////////////////////////////////
void setup() {
//Pin Initialization
  initializeInputs();
  initializeOutputs();
  
  //Motor Setup
  Timer5.initialize(4096);                            //start timer five at ~4khz
  Timer5.pwm(PITCH_PWM,0);
  Timer5.pwm(YAW_PWM,0);
  Timer5.pwm(SPRING_PWM,0);

  //LCD Setup
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight 
  
  //Keypad setup
  keypad.addEventListener(keypadEvent); // Add an event listener for the keypad. Callback in UI.ino
  
  //Serial UI set-up
  Serial.begin(115200); 
  help();
  cmd.begin( Serial, cmd_buffer, sizeof( cmd_buffer ) ) //start the serial ui
      .list( cmdlist)                                   //assign command list from above
      .onCommand( cmd_callback );                       //assign callback, located in UI.ino

  //Main Sequence Set-up
  Main.begin();
  Main.onStep( 0, Loading, Loading.EVT_ON );  //Loading
  Main.onStep( 1, Aiming, Aiming.EVT_ON );  //Aiming
  Main.onStep( 2, Firing, Firing.EVT_ON );  //Firing
  Loading.begin()
         .onChange(true, loadSq, loadSq.EVT_STEP); //Step loadSq S0->S1
  Aiming.begin();
  Firing.begin()
        .onChange(true, fireSq, fireSq.EVT_STEP); //Step fireSq S0->S1
  
  //Ball Load Sequence Set-up
  loadSq.begin();
  loadSq.onStep(0 , [] (int idx, int v, int up){    //First step of the loadSq is to grab the carriage
    Serial.println(F("loadSq state 1"));
    if (Loading.state()){
      runHome();
    }
    });
  loadSq.onStep(1, [] ( int idx, int v, int up ) {    //Run the carriage down to get a ball
   // if (Loading.state()){
      springLoad.trigger(springLoad.EVT_START);
      springEn = false;
      spring(4096);
      yawSet = 35;
      newBall.trigger(newBall.EVT_ON);
  });  
  //loadSq.onStep(2, newBall, newBall.EVT_ON);           //Call for a new ball
  loadSq.onStep(2, [] ( int idx, int v, int up ) {     //Return to previous preset
    printStates();
    //runPreset(currentPreset);
    Loading.trigger(Loading.EVT_OFF);                  //Finish Loading Sequence
    Main.trigger(Main.EVT_STEP);                       //Transistion to Aiming
  });

  fireSq.begin();
    fireSq.onStep(0 , moving, moving.EVT_START);    //Step to ensure the rig has stopped moving
    fireSq.onStep(1, [](int idx, int v, int up){    //Throw the ball!
      Serial.println(F("Fire in the hole!"));
      doorSol.trigger(doorSol.EVT_BLINK);
      fireSol.trigger(fireSol.EVT_BLINK);
      });

    doorSol.begin(SAFETY_DOOR,true).blink(2000,250,1);
    fireSol.begin(FIRE_SOL).blink(2005,250,1)
           .onFinish([](int idx, int v, int up){
           Firing.trigger(Firing.EVT_OFF);
           Main.trigger(Main.EVT_STEP); 
           });
      

    moving.begin(200)                       //initialize timer at 200 milli secs
         .repeat(-1)
         .onTimer( [] ( int idx, int v, int up ) {      //lambda function that turns off motor
      if(atSetPoint){
      pitchEn = false;
      yawEn = false;
      springEn = false;
      fireSq.trigger(fireSq.EVT_STEP);                //Step fire sequence S1->S2
      moving.trigger(moving.EVT_STOP);
      Serial.println(F("Still moving...")); 
      }
      });
   
  springLoad.begin(3000)                                   //initialize timer at 3 secs
         .onTimer( [] ( int idx, int v, int up ) {      //lambda function that turns off motor
      spring(0);
      springPos = 300;
      springSet = 300;
      springEn = false;
      //loadSq.trigger(loadSq.EVT_STEP);                //Step loadSq S2->S3
    });
  
  newBall.begin(LATCH);                                 //Starts in IDLE state, BALL_IN: LOW
  ballReady.begin(BALL_IN,20)                           //when ballReady is HIGH for 20ms:
           .onChange(HIGH,ballReadyCB);                 // run callback that turns off newBall and turns on lift motor
                                                        //make lambda function: https://github.com/tinkerspy/Automaton/wiki/Introduction
  ballLift.begin(BALL_LOAD, true);                            //Starts in IDLE state, BALL_LOAD: LOW
  loadSense.begin(LOADED,200)                            //when loadSense is HIGH for 20ms:
           .onChange(HIGH,[] ( int idx, int v, int up ) {//turn off the lift motor and advance the LoadSq
            if (loadSq.state()==1){
              ballLift.trigger(ballLift.EVT_OFF);      
              loadSq.trigger(loadSq.EVT_STEP);         //Step loadSq S3->S4
            }
            });    

  //Home Motors Sequence Set-up
  yawHome.begin(3000)                                   //initialize timer at 3 secs
         .onTimer( [] ( int idx, int v, int up ) {      //lambda function to turn off motor and reset PID
      yaw(0);                                           //turn motor off
      EncYaw.write(0);                                  //set the encoder to zero
      yawSet = EncYaw.read();                           //Yaw setpoint equals encoder value (0)
      yawPos = EncYaw.read();                            //Sync control loop sample with new home
      yawEn = true;                                     //Turn motor control back on
    });
  pitchHome.begin(3000)                                 //initialize timer at 3 secs
         .onTimer( [] ( int idx, int v, int up ) {      //lambda function to turn off motor and reset PID
      pitch(0);                                         //turn the motore off
      EncPitch.write(0);                                //set the encoder to zero
      pitchSet = EncPitch.read();                       //Pitch setpoint equals encoder value (0)
      pitchPos = EncPitch.read();                        //Sync control loop sample with new home
      pitchEn = true;                                   //Turn motor controll back  on
    });
  springHome.begin(3005)                                   //initialize timer at 3 secs
         .onTimer( [] ( int idx, int v, int up ) {      //lambda function that turns off motor
      spring(0);
      springPos = 286;
      springSet = 0;
      springEn = true;
      if(Loading.state()){
      loadSq.trigger(loadSq.EVT_STEP);                  //Step loadSq S1->S2
      }
    }); 


 printEncoders.begin(100)
            .onTimer(printPos)
            .repeat(-1)
            .start();
  
loadEEPromPresets();                                  //load presets from memory

automaton.run();
Main.trigger(Main.EVT_STEP);
printStates();
    
}

/////////////////////////////////
//Loop
/////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();                           //poll the keypad for pressed keys
  encoders();                                           //passes volatile encoder states to globals for use in control loop
  automaton.run();                                      //run the state machines
  feedback();
  atSetPoint = motors();
}
