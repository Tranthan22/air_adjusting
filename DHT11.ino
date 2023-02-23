int fan = 4;

#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const int DHTPIN = 7;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);

byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

void setup() {
  lcd.init();  
  lcd.backlight();
  
  lcd.print("Nhiet do: ");
  lcd.setCursor(0,1);
  lcd.print("Do am: ");
  
  lcd.createChar(1, degree);
  
  pinMode(fan, OUTPUT);
  
  dht.begin();  
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  Serial.print("Nhiet do: ");
  Serial.println(t);
  Serial.print("Do am: ");
  Serial.println(h);               
  
  Serial.println();   
  if (isnan(t) || isnan(h)) {
  } 
  else {
    lcd.setCursor(10,0);
    lcd.print(round(t));
    lcd.print(" ");
    lcd.write(1);
    lcd.print("C");

    lcd.setCursor(10,1);
    lcd.print(round(h));
    lcd.print(" %");    
  }
  delay(1000);
  if(t > 30) 
  {
    digitalWrite(fan,HIGH); //Bật quạt
  }
  if(t > 21 && t <=30)
  {
    digitalWrite(fan,LOW); //Tắt quạt
  } 
  
}
