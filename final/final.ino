
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// #include <Servo.h>
//        Servo myservos[2];
const char* ssid = "S20fe";
const char* password = "Sarthak@1009";
const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* topic = "technotron_atomquest_2023"; // Specify your MQTT topic here

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
// void opendrawer1(int no){
  
//   for (int i = 110; i >= 0; i--) {
//     moveServo(no, i);  // Move the second servo
//     delay(15);
//   }
//   delay(1000);
//   for (int i = 0; i <= 110; i++) {
//     moveServo(no, i);  // Move the second servo
//     delay(15);
//   }
//  Serial.println(no);
//  delay(1000);

}
void callback(char* topic, byte* payload, unsigned int length) {
  // Serial.print("Message received on topic: ");
  pinMode(BUILTIN_LED, OUTPUT);
  // Serial.println(topic);
  // Serial.print("Payload: ");
  for (int i = 0; i < length; i++) {
    // Serial.print((char)payload[i]);
  }
  // Serial.println();
  char payloadStr[length + 1];  // Add 1 for the null terminator
  for (int i = 0; i < length; i++) {
    payloadStr[i] = (char)payload[i];
  }
  payloadStr[length] = '\0'; // Null-terminate the string

  // Serial.println(payloadStr);

  // Convert the payload string to an integer
  int value = atoi(payloadStr);

  // Print the integer value
  // Serial.print("Integer Value: ");
  Serial.println(value);
  opendrawer1(value);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(topic); // Subscribe to the specified topic
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  // myservos[0].attach(D2);  
  // myservos[1].attach(D3);
  // myservos[0].write(110);
  // myservos[1].write(110);


}
// void moveServo(int servoNumber, int angle) {
//   if (servoNumber >= 0 && servoNumber < 9) {  // Check if the servoNumber is within the valid range
//     myservos[servoNumber - 1].write(angle);
//   } else {
//     Serial.println("Invalid servo number");
//   }
// }

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
// void setup() {
//   Serial.begin(115200); // Set the baud rate
// }

// void loop() {
//   // Your data to be sent
//   String dataToSend = "Hello, Ardu!";

//   // Send data over serial
//   Serial.println(dataToSend);

//   delay(1000); // Adjust delay as needed
// }
