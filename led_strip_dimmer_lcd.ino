#include <LCD_I2C.h>

#define adcPin A0
#define pwmPin 3

// Change the address according with the device in use
LCD_I2C lcd(0x3f);

// Custom haracters definition (rectangles used for progress bar)
uint8_t full[8] =
{
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
};

uint8_t empty[8] =
{
    0b11111,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b11111,
};

int adcValue = 0;
int pwmValue = 0;
int i=0;

void setup() {
  // Set mosfet control pin as output
  pinMode(pwmPin, OUTPUT);
  analogWrite(pwmPin, 0);

  // Initialize display
  lcd.begin();

  // Create custom chars
  lcd.createChar(0, full);
  lcd.createChar(1, empty);
  
  lcd.backlight();
  lcd.print(" PWM Led Dimmer");
  
  Serial.begin(115200);
  
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   LUMINOSITA'");
}

void loop() {
  // Read analog value from potentiometer
  adcValue = analogRead(adcPin);

  // Truncate value to 8 bit
  pwmValue = adcValue >> 2;

  // Set pwm output
  analogWrite(pwmPin, pwmValue);

  // Display pwm value
  printBar(pwmValue);
  
  if(i++ == 10){
    Serial.print(adcValue);
    Serial.print(" ---> ");
    Serial.println(pwmValue);
    i = 0;
  }

  delay(50);
}

void printBar(int value){
  int i=0, j=16;
  lcd.setCursor(0, 1);
  unsigned char b=(value+1)/16;
  while(b > i){
    lcd.write(0);
    i++;
    j--;
  }
  while(j > 0){
    lcd.write(1);
    j--;
  }
}
