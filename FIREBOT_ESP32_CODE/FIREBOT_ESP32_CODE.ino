/* INDUCTIVO, ALFRED AARON M.
    20221121217
    FIREBOT PROJECT ESP32 CODE (FOR MOVEMENT)
*/

#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

// ==== Motor Pins ====
int M1Pin1 = 21;  // Left Motor
int M1Pin2 = 19;
int M2Pin1 = 22;  // Right Motor
int M2Pin2 = 23;

// ==== Access Point Credentials ====
const char* ap_ssid = "FIREBOT";
const char* ap_password = "12345678";

WebServer server(80);

// === HTML Webpage ===
String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>FIREBOT CONTROLLER</title>
  <style>
    body { text-align: center; font-family: Monaco; font-size:20px; background-color: orange; }
    button { width: 240px; height: 120px; font-size: 30px; margin: 10px; }
  </style>
</head>
<body>
  <h2>FIREBOT Controller</h2>
  <button onclick="location.href='/forward'">FORWARD</button><br>
  <button onclick="location.href='/left'">LEFT</button>
  <button onclick="location.href='/stop'">STOP</button>
  <button onclick="location.href='/right'">RIGHT</button><br>
  <button onclick="location.href='/backward'">BACKWARD</button>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  pinMode(M2Pin1, OUTPUT);
  pinMode(M2Pin2, OUTPUT);
  pinMode(M1Pin1, OUTPUT);
  pinMode(M1Pin2, OUTPUT);

  stopMotors();

  // ==== WiFi Access Point ====
  WiFi.softAP(ap_ssid, ap_password);
  Serial.println("Access Point Started!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // ==== Web Server Routes ====
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);

  server.begin();
}

void loop() {
  server.handleClient();
}

// === Web Handlers ===
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void handleForward() {
  forward();
  server.send(200, "text/html", htmlPage);
}
void handleBackward() {
  backward();
  server.send(200, "text/html", htmlPage);
}
void handleLeft() {
  turnLeft();
  server.send(200, "text/html", htmlPage);
}
void handleRight() {
  turnRight();
  server.send(200, "text/html", htmlPage);
}
void handleStop() {
  stopMotors();
  server.send(200, "text/html", htmlPage);
}

// === Motor Movements ===
void forward() {
  digitalWrite(M2Pin1, LOW);
  digitalWrite(M2Pin2, HIGH);
  digitalWrite(M1Pin1, LOW);
  digitalWrite(M1Pin2, HIGH);
}
void backward() {
  digitalWrite(M2Pin1, HIGH);
  digitalWrite(M2Pin2, LOW);
  digitalWrite(M1Pin1, HIGH);
  digitalWrite(M1Pin2, LOW);
}
void turnRight() {
  digitalWrite(M2Pin1, HIGH);
  digitalWrite(M2Pin2, LOW);
  digitalWrite(M1Pin1, LOW);
  digitalWrite(M1Pin2, HIGH);
}
void turnLeft() {
  digitalWrite(M2Pin1, LOW);
  digitalWrite(M2Pin2, HIGH);
  digitalWrite(M1Pin1, HIGH);
  digitalWrite(M1Pin2, LOW);
}
void stopMotors() {
  digitalWrite(M2Pin1, LOW);
  digitalWrite(M2Pin2, LOW);
  digitalWrite(M1Pin1, LOW);
  digitalWrite(M1Pin2, LOW);
}










