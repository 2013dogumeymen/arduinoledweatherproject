#include <DHT.h>

// DHT sensör ayarları
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// RGB LED pinleri
#define REDPIN 9
#define GREENPIN 10
#define BLUEPIN 11

// Zamanlama değişkenleri
unsigned long previousMillis = 0;
const long interval = 2000; // 2 saniye aralık

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);

  Serial.println("Hava Durumu Sistemi Başlatıldı!");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Sıcaklık değerlerini oku
    float celsius = dht.readTemperature();
    float fahrenheit = dht.readTemperature(true);
    float kelvin = celsius + 273.15;

    if (isnan(celsius)) {
      Serial.println("DHT sensör verisi alınamadı! Sensörü kontrol edin.");
      setColor(0, 0, 255); // Hata için mavi
    } else {
      Serial.print("Sıcaklık: ");
      Serial.print(celsius);
      Serial.print(" °C, ");
      Serial.print(fahrenheit);
      Serial.print(" °F, ");
      Serial.print(kelvin);
      Serial.println(" K");

      // Sıcaklığa göre LED rengini ve açıklamayı ayarla
      if (celsius <= 15) {
        setColor(0, 0, 255); // Mavi
        Serial.println("LED Renk: Mavi (Soğuk)");
      } else if (celsius > 15 && celsius <= 18) {
        setColor(0, 255, 0); // Yeşil
        Serial.println("LED Renk: Yeşil (Hafif Soğuk)");
      } else if (celsius > 18 && celsius <= 22) {
        setColor(255, 255, 0); // Sarı
        Serial.println("LED Renk: Sarı (Oda Sıcaklığı - Ilık)");
      } else if (celsius > 22 && celsius <= 25) {
        setColor(255, 140, 0); // Turuncu
        Serial.println("LED Renk: Turuncu (Oda Sıcaklığı)");
      } else if (celsius > 25 && celsius <= 30) {
        setColor(255, 0, 0); // Kırmızı
        Serial.println("LED Renk: Kırmızı (Sıcak)");
      } else {
        setColor(128, 0, 128); // Mor
        Serial.println("LED Renk: Mor (Aşırı Sıcak)");
      }
      Serial.println("-------------------------------");
    }
  }
}

// RGB LED için renk ayar fonksiyonu
void setColor(int red, int green, int blue) {
  analogWrite(REDPIN, red);
  analogWrite(GREENPIN, green);
  analogWrite(BLUEPIN, blue);
}
