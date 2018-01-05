// declarations for motor control

#define ID  0
#define DIR1  1
#define DIR2  2
#define SPEED  3
#define NUM_MOTORS  3
#define NUM_PRESETS  10
#define PITCH_MIN 1750 //minimum output for pitch pid controller
#define YAW_MIN 900    //minimum output for yaw pid controller

/////////////////////////////////
//Global Variables
/////////////////////////////////
int presets[NUM_PRESETS][NUM_MOTORS];
int defaultPresets[NUM_PRESETS][NUM_MOTORS] =
// {Pitch, Yaw, Spring}
{
   {0, 0, 0},    //0  Keys arranged like a phone keypad '1' top left
   {70, 0, 30 },  //1
   {70, 35, 30 },  //2
   {70, 35, 30 },  //3
   {35, 0, 30 },  //4
   {35, 35, 30 },  //5
   {35, 70, 30 },  //6
   {70, 0, 30 },  //7
   {70, 35, 30 },  //8
   {70, 70, 30 }   //9
 };
