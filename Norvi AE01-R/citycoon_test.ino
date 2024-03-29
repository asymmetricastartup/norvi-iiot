#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "FASTWEB-Ubx8JX";
const char* password = "TGqfj9GTK4";
const char* mqtt_server = "dashboard.cityconn.cloud";
const int mqtt_port = 30883;
const char* mqtt_user = "dbagroup";
const char* mqtt_password = "eCFckRQHrW2y6gL";

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Wire.begin(16,17);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
  
  Serial.begin(115200);

  // Connessione alla rete WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connessione in corso");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnesso alla rete WiFi");

  // Connessione al broker MQTT
  client.setServer(mqtt_server, mqtt_port);
  while (!client.connected()) {
    Serial.println("Connessione al broker MQTT...");
    if (client.connect("ESP32Client"), mqtt_user, mqtt_port) {
      Serial.println("Connesso al broker MQTT");
    } else {
      Serial.print("Errore di connessione, riprovo in 5 secondi...");
      delay(5000);
    }
  }
  client.publish("measures/@d4:d4:da:59:08:c4/System/SN", "d4:d4:da:59:08:c4");
  client.publish("measures/@d4:d4:da:59:08:c4/System/EC", "Norvi AE01-R");
  client.publish("measures/@d4:d4:da:59:08:c4/System/uptime", "Online");
}

void loop() {

  client.publish("measures/@d4:d4:da:59:08:c4/PM_1.0", "2.84");
  client.publish("measures/@d4:d4:da:59:08:c4/PM_2.5", "3.91");
  client.publish("measures/@d4:d4:da:59:08:c4/PM_4.0", "4.66");
  client.publish("measures/@d4:d4:da:59:08:c4/PM_10.0", "5.04");

  client.publish("measures/@d4:d4:da:59:08:c4/NC_0.5", "16.76");
  client.publish("measures/@d4:d4:da:59:08:c4/NC_1.0", "21.45");
  client.publish("measures/@d4:d4:da:59:08:c4/NC_2.5", "22.54");
  client.publish("measures/@d4:d4:da:59:08:c4/NC_4.0", "22.74");
  client.publish("measures/@d4:d4:da:59:08:c4/NC_10.0", "22.79");

  client.publish("measures/@d4:d4:da:59:08:c4/TP", "0.74");

  client.loop();
}
