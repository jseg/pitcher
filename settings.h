// declarations for motor control

#define ID  0
#define DIR1  1
#define DIR2  2
#define SPEED  3
#define NUM_MOTORS  3
#define NUM_PRESETS  10

/////////////////////////////////
//Global Variables
/////////////////////////////////
int presets[NUM_PRESETS][NUM_MOTORS];
int defaultPresets[NUM_PRESETS][NUM_MOTORS] =
// {V, H, P}
{
   {3, 10, 0},
   {3, 10, 30 },
   {3, 20, 30 },
   {3, 30, 30 },
   {5, 10, 30 },
   {5, 20, 30 },
   {5, 30, 30 },
   {7, 10, 30 },
   {7, 20, 30 },
   {7, 30, 30 }
 };
