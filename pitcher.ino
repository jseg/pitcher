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

byte rowPins[ROWS] = {31, 32, 33, 34}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {35, 36, 37, 38, 39}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );//instantiate keypad object

//Encoders
//Documentation: https://www.pjrc.com/teensy/td_libs_Encoder.html
int yawPos; //value of yaw encoder
int pitchPos; //value of pitch encoder
Encoder EncPitch(PITCH_A, PITCH_B); //instantiate pitch encoder, uses INT0 and INT1
Encoder EncYaw(YAW_A, YAW_B); ////instantiate pitch encoder, uses INT4 and INT5

//State Machines

//Serial Command Line object 
//Documentation:https://github.com/tinkerspy/Automaton/wiki/The-command-machine
Atm_command cmd;  //This object is the primary way to control the machine during development     
char cmd_buffer[80];   // input buffer
enum { CMD_HIGH, CMD_LOW, CMD_READ, CMD_AREAD, CMD_AWRITE, //enum for switchcase in callback
       CMD_MODE_INPUT, CMD_MODE_OUTPUT, CMD_MODE_PULLUP, CMD_LOAD, CMD_NUMKEY, CMD_EEPROMSETUP, CMD_PITCH, CMD_YAW, CMD_SPRING, CMD_HOME };
const char cmdlist[] = //must be in the same order as enum
      "high low read aread awrite mode_input mode_output mode_pullup load numkey eepromsetup pitch yaw spring home"; 
      
//Objects related to the Ball Load Sequence
//"LED" state machine reference: https://github.com/tinkerspy/Automaton/wiki/The-led-machine
//"Digital state machine reference: https://github.com/tinkerspy/Automaton/wiki/The-digital-machine
Atm_led ballLift; //Controlls the ball lift arm motor
Atm_led newBall; //Controlls the "Latch" signal to call for a new ball from the hopper
Atm_digital ballReady; //Microswitch to signal that a ball is ready to load
Atm_digital loadSense; //Mircoswitch under the loading arm depressed and high at idle

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
  
  //Keypad setup
  keypad.addEventListener(keypadEvent); // Add an event listener for the keypad. Callback in UI.ino
  
  //Serial UI set-up
  Serial.begin(9600); 
  cmd.begin( Serial, cmd_buffer, sizeof( cmd_buffer ) ) //start the serial ui
      .list( cmdlist)                                   //assign command list from above
      .onCommand( cmd_callback );                       //assign callback, located in UI.ino
  
  //Ball Load Sequence Set-up
  newBall.begin(LATCH);                                 //Starts in IDLE state, BALL_IN: LOW
    ballReady.trace(Serial);
  loadSense.trace(Serial);
  newBall.begin(LATCH);                                 //Starts in IDLE state, BALL_IN: LOW
  ballReady.begin(BALL_IN,20)                            //when ballReady is HIGH for 20ms:
           .onChange(HIGH,ballReadyCB);                 // run callback that turns off newBall and turns on lift motor
                                                        //make lambda function: https://github.com/tinkerspy/Automaton/wiki/Introduction
  ballLift.begin(BALL_LOAD);                            //Starts in IDLE state, BALL_LOAD: LOW
  loadSense.begin(LOADED,20)                            //when loadSense is HIGH for 20ms:
           .onChange(HIGH,ballLift,ballLift.EVT_ON);   //turn off the lift motor

  //Home Motors Sequence Set-up
  yawHome.begin(3000)                                   //initialize timer at 3 secs
         .onTimer( [] ( int idx, int v, int up ) {      //lambda function that turns off motor
      yaw(0);
    });
  pitchHome.begin(3000)                                   //initialize timer at 3 secs
         .onTimer( [] ( int idx, int v, int up ) {      //lambda function that turns off motor
      pitch(0);
    });
  springHome.begin(3000)                                   //initialize timer at 3 secs
         .onTimer( [] ( int idx, int v, int up ) {      //lambda function that turns off motor
      spring(0);
    }); 

  printEncoders.begin(300)
          .onTimer(printPos)
          .repeat(-1)
          .start();
  loadEEPromPresets();                                  //load presets from memory
  help();
}

/////////////////////////////////
//Loop
/////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();                           //poll the keypad for pressed keys
  encoders();                                           //passes volatile encoder states to globals for use in control loop
  automaton.run();                                      //run the state machines
}
