int latchPin = 4; // D2 seg
int clockPin = 5; // D1 seg
int dataPin = 16; // D0 seg
unsigned int u2 = 0, u4 = 0, u6 = 0, u81 = 0; // 81 is the 8x8 chip, do not change!!!!!!!! seg
const int ledPin = 0; // D3  Pin connected to the LED for blinking
unsigned long previousMillis = 0;  // Variable to store previous value of millis() for blinking
const long interval = 1000;  // Interval between blinks in milliseconds
int go[10] = {
  0b01111110, //0
  0b00001100, //1
  0b10110110, //2
  0b10011110, //3
  0b11001100, //4
  0b11011010, //5
  0b11111010, //6
  0b00001110, //7
  0b11111110, //8
  0b11011110  //9
};

#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define WIFI_SSID "wifi name" // EC co. Workshop
#define WIFI_PASS "password"  // 12344321

const long utcOffsetInSeconds = 7200;
uint32_t pes_patron;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ua.pool.ntp.org", utcOffsetInSeconds);

void setup()
{
  pinMode(latchPin, OUTPUT); // seg
  pinMode(clockPin, OUTPUT); // seg
  pinMode(dataPin, OUTPUT);  // seg
  pinMode(ledPin, OUTPUT);   // blink
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(';');
    digitalWrite(latchPin, LOW); // Start of transmission
    shiftOut(dataPin, clockPin, MSBFIRST, 0b01110000); // L
    shiftOut(dataPin, clockPin, MSBFIRST, 0b01111110); // 0
    shiftOut(dataPin, clockPin, MSBFIRST, 0b11101110); // A
    shiftOut(dataPin, clockPin, MSBFIRST, 0b10111100); // d
    digitalWrite(latchPin, HIGH); // End of transmission
  }

  Serial.println("Connected");
  timeClient.begin();
  timeClient.update();
}

void loop()
{
  if (digitalRead(13) == 0) {
    timeClient.setTimeOffset(10800);
  } else {
    timeClient.setTimeOffset(7200);
  }

  if (millis() - pes_patron >= 3600000) {
    pes_patron = millis();
    timeClient.update();
  }

  Serial.print(timeClient.getHours());
  Serial.print(':');
  Serial.print(timeClient.getMinutes());
  Serial.print(';');

  min(timeClient.getMinutes());
  hours(timeClient.getHours());

  digitalWrite(latchPin, LOW); // Start of transmission
  shiftOut(dataPin, clockPin, MSBFIRST, go[u81]); // U8
  shiftOut(dataPin, clockPin, MSBFIRST, go[u6]);  // U6
  shiftOut(dataPin, clockPin, MSBFIRST, go[u4]);  // U4
  shiftOut(dataPin, clockPin, MSBFIRST, go[u2]);  // U2
  digitalWrite(latchPin, HIGH); // End of transmission

  blinkLED();  // Call function to blink LED
}

void min(unsigned int razbivka_chislam) { // Function to split minute value
  u4 = razbivka_chislam % 100 / 10; // tens
  u2 = razbivka_chislam % 10;       // units
}

void hours(unsigned int razbivka_chislah) { // Function to split hour value
  u81 = razbivka_chislah % 100 / 10; // tens
  u6 = razbivka_chislah % 10;        // units
}

void blinkLED() {
  unsigned long currentMillis = millis();  // Get current millis()
  if (currentMillis - previousMillis >= interval) { // Check if it's time to blink again
    previousMillis = currentMillis; // Save the new time
    if (digitalRead(ledPin) == HIGH) { // Toggle LED state
      digitalWrite(ledPin, LOW);
    } else {
      digitalWrite(ledPin, HIGH);
    }
  }
}
