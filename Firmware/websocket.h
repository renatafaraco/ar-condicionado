#include <WebSocketsServer.h>

WebSocketsServer webSocket(81);
uint8_t socketNumber = 0;
bool websocketConnected = false;

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
      websocketConnected = false;
      break;

    case WStype_CONNECTED: {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Conectador em %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        yield();
        socketNumber = num;
        websocketConnected = true;
        break;
      }

    case WStype_TEXT:
      if (payload[0] == '#') {
        Serial.printf("[%u] Recebeu texto: %s\n", num, payload);
        const char msg = (char) payload[1];
        if (msg == '0') {
          Serial.println("Conexão estabelida");
          float t = getTemperatura();
          String msgToSend = "#Temp$" + String(t,2);
          Serial.println(msgToSend);
          webSocket.sendTXT(socketNumber,msgToSend);
          msgToSend = "#Agenda$";
          msgToSend += getAgendaConfig();
          Serial.println(msgToSend);
          webSocket.sendTXT(socketNumber,msgToSend);          
        }
        else if (msg == '1') {
          Serial.println("#Ligar");
          controleLigar();
          webSocket.sendTXT(socketNumber, "#ok");
          yield();
        }
        else if (msg == '2') {
          Serial.println("#Desligar");
          controleDesligar();
          webSocket.sendTXT(socketNumber, "#ok");
          yield();
        }
        else if (msg == '3') {
          Serial.println("#Setar");
          controleMudarTemp(22);
          webSocket.sendTXT(socketNumber, "#ok");
          yield();
        }
        else if (msg == '4') {
          Serial.println("#Agenda");
          webSocket.sendTXT(socketNumber, "#ok");
          yield();
        }
        else if (msg == '5') {
          float t = getTemperatura();
          String msgToSend = "#Temp$" + String(t,2);
          Serial.println(msgToSend);
          webSocket.sendTXT(socketNumber,msgToSend);
          yield();
        }
        else {
          webSocket.sendTXT(socketNumber, "#nok");
          yield();
          break;
        }
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

