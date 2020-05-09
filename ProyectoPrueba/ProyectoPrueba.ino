#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xB4, 0x21, 0x8A, 0xF0, 0x3A, 0x28 };  //Sustituir YY por número de puesto

IPAddress server(192, 168, 0, 7);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

WiFiClient wifiCl;
PubSubClient client(server, 1883, callback, wifiCl);

void setup()
{
  WiFi.begin(mac);
  Serial.begin(9600);
  // Note - the default maximum packet size is 128 bytes. If the
  // combined length of clientId, username and password exceed this,
  // you will need to increase the value of MQTT_MAX_PACKET_SIZE in
  // PubSubClient.h

  if (client.connect("arduinoClient01", "curso_iot", "raspberry")) {  //Sustituir XX por número de puesto
    client.publish("arduino/led", "hello world");
    client.subscribe("inTopic");
  }
}

void loop()
{
  client.loop();
}
