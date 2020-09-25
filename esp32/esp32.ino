#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_MLX90614.h>


const char * ssid = "SahabatSatwa";
const char * password = "Amd2core";
const String ip_address = "localhost";
const int interval = 3000;


int temp;
Adafruit_MLX90614 mlx;


void setup() {
  
  Serial.begin(9600);
  mlx.begin();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
    //Serial.println(Wifi.localIP());
    if ((++i % 16) == 0) {
      Serial.println(F(" Menunggu koneksi ulang"));
    }
  }
}

void loop() { 
  temp = mlx.readObjectTempC();
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://192.168.1.12:6969/input/suhu");
    http.addHeader("Content-Type", "application/json");
    // constructing the json
    String data = String(temp);
    Serial.println(data);
    int httpResponseCode = http.POST(data);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Pengiriman metode POST error: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Koneksi Wifi Error");
  }
  delay(interval);
}
