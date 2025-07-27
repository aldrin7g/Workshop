#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL35SJ7I046"
#define BLYNK_TEMPLATE_NAME "Demo"
#define BLYNK_AUTH_TOKEN "VLMki0D6J0GpXc9VyDTsjys4V6U_I9_A"
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

//----------- Enter you Wi-Fi Details---------//
char ssid[] = "Virus#404"; //SSID
char password[] = "password2"; // Password
//-------------------------------------------//

#define DHTPIN D1          //pin where the dht11 is connected
#define LED_PIN 2

DHT dht(DHTPIN, DHT11);
float temperature, humidity;
int value = 0;
BlynkTimer timer;

BLYNK_WRITE(V2)
{
  value = param.asInt(); // assigning incoming value from pin V1 to a variable
}

void sendSensor(){
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  Serial.print("\nTemperature: ");
  Serial.print(temperature);
  Serial.print(" Humidity: ");
  Serial.println(humidity);

  if (isnan(temperature) || isnan(humidity)) 
  {
      Serial.println("Failed to read from DHT sensor!");
      return;
  }
  
  if (value == 1)
    digitalWrite(LED_PIN, HIGH);
  else
    digitalWrite(LED_PIN, LOW);
}