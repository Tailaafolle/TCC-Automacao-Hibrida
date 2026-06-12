#include <ESP8266WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"
#include "SinricProContactsensor.h" // biblioteca da campainha

//dados do wifi e sinric
#define WIFI_SSID         "Nomedowifi"
#define WIFI_PASS         "Senhadowifi"
#define APP_KEY           "Key"
#define APP_SECRET        "AppSecret"
#define PORTA_ID          "IdDaPorta"
#define CAMPAINHA_ID      "IdDaCampainha" 

unsigned long tempoContatoCampainha = 0;
bool campainhaAtiva = false;

//função quando você manda a alexa abrir a porta
bool onPowerState(const String &deviceId, bool &state) {
  if (deviceId == PORTA_ID) {
    if (state) {
      Serial.print('A'); //envia 'A' do serial pro arduino abri a porta
    }
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(9600); 
  
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  //configura o dispositivo da porta no sinricpro
  SinricProSwitch& minhaPorta = SinricPro[PORTA_ID];
  minhaPorta.onPowerState(onPowerState);
  
  // inicia o dispositivo virtual da campainha
  SinricProContactsensor& minhaCampainha = SinricPro[CAMPAINHA_ID];
  
  SinricPro.begin(APP_KEY, APP_SECRET);
}

void loop() {
  SinricPro.handle(); 
  
  // ouve se o arduino enviou algum alerta
  if (Serial.available() > 0) {
    char caractereRecebido = Serial.read();
    
    // se o arduino mandou o'S' (sensor de som) 
    if (caractereRecebido == 'S' && !campainhaAtiva) {
      SinricProContactsensor& minhaCampainha = SinricPro[CAMPAINHA_ID];
      
      minhaCampainha.sendContactEvent(true);  // Dispara a Alexa
      campainhaAtiva = true;
      tempoContatoCampainha = millis();
    }
  }

  // Reseta o sensor apos 2 segundos para nao travar a internet do esp
  if (campainhaAtiva && (millis() - tempoContatoCampainha > 2000)) {
    SinricProContactsensor& minhaCampainha = SinricPro[CAMPAINHA_ID];
    
    minhaCampainha.sendContactEvent(false); // reseta para a proxima batida na porta
    campainhaAtiva = false;
  }
}