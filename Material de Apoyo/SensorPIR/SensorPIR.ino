int pirSensor = 2;

void setup() {
  Serial.begin(9600);
  pinMode(pirSensor, INPUT);
}

void loop() {
  int value  = digitalRead(pirSensor); // The PIR sensor will return a 1 if detects movement, 0 othewise
  Serial.println(value);
  delay(250);
}
