#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3KudTKDf4"
#define BLYNK_TEMPLATE_NAME "IoTWorkshop"
#define BLYNK_AUTH_TOKEN "flRMtyCHLcoYJhQwiIB9qVMGl-PkVNF-"
#include <BlynkSimpleEsp32.h>

//----------- Enter you Wi-Fi Details---------//
char ssid[] = "Wokwi-GUEST"; //SSID
char password[] = ""; // Password
//-------------------------------------------//

// Define the pins for the ultrasonic sensor
const int trigPin = D1;
const int echoPin = D2;
int distance_cm = 0;

BlynkTimer timer;

void sendSensor(){
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V3, distance_cm);
}

void measure_distance(){
  // Send a pulse to the trigger pin to start the measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse from the echo pin
  long duration = pulseIn(echoPin, HIGH);

  // Convert the duration into distance in centimeters
  distance_cm = duration * 0.034 / 2;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // Wait for a short time before taking the next measurement
  delay(1000);
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run(); // Initiates BlynkTimer 

  measure_distance();

}
