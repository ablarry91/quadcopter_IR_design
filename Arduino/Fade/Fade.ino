/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 */

int led = 10;           // the pin that the LED is attached to
int brightness = 1;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
String inString = "";    // string to hold input

// the setup routine runs once when you press reset:
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  //increase the clock speed to about 30 MHz
  TCCR1B = TCCR1B & B11111000 | B00000001; 

  //
  //  //  /**********************************************************************************/
  //  //// Set pwm clock divider
  //  ///**********************************************************************************/ 
  //  TCCR1B &= ~(1 << CS12);
  //  TCCR1B  |=   (1 << CS11);
  //  TCCR1B &= ~(1 << CS10);  
  //
  //
  //  ///**********************************************************************************/
  //  //// Set pwm resolution  to mode 7 (10 bit)
  //  ///**********************************************************************************/ 
  //  //
  //  TCCR1B &= ~(1 << WGM13);    // Timer B clear bit 4
  //  TCCR1B |=  (1 << WGM12);    // set bit 3
  //
  //  TCCR1A |= (1 << WGM11);    //  Timer A set bit 1
  //  TCCR1A |= (1 << WGM10);    //  set bit 0

  fullCycle();

} 

// the loop routine runs over and over again forever:
void loop()  { 
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {
      delay(3000);
      Serial.print("Value:");
      Serial.println(inString.toInt());
      Serial.print("String: ");
      Serial.println(inString);
      // clear the string for new input:
      changePWM(inString.toInt());
      delay(1000);
      changePWM(0);
      inString = "";
    }
  }
}

void changePWM(int input) {
  analogWrite(led, input);
}

void fullCycle() {
  boolean trigger = false;

  while (1) {
    analogWrite(led,brightness);
    brightness = brightness + fadeAmount;
    Serial.println(brightness); 
    delay(10);   
    if (brightness == 0 & trigger) {
      return;
    }
    if (brightness == 0 || brightness == 150) {
      fadeAmount = -fadeAmount;
      trigger = true;
    }
  }



}




