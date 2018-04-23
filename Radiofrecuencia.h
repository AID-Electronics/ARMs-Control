#ifndef RADIOFRECUENCIA_H
#define RADIOFRECUENCIA_H

#include <Arduino.h>

bool RxStart = 0;
bool RxEnd = 0;
unsigned int RxCont = 0;
char RxBuff[9];
bool negativo;
double alabeo;
double cabeceo;

void getOrientExterna() {

  if (Serial1.available()) {
    char token = Serial1.read();
    //Serial.print(token);
    if (token == '=') {
      RxStart = 1;
      RxCont = 0;
      negativo = 0;
    }
    else {
      if (token == ',') {
        RxBuff[RxCont] = '\0';
        RxCont = 0;

        char *p;
        alabeo = strtod(RxBuff, &p);
        if (negativo == true) {
          alabeo = 0 - alabeo;
          negativo = false;
        }
        Serial.print("   Alabeo: ");
        Serial.print(alabeo, 4);
      }
      else if (token == '-') {
        negativo = true;
      }
      else if (token == ';') {
        RxStart = 0;
        RxBuff[RxCont] = '\0';
        RxCont = 0;
        //Serial.print("\tBuffer: ");
        //Serial.print(RxBuff);

        char *p;
        cabeceo = strtod(RxBuff, &p);
        if (negativo == true) {
          cabeceo = 0 - cabeceo;
          negativo = false;
        }
        Serial.print("\tCabeceo: ");
        Serial.println(cabeceo, 4);
      }
      else if (RxStart == true) {
        RxBuff[RxCont] = token;
        RxCont++;
      }
    }
  }
}

#endif
