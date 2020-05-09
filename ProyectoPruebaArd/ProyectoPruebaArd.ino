#include <YunClient.h>
#include <PubSubClient.h>

#define MQTT_SERVER "5.196.95.208"
#define MQTT_CLIENTID "YUN-Sensor"
const int LROJO = 8;
const int LAMARILLO = 6;
const int LVERDE = 5;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  int i=0;
  for (i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  char ca = (char)payload[0];
  Serial.println();
  switch(ca){ // Por supuesto, aquí se utilizaría switch
  case 'a':
    digitalWrite(LAMARILLO,HIGH);
    digitalWrite(LVERDE,LOW);
    digitalWrite(LROJO,LOW);
    Serial.println("Se recibió una a");
  break;
  case 'v':
    digitalWrite(LAMARILLO,LOW);
    digitalWrite(LVERDE,HIGH);
    digitalWrite(LROJO,LOW);
    Serial.println("Se recibió una v");
  break;
  case 'r':
    digitalWrite(LAMARILLO,LOW);
    digitalWrite(LVERDE,LOW);
    digitalWrite(LROJO,HIGH);
    Serial.println("Se recibió una r");
  break;
  case 'b':
    digitalWrite(LAMARILLO,LOW);
    digitalWrite(LVERDE,LOW);
    digitalWrite(LROJO,LOW);
    Serial1.println("Se recibió una b");
  break;
}
}

YunClient yun;
PubSubClient mqtt(MQTT_SERVER, 1883, callback, yun);

void setup()
{
  Serial.begin(9600);
  Bridge.begin();
  if (mqtt.connect(MQTT_CLIENTID)) {
    mqtt.publish("arduino/led","Quibo");
    mqtt.setCallback(callback);
    mqtt.subscribe("arduino/led");
  }
  pinMode(LROJO, OUTPUT);
  pinMode(LAMARILLO, OUTPUT);
  pinMode(LVERDE, OUTPUT);
}

void loop()
{
  mqtt.loop();
}
