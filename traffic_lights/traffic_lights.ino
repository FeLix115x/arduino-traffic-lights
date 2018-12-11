/**
   Traffic light project
*/


int carRed = 12; //car red light being assigned
int carYellow = 11;
int carGreen = 10;

int pedRed = 9; //pedestrian red light being assigned
int pedGreen = 8;

int button = 13; // button pin assigned

int crossTime = 5000;
unsigned long carGreenTime; // collects the time since the car green light is on
int minCarGreenTime = 5000; //minimum time cars will have green light ON

int a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6;

// ultrasonic sensor
int trigPin = A0;
int echoPin = A1;

long duration;
int distance;

int speakerPin = A2;  // speaker pin

void setup () {
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
  pinMode(a, OUTPUT); // a
  pinMode(b, OUTPUT); // b
  pinMode(c, OUTPUT); // c
  pinMode(d, OUTPUT); // d
  pinMode(e, OUTPUT);   // e
  pinMode(f, OUTPUT); // f
  pinMode(g, OUTPUT);   // g

  clearDisplay();
  //tone(speakerPin, 262);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  /* check if button is pressed
    and it is over 5 sec since car green light is ON*/
  int state = digitalRead(button);
  if ((state == HIGH || distance < 20) && (millis() - carGreenTime) > minCarGreenTime) {
    changeLights();
  }
}

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

  tone(speakerPin, 262);
  delay(crossTime); //delay preset time of 5 seconds

  noTone(speakerPin);
  for (int i = 5; i >= 0; i--) {
    setSevenSegNumber(i);
    tone(speakerPin, 262);
    delay(1000);
    clearDisplay();
    noTone(speakerPin);
  }

  // flashing of pedestrian green light for 5 seconds in total, i.e. 10 iterations of 0.5 seconds
  for (int x = 0; x < 10; x++) {
    sevseg.refreshDisplay();
    digitalWrite(pedGreen, HIGH);
    delay(250);
    digitalWrite(pedGreen, LOW);
    delay(250);
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

void clearDisplay() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
