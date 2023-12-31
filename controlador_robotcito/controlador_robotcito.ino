/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-websocket-server-arduino/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";


bool RightState = 0;
bool LeftState = 0;
int RightPin = 29;
int LeftPin = 28;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>ESP Web Server</title>
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <link rel="icon" href="data:," />
    <style>
      * {
        box-sizing: border-box;
      }
      html {
        font-family: Arial, Helvetica, sans-serif;
        text-align: center;
      }
      h1 {
        font-size: 1.8rem;
        color: white;
      }
      h2 {
        font-size: 1.5rem;
        font-weight: bold;
        color: #143642;
      }
      .topnav {
        overflow: hidden;
        background-color: #143642;
      }
      body {
        max-width: 100%;
        margin: 0;
      }
      .content {
        padding: 30px;
        max-width: 600px;
        margin: 0 auto;
      }
      .card {
        background-color: #f8f7f9;
        box-shadow: 2px 2px 12px 1px rgba(140, 140, 140, 0.5);
        padding-top: 10px;
        padding-bottom: 20px;
      }
      .button {
        padding: 3vh 3vh;
        font-size: 24px;
        text-align: center;
        outline: none;
        color: #fff;
        background-color: #0f8b8d;
        border: none;
        border-radius: 5px;
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
        -webkit-tap-highlight-color: rgba(0, 0, 0, 0);
      }
      /*.button:hover {background-color: #0f8b8d}*/
      .button:active {
        background-color: #e00000;
        box-shadow: 2 2px #cdcdcd;
        transform: translateY(2px);
      }
      .state {
        font-size: 1.5rem;
        color: #8c8c8c;
        font-weight: bold;
      }
      .box {
        display: flex;
        flex-direction: column;
        text-align: justify;
        align-items: center;
        width: 90vw;
      }
      .leftButton {
        position: absolute;
        top: 50vh;
        left: 20vw;
      }
      .rightButton {
        position: absolute;
        top: 50vh;
        left: 80vw;
      }
    </style>
    <title>Epic Robot Controller</title>
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <link rel="icon" href="data:," />
  </head>
  <body>
    <!-- <div class="topnav">
      <h1>ESP WebSocket Server</h1>
    </div> -->
    <!-- <div class="content"> -->
    <!-- <div class="card"> -->
    <!-- <h2>Output - GPIO 2</h2> -->
    <!-- <p class="state">state: <span id="state">%STATE%</span></p> -->
    <!-- </div> -->
    <!-- </div> -->
    <div class="">
      <button id="Right" class="button rightButton">Right</button
      ><button id="Left" class="button leftButton">Left</button>
    </div>
    <script>
      var gateway = `ws://${window.location.hostname}/ws`;
      var websocket;
      window.addEventListener("load", onLoad);
      function initWebSocket() {
        console.log("Trying to open a WebSocket connection...");
        websocket = new WebSocket(gateway);
        websocket.onopen = onOpen;
        websocket.onclose = onClose;
        websocket.onmessage = onMessage; // <-- add this line
      }
      function onOpen(event) {
        console.log("Connection opened");
      }
      function onClose(event) {
        console.log("Connection closed");
        setTimeout(initWebSocket, 2000);
      }
      function onMessage(event) {
        var state;
        if (event.data == "1") {
          state = "ON";
        } else {
          state = "OFF";
        }
        document.getElementById("state").innerHTML = state;
      }
      function onLoad(event) {
        initWebSocket();
        initButton();
      }
      function initButton() {
        document.getElementById("Right").addEventListener("click", Right);
        document.getElementById("Left").addEventListener("click", Left);
      }
      function Right() {
        websocket.send("Right"); //envia al servidor el texto right
      }
      function Left() {
        websocket.send("Left"); //envia al servidor el texto left
      }
    </script>
  </body>
</html>

)rawliteral";

// esta funcion notifica a todos los usuarios del cambio del estado del led
void notifyClients() {
  ws.textAll(String(ledState));
}

//  cambia el estado de los botones
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "Right") == 0) {
      RightState = !RightState;
      notifyClients();
    }
    if (strcmp((char*)data, "Left") == 0) {
      LeftState = !LeftState;
      notifyClients();
    }
  }
}

// funcion que muestra en la consola las ip
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

//funcion que inicia el websocket
void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

// Esta funcion se encarga de cambiar el cuadrito que decia si está encendido o no el led
String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if (ledState){
      return "ON";
    }
    else{
      return "OFF";
    }
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(RightPin, OUTPUT);
  pinMode(LeftPin, OUTPUT);
  digitalWrite(RightPin, LOW);
  digitalWrite(LeftPin, LOW);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();
}

void loop() {
  ws.cleanupClients();
  digitalWrite(RightPin, RightState);
  digitalWrite(LeftPin, LeftState);
}