
const int trigPin = 9;
const int echoPin = 10;
const int redPin = 6;
const int greenPin = 5;
const int potPin = A0;
const int buttonPin = 3;
unsigned long currentTime;
long duration;
float distance;
int potAnalog;
int brightness;
bool check = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); 
}

void loop() {
  potAnalog = analogRead(potPin);
  changeBrightness();
  //Serial.print("Brightness: ");
  //Serial.println(brightness);
  pingDistance();
  checkRisingEdge();
  Serial.print("Distance: ");
  Serial.println(distance / 100);
  Serial.print("Analog: ");
  Serial.println(potAnalog);
  if (currentTime + 10000 > millis()) {
    setLED(1);
  } else {
    setLED(0);
  }
}

void pingDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 3.4 / 2;
}

void changeBrightness() {
  if (potAnalog / 4 > 32) {
    brightness = (potAnalog / 4);
  } 
  if (potAnalog / 4 < 20) {
    brightness = 0;
  }
}

void checkRisingEdge() {
  if (digitalRead(buttonPin) == HIGH) {
    if (check == false) {
      risingEdge();
      check = true;
    }
  }
  if (digitalRead(buttonPin) == LOW) {
    check = false;
  }
}

void risingEdge() {
  currentTime = millis();
}

void setLED(int i) {
  if (i == 1) {
    if (distance < 800) {
      analogWrite(greenPin, brightness);
      analogWrite(redPin, 0);
    } 
    if (distance > 1000) {
      analogWrite(redPin, brightness);
      analogWrite(greenPin, 0);
    }
  }
  if (i == 0) {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
  }
}