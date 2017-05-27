#include <DHT.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Ethernet.h>

const char* ssid = "GrzesioNet";
const char* password = "UBPUKBQB";
IPAddress ip(192, 168, 0, 102);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  HTTPClient http;
  http.begin("http://192.168.0.100:3000/data/temp=" + String(temp, 2) + "&hum=" + String(hum, 2));
  http.GET();
  Serial.println(temp);
  Serial.println(("temp=" + String(temp, 2) + "&hum=" + String(hum, 2)));

  http.end();
  delay(6000);
}
