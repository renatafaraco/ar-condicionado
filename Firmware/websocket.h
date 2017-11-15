#include <WebSocketsServer.h>

WebSocketsServer webSocket(81);
uint8_t socketNumber = 0;
bool websocketConnected = false;

void processAgenda(uint8_t * payload);
void processTemp(uint8_t * payload);
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
          float h = getUmidade();
          msgToSend = "#Umid$" + String(h,2);
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
          webSocket.sendTXT(socketNumber, "#ok");
          processTemp(payload);
          yield();
        }
        else if (msg == '4') {
          Serial.println("#Agenda");
          webSocket.sendTXT(socketNumber, "#ok");
          processAgenda(payload);
          yield();
        }
        else if (msg == '5') {
          float t = getTemperatura();
          String msgToSend = "#Temp$" + String(t,2);
          Serial.println(msgToSend);
          webSocket.sendTXT(socketNumber,msgToSend);
          yield();
        }
        else if (msg == '6') {
          float h = getUmidade();
          String msgToSend = "#Umid$" + String(h,2);
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

void processAgenda(uint8_t * payload) {  // muito feito, refazer o split melhor depois
  String sMensagem((char*) payload);
  int primeiroS = sMensagem.indexOf('$');
  String isAgendaAtiva = sMensagem.substring(primeiroS+1, primeiroS+2);
  Serial.println ("Status agenda: " + isAgendaAtiva);
  int segundoS = sMensagem.indexOf('$',primeiroS+1);
  int terceiroS = sMensagem.indexOf(':',segundoS+1);
  String horaInicio = sMensagem.substring(segundoS+1, terceiroS);
  Serial.println("Hora inicio: " + horaInicio);
  int quartoS = sMensagem.indexOf('$',terceiroS+1);
  String minutoInicio = sMensagem.substring(terceiroS+1, quartoS);
  Serial.println("Minuto inicio: " + minutoInicio);
  int quintoS = sMensagem.indexOf(':', quartoS+1);
  String horaFim = sMensagem.substring(quartoS+1, quintoS);
  Serial.println("Hora fim: " + horaFim);
  String minutoFim = sMensagem.substring(quintoS+1, sMensagem.length());
  Serial.println("Minuto fim: " + minutoFim);
  yield();
  saveAgendaConfig(isAgendaAtiva.toInt(),horaInicio.toInt(), minutoInicio.toInt(),horaFim.toInt(), minutoFim.toInt());
  
}

void processTemp(uint8_t * payload) {
  String sMensagem((char*) payload);
  int primeiroS = sMensagem.indexOf('$');
  String temp = sMensagem.substring(primeiroS+1, sMensagem.length());  
  Serial.println("Temp = " + temp);
  controleMudarTemp(temp.toInt());
}

void websocketLoop() {
  webSocket.loop();
}

