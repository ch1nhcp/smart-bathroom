#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <DHT.h>

const int DHTPIN = 5;//Chân Out của cảm biến nối chân số 5 Arduino

const int DHTTYPE = DHT11;   // Khai báo kiểu cảm biến là DHT11
//const int DHTTYPE = DHT22;   // DHT 22
//const int DHTTYPE = DHT21;   // DHT 21

DHT dht(DHTPIN, DHTTYPE); //Khai báo thư viện chân cảm biến và kiểu cảm biến

// Vỗ tay bật tắt đèn-------
int soundSensor = 2;
int LED = 4;
boolean LEDStatus = false;
//----------------------------------

// Bật đèn khi trời tối
int cambien = 10;// khai báo chân digital 10 cho cảm biến

int Led = 8;//kháo báo chân digital 8 cho đèn LED
//======================

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
  pinMode(Led, OUTPUT); //pinMode xuất tín hiệu đầu ra cho led
  pinMode(cambien, INPUT); //pinMode nhận tín hiệu đầu vào cho cảm biê
  //--------------------------------------
}

void loop()

{
  // Đo nhiệt độ, độ ẩm ===================
  float doam = dht.readHumidity(); //Đọc độ ẩm

  float doC = dht.readTemperature(); //Đọc nhiệt độ C

  float doF = dht.readTemperature(true); //Đọc nhiệt độ F

  // Kiểm tra cảm biến có hoạt động hay không
  if (isnan(doam) || isnan(doC) || isnan(doF))
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
      Serial.print("Đã bật đèn! ");
    }
    else {
      LEDStatus = false;
      digitalWrite(LED, LOW);
      Serial.print("Đã tắt đèn! ");
    }
  }
  //===========================

  // Bật đèn khi trời tối
  int value = digitalRead(cambien);//lưu giá trị cảm biến vào biến value

  digitalWrite(Led, value); //xuất giá trị ra đèn LED
  //======================================

}
