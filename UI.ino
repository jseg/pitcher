void keypadEvent(KeypadEvent key){
    switch (keypad.getState()){
    case PRESSED:
        switch (key){
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
           runPreset(atoi( cmd.arg(key) ));     //function to move set points to a new preset
           Serial.print(F("Pressed: "));        //feedback
           Serial.println(key);
          break;
        case 'a':
            newBall.trigger(newBall.EVT_ON);
            break;
        case 'b':
        case 'c': 
        case 'd':       
        case 'e':
        case 'g':
        case 'h': 
        //callback
          break;
        case '#':       
        case '*':
          //callback
          break;
        break;
        
          
        }
        break;

    case RELEASED:
//        if (key == '*') {
//            digitalWrite(ledPin,ledPin_state);    // Restore LED state from before it started blinking.
//            blink = false;
//        }
        break;

    case HOLD:
//        if (key == '*') {
//            blink = true;    // Blink the LED when holding the * key.
//        }
        break;
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
      return;
  }
}

void help(){
  Serial.println(F("Recognized commands:"));
  Serial.println(F("high pin        *set a pin to HIGH"));
  Serial.println(F("low pin         *set a pin to LOW"));
  Serial.println(F("read pin        *read the current state of a pin"));
  Serial.println(F("aread pin       *read an analog pin"));
  Serial.println(F("awrite pin      *write an analog value to a pin"));
  Serial.println(F("mode_input pin  *set a pin to input mode"));
  Serial.println(F("mode_output pin *set a pin to output mode"));
  Serial.println(F("mode_pullup pin *turn on an internal pullup"));
  Serial.println(F("load            *load a ball in the launcher"));
  Serial.println(F("num_key num     *simulate a number key"));
  Serial.println(F("eepromSetup     *setup a new eeprom"));
}
