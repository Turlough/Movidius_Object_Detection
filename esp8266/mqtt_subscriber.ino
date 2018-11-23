
/**
 * Standard mosquitto client implementation.
 * Run this on an ESP8266.
 * Connect the Tx pin to the Rx pin of the Arduino.
 * Commands received via MQTT are relayed 
 * to the Arduino over the serial connection.
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//edit the following for your wifi network and mqtt broker
#define wifi_ssid "oort"
#define wifi_password "0lympusM@ns"

#define mqtt_server "iot.eclipse.org"
#define mqtt_port 1883
#define mqtt_user "miele"
#define mqtt_password "password"

#define in_topic "/home/miele"

WiFiClient espClient;
PubSubClient client;

void setup() {
  //The ESP6266 can communicate at 115200 baud
  //but we need to communicate with the Arduino at 9600 baud
  Serial.begin(9600);
  digitalWrite(BUILTIN_LED, LOW);
  setup_wifi();
  client.setClient(espClient);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  digitalWrite(BUILTIN_LED, HIGH);
}

void setup_wifi() {
  pinMode(LED_BUILTIN, OUTPUT);
  delay(10);

  Serial.println(wifi_ssid);
  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

  }


  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      client.subscribe(in_topic);
      digitalWrite(BUILTIN_LED, HIGH);
    } else {
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {

 digitalWrite(BUILTIN_LED, LOW);
 for (int i = 0; i < length; i++) {
  char receivedChar = (char)payload[i];

  //The received character acts as a command
  Serial.println(receivedChar);
  
 }
 delay(100);
 digitalWrite(BUILTIN_LED, HIGH);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(50);
}
