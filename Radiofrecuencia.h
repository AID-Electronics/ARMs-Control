#ifndef RADIOFRECUENCIA_H
#define RADIOFRECUENCIA_H

#include <Arduino.h>
#include "Trigonometria.h"

bool RxStart = 0;
//bool RxEnd = 0;
unsigned int RxCont = 0;
char RxBuff[9];
bool negativo;
double alabeoPlat;
double cabeceoPlat;

void getOrientRF(Vector3D *v) {
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
        v->y = strtod(RxBuff, &p);
        if (negativo == true) {
          v->y = 0 - v->y;
          negativo = false;
        }
        //Serial.print("   Alabeo: ");
        //Serial.print(v->y, 4);
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
        v->z = strtod(RxBuff, &p);
        if (negativo == true) {
          v->z = 0 - v->z;
          negativo = false;
        }
        //Serial.print("\tCabeceo: ");
        //Serial.println(v->z, 4);
      }
      else if (RxStart == true) {
        RxBuff[RxCont] = token;
        RxCont++;
      }
    }
  }
}

#endif
