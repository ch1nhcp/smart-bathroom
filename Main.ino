#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <DHT.h>

const int DHTPIN = 5;//Chân Out của cảm biến nối chân số 5 Arduino
const int DHTTYPE = DHT11;   // Khai báo kiểu cảm biến là DHT11
DHT dht(DHTPIN, DHTTYPE); //Khai báo thư viện chân cảm biến và kiểu cảm biến

// Vỗ tay bật tắt đèn-------
int soundSensor = 7;
int LED = 6;
boolean LEDStatus = false;
//----------------------------------

// Bật đèn khi trời tối
int cambien = 10;// khai báo chân digital 10 cho cảm biến
int LedOutside = 8;//kháo báo chân digital 8 cho đèn LED
//======================

//Đo và cảnh báo mực nước
const int Sensor = A0;
int SensorValue = 0;
int RedLed = 2, YellowLed = 3, Buzzer = 4;
//===============================

//Đo và cảnh báo nhiệt độ nước
//float sinVal;
//int toneVal;
//unsigned long tepTimer ;
//===============================

void setup()
{
  // Đo nhiệt độ, độ ẩm ===================
  Serial.begin(9600);

  dht.begin(); //Khởi động cảm biến

  lcd.init(); //Khởi động LCD
  lcd.backlight(); //Mở đèn
  lcd.setCursor(0, 0);
  lcd.print("DO AM:");
  lcd.setCursor(0, 1);
  lcd.print("NHIET DO:");
  //----------------------------------

  // Vỗ tay bật tắt đèn-------
  pinMode(soundSensor, INPUT);
  pinMode(LED, OUTPUT);
  //----------------------------------

  // Tu dong bat den khi troi toi
  pinMode(LedOutside, OUTPUT); //pinMode xuất tín hiệu đầu ra cho led
  pinMode(cambien, INPUT); //pinMode nhận tín hiệu đầu vào cho cảm biên
  //--------------------------------------

  // Đo và cảnh báo mực nước
  pinMode(RedLed, OUTPUT);
  pinMode(YellowLed, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  //  Serial.begin(9600);
  //===============================

  //Đo và cảnh báo nhiệt độ nước
//  pinMode(6, OUTPUT);
//  Serial.begin(9600);
  //===============================
}

void loop()

{
  // Đo nhiệt độ, độ ẩm ===================
  float doam = dht.readHumidity(); //Đọc độ ẩm

  float doC = dht.readTemperature(); //Đọc nhiệt độ C

  //  float doF = dht.readTemperature(true); //Đọc nhiệt độ F

  // Kiểm tra cảm biến có hoạt động hay không
  if (isnan(doam) || isnan(doC))
  {
    Serial.println("Không có giá trị trả về từ cảm biến DHT");
    return;
  }

  Serial.print("Độ ẩm: ");
  Serial.print(doam);
  lcd.setCursor(7, 0); //con trỏ vị trí số 7, hiện ô số 8
  lcd.print(doam);
  lcd.setCursor(12, 0); //Con trở ở vị trí 12, hiện ô 13
  lcd.print("%");

  Serial.print("%  Nhiệt độ: ");
  Serial.print(doC);
  Serial.println("°C");

  lcd.setCursor(10, 1);
  lcd.print(doC);
  lcd.setCursor(14, 1);
  lcd.print("*C");

  delay(1000);
  //==================================

  // Vỗ tay bật tắt đèn
  int SensorData = digitalRead(soundSensor);
  if (SensorData == 1) {

    if (LEDStatus == false) {
      LEDStatus = true;
      digitalWrite(LED, HIGH);
      delay(200);
      Serial.print("Đã bật đèn! ");
    }
    else {
      LEDStatus = false;
      digitalWrite(LED, LOW);
      delay(200);
      Serial.print("Đã tắt đèn! ");
    }
  }
  //===========================

  // Bật đèn khi trời tối
  int value = digitalRead(cambien);//lưu giá trị cảm biến vào biến value
  digitalWrite(LedOutside, value); //xuất giá trị ra đèn LED
  //======================================


  //Đo và cảnh báo mực nước: đèn đỏ + báo còi nếu mực nước thấp, đèn xanh nếu ok
  SensorValue = analogRead(Sensor);
  Serial.print("Mức nước = ");
  Serial.print(SensorValue);
  Serial.println();
  delay(50);

  if (SensorValue >= 150) {
    digitalWrite(RedLed , LOW);
    digitalWrite(YellowLed , HIGH);
    digitalWrite(Buzzer , LOW);
    delay(50);
  } else
  {
    digitalWrite(RedLed , HIGH);
    digitalWrite(YellowLed , LOW);
    digitalWrite(Buzzer , HIGH);
    delay(50);
  }


  //===============================
  //Đo và cảnh báo nhiệt độ nước
//  int val;
//  double data;
//  val = analogRead(A2);
//  data = (double) val * (5 / 10.24); // convert the voltage to temperture
//
//  if (data > 27) {    // If the temperture is over 27 degree, buzzer will alarm.
//    for (int x = 0; x < 180; x++) {
//      sinVal = (sin(x * (3.1412 / 180)));
//      toneVal = 2000 + (int(sinVal * 1000));
//      tone(6, toneVal);
//      delay(2);
//    }
//  } else {    // If the temperturn is below 27 degree, buzzer will not alarm
//    noTone(6);
//  }
//
//  if (millis() - tepTimer > 500) {   // output the temperture value per 500ms
//    tepTimer = millis();
//    Serial.print("Nhiệt độ nước: ");
//    Serial.print(data);
//    Serial.println("C");
//  }
  //===============================
}
