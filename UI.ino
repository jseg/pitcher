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
        case '0':if (Aiming.state()){
            runPreset(lastPreset);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(9);
            }
          break;
        
        case 'a':flightTime=621;
                 throwSpeed = 60;
                 screen(2);
        break;
        case 'b':flightTime=594;
                 throwSpeed = 65;
                 screen(2);
        break;
        case 'c':flightTime=567;
                 throwSpeed = 70;
                 screen(2);
        break;
        case 'd':flightTime=540;
                 throwSpeed = 75;
                 screen(2);
        break;
        case 'e':flightTime=513;
                 throwSpeed = 80;
                 screen(2);
        break;
        case 'f':flightTime=486;
                 throwSpeed = 85;
                 screen(2);
        break;
        case 'g':flightTime=459;
                 throwSpeed = 90;
                 screen(2);
        break;
        case 'h':flightTime=432;
                 throwSpeed = 95;
                 screen(2);
        break;
        //callback
          break;
        case '#':
          if(Aiming.state()){
            if(currentPreset != 0){
              soundExplode.trigger(soundExplode.EVT_BLINK);
              automaton.delay(3000);
              Aiming.trigger(Aiming.EVT_OFF);  //Finished Aiming
              Main.trigger(Main.EVT_STEP);     //Now Firing
            }
            //else play an "Error" sound
          }
          break;    
        case '*':
          edit = true;
          mess = 3;
          screen(mess);
          break;   
        }
        break;

    case RELEASED:
        break;

    case HOLD:
        if (key == '1' || '2' || '3' || '4' || '5' || '6' || '7' || '8' || '9') {
            
       rethrow = !rethrow;    // Blink the LED when holding the * key.
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
       }
    }
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
            savePreset(digitalRead(HAND));
          break;
        case '#':
          if(Aiming.state()){
            Aiming.trigger(Aiming.EVT_OFF);  //Finished Aiming
            Main.trigger(Main.EVT_STEP);     //Now Firing
          }
          break;    
        case '*':
          edit = false;
          screen(2);
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
  int arg2 = atoi( cmd.arg(2));
  int arg3 = atoi( cmd.arg(3));
  switch ( v ) {
    case CMD_LOAD:
      newBall.trigger(newBall.EVT_ON);  //trigger a new ball to be loaded
      //TODO: add logic to insure that the events cannot run if a ball is already loaded.
      return;
    case CMD_PRESET:
      if (Aiming.state()){      
        runPreset(pin);     //function to move set points to a new preset
        atSetPoint = false;
        keyed = true;
      }
      return;
    case CMD_FIRE:
      throwSpeed = arg3;
      flightTime = timeOfFlight(throwSpeed);
      rethrow = (bool)arg2;
      Serial.print("Rethrow: ");
      Serial.println(rethrow);
      if(pin){
        if(Aiming.state()){
              if(currentPreset != 0 && atSetPoint){
                soundExplode.trigger(soundExplode.EVT_BLINK);
                automaton.delay(3000);
                Aiming.trigger(Aiming.EVT_OFF);  //Finished Aiming
                Main.trigger(Main.EVT_STEP);     //Now Firing
              }
              //else play an "Error" sound
            }
        }
          break;
    case CMD_HAND:
      batterHand = pin;
      loadEEPromPresets(0,0,0);
      break;
    case CMD_EEPROMSETUP:  //Comand to set-up eeprom on a new unit
      loadFactoryPresets()
      break;
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

void screen(int c){
           char message[20];
           lcd.clear();
           delay(25);
           if(rethrow){
            lcd.setCursor ( 19, 3 );
            lcd.print(F("*"));
           }
  switch(c){
    case 0: printEncoders.stop();
            lcd.setCursor ( 0, 0 );
            lcd.print(F("Loading"));
            lcd.setCursor ( 0, 1 );
            lcd.print(F("Ready in a moment..."));
            break;
    case 1: printEncoders.stop();
            lcd.setCursor ( 0, 0 );
            lcd.print(F("Choose a new pitch"));
            lcd.setCursor ( 0, 1 );
            lcd.print(F("or press 0 to repeat"));
            lcd.setCursor ( 0, 2 );
            lcd.print(F("the last pitch."));
            lcd.setCursor ( 0, 3 );
            lcd.print(F("Speed: "));
            lcd.print(throwSpeed);
            lcd.print(F(" MPH"));
            break;
    case 2: printEncoders.stop();
            lcd.clear();
            lcd.setCursor ( 0, 0 );
            lcd.print(F("Press Fire to throw"));
            lcd.setCursor ( 0, 1 );
            if(digitalRead(HAND)){
            strcpy_P(message, (PGM_P)pgm_read_word(&(right_table[whatPitch()])));
            }
            else{
            strcpy_P(message, (PGM_P)pgm_read_word(&(left_table[whatPitch()])));  
            }
            lcd.print(message);
            lcd.setCursor ( 0, 2 );
            lcd.print(F("Speed: "));
            lcd.print(throwSpeed);
            lcd.print(F(" MPH"));
            lcd.setCursor ( 0, 3 );
            lcd.print(F("Press Edit to adjust"));
            break;
    case 3:
            lcd.setCursor ( 0, 0 );
            lcd.print(F("Use arrows to adjust"));
            lcd.setCursor ( 0, 1 );
            lcd.print(F("P: "));
            lcd.print(presets[currentPreset][0]);
            lcd.print(F(" Y: "));
            lcd.print(presets[currentPreset][1]);
            lcd.print(F(" S: "));
            lcd.print(presets[currentPreset][2]);
            lcd.print(F("   "));
            lcd.setCursor ( 0, 2 );
            lcd.print(F("Press Save, then"));
            lcd.setCursor ( 0, 3 );
            lcd.print(F("press Edit to exit."));
            //lcd.print(throwSpeed);
            printEncoders.start();
            break;
    case 4: printEncoders.stop();
            lcd.setCursor ( 0, 0 );
            lcd.print(F("Throwing:"));
            lcd.setCursor ( 0, 1 );
             if(digitalRead(HAND)){
            strcpy_P(message, (PGM_P)pgm_read_word(&(right_table[whatPitch()])));
            }
            else{
            strcpy_P(message, (PGM_P)pgm_read_word(&(left_table[whatPitch()])));  
            }
            lcd.print(message);
            lcd.setCursor ( 0, 2 );
            lcd.print(F("Simulated speed: "));
            lcd.setCursor ( 0, 3 );
            lcd.print(throwSpeed);
            lcd.print(F(" MPH"));
            break;
            
  }
}

void printPos(int idx, int v, int up ){
  lcd.setCursor ( 0, 1 );
            lcd.print(F("P: "));
            lcd.print(map(EncPitch.read(),PITCHMIN,PITCHMAX,0,100));
            lcd.print(F(" Y: "));
            lcd.print(map(EncYaw.read(),YAWMIN,YAWMAX,0,100));
            lcd.print(F(" S: "));
            lcd.print(map((EncSpring.read()/10),SPRINGMIN,SPRINGMAX,0,100));
            lcd.print(F("   "));
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
