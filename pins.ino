
void initializeInputs(){
 pinMode(BALL_IN,INPUT);
 pinMode(LOADED,INPUT);
}

void initializeOutputs(){  //set pin modes and intial states
  //Sounds
  pinMode(SOUND_ON,OUTPUT);
  digitalWrite(SOUND_ON,HIGH);
  pinMode(SOUND_CRACK,OUTPUT);
  digitalWrite(SOUND_CRACK,HIGH);
  pinMode(SOUND_GRUNT,OUTPUT);
  digitalWrite(SOUND_GRUNT,HIGH);
  pinMode(SOUND_FOUR,OUTPUT);
  digitalWrite(SOUND_FOUR,HIGH);
  pinMode(SOUND_FIVE,OUTPUT);
  digitalWrite(SOUND_FIVE,HIGH);
  pinMode(SOUND_SIX,OUTPUT);
  digitalWrite(SOUND_SIX,HIGH);
  pinMode(SOUND_SEVEN,OUTPUT);
  digitalWrite(SOUND_SEVEN,HIGH);
  pinMode(SOUND_EIGHT,OUTPUT);
  digitalWrite(SOUND_EIGHT,HIGH);

  //Motors
//  pinMode(SPRING_PWM,OUTPUT);
//  digitalWrite(SPRING_PWM,LOW);
  pinMode(SPRING_D,OUTPUT);
  digitalWrite(SPRING_D,LOW);
//  pinMode(PITCH_PWM,OUTPUT);
//  digitalWrite(PITCH_PWM,LOW);
  pinMode(PITCH_F,OUTPUT);
  digitalWrite(PITCH_F,LOW);
  pinMode(PITCH_R,OUTPUT);
  digitalWrite(PITCH_R,LOW);
//  pinMode(YAW_PWM,OUTPUT);
//  digitalWrite(YAW_PWM,LOW);
  pinMode(YAW_F,OUTPUT);
  digitalWrite(YAW_F,LOW);
  pinMode(YAW_R,OUTPUT);
  digitalWrite(YAW_R,LOW);

  //Relay
  pinMode(BALL_LOAD,OUTPUT);
  digitalWrite(BALL_LOAD,HIGH);
  pinMode(SAFETY_DOOR,OUTPUT);
  digitalWrite(SAFETY_DOOR,HIGH);
  pinMode(REJECT_SOL,OUTPUT);
  digitalWrite(REJECT_SOL,HIGH);
  pinMode(FIRE_SOL,OUTPUT);
  digitalWrite(FIRE_SOL,HIGH);
  pinMode(POWER_CUT,OUTPUT);
  digitalWrite(POWER_CUT,HIGH);

  //Digital Signals
  pinMode(LATCH,OUTPUT);
  digitalWrite(LATCH,HIGH);
}
