#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

const char* host = "your_MySQL_server_IP";
const uint16_t port = 3306;
const char* user = "your_MySQL_username";
const char* password = "your_MySQL_password";
const char* database = "your_MySQL_database";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  if (!client.connect(host, port)) {
    Serial.println("Failed to connect to MySQL server");
    return;
  }

  String query = "INSERT INTO your_table (column1, column2) VALUES ('value1', 'value2')";

  client.println("POST /query HTTP/1.1");
  client.println("Host: " + String(host));
  client.println("User-Agent: ESP32");
  client.println("Connection: close");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.println("Content-Length: " + String(query.length()));
  client.println();
  client.println(query);

  while(!client.available()) {
    delay(1000);
  }

  String response = client.readStringUntil('\r');
  Serial.println(response);

  client.stop();
}

void loop() {
  // Your code here
}
