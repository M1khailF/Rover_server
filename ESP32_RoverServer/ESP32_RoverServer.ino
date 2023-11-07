#include <WiFi.h>
#include <ESPAsyncWebServer.h>
//#include "Esp_rover.h"
//
//Esp_rover esp;

const char* ssid     = "ESP32_Rover";
const char* password = "12345678";

IPAddress local_ip(192, 168, 2, 1);
IPAddress gateway(192, 168, 2, 1);
IPAddress subnet(255, 255, 255, 0);

AsyncWebServer server(9999);

float MotorValue = 0;
float AngleValue = 0;
int ArmState = 0;

void setup() {
  Serial.begin(115200);
  // Подключение к Wi-Fi
  //  /WiFi.begin(ssid, password);
  //  while (WiFi.status() != WL_CONNECTED) {
  //    delay(1000);
  //    Serial.println("Подключение к Wi-Fi...");
  //  }
  //  Serial.println("Подключено к Wi-Fi!");
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Определение обработчиков маршрутов HTTP
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    String html = "<html><body><h1>ESP32-Rover</h1>";

    html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    html += "<link rel=\"icon\" href=\"data:,\">";
    html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
    html += "button { background-color: #4CAF50; border: none; color: white; padding: 16px 20px;text-decoration: none; font-size: 30px;white-space: nowrap;margin: 10px 10px; cursor: pointer;}";
    html += "pos1 {position: relative;top: 0px; left: 60px;}";
    html += "pos2 {position: relative;top: -86px; left: 50px;}";
    html += "</style></head>";

    html += "<h2><p>Motor: <output id='motorValue'>" + String(MotorValue) + "</output></p><input type='range' min='0.0' max='1.0' value='" + String(MotorValue) + "' step = '0.01' onchange='updateSliderValueMotor(this.value);'oninput='motorValue.value = this.value'></h2>";
    html += "<script>function updateSliderValueMotor(value){var xhttp=new XMLHttpRequest();xhttp.open(\"GET\",\"/motor?value=\"+value,true);xhttp.send();}</script>";

    html += "<h3><p>Angle: <output id='angleValue'>" + String(AngleValue) + "</output></p><input type='range' min='-1.0' max='1.0' value='" + String(AngleValue) + "' step = '0.01' onchange='updateSliderValueAngle(this.value);'oninput='angleValue.value = this.value'></h3>";
    html += "<script>function updateSliderValueAngle(value){var xhttp=new XMLHttpRequest();xhttp.open(\"GET\",\"/angle?value=\"+value,true);xhttp.send();}</script>";

    html += "<h4><button onclick='toggleButtonON()'>ARM</button><br>";

    html += "<script>function toggleButtonON() {";
    html += "var xhttp = new XMLHttpRequest();";
    html += "xhttp.open('GET', '/armState?value=1', true);";
    html += "xhttp.send(); }</script>";

    html += "<button onclick='toggleButtonOFF()'>DISARM</button><br>";

    html += "<script>function toggleButtonOFF() {";
    html += "var xhttp = new XMLHttpRequest();";
    html += "xhttp.open('GET', '/armState?value=0', true);";
    html += "xhttp.send(); }</script></h4>";

    html += "</body></html>";
    
    request->send(200, "text/html", html);
  });

  server.on("/motor", HTTP_GET, [](AsyncWebServerRequest * request) {
    String value = request->getParam("value")->value();
    MotorValue = value.toFloat();
    String html = "<html><body><h1>Slider Value: " + String(MotorValue) + "</h1>";
    request->send(200, "text/html", html);
    //    /request->send(200, "text/plain", "OK");
  });

  server.on("/angle", HTTP_GET, [](AsyncWebServerRequest * request) {
    String value = request->getParam("value")->value();
    AngleValue = value.toFloat();
    request->send(200, "text/plain", "OK");
  });

  server.on("/armState", HTTP_GET, [](AsyncWebServerRequest * request) {
    String value = request->getParam("value")->value();
    ArmState = value.toInt();
    request->send(200, "text/plain", "OK");
  });
  // Запуск сервера
  server.begin();

//  /esp.begin();
  
}

void loop() {
  // Ваш дополнительный код
  Serial.print("Значение (Мотора, угла, ARM): ");
  Serial.print(MotorValue);
  Serial.print(" ");
  Serial.print(AngleValue);
  Serial.print(" ");
  Serial.println(ArmState);
  delay(100);
  
//  esp.motor(MotorValue);
//  esp.servo(AngleValue);
//  delay(100);
//  esp.arm(ArmState);
  
}
