
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
  return;
}



