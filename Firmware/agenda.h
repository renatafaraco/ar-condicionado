#include <EEPROM.h>
#define MEM_ALOC_SIZE 10

#define EEPROM_AGENDA 0 // endereço eeprom para agenda ativa
#define EEPROM_HORA_INICIO 1 // endereço eeprom para hora inicio
#define EEPROM_MIN_INICIO 2 // endereço eeprom para minuto inicio
#define EEPROM_HORA_FIM 3 // endereço eeprom para hora fim
#define EEPROM_MIN_FIM 4  // endereço eeprom para minuto fim

#define ME_AGUARDANDO 0 // máquina de estado aguardando
#define ME_REQUISICAO 1 // requisição ao sevidor NTP


int maquinaAgenda = ME_AGUARDANDO;
unsigned long intervaloAgenda = 2*60*1000;
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
     int cb;
     switch(maquinaAgenda) {
      case ME_AGUARDANDO:
        if (millis() - controleAgenda >= intervaloAgenda) {
          maquinaAgenda = ME_REQUISICAO;
        }
        break;
  
      case ME_REQUISICAO:
        testeAgenda();
        controleAgenda = millis();
        maquinaAgenda = ME_AGUARDANDO;
        break;
     }
  }
}

void testeAgenda() {
  Serial.println("Fazendo o teste da hora");
  checkNTP();
//  udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
//  unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
//  unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
//  unsigned long secsSince1900 = highWord << 16 | lowWord;
//  const unsigned long seventyYears = 2208988800UL;
//  unsigned long epoch = secsSince1900 - seventyYears;
//  Serial.print(F("UNIX"));
//  Serial.println(epoch);
//  int hr=(epoch  % 86400L) / 3600;
//  int min=(epoch % 3600) / 60;
//  int sec=(epoch % 60);
//  Serial.print("Hora agora: ");
//  Serial.println(hr);
//  Serial.print("Min agora: ");
//  Serial.println(min);
//  Serial.print("Sec agora: ");
//  Serial.println(sec);
//
//  if (arLigado() && hr > getHoraFim() && min > getMinFim()) {
//    Serial.println("Desligando ar");
//    controleDesligar(); 
//  } else if (!arLigado() && hr > getHoraInicio() && min > getMinInicio()) {
//    Serial.println("Ligando ar");
//    controleLigar(); 
//  }
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
  Serial.print("gravou ativo: ");
  Serial.println(ativo);
}

bool getAgendaAtiva() {
  EEPROM.begin(MEM_ALOC_SIZE);
  bool ativo = EEPROM.read(EEPROM_AGENDA);
  EEPROM.end();
  return ativo;
}


void setHoraInicio(int horaInicio) {
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.write(EEPROM_HORA_INICIO, horaInicio);
  Serial.print("gravou hora inicio: ");
  Serial.println(horaInicio);
  EEPROM.end();
}

int getHoraInicio() {
  EEPROM.begin(MEM_ALOC_SIZE);
  int horaInicio = EEPROM.read(EEPROM_HORA_INICIO);
  Serial.print("retornou hora inicio: ");
  Serial.println(horaInicio);
  EEPROM.end();
  return horaInicio;
}


void setMinInicio(int minInicio) {
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.write(EEPROM_MIN_INICIO, minInicio);
  Serial.print("gravou minuto inicio: ");
  Serial.println(minInicio);
  EEPROM.end();
}

int getMinInicio() {
  EEPROM.begin(MEM_ALOC_SIZE);
  int minInicio = EEPROM.read(EEPROM_MIN_INICIO);
  Serial.print("retornou minuto inicio: ");
  Serial.println(minInicio);
  EEPROM.end();
  return minInicio;
}


void setHoraFim(int horaFim) {
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.write(EEPROM_HORA_FIM, horaFim);
  Serial.print("gravou hora fim: ");
  Serial.println(horaFim);
  EEPROM.end();
}

int getHoraFim() {
  EEPROM.begin(MEM_ALOC_SIZE);
  int horaFim = EEPROM.read(EEPROM_HORA_FIM);
  Serial.print("retornou hora fim: ");
  Serial.println(horaFim);
  EEPROM.end();
  return horaFim;
}


void setMinFim(int minFim) {
  EEPROM.begin(MEM_ALOC_SIZE);
  EEPROM.write(EEPROM_MIN_FIM, minFim);
  Serial.print("gravou minuto fim: ");
  Serial.println(minFim);
  EEPROM.end();
}

int getMinFim() {
  EEPROM.begin(MEM_ALOC_SIZE);
  int minFim = EEPROM.read(EEPROM_MIN_FIM);
  Serial.print("retornou minuto fim: ");
  Serial.println(minFim);
  EEPROM.end();
  return minFim;
}
