/**
 * Traffic lights project for Arduino
 */
const int carRed = 12; //car red light being assigned
const int carYellow = 11;
const int carGreen = 10;

const int pedRed = 9; //pedestrian red light being assigned
const int pedGreen = 8;

const int button = 13; // button pin assigned

const int crossTime = 5000;
unsigned long carGreenTime; // collects the time since the car green light is on
int minCarGreenTime = 5000; //minimum time cars will have green light ON

const int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6;  // defining 7-sgement pin variables

// ultrasonic sensor
const int trigPin = A0;
const int echoPin = A1;

long duration;
int distance;

const int speakerPin = A2;  // speaker pin

void setup () {
  // traffic lights setup
  pinMode(carRed, OUTPUT); // declare LED pins to be an output
  pinMode(carYellow, OUTPUT);
  pinMode(carGreen, OUTPUT);
  pinMode(pedRed, OUTPUT);
  pinMode(pedGreen, OUTPUT);
  pinMode(button, INPUT); // declare button pin to be an input
  digitalWrite(carGreen, HIGH); //start with green car light on
  digitalWrite(pedRed, HIGH); //start with red ped light on

  // Ultrasonic sensor setup
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // 7 segment manual setup
  pinMode(a, OUTPUT); 
  pinMode(b, OUTPUT); 
  pinMode(c, OUTPUT); 
  pinMode(d, OUTPUT); 
  pinMode(e, OUTPUT);  
  pinMode(f, OUTPUT); 
  pinMode(g, OUTPUT);  
  clearDisplay(); // set all segments to LOW
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH); // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  
  distance = duration * 0.034 / 2; // Calculates the distance
  
  /* check if button is pressed or distance is small enough (<20 units)
    and it is over 5 sec since car green light is ON*/
  int state = digitalRead(button);
  if ((state == HIGH || distance < 20) && (millis() - carGreenTime) > minCarGreenTime) {
    changeLights();
  }
}

/**
 * Is triggered every time a button is pressed or distance to the sensor is less than 20 units
 */
void changeLights() {
  clearDisplay();
  delay(2000);
  digitalWrite(carGreen, LOW);

  digitalWrite(carYellow, HIGH);
  delay(2000);
  digitalWrite(carYellow, LOW);
  digitalWrite(carRed, HIGH);
  delay(1000);
  digitalWrite(pedRed, LOW);
  digitalWrite(pedGreen, HIGH);

  tone(speakerPin, 262);  // sound signal
  delay(crossTime); //delay preset time of 5 seconds
  
  noTone(speakerPin);
  
  // flashing of pedestrian green light for 5 seconds in total
  for (int i = 5; i >= 0; i--) {
    setSevenSegNumber(i);
    tone(speakerPin, 262);
    digitalWrite(pedGreen, HIGH);
    delay(500);
    clearDisplay();
    noTone(speakerPin);
    digitalWrite(pedGreen, LOW);
    delay(500);
  }
  

  digitalWrite(pedRed, HIGH);
  delay(100);
  digitalWrite(carYellow, HIGH);
  delay(2000);
  digitalWrite(carRed, LOW);
  digitalWrite(carYellow, LOW);
  digitalWrite(carGreen, HIGH);

  carGreenTime = millis(); //record time since car green lights are on
}

/**
 * Manually switches on pins of a single 7-segment display
 * between 0 and 5
 */
void setSevenSegNumber(int n) {
  switch (n) {
    case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      break;
    case 1:
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      break;
    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      break;
    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      break;
    case 4:
      digitalWrite(f, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(c, HIGH);
      break;
    case 5:
      digitalWrite(a, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      break;
    default:
      clearDisplay();	// clears all pins by default
      break;
  }
}

/**
 * Resets the 7-segment display
 */
void clearDisplay() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
