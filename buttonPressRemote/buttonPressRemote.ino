
int inPin = 7;  // the pin number for input (for me a push button)
int onPinA = 8; // Pin for controlling the remote
int offPinA = 9;
int ledPin = 13; 

int current;         // Current state of the button
                     // (LOW is pressed b/c i'm using the pullup resistors)
long millis_held;    // How long the button was held (milliseconds)
long secs_held;      // How long the button was held (seconds)
long prev_secs_held; // How long the button was held in the previous check
byte previous = HIGH;
unsigned long firstTime; // how long since the button was first pressed 

void setup() {
  Serial.begin(9600);         // Use serial for debugging
  
  pinMode(ledPin, OUTPUT);
  pinMode(onPinA, OUTPUT);
  pinMode(offPinA, OUTPUT);

  
  digitalWrite(onPinA, HIGH);  // 
  digitalWrite(offPinA, LOW);  // Transistor should be low
  digitalWrite(inPin, HIGH);  // 
}

void loop() {
  current = digitalRead(inPin);

  // if the button state changes to pressed, remember the start time 
  if (current == LOW && previous == HIGH && (millis() - firstTime) > 200) {
    firstTime = millis();
  }

  millis_held = (millis() - firstTime);
  secs_held = millis_held / 1000;

  // This if statement is a basic debouncing tool, the button must be pushed for at least
  // 100 milliseconds in a row for it to be considered as a push.
  if (millis_held > 50) {

    if (current == LOW && secs_held > prev_secs_held) {
      ledblink(1, 50, ledPin); // Each second the button is held blink the indicator led
    }

    // check if the button was released since we last checked
    if (current == HIGH && previous == LOW) {
      // HERE YOU WOULD ADD VARIOUS ACTIONS AND TIMES FOR YOUR OWN CODE
      // ===============================================================================

      // Button pressed for less than 6 seconds, turn on.
      if (secs_held < 6) {
        Serial.print("Short Press: ");
        Serial.print(secs_held);
        Serial.print("   Milliseconds held: ");
        Serial.println(millis_held);
        //Turn on sockets
        turnSocketsOn();
      }

      // Button held for more than 6 seconds, turn off.
      if (secs_held >= 6) {
        Serial.print("Long Press: ");
        Serial.print(secs_held);
        Serial.print("   Milliseconds held: ");
        Serial.println(millis_held);
        //Turn off sockets
        turnSocketsOff();
      }
      // ===============================================================================
    }
  }

  previous = current;
  prev_secs_held = secs_held;
}

// Just a simple helper function to blink an led in various patterns
void ledblink(int times, int lengthms, int pinnum){
  for (int x=0; x<times;x++) {
    digitalWrite(pinnum, HIGH);
    delay (lengthms);
    digitalWrite(pinnum, LOW);
    delay(lengthms);
  }
}

//Function to send a radio signal to turn sockets on
void turnSocketsOn() {
  // For RPi parsing
  Serial.println("status : 1");
  //  delay
  delay(2000);
  Serial.println("Turning sockets on: ");
  //  turn on 3 times
  digitalWrite(onPinA, LOW);
  delay(1000);
  digitalWrite(onPinA, HIGH);
  delay(1000);
  
  digitalWrite(onPinA, LOW);
  delay(1000);
  digitalWrite(onPinA, HIGH);
  delay(1000);
  
  digitalWrite(onPinA, LOW);
  delay(1000);
  digitalWrite(onPinA, HIGH);
  Serial.println("Sockets on complete.");
  // Send ON signal to PI 
}
//Function to send a radio signal to turn sockets off
void turnSocketsOff() {
  // For RPi parsing
  Serial.println("status : 0");
  Serial.println("Turning sockets off: ");
  // turn off 3 times
  digitalWrite(offPinA, HIGH);
  delay(1000);
  digitalWrite(offPinA, LOW);
  delay(1000);

  digitalWrite(offPinA, HIGH);
  delay(1000);
  digitalWrite(offPinA, LOW);
  delay(1000);

  digitalWrite(offPinA, HIGH);
  delay(1000);
  digitalWrite(offPinA, LOW);
  
  Serial.println("Sockets off complete. ");
  // Send OFF signal to PI
}
