#include <YunClient.h>
#include <PubSubClient.h>

#define MQTT_SERVER "5.196.95.208"
#define MQTT_CLIENTID "YUN-Sensor"
const int sensorPin = A0;
#include <Bridge.h>
#include <BridgeHttpClient.h>
BridgeHttpClient clientTB;
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
    mqtt.publish("proyectoNTI/aspersor","ConexionSensor");
    mqtt.setCallback(callback);
    //mqtt.subscribe("proyectoNTI/aspersor");
  }
  
while (!SerialUSB); // wait for a serial connection
clientTB.addHeader("Content-Type: application/json");
SerialUSB.println("Finish setup");
}



void loop()
{
  //mqtt.loop();
  int humedad = analogRead(sensorPin);
  clientTB.enableInsecure();
  String s = "{\"humedad\":{\"value\":"+String(humedad)+"}}";
  char buf[s.length()+1];
  s.toCharArray(buf,s.length()+1);
  SerialUSB.println("Envio: "+String(buf));
  clientTB.put("http://207.249.127.101:1026/v2/entities/SensorMaceta/attrs",buf);

  if (humedad > 450)
  {
    col=1;
  }
  else{
    col=3;
  }
  switch (col){
    case 1: 
    mqtt.publish("proyectoNTI/aspersor","v");
    
    break;
    case 2:
    mqtt.publish("proyectoNTI/aspersor","a");
    
    break;
    case 3:
    mqtt.publish("proyectoNTI/aspersor","r");
    
    break;
  }
  delay(5000);
}
