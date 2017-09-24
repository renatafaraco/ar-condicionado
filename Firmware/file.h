#include <FS.h>

void fileSetup() {
  SPIFFS.begin();
}

void scanFiles() {
  Serial.println("Escaniando arquivos:");
  Dir dir = SPIFFS.openDir("/"); 
  while (dir.next()) { 
    Serial.print(dir.fileName());
    Serial.print(" - "); 
    File f = dir.openFile("r"); 
    Serial.print(f.size());
    Serial.println(" bytes."); 
  }
  yield();
}

void sendFile(String path) {
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    size_t enviado = server.streamFile(file,"text/html");
    file.close();
  }
}

