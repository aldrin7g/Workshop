#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>
#include <DHT.h>  // Including library for dht

//----------- Enter you Wi-Fi Details---------//
char ssid[] = "Virus#404"; //SSID
char pass[] = "password1"; // Password
//-------------------------------------------//

#define REFERENCE_URL "iot-workshop-73bb8-default-rtdb.firebaseio.com"  // Your Firebase project reference url

Firebase firebase(REFERENCE_URL);

#define BUTTON_PIN  5 // Change this to the pin you connect the button to
#define LED_PIN     4 // Change this to the pin you connect the LED to

#define DHTPIN 0          //pin where the dht11 is connected
DHT dht(DHTPIN, DHT11);

int buttonState = LOW;
int lastButtonState = LOW;
bool ledState = LOW;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.mode(WIFI_STA);
  delay(1000);
}

void WiFiConnect(){
if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
}

void DHT_Sensor(){
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.print("\nTemperature: ");
  Serial.print(temperature);
  firebase.setInt("/IoT_Workshop/Temperature", temperature);
  Serial.print(" Humidity: ");
  Serial.println(humidity);
  firebase.setInt("/IoT_Workshop/Humidity", humidity);

  if (isnan(temperature) || isnan(humidity)) 
  {
      Serial.println("Failed to read from DHT sensor!");
      return;
  }
  delay(1000);
}

void Button(){
int CurrentButtonState = digitalRead(BUTTON_PIN);

  if (CurrentButtonState != lastButtonState) {
    if (CurrentButtonState == HIGH) {
      ledState = !ledState;
      firebase.setInt("/IoT_Workshop/Button", ledState);
      int data = firebase.getInt("IoT_Workshop/setInt");
      Serial.print("Received Button State: ");
      Serial.println(data);
    }
    delay(50); // Debounce delay
  }

  lastButtonState = CurrentButtonState;
}

void loop() {

WiFiConnect();
DHT_Sensor();
Button();
}
