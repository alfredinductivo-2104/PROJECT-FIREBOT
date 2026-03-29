/* INDUCTIVO, ALFRED AARON M.
    20221121217
    FIREBOT PROJECT ARDUINO NANO CODE (FIREFIGHTING)
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Servo.h>

Servo servo;

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// INPUTS
const int FSR = A0;
const int FSC = A1;
const int FSL = A2;

// OUTPUTS
const int pump = 13;
const int servoPin = 9;
const int GLED = 12;
const int YLED = 11;
const int RLED = 10;
const int Motor1En = 5;
const int Motor2En = 6;

void setup() {
  pinMode(FSR, INPUT);
  pinMode(FSC, INPUT);
  pinMode(FSL, INPUT);
  pinMode(RLED, OUTPUT);
  pinMode(YLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(Motor1En, OUTPUT);
  pinMode(Motor2En, OUTPUT);
  pinMode(pump, OUTPUT);

  servo.attach(servoPin);
  servo.write(90);
  Serial.begin(9600);

  analogWrite(Motor1En, 255);
  analogWrite(Motor2En, 255);
  digitalWrite(pump, HIGH);

  lcd.init();
  lcd.backlight();
  dht.begin();

  lcd.setCursor(4, 0);
  lcd.print("FIREBOT");
  lcd.setCursor(4, 1);
  lcd.print("ENGAGED");
  delay(2000);
  lcd.clear();
}

void loop() {

  int FlameR = analogRead(FSR);
  int FlameC = analogRead(FSC);
  int FlameL = analogRead(FSL);

  //SENSOR TESTING
  Serial.print("Right:");
  Serial.println(FlameR);
  Serial.print("Center:");
  Serial.println(FlameC);
  Serial.print("Left:");
  Serial.println(FlameL);


  if (FlameC < 100) {
    servo.write(90);
    digitalWrite(pump, LOW);
    delay(1500);
  } else if (FlameR < 100) {
    servo.write(30);
    digitalWrite(pump, LOW);
    delay(1500);
  } else if (FlameL < 100) {
    servo.write(150);
    digitalWrite(pump, LOW);
    delay(1500);
  } else {
    servo.write(90);
    digitalWrite(pump, HIGH);
  }

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (!isnan(humidity) && !isnan(temperature)) {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C  ");

    lcd.setCursor(0, 1);
    lcd.print("Hum : ");
    lcd.print(humidity);
    lcd.print(" %  ");

    if (temperature <= 32) {
      digitalWrite(GLED, HIGH);
      digitalWrite(YLED, LOW);
      digitalWrite(RLED, LOW);
    } else if (temperature > 32 && temperature <= 36) {
      digitalWrite(GLED, LOW);
      digitalWrite(YLED, HIGH);
      digitalWrite(RLED, LOW);
    } else if (temperature > 37) {
      digitalWrite(GLED, LOW);
      digitalWrite(YLED, LOW);
      digitalWrite(RLED, HIGH);
    }
  } else {
    Serial.println("Sensor Error");
  }
  delay(1000);
}
