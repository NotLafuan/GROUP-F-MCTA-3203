#include <WiFi.h>
#include <HTTPClient.h>

const int analogPin = A0;
const char* ssid = "S21Ultra";
const char* password = "gmej3191";
// Domain Name with full URL Path for HTTP POST Request
const char* serverName = "http://api.thingspeak.com/update";
// write API Key provided by thingspeak
String apiKey = "96XP1400SYI2ACOL";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {

  int sensorValue = analogRead(analogPin);
    float voltage = sensorValue * (5.0 / 4095.0);
  float temperature = ((voltage - 0.5) * 100.0)-400;

  if(WiFi.status()== WL_CONNECTED){

      WiFiClient client;
      HTTPClient http;
      delay(2000); // wait for 10 seconds

     //float h = dht.readHumidity();

      float t = temperature;

      // Your Domain name with URL path or IP address with path

      http.begin(client, serverName);

      // Specify content-type header

      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "api_key=" + apiKey + "&field1=" + String(t);          
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
      /*
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      // JSON data to send with HTTP POST
      String httpRequestData = "{\"api_key\":\"" + apiKey + "\",\"field1\":\"" + String(random(40)) + "\"}";          
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);*/
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
      delay(2000);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}