#include <YunClient.h>
#include <PubSubClient.h>

#define MQTT_SERVER "5.196.95.208"
#define MQTT_CLIENTID "YUN-Sensor"
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  int i=0;
  for (i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
}

YunClient yun;
PubSubClient mqtt(MQTT_SERVER, 1883, callback, yun);
int col = 1;
void setup()
{
  Serial.begin(9600);
  Bridge.begin();
  if (mqtt.connect(MQTT_CLIENTID)) {
    mqtt.publish("proyectoNTI/aspersor","ConexiónSensor");
    mqtt.setCallback(callback);
    mqtt.subscribe("proyectoNTI/aspersor");
  }
  
}

void loop()
{
  mqtt.loop();
  switch (col){
    case 1: 
    mqtt.publish("proyectoNTI/aspersor","v");
    col=2;
    break;
    case 2:
    mqtt.publish("proyectoNTI/aspersor","a");
    col=3;
    break;
    case 3:
    mqtt.publish("proyectoNTI/aspersor","r");
    col=1;
    break;
  }
  delay(5000);
}
