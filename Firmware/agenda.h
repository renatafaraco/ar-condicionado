#include <EEPROM.h>


#define EEPROM_AGENDA 0 // endereço eeprom para agenda ativa
#define EEPROM_HORA_INICIO 1 // endereço eeprom para hora inicio
#define EEPROM_MIN_INICIO 2 // endereço eeprom para minuto inicio
#define EEPROM_HORA_FIM 3 // endereço eeprom para hora fim
#define EEPROM_MIN_FIM 4  // endereço eeprom para minuto fim

#define ME_AGUARDANDO 0 // máquina de estado aguardando
#define ME_REQUISICAO 1 // requisição ao sevidor NTP
#define ME_RESPOSTA 2 // resposta do sevidor NTP

int maquinaAgenda = ME_AGUARDANDO;
unsigned long intervaloAgenda = 5*60*1000;
unsigned long controleAgenda = 0;

void setAgendaAtiva(bool ativo);
bool getAgendaAtiva();
void setHoraInicio(int horaInicio);
int getHoraInicio();
void setMinInicio(int minInicio);
int getMinInicio();
void setHoraFim(int horaFim);
int getHoraFim();
void setMinFim(int minFim);
int getMinFim();
void testeAgenda();
String getAgendaConfig();


void agendaSetup() {
  controleAgenda = millis();
  Serial.println(getAgendaConfig());
}


void agendaLoop() {
  if(getAgendaAtiva()) {
     switch(maquinaAgenda) {
      case ME_AGUARDANDO:
        if (millis() - controleAgenda >= intervaloAgenda) {
          maquinaAgenda = ME_REQUISICAO;
        }
        break;
  
      case ME_REQUISICAO:
        sendNTPpacket(timeServerIP);
        maquinaAgenda = ME_RESPOSTA;
        break;
        
      case ME_RESPOSTA:
        int cb = udp.parsePacket();
        if (!cb) {
          break;
        }
        testeAgenda();
        controleAgenda = millis();
        maquinaAgenda = ME_AGUARDANDO;
        break;
     }
  }
}

void testeAgenda() {
  Serial.println("Fazendo o teste da hora");
  udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
  unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
  unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
  unsigned long secsSince1900 = highWord << 16 | lowWord;
  const unsigned long seventyYears = 2208988800UL;
  unsigned long epoch = secsSince1900 - seventyYears;
  Serial.print(F("UNIX"));
  Serial.println(epoch);
  int hr=(epoch  % 86400L) / 3600;
  int min=(epoch % 3600) / 60;
  int sec=(epoch % 60);

  if (arLigado() && hr > getHoraFim() && min > getMinFim()) {
    controleDesligar(); 
  } else if (!arLigado() && hr > getHoraInicio() && min > getMinInicio()) {
    controleLigar(); 
  }
  yield();
}

void saveAgendaConfig(bool ativo, int hrInicio, int minInicio, int hrFim, int minFim) {
  setAgendaAtiva(ativo);
  setHoraInicio(hrInicio);
  setMinInicio(minInicio);
  setHoraFim(hrFim);
  setMinFim(minFim);
}

String getAgendaConfig() {
  String configAgenda = "";
  configAgenda += String(getAgendaAtiva());
  configAgenda += "&";
  configAgenda += String(getHoraInicio());
  configAgenda += ":";
  configAgenda += String(getMinInicio());
  configAgenda += "&";
  configAgenda += String(getHoraFim());
  configAgenda += ":";
  configAgenda += String(getMinFim());
  return configAgenda;
}

void setAgendaAtiva(bool ativo) {
  EEPROM.write(EEPROM_AGENDA, ativo);
}

bool getAgendaAtiva() {
  bool ativo = EEPROM.read(EEPROM_AGENDA);
  return ativo;
}


void setHoraInicio(int horaInicio) {
  if (horaInicio < 24 || horaInicio >=0) {
    EEPROM.write(EEPROM_HORA_INICIO, horaInicio);
  }
}

int getHoraInicio() {
  int horaInicio = EEPROM.read(EEPROM_HORA_INICIO);
  return horaInicio;
}


void setMinInicio(int minInicio) {
  if (minInicio < 60 || minInicio >=0) {
    EEPROM.write(EEPROM_MIN_INICIO, minInicio);
  }
}

int getMinInicio() {
  int minInicio = EEPROM.read(EEPROM_MIN_INICIO);
  return minInicio;
}


void setHoraFim(int horaFim) {
  if (horaFim < 24 || horaFim >=0) {
    EEPROM.write(EEPROM_HORA_FIM, horaFim);
  }
}

int getHoraFim() {
  int horaFim = EEPROM.read(EEPROM_HORA_FIM);
  return horaFim;
}


void setMinFim(int minFim) {
  if (minFim < 60 || minFim >=0) {
    EEPROM.write(EEPROM_MIN_FIM, minFim);
  }
}

int getMinFim() {
  int minFim = EEPROM.read(EEPROM_MIN_FIM);
  return minFim;
}
