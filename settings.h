// declarations for motor control

#define ID  0
#define DIR1  1
#define DIR2  2
#define SPEED  300
#define NUM_MOTORS  3
#define NUM_PRESETS  10
#define PITCH_MIN 1750 //minimum output for pitch pid controller
#define YAW_MIN 900    //minimum output for yaw pid controller

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

