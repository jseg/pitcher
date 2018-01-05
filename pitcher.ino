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
int yawPos = 0; //value of yaw encoder
int pitchPos = 0; //value of pitch encoder
Encoder EncPitch(PITCH_A, PITCH_B); //instantiate pitch encoder, uses INT0 and INT1
Encoder EncYaw(YAW_A, YAW_B); ////instantiate pitch encoder, uses INT4 and INT5

//PID Loops 
bool pitchEn, yawEn;            //Enable booleans for PID loops
double pitchSet = 0, pitchIn = 0, pitchOut = 0, yawSet = 0, yawIn = 0, yawOut = 0;  //PID loop inputs and outputs
double pitchKp = 10, pitchKi= 50, pitchKd=5;  //Initial pitch PID parameters
double yawKp = 10, yawKi= 50, yawKd=5;  //Initial pitch PID parameters
PID pitchPID(&pitchIn, &pitchOut, &pitchSet,pitchKp,pitchKi,pitchKd,P_ON_M, DIRECT);
PID yawPID(&yawIn, &yawOut, &yawSet,yawKp,yawKi,yawKd,P_ON_M, DIRECT);

//State Machines

//Serial Command Line object 
//Documentation:https://github.com/tinkerspy/Automaton/wiki/The-command-machine
Atm_command cmd;  //This object is the primary way to control the machine during development     
char cmd_buffer[80];   // input buffer
enum { CMD_HIGH, CMD_LOW, CMD_READ, CMD_AREAD, CMD_AWRITE, //enum for switchcase in callback
       CMD_MODE_INPUT, CMD_MODE_OUTPUT, CMD_MODE_PULLUP, CMD_LOAD, CMD_NUMKEY, CMD_EEPROMSETUP, CMD_PITCH, CMD_YAW, CMD_SPRING, CMD_HOME, CMD_PID, CMD_YAWSET, CMD_PITCHSET, CMD_MOVE };
const char cmdlist[] = //must be in the same order as enum
      "high low read aread awrite mode_input mode_output mode_pullup load numkey eepromsetup pitch yaw spring home pid yawset pitchset move"; 
      
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
//Atm_timer printEncoders;







/////////////////////////////////
//Setup
/////////////////////////////////
void setup() {

  //Motor Setup
  Timer5.initialize(4096);                            //start timer five at ~4khz
  Timer5.pwm(PITCH_PWM,0);
  Timer5.pwm(YAW_PWM,0);
  Timer5.pwm(SPRING_PWM,0);
  
  //Keypad setup
  keypad.addEventListener(keypadEvent); // Add an event listener for the keypad. Callback in UI.ino
  
  //Serial UI set-up
  Serial.begin(9600); 
  help();
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
         .onTimer( [] ( int idx, int v, int up ) {      //lambda function to turn off motor and reset PID
      yaw(0);                                           //turn motor off
      EncYaw.write(0);                                  //set the encoder to zero
      yawSet = EncYaw.read();                           //Yaw setpoint equals encoder value (0)
      yawIn = EncYaw.read();                            //Sync control loop sample with new home
      yawPID.SetMode(AUTOMATIC);                        //Turn PID back on
    });
  pitchHome.begin(3000)                                 //initialize timer at 3 secs
         .onTimer( [] ( int idx, int v, int up ) {      //lambda function to turn off motor and reset PID
      pitch(0);                                         //turn the motore off
      EncPitch.write(0);                                //set the encoder to zero
      pitchSet = EncPitch.read();                       //Pitch setpoint equals encoder value (0)
      pitchIn = EncPitch.read();                        //Sync control loop sample with new home
      pitchPID.SetMode(AUTOMATIC);                      //Turn PID back on
    });
  springHome.begin(3000)                                   //initialize timer at 3 secs
         .onTimer( [] ( int idx, int v, int up ) {      //lambda function that turns off motor
      spring(0);
    }); 

//  printEncoders.begin(1000)
//          .onTimer(printPos)
//          .repeat(-1)
//          .start();
  loadEEPromPresets();                                  //load presets from memory
  
  
  //Pin Initialization
  initializeInputs();
  initializeOutputs();

pitchPID.SetOutputLimits(-4096,4096);
pitchPID.SetSampleTime(50);  

yawPID.SetOutputLimits(-4096,4096);
yawPID.SetSampleTime(50);  
}

/////////////////////////////////
//Loop
/////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:
  char key = keypad.getKey();                           //poll the keypad for pressed keys
  encoders();                                           //passes volatile encoder states to globals for use in control loop
  automaton.run();                                      //run the state machines
  pid();
  feedback();
}
