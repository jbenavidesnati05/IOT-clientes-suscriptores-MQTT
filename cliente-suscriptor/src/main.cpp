#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "Comunidad IoT";
const char* pass = "Sistecredito2023*";
const int led_d0 = 16;
const int led_d1 = 4;
const int led_d2 = 2;
const int led_d3 = 12;
const char* mqtt_server = "192.168.0.101";
//initializes the espclient
WiFiClient espClient;
PubSubClient client(espClient);
void callback(String topic, byte* message, unsigned int length){
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  if (topic == "LED/1")
  {
    Serial.print("Led Daniel ");
    if (messageTemp == "on")
    {
      digitalWrite(led_d0, LOW);
      Serial.print("on");
    }
    else if (messageTemp == "off")
    {
      digitalWrite(led_d0, HIGH);
      Serial.print("off");
    }
    Serial.println();
  }
  if (topic == "LED/2")
  {
    Serial.print("Led Edisson ");
    if (messageTemp == "on")
    {
      digitalWrite(led_d1, LOW);
      Serial.print("on");
    }
    else if (messageTemp == "off")
    {
      digitalWrite(led_d1, HIGH);
      Serial.print("off");
    }
    Serial.println();
  }
  if (topic == "LED/3")
  {
    Serial.print("Led Jorge ");
    if (messageTemp == "on")
    {
      digitalWrite(led_d2, LOW);
      Serial.print("on");
    }
    else if (messageTemp == "off")
    {
      digitalWrite(led_d2, HIGH);
      Serial.print("off");
    }
    Serial.println();
  }
  if (topic == "LED/4")
  {
    Serial.print("Led Valentina ");
    if (messageTemp == "on")
    {
      digitalWrite(led_d3, LOW);
      Serial.print("on");
    }
    else if (messageTemp == "off")
    {
      digitalWrite(led_d3, HIGH);
      Serial.print("off");
    }
    Serial.println();
  }
}
void setup_wifi(){
  delay(10);
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Wifi connected IP: ");
  Serial.println(WiFi.localIP());
}
void connection_client_sub(){
  Serial.println("Connecting the broker: ");
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial.print("Attemting MQTT connection...");
  if (client.connect(mqtt_server)){
    Serial.println("Connected");
  }
  else{
    Serial.print("Failed, rc=");
    Serial.print(client.state());
    Serial.println("Try again in 5 seconds");
    delay(50000);
  }
    client.subscribe("LED/1");
    client.subscribe("LED/2");
    client.subscribe("LED/3");
    client.subscribe("LED/4");
}
void setup() {
  pinMode(led_d0, OUTPUT);
  pinMode(led_d1, OUTPUT);
  pinMode(led_d2, OUTPUT);
  pinMode(led_d3, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  connection_client_sub();
}
void loop() {
    client.loop();
}