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
   {60, 10, 200 },  //1
   {60, 35, 200 },  //2
   {60, 35, 200 },  //3
   {35, 10, 200 },  //4
   {35, 35, 200 },  //5
   {35, 60, 200 },  //6
   {10, 10, 200 },  //7
   {10, 35, 200 },  //8
   {10, 70, 200 }   //9
 };
int defaultPresets[NUM_PRESETS][NUM_MOTORS] =
// {Pitch, Yaw, Spring}
{
   {0, 0, 0},    //0  Keys arranged like a phone keypad '1' top left
   {60, 10, 200 },  //1
   {60, 35, 200 },  //2
   {60, 60, 200 },  //3
   {35, 10, 170 },  //4
   {35, 35, 170 },  //5
   {35, 60, 170 },  //6
   {10, 10, 150 },  //7
   {10, 35, 150 },  //8
   {10, 60, 150 }   //9
 };

 const char gc1[] PROGMEM = "High and Away";
const char gc2[] PROGMEM = "High";
const char gc3[] PROGMEM = "High and Inside";
const char gc4[] PROGMEM = "Outside";
const char gc5[] PROGMEM = "Down the Middle";
const char gc6[] PROGMEM = "Inside";
const char gc7[] PROGMEM = "Low and Away ";
const char gc8[] PROGMEM = "Low";
const char gc9[] PROGMEM = "Low and Inside";

PGM_P const code_table[] PROGMEM = {
  gc1, gc2, gc3, gc4, gc5, gc6, gc7, gc8, gc9};

 

