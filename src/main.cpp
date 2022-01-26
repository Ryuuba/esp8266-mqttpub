#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "NetwData.h"

#define LED_D1 5 // Assign LED_D1 pin i.e: D1 on NodeMCU
// Replace the next variables with your SSID/Password combination

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[10];
int value = 0;
float rndnum = 0.0;

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client"))
      Serial.println("connected");
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // initialize GPIO 5 as an output
  delay(1000);
  Serial.begin(9600);
  pinMode(D5, OUTPUT);
  Serial.printf("Connecting to %s\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.printf("WiFi connected\nIP addres: %s\n", WiFi.localIP().toString().c_str());
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected());
    reconnect();
  client.loop();
  rndnum = random(0, 100);
  sprintf(msg, "%f", rndnum);
  client.publish("main/esp32/rng", msg);
  Serial.printf("rand value: %s\n", msg);
  digitalWrite(D5, HIGH); // turn the LED_D1 on
  delay(1000); // wait for a second
  digitalWrite(D5, LOW); // turn the LED_D1 off
  delay(1000); // wait for a second
}