#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

const int led1 = D0; // GPIO5
const int led2 = D1; // GPIO4
const int led3 = D2; // GPIO0

// Replace with your network credentials
const char* ssid = "OPPOK10";
const char* password = "12345678";

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.println();

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
}

void loop() {
  // Wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {
    
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

    // Ignore SSL certificate validation
    client->setInsecure();
    
    // Create an HTTPClient instance
    HTTPClient https;
    
    // Generate a random float number between 0.0 and 100.0
    float randomNumber = random(0, 10000) / 100.0;
    
    // Create the URL with the random number
    String url = "https://erp.nitttrbpl.ac.in/iotcloud/TempCntrl?deviceId=apple&temp=" + String(randomNumber, 2);

    // Initializing an HTTPS communication using the secure client
    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, url)) {  // HTTPS
      Serial.print("[HTTPS] GET...\n");
      // Start connection and send HTTP header
      int httpCode = https.GET();
      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been sent and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        // File found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println("payload=" + payload);
          
          digitalWrite(led1, LOW);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          
          if (payload == "g") {
            digitalWrite(led1, HIGH);
            Serial.println("LED 1 is ON");
            delay(1000);
          } else if (payload == "y") {
            digitalWrite(led2, HIGH);
            Serial.println("LED 2 is ON");
            delay(1000);
          } else {
            digitalWrite(led3, HIGH);
            Serial.println("LED 3 is ON");
            delay(1000);
          }
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
    Serial.println(randomNumber);
    delay(5000);
  }

  Serial.println();
  Serial.println("Waiting 2min before the next round...");
  delay(120000);
}
