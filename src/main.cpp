#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"
#include <fauxmoESP.h>
#include "config.h"


// Credenciais WiFi
// const char *ssid = "";
// const char *password = "";

WebServer server(8080);
fauxmoESP fauxmo;

const int led1 = 4;
const int led2 = 21;
const int led3 = 22;

void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    server.send(404, "text/plain", "Arquivo não encontrado");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handleJS() {
  File file = SPIFFS.open("/script.js", "r");
  if (!file) {
    server.send(404, "text/plain", "Arquivo não encontrado");
    return;
  }
  server.streamFile(file, "application/javascript");
  file.close();
}

void handleCSS() {
  File file = SPIFFS.open("/style.css", "r");
  if (!file) {
    server.send(404, "text/plain", "Arquivo não encontrado");
    return;
  }
  server.streamFile(file, "text/css");
  file.close();
}

void ligar_led1() {
  digitalWrite(led1, HIGH);
  server.send(200, "text/plain", "LED 1 Ligado");
}

void ligar_led2() {
  digitalWrite(led2, HIGH);
  server.send(200, "text/plain", "LED 2 Ligado");
}

void ligar_led3() {
  digitalWrite(led3, HIGH);
  server.send(200, "text/plain", "LED 3 Ligado");
}

void desligar_tudo() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  server.send(200, "text/plain", "Desligar tudo");
}

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.println(WiFi.localIP());

  if (!SPIFFS.begin(true)) {
    Serial.println("Erro ao montar SPIFFS");
    return;
  }

  server.on("/", HTTP_GET, handleRoot);
  server.on("/script.js", HTTP_GET, handleJS);
  server.on("/style.css", HTTP_GET, handleCSS);
  server.on("/led1", HTTP_GET, ligar_led1);
  server.on("/led2", HTTP_GET, ligar_led2);
  server.on("/led3", HTTP_GET, ligar_led3);
  server.on("/desligar_tudo", HTTP_GET, desligar_tudo);

  server.begin();
  Serial.println("Servidor iniciado");

  // Configuração do fauxmo para Alexa
  fauxmo.createServer(true);      // start HTTP server
  fauxmo.setPort(80);             // porta padrão
  fauxmo.enable(true);

  // Adiciona dispositivos que Alexa vai reconhecer
  fauxmo.addDevice("Luz 1");
  fauxmo.addDevice("Luz 2");
  fauxmo.addDevice("Luz 3");

  fauxmo.onSetState([](unsigned char device_id, const char *device_name, bool state, unsigned char value) {
    Serial.printf("[ALEXA] %s está %s\n", device_name, state ? "ligada" : "desligada");

    if (strcmp(device_name, "Luz 1") == 0) {
      digitalWrite(led1, state ? HIGH : LOW);
    } else if (strcmp(device_name, "Luz 2") == 0) {
      digitalWrite(led2, state ? HIGH : LOW);
    } else if (strcmp(device_name, "Luz 3") == 0) {
      digitalWrite(led3, state ? HIGH : LOW);
    }
  });
}

void loop() {
  server.handleClient();
  fauxmo.handle();
}
