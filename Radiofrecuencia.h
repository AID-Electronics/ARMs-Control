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

uint8_t nDato = 0;

void getOrientRF(Vector3D *v) {
  if (Serial1.available()) {
    char token = Serial1.read();
    //Serial.print(token);
    if (token == '=') {
      RxStart = 1;
      RxCont = 0;
      negativo = 0;
      nDato = 0;
    }
    else {
      if (token == ',') {
        RxBuff[RxCont] = '\0';
        RxCont = 0;
        
        char *p; //Utilizado unicamente en la funcion strtod
        double num = strtod(RxBuff, &p);
        if (negativo == true) {
          num = 0 - num;
          negativo = false;
        }
        if(nDato == 0){
          v->x = num;
          Serial.print("   X: ");
          Serial.print(v->x, 4);
        }
        else if (nDato == 1){
          v->y = num;
          Serial.print("\tY: ");
          Serial.print(v->y, 4);
        }
        
        nDato++;
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
        double num = strtod(RxBuff, &p);
        if (negativo == true) {
          num = 0 - num;
          negativo = false;
        }
        if(nDato == 2){
          v->z = num;
          Serial.print("\tZ: ");
          Serial.println(num, 4);
        }
        nDato = 0;
        
      }
      else if (RxStart == true) {
        RxBuff[RxCont] = token;
        RxCont++;
      }
    }
  }
}

#endif
