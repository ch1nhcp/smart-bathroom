#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <DHT.h>

const int DHTPIN = 5;//Chân Out của cảm biến nối chân số 5 Arduino

const int DHTTYPE = DHT11;   // Khai báo kiểu cảm biến là DHT11
//const int DHTTYPE = DHT22;   // DHT 22
//const int DHTTYPE = DHT21;   // DHT 21

DHT dht(DHTPIN, DHTTYPE); //Khai báo thư viện chân cảm biến và kiểu cảm biến

void setup()
{
  Serial.begin(9600);

  dht.begin(); //Khởi động cảm biến

  lcd.init(); //Khởi động LCD
  lcd.backlight(); //Mở đèn
  lcd.setCursor(0, 0);
  lcd.print("DO AM:");
  lcd.setCursor(0, 1);
  lcd.print("NHIET DO:");
}

void loop()

// Đo nhiệt độ, độ ẩm
{
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
}
