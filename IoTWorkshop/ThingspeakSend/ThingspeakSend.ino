#include <ESP8266WiFi.h>
#include <DHT.h>
#include "ThingSpeak.h"

//----------- Enter you Wi-Fi Details---------//
char ssid[] = "Virus#404"; //SSID
char password[] = "password2"; // Password
//-------------------------------------------//

#define DHTPIN D1          //pin where the dht11 is connected
DHT dht(DHTPIN, DHT11);

WiFiClient  client;

unsigned long Channel_ID = 2464797; // Channel ID
const char * WriteAPIKey = "7L3YLFASOD4HGFV0"; // Your write API Key

void setup() {

  Serial.begin(115200);
  dht.begin();
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop() {

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, password);
      Serial.print(".");
      delay(3000);
    }
    Serial.println("\nWiFi Connected.");
  }


  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.print("\nTemperature: ");
  Serial.print(temperature);
  Serial.print("  Humidity: ");
  Serial.println(humidity);

  if (isnan(temperature) || isnan(humidity)) 
  {
      Serial.println("Failed to read from DHT sensor!");
      return;
  }

  ThingSpeak.writeField(Channel_ID, 1, temperature, WriteAPIKey);
  ThingSpeak.writeField(Channel_ID, 2, humidity, WriteAPIKey);
}

