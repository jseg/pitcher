

void loadDefaultPresets(){
 if(!digitalRead(HAND)){
   Serial.println(F("Load Left Presets"));
   for( int i = 0; i< NUM_PRESETS; i++)
   {
     for( int j = 0; j < NUM_MOTORS ;j++){
       presets[i][j] = leftPresets[i][j];
     }
   }
 }
 else{
  Serial.println(F("Load Right Presets"));
   for( int i = 0; i< NUM_PRESETS; i++)
   {
     for( int j = 0; j < NUM_MOTORS ;j++){
       presets[i][j] = rightPresets[i][j];
     }
   }
 }
}

void loadFactoryPresets(){
 Serial.println("Load Default Presets");
 for( int i = 0; i< NUM_PRESETS; i++)
 {
   for( int j = 0; j < NUM_MOTORS ;j++){
     presets[i][j] = defaultPresets[i][j];
   }
 }
}

void loadEEPromPresets(int idx, int v, int up){
 if(edit){savePreset(!(batterHand));} //save previous hand settings
 Serial.println("load EEProm Presets");
 int b = 0; //right
 if(!(batterHand)){
    b = 1000;           //left
    }
    for(int i = 0; i< NUM_PRESETS; i++)
   {
       for(int j = 0; j < NUM_MOTORS ;j++){
         int val = EEPROM.read(b);
         presets[i][j] = val;
         b++;
       }
   }
 pitchSet = map(presets[currentPreset][0],0,100,PITCHMIN,PITCHMAX);  //Update motor setpoints
 yawSet = map(presets[currentPreset][1],0,100,YAWMIN,YAWMAX);
 springSet =map(presets[currentPreset][2],0,100,SPRINGMIN,SPRINGMAX);
 //screen(mess);
}

void savePreset(int side){ // 1 right 0 left
  Serial.println("save preset" );
 int b = 0;
 if(!side){
    b = 1000;
    }
    for(int i = 0; i< NUM_PRESETS; i++){
    
       for( int j = 0; j < NUM_MOTORS ;j++){
        
         int val = presets[i][j];
         EEPROM.write(b, val);
         Serial.println(val);
         b++;
       }
   }
}

void ballReadyCB(int idx, int v, int up){                //called when ballReady microswitch goes HIGH
  if (loadSq.state()==1){
    newBall.trigger(newBall.EVT_OFF);       //turn off newBall signal
    delay(1000);                             //quick delay to give the ball a moment to settle
    ballLift.trigger(ballLift.EVT_ON);      //turn on ball lift signal LOW to run motor
    Serial.println(F("Ball Ready"));        //debug feedback
  }
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
  pitchSet = map(constrain(presets[num][0],0,100),0,100,PITCHMIN,PITCHMAX);
  yawSet = map(constrain(presets[num][1],0,100),0,100,YAWMIN,YAWMAX);
  springSet = map(constrain(presets[num][2],0,100),0,100,SPRINGMIN,SPRINGMAX);
  currentPreset = num;
  screen(2);
  //moving.trigger(moving.EVT_START);
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
    spring(-4096);
    pitchHome.start();
    yawHome.start();
    springHome.start();
    
}

void encoders(){
  if (pitchPos != EncPitch.read()){
    pitchPos = EncPitch.read();
//    Serial.print(F("Pitch Encoder: "));
//    Serial.println(EncPitch.read());  
  }
  if (yawPos != EncYaw.read()){
    yawPos = EncYaw.read();
//    Serial.print(F("Yaw Encoder: "));
//    Serial.println(EncYaw.read());
  }
//  if (springPos != lastSpringPos){
//     lastSpringPos = springPos;
//    Serial.print(F("Spring Encoder: "));
//    Serial.println(springPos);
if (springPos != ((EncSpring.read()/10))){
    springPos = ((EncSpring.read()/10));
    Serial.print(F("Spring Encoder: "));
    Serial.println(((EncSpring.read()/10)));
  }
  
}

int scale(int setPt, int EncPos, int minSpeed){
  
    int error = setPt - EncPos;
    if (error > 20){
      return(4096);
    }
    if ((error <= 20) && (error > 2)){
      return map(error,1,80,minSpeed,4096);
    }
    if (error < -20){
      return(-4096);
    }
    if ((error >= -20) && (error < -2)){
      return map(error,-80,-1,-4096,(-1 * minSpeed));
    }
    else return 0;
}

bool motors(){
  if (pitchEn){
    pitch(scale(pitchSet, EncPitch.read(), 1750));
  }
  if (yawEn){
    yaw(scale(yawSet, EncYaw.read(), 1250));
  }
  if (springEn){
    //spring(scale(springSet, springPos, 1450));
    spring(scale(springSet, ((EncSpring.read()/10)), 1450));
  }
  //if((abs(pitchSet-EncPitch.read())<=1)&&(abs(yawSet-EncYaw.read())<=1)&&(abs(springSet-springPos)<=1)){
  if((abs(pitchSet-EncPitch.read())<=2)&&(abs(yawSet-EncYaw.read())<=2)&&(abs(springSet-((EncSpring.read()/10))<=2))){
    return 1; //at set point
  }
  else{
    return 0; //not at set point
  }
}

void feedback(){
 static bool moving = 0;
 if (moving != atSetPoint){
    moving = atSetPoint;
    if(!atSetPoint){
      Serial.print(F("Moving now...")); 
    }
    else{
      Serial.print(F("Arrived"));
    }
 }
}

void encoderSpring(){
  //byte oldSREG = SREG; //remember if interupts are on or off
  //noInterrupts(); //Turn off interrupts
  if(springDir) {
     springPos++;
  } 
  else {
    springPos--; 
  }
  //SREG = oldSREG; //Turn back on interrupts, if they were off
  //interrupts();
 }

 void nudge(int p, int y, int s){
  presets[currentPreset][0] = constrain(presets[currentPreset][0]+p,0,100);
  presets[currentPreset][1] = constrain(presets[currentPreset][1]+y,0,100);
  presets[currentPreset][2] = constrain(presets[currentPreset][2]+s,0,100);
  pitchSet = map(constrain(presets[currentPreset][0],0,100),0,100,PITCHMIN,PITCHMAX);
  yawSet = map(constrain(presets[currentPreset][1],0,100),0,100,YAWMIN,YAWMAX);
  springSet = map(constrain(presets[currentPreset][2],0,100),0,100,SPRINGMIN,SPRINGMAX); 
 }
 
int whatPitch(){
  if (currentPreset == 0){
    return lastPreset-1;
  }
  else {
    return currentPreset-1;
  }
}

int timeOfFlight(int s){
  return (int)((-5.4*s)+945);
}

