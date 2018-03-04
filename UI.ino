void keypadEvent(KeypadEvent key){
  if(!edit){
    switch (keypad.getState()){
    case PRESSED:
        switch (key){
        case '1':
          if (Aiming.state()){
            runPreset(1);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(1);
            }
          break;
        case '2':
          if (Aiming.state()){
            runPreset(2);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(2);
            }
          break;
        case '3':
          if (Aiming.state()){
            runPreset(3);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(3);
            }
          break;
        case '4':
          if (Aiming.state()){
            runPreset(4);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(4);
            }
          break;
        case '5':
          if (Aiming.state()){
            runPreset(5);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(5);
            }
          break;
        case '6':
          if (Aiming.state()){
            runPreset(6);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(6);
            }
          break;
        case '7':
          if (Aiming.state()){
            runPreset(7);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(7);
            }
          break;
        case '8':
          if (Aiming.state()){
            runPreset(8);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(8);
            }
          break;
        case '9':
          if (Aiming.state()){
            runPreset(9);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(9);
            }
          break;
        case 'a':flightTime=198;
        case 'b':flightTime=171;
        case 'c':flightTime=144; 
        case 'd':flightTime=117;       
        case 'e':flightTime=90;
        case 'f':flightTime=63;
        case 'g':flightTime=36;
        case 'h':flightTime=9;
        //callback
          break;
        case '#':
          if(Aiming.state()){
            Aiming.trigger(Aiming.EVT_OFF);  //Finished Aiming
            Main.trigger(Main.EVT_STEP);     //Now Firing
          }
          break;    
        case '*':
          edit = true;
          break;   
        }
        break;

    case RELEASED:
        break;

    case HOLD:
        break;
    }
  }
  else{
    switch (keypad.getState()){
    case PRESSED:
        switch (key){
        case '1':
            nudge(0,0,2);
            break;
          break;
        case '2':
          nudge(1,0,0);
          break;
        case '3':
          break;
        case '4':
          nudge(0,-1,0);
          break;
        case '5':
          break;
        case '6':
          nudge(0,1,0);
          break;
        case '7':
          break;
        case '8':
          nudge(-1,0,0);
          break;
        case '9':
          nudge(0,0,-2);
          break;
        case 'a':
        case 'b':
        case 'c': 
        case 'd':       
        case 'e':
            break;
        case 'f': loadDefaultPresets();
            break;
        case 'g':
          break;
        case 'h': 
            savePreset();
          break;
        case '#':
          if(Aiming.state()){
            Aiming.trigger(Aiming.EVT_OFF);  //Finished Aiming
            Main.trigger(Main.EVT_STEP);     //Now Firing
          }
          break;    
        case '*':
          edit = true;
          break;         
        }
        break;

    case RELEASED:
        break;

    case HOLD:
        break;
    }
  }
}



void cmd_callback( int idx, int v, int up ) {
  int pin = atoi( cmd.arg( 1 ) );
  switch ( v ) {
    case CMD_HIGH: 
      digitalWrite( pin, HIGH );
      return;
    case CMD_LOW:
      digitalWrite( pin, LOW );
      return;
    case CMD_READ:
      Serial.println( digitalRead( pin ) );
      return;
    case CMD_AREAD:
      Serial.println( analogRead( pin ) );
      return;
    case CMD_AWRITE:
      analogWrite( pin, atoi( cmd.arg( 2 ) ) );
      return;
    case CMD_MODE_INPUT:
      pinMode( pin, INPUT );
      return;
    case CMD_MODE_OUTPUT:
      pinMode( pin, OUTPUT );
      return;
    case CMD_MODE_PULLUP:
      pinMode( pin, INPUT_PULLUP );
      return;
    case CMD_LOAD:
      newBall.trigger(newBall.EVT_ON);  //trigger a new ball to be loaded
      //TODO: add logic to insure that the events cannot run if a ball is already loaded.
      return;
    case CMD_NUMKEY:      
      runPreset(pin);     //function to move set points to a new preset
      return;
    case CMD_EEPROMSETUP:  //Comand to set-up eeprom on a new unit
      loadDefaultPresets();
      savePreset();
    case CMD_PITCH:
      pitch(pin);
      Serial.print(F("Pitch: "));
      Serial.println(pin);
      return;
    case CMD_YAW:
      yaw(pin);
      Serial.print(F("Yaw: "));
      Serial.println(pin);
      return;
    case CMD_SPRING:
      spring(pin);
      Serial.print(F("Spring: "));
      Serial.println(pin);
      return;
    case CMD_HOME:
      runHome();
      return;
    case CMD_PID:
      if (pin == 1){
        pitchEn = true;         //turn on motor control
        yawEn = true;           //
        springEn = true;
        Serial.println(F("Motor Control On"));
      }
      else{
        pitchEn = false;         //turn on motor control
        yawEn = false;           //
        springEn = false;
        Serial.println(F("Motor Control Off"));
      }
     return;
    case CMD_MOVE:
      pitchSet = pin;
      yawSet = atoi(cmd.arg(2));
      springSet = atoi(cmd.arg(3));
      Serial.print(F("Pitch Setpoint: "));
      Serial.println(pin);
      Serial.print(F("Yaw Setpoint: "));
      Serial.println(atoi(cmd.arg(2)));
      Serial.print(F("Sprint Setpoint: "));
      Serial.println(atoi(cmd.arg(3)));
      return;
    case CMD_STATE:
      printStates();
      return;
    case CMD_SERIAL:
      printEncoders.start();
      return;
  }
}

void printPos(int idx, int v, int up ){
  static bool refresh = true; 
  static int lastStep = 0;
  static int lastPreset = 0;
  static bool lastEdit = false;
  if(Main.state()!=lastStep){    //Detect if the state has changed
    lastStep=Main.state();
    refresh = true;  
  }
  if(edit!=lastEdit){        //Check if edit mode has changed
    lastEdit = edit;
    refresh = true;
  }
  if(currentPreset!=lastPreset){  //Check if the preset has changed
    lastPreset = currentPreset;
    refresh = true;
  }
  
if(refresh){
  lcd.clear();
  if(Loading.state()){
      lcd.setCursor ( 0, 0 );
      lcd.print(F("Loading"));
  }
  else if(Aiming.state()){
    if(edit){
        lcd.setCursor ( 0, 0 );
        lcd.print(F("Edit Preset: "));
        lcd.print(currentPreset);
    }
    else{
      lcd.print(F("Aim to Preset: "));
      lcd.print(currentPreset);
    }
  }
  else if(Firing.state()){
    lcd.print(F("Firing"));
  }
  lcd.setCursor ( 0, 1 );  
  lcd.print(F("Pitch Encoder: "));
  lcd.setCursor ( 0, 2 );  
  lcd.print(F("Yaw Encoder: "));
  lcd.setCursor ( 0, 3 );  
  lcd.print(F("Spring Encoder: "));
  refresh = false;
}
    lcd.setCursor ( 17, 1 );
    lcd.print("   ");
     lcd.setCursor ( 17, 1 ); 
    lcd.print(EncPitch.read());
    lcd.setCursor ( 17, 2 );
    lcd.print("   ");
     lcd.setCursor ( 17, 2 );
    lcd.print(EncYaw.read());
    lcd.setCursor ( 17, 3 );
    lcd.print("   ");
     lcd.setCursor ( 17, 3 ); 
    lcd.print(springPos);
}

void help(){
  Serial.println(F("Recognized commands:"));
  Serial.println(F("high pin         *set a pin to HIGH"));
  Serial.println(F("low pin          *set a pin to LOW"));
  Serial.println(F("read pin         *read the current state of a pin"));
  Serial.println(F("aread pin        *read an analog pin"));
  Serial.println(F("awrite pin       *write an analog value to a pin"));
  Serial.println(F("mode_input pin   *set a pin to input mode"));
  Serial.println(F("mode_output pin  *set a pin to output mode"));
  Serial.println(F("mode_pullup pin  *turn on an internal pullup"));
  Serial.println(F("load             *load a ball in the launcher"));
  Serial.println(F("num_key num      *simulate a number key"));
  Serial.println(F("pitch num        *run pitch motor at speed num"));
  Serial.println(F("yaw num          *run yaw motor at speed num"));
  Serial.println(F("spring num       *run spring motor at speed num"));
  Serial.println(F("home             *run run all motors home"));
  Serial.println(F("pid bool         *enable (1) or disable (0) position control"));
  Serial.println(F("move num num num *run to position num num num"));
  
}

void printStates(){
     Serial.println(F("*****************"));
     Serial.print(F("Loading state: "));
     Serial.println(Loading.state());
     Serial.print(F("Aiming state: "));
     Serial.println(Aiming.state());
     Serial.print(F("Firing state: "));
     Serial.println(Firing.state());
     Serial.print(F("Main state: "));
     Serial.println(Main.state());
     Serial.print(F("loadSq state: "));
     Serial.println(loadSq.state());
     Serial.print(F("fireSq state: "));
     Serial.println(fireSq.state());
     Serial.println(F("*****************"));
}
