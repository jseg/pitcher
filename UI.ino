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
            Serial.println(1);
            }
          break;
        case '3':
          if (Aiming.state()){
            runPreset(3);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(1);
            }
          break;
        case '4':
          if (Aiming.state()){
            runPreset(4);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(1);
            }
          break;
        case '5':
          if (Aiming.state()){
            runPreset(5);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(1);
            }
          break;
        case '6':
          if (Aiming.state()){
            runPreset(6);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(1);
            }
          break;
        case '7':
          if (Aiming.state()){
            runPreset(7);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(1);
            }
          break;
        case '8':
          if (Aiming.state()){
            runPreset(8);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(1);
            }
          break;
        case '9':
          if (Aiming.state()){
            runPreset(9);     //function to move set points to a new preset
            Serial.print(F("Pressed: "));        //feedback
            Serial.println(1);
            }
          break;
        case 'a':
            //newBall.trigger(newBall.EVT_ON);
            break;
        case 'b':
        case 'c': 
        case 'd':       
        case 'e':
        case 'g':
          Aiming.trigger(Aiming.EVT_OFF);
          Main.trigger(Main.EVT_STEP);
          fireSq.trigger(fireSq.EVT_STEP);
          break;
        case 'h': 
        //callback
          break;
        case '#':
          edit = true;
          break;       
        case '*':
          pitchEn = false;
          yawEn = false;
          springEn = false;
          pitch(0);
          yaw(0);
          spring(0);
          //callback
          break;
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
          break;
        case '2':
          break;
        case '3':
          break;
        case '4':
          break;
        case '5':
          break;
        case '6':
          break;
        case '7':
          break;
        case '8':
          break;
        case '9':
          break;
        case 'a':
            //newBall.trigger(newBall.EVT_ON);
            break;
        case 'b':
        case 'c': 
        case 'd':       
        case 'e':
        case 'g':
          Aiming.trigger(Aiming.EVT_OFF);
          Main.trigger(Main.EVT_STEP);
        case 'h': 
        //callback
          break;
        case '#':  
           edit = false;
           break;     
        case '*':
          pitchEn = false;
          yawEn = false;
          springEn = false;
          pitch(0);
          yaw(0);
          spring(0);
          //callback
          break;
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
  }
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
