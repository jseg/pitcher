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

/////////////////////////////////
//Global Variables
/////////////////////////////////
int presets[NUM_PRESETS][NUM_MOTORS]=
   {
   {0, 0, 0},    //0  Keys arranged like a phone keypad '1' top left
   {60, 10, 2000 },  //1
   {60, 35, 2000 },  //2
   {60, 35, 2000},  //3
   {35, 10, 2000 },  //4
   {35, 35, 2000 },  //5
   {35, 60, 2000 },  //6
   {10, 10, 2000 },  //7
   {10, 35, 2000 },  //8
   {10, 70, 2000 }   //9
 };
int defaultPresets[NUM_PRESETS][NUM_MOTORS] =
// {Pitch, Yaw, Spring}
{
   {0, 0, 0},    //0  Keys arranged like a phone keypad '1' top left
   {60, 10, 2000 },  //1
   {60, 35, 2000 },  //2
   {60, 60, 2000 },  //3
   {35, 10, 1700 },  //4
   {35, 35, 1700 },  //5
   {35, 60, 1700 },  //6
   {10, 10, 1500 },  //7
   {10, 35, 1500 },  //8
   {10, 60, 1500 }   //9
 };


 int rightPresets[NUM_PRESETS][NUM_MOTORS] =
// {Pitch, Yaw, Spring}
{
   {0, 0, 0},    //0  Keys arranged like a phone keypad '1' top left
   {60, 10, 2000 },  //1
   {60, 35, 2000 },  //2
   {60, 60, 2000 },  //3
   {35, 10, 1700 },  //4
   {35, 35, 1700 },  //5
   {35, 60, 1700 },  //6
   {10, 10, 1500 },  //7
   {10, 35, 1500 },  //8
   {10, 60, 1500 }   //9
 };

 int leftPresets[NUM_PRESETS][NUM_MOTORS] =
// {Pitch, Yaw, Spring}
{
   {0, 0, 0},    //0  Keys arranged like a phone keypad '1' top left
   {60, 20, 2000 },  //1
   {60, 45, 2000 },  //2
   {60, 70, 2000 },  //3
   {35, 20, 1700 },  //4
   {35, 45, 1700 },  //5
   {35, 70, 1700 },  //6
   {10, 20, 1500 },  //7
   {10, 45, 1500 },  //8
   {10, 70, 1500 }   //9
 };

const char rc1[] PROGMEM = "High and Away";
const char rc2[] PROGMEM = "High";
const char rc3[] PROGMEM = "High and Inside";
const char rc4[] PROGMEM = "Outside";
const char rc5[] PROGMEM = "Down the Middle";
const char rc6[] PROGMEM = "Inside";
const char rc7[] PROGMEM = "Low and Away ";
const char rc8[] PROGMEM = "Low";
const char rc9[] PROGMEM = "Low and Inside";

PGM_P const right_table[] PROGMEM = {
  rc1, rc2, rc3, rc4, rc5, rc6, rc7, rc8, rc9};

const char lc1[] PROGMEM = "High and Inside";
const char lc2[] PROGMEM = "High";
const char lc3[] PROGMEM = "High and Away";
const char lc4[] PROGMEM = "Inside";
const char lc5[] PROGMEM = "Down the Middle";
const char lc6[] PROGMEM = "Outside";
const char lc7[] PROGMEM = "Low and Inside ";
const char lc8[] PROGMEM = "Low";
const char lc9[] PROGMEM = "Low and Away";

PGM_P const left_table[] PROGMEM = {
  lc1, lc2, lc3, lc4, lc5, lc6, lc7, lc8, lc9};


 

