#include <WiFi.h>

const char* ssid = "S20fe";
const char* password = "Sarthak@1009";

const int ledPin = 2; // Define the pin for the LED

void setup_wifi() {
  Serial.begin(115200);
  delay(10);
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;

    if (attempts > 20) { // Try for 10 seconds
      break;
    }
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("WiFi connection failed. Please check credentials.");
  }
}

void setup() {
  pinMode(ledPin, OUTPUT); // Set the LED pin as an output
  setup_wifi();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // If WiFi is connected, turn on the LED
    digitalWrite(ledPin, HIGH);
  } else {
    // If WiFi is disconnected, turn off the LED
    digitalWrite(ledPin, LOW);
    // Attempt reconnection
    setup_wifi();
  }

  // delay(5000); // Delay before attempting reconnection (5 seconds)
}
