/*

*/

#define adcPin A0
#define pwmPin 3

int adcValue = 0;
int pwmValue = 0;

int i = 0;

void setup() {
  Serial.begin(115200);
  pinMode(pwmPin, OUTPUT);
}

void loop() {
  adcValue = analogRead(adcPin);
  pwmValue = adcValue >> 2;
  analogWrite(pwmPin, pwmValue);

  if(i++ == 10){
    Serial.print(adcValue);
    Serial.print(" ---> ");
    Serial.println(pwmValue);
    i = 0;
  }

  delay(50);
}
