//Sound Ajustments
#define TOSSTIME 200    //Amount of time required for the ball to travel from the pocket to strike zone plane
#define SIGNALTIME 230  //Amount of time require for the sound board to resond to a signal
#define OFFSETTIME 400  //Amount of time to shift the entire sequence to allow for faster pitches

// declarations for motor control

#define ID  0
#define DIR1  1
#define DIR2  2
#define SPEED  450  
#define NUM_MOTORS  3
#define NUM_PRESETS  10
#define PITCH_MIN 1750 //minimum output for pitch pid controller
#define YAW_MIN 900    //minimum output for yaw pid controller
#define SOUND_DELAY 400

// Servo door adjustments
#define SERVO_OPEN 60
#define SERVO_CLOSED 0

/////////////////////////////////
//Global Variables
/////////////////////////////////
int presets[NUM_PRESETS][NUM_MOTORS]=
   {
   {0, 0, 0},    //0  Keys arranged like a phone keypad '1' top left
   {60, 10, 190 },  //1
   {60, 35, 190 },  //2
   {60, 35, 190},  //3
   {35, 10, 180 },  //4
   {35, 35, 180 },  //5
   {35, 60, 180 },  //6
   {10, 10, 160 },  //7
   {20, 35, 160 },  //8
   {10, 70, 160 }   //9
 };
int defaultPresets[NUM_PRESETS][NUM_MOTORS] =
// {Pitch, Yaw, Spring}
{
   {0, 0, 0},    //0  Keys arranged like a phone keypad '1' top left
   {60, 10, 190 },  //1
   {60, 35, 190 },  //2
   {60, 60, 190 },  //3
   {35, 10, 180 },  //4
   {35, 35, 180 },  //5
   {35, 60, 180 },  //6
   {10, 10, 160 },  //7
   {20, 35, 160 },  //8
   {10, 60, 160 }   //9
 };


 int rightPresets[NUM_PRESETS][NUM_MOTORS] =
// {Pitch, Yaw, Spring}
{
   {0, 0, 0},    //0  Keys arranged like a phone keypad '1' top left
   {60, 10, 190 },  //1
   {60, 35, 190 },  //2
   {60, 60, 190 },  //3
   {35, 10, 180 },  //4
   {35, 35, 180 },  //5
   {35, 60, 180 },  //6
   {10, 10, 160 },  //7
   {20, 35, 160 },  //8
   {10, 60, 160 }   //9
 };

 int leftPresets[NUM_PRESETS][NUM_MOTORS] =
// {Pitch, Yaw, Spring}
{
   {0, 0, 0},    //0  Keys arranged like a phone keypad '1' top left
   {60, 20, 190 },  //1
   {60, 45, 190 },  //2
   {60, 70, 190 },  //3
   {35, 20, 180 },  //4
   {35, 45, 180 },  //5
   {35, 70, 180 },  //6
   {10, 20, 160 },  //7
   {20, 45, 160 },  //8
   {10, 70, 160 }   //9
 };

const char rc1[] PROGMEM = "High Outside";
const char rc2[] PROGMEM = "High Middle";
const char rc3[] PROGMEM = "High Inside";
const char rc4[] PROGMEM = "Middle Outside";
const char rc5[] PROGMEM = "Middle Middle";
const char rc6[] PROGMEM = "Middle Inside";
const char rc7[] PROGMEM = "Low Outside ";
const char rc8[] PROGMEM = "Low Middle";
const char rc9[] PROGMEM = "Low Inside";

PGM_P const right_table[] PROGMEM = {
  rc1, rc2, rc3, rc4, rc5, rc6, rc7, rc8, rc9};

const char lc1[] PROGMEM = "High Inside";
const char lc2[] PROGMEM = "High Middle";
const char lc3[] PROGMEM = "High Outside";
const char lc4[] PROGMEM = "Middle Inside";
const char lc5[] PROGMEM = "Middle Middle";
const char lc6[] PROGMEM = "Middle Outside";
const char lc7[] PROGMEM = "Low Inside ";
const char lc8[] PROGMEM = "Low Middle";
const char lc9[] PROGMEM = "Low Outside";

PGM_P const left_table[] PROGMEM = {
  lc1, lc2, lc3, lc4, lc5, lc6, lc7, lc8, lc9};


 

