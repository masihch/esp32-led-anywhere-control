/* If you need any guidance, be sure to message me
 My Website : https://masihch.com 

 The address of the test dashboard for this project is:
 https://lab.masihch.com/sound-trigger-esp32-from-anywhere-in-the-world/index.html
*/


#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char* ssid = "*****";       //your  AP(router) ssid
const char* password = "*****"; //your  AP(router) pass

const char* mqtt_server = "broker.masihch.com"; // my free public mqtt broker : domain
const int   mqtt_port   = 8883;                 // my free public mqtt broker : port
const char* mqtt_user   = "freeplan";            // my free public mqtt broker : user
const char* mqtt_pass   = "12345678";            // my free public mqtt broker : pass
const char* topic       = "sensor/sound";        // subscribed topic 


const int micDigitalPin = 4; // Input microphone pin

unsigned long lastDetectTime = 0;
const unsigned long lockoutTime = 500;
const unsigned long noDetectDelay = 10000;

bool detectPrinted = false;
bool noDetectPrinted = false;

WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(greenLED, HIGH);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_pass)) {
      Serial.println("connected");
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
  pinMode(micDigitalPin, INPUT);

  setup_wifi();

  espClient.setInsecure();

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int state = digitalRead(micDigitalPin);

  if (state == HIGH && (millis() - lastDetectTime > lockoutTime)) {
    Serial.println("detect");
    client.publish(topic, "detect");
    lastDetectTime = millis();
    detectPrinted = true;
    noDetectPrinted = false;
  }

  if (detectPrinted && !noDetectPrinted && (millis() - lastDetectTime >= noDetectDelay)) {
    Serial.println("nodetect");
    client.publish(topic, "nodetect");
    noDetectPrinted = true;
  }
}
