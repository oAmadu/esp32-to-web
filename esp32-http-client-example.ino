#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

//const String urls = "https://s-m.com.sa/s.html";
const String urls = "https://s-m.com.sa/f.html";

String payload = "";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(25, OUTPUT);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());

  Serial.print("Fetching " + urls + "... ");
}

void loop() {
  HTTPClient http; // Corrected class name
  http.begin(urls);
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0 ){
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println("--");
    Serial.println(payload);
    if ( payload == "forward"){
      digitalWrite(25, HIGH);
    }else{
      digitalWrite(25,LOW);
    }
  }else{
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");
  }
}