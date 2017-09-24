#include <WebSocketsServer.h>

WebSocketsServer webSocket(81); 
uint8_t socketNumber = 0;

void websocketHandler(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght);

void websocketSetup() {
  webSocket.begin();                                
  webSocket.onEvent(websocketHandler);                
}

void websocketHandler(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {

  switch (type) { 
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Desconectou. \n", num);
      yield();
      break;

    case WStype_CONNECTED: {          
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Conectador em %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      yield();
      socketNumber = num;
      break;
      }

    case WStype_TEXT:
      if (payload[0] == '#') {
        Serial.printf("[%u] Recebeu texto: %s\n", num, payload);
        webSocket.sendTXT(socketNumber, "#oi webbrowser");
        yield();
      }
      break;

    case WStype_ERROR:
      Serial.printf("[%u] Erro %s\n", num, payload);
      yield();
  }
}

void websocketLoop() {
  webSocket.loop();
}

