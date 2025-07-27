#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>

//----------- Enter you Wi-Fi Details---------//
char ssid[] = "Virus#404"; //SSID
char pass[] = "password1"; // Password
//-------------------------------------------//

#define REFERENCE_URL "iot-workshop-73bb8-default-rtdb.firebaseio.com"  // Your Firebase project reference url

Firebase firebase(REFERENCE_URL);

#define BUTTON_PIN  5 // Change this to the pin you connect the button to
#define LED_PIN     4 // Change this to the pin you connect the LED to

int buttonState = LOW;
int lastButtonState = LOW;
bool ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  delay(1000);
}

void loop() {

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

  int CurrentButtonState = digitalRead(BUTTON_PIN);

  if (CurrentButtonState != lastButtonState) {
    if (CurrentButtonState == HIGH) {
      ledState = !ledState;
      firebase.setInt("/Example/setInt", ledState);
      int data = firebase.getInt("Example/setInt");
      Serial.print("Received Button State: ");
      Serial.println(data);
    }
    delay(50); // Debounce delay
  }

  lastButtonState = CurrentButtonState;
}
