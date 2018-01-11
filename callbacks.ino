
void loadDefaultPresets(){
 Serial.println("Load Default Presets");
 for( int i = 0; i< NUM_PRESETS; i++)
 {
   for( int j = 0; j < NUM_MOTORS ;j++){
     presets[i][j] = defaultPresets[i][j];
   }
 }
}

void loadEEPromPresets(){
  
 Serial.println("load EEProm Presets");
  int b = 0;
  for(int i = 0; i< NUM_PRESETS; i++)
 {
     for(int j = 0; j < NUM_MOTORS ;j++){
       int value = EEPROM.read(b);
       presets[i][j] = value;
       b++;
     }
 }
}

void savePreset(){
  Serial.println("save preset" );
 int b = 0;
    for(int i = 0; i< NUM_PRESETS; i++){
    
       for( int j = 0; j < NUM_MOTORS ;j++){
        
         int value = presets[i][j];
         EEPROM.write(b, value);
         Serial.println(value);
         b++;
       }
   }
}

void ballReadyCB(int idx, int v, int up){                //called when ballReady microswitch goes HIGH
  newBall.trigger(newBall.EVT_OFF);       //turn off newBall signal
  ballLift.trigger(ballLift.EVT_OFF);      //turn on ball lift signal LOW to run motor
  Serial.println(F("Ball Ready"));        //debug feedback
}

void runPreset(int num){
  if(!pitchEn){
    pitchEn = true;
  }
  if(!yawEn){
    yawEn = true;
  }
  if(!springEn){
    springEn = true;
  }
  pitchSet = presets[num][0];
  yawSet = presets[num][1];
  springSet = presets[num][2];
  return;
}

void pitch(int duty){
  if (duty >= 0) {
    digitalWrite(PITCH_F, HIGH);
    digitalWrite(PITCH_R, LOW);
    Timer5.setPwmDuty(PITCH_PWM,duty);
  }
  else {
    digitalWrite(PITCH_F, LOW);
    digitalWrite(PITCH_R, HIGH);
    Timer5.setPwmDuty(PITCH_PWM,abs(duty));
  }
}

void yaw(int duty){
  if (duty >= 0) {
    digitalWrite(YAW_F, HIGH);
    digitalWrite(YAW_R, LOW);
    Timer5.setPwmDuty(YAW_PWM,duty);
  }
  else {
    digitalWrite(YAW_F, LOW);
    digitalWrite(YAW_R, HIGH);
    Timer5.setPwmDuty(YAW_PWM,abs(duty));
  }
}

void spring(int duty){
  if (duty >= 0) {
    digitalWrite(SPRING_D, HIGH);
    springDir = true;               //set a direction flag to be read by the spring ISR
    Timer5.setPwmDuty(SPRING_PWM,duty);
   }
  else {
    digitalWrite(SPRING_D, LOW);
    springDir = false;            ////set a direction flag to be read by the spring ISR
    Timer5.setPwmDuty(SPRING_PWM,abs(duty));
  }
return;
}

void runHome(){
    pitchEn = false;  //Turn off the control loops
    yawEn = false;
    springEn = false;    
    pitch(-4096);
    yaw(-4096);
    spring(4096);
    pitchHome.start();
    yawHome.start();
    springHome.start();
}

//void printPos(int idx, int v, int up ){
//  Serial.print(F("Pitch Encoder: "));
//  Serial.println(EncPitch.read());
//  Serial.print(F("Yaw Encoder: "));
//  Serial.println(EncYaw.read());
//}

void encoders(){
  if (pitchPos != EncPitch.read()){
    pitchPos = EncPitch.read();
    Serial.print(F("Pitch Encoder: "));
    Serial.println(EncPitch.read());  
  }
  if (yawPos != EncYaw.read()){
    yawPos = EncYaw.read();
    Serial.print(F("Yaw Encoder: "));
    Serial.println(EncYaw.read());
  }
  if (springPos != lastSpringPos){
     lastSpringPos = springPos;
    Serial.print(F("Spring Encoder: "));
    Serial.println(springPos);
  }
  
}

int scale(int setPt, int EncPos, int minSpeed){
  
    int error = setPt - EncPos;
    if (error > 20){
      return(4096);
    }
    if ((error <= 20) && (error > 1)){
      return map(error,1,80,minSpeed,4096);
    }
    if (error < -20){
      return(-4096);
    }
    if ((error >= -20) && (error < -0)){
      return map(error,-80,-1,-4096,(-1 * minSpeed));
    }
    else return 0;
}

void motors(){
  if (pitchEn){
    pitch(scale(pitchSet, EncPitch.read(), 1750));
  }
  if (yawEn){
    yaw(scale(yawSet, EncYaw.read(), 1250));
  }
  if (springEn){
    spring(scale(springSet, springPos, 3000));
  }
}

void feedback(){
 
}

void encoderSpring(){
  byte oldSREG = SREG; //remember if interupts are on or off
  noInterrupts(); //Turn off interrupts
  if(springDir) {
     springPos++;
  } 
  else {
    springPos--; 
  }
  SREG = oldSREG; //Turn back on interrupts, if they were off
  interrupts();
 }

