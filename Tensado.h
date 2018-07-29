#ifndef Tensado_H
#define Tensado_H

#include <Arduino.h>
#include "Schneider_LMD_P84.h"

#define esperaMovimiento 500

class Tensado {
    long posAnterior;
    long posActual;
    long posMasTenso;

    bool limiteConocido;
    int estadoTensado;

    Tensado(){
        posAnterior = 0;
        posActual = 0;
        posMasTenso = 0;

        limiteConocido = false;
        estadoTensado = 0;
    }
    int tensaCable(long ID, long pasos);
    void printStatus(long ID);

};

int Tensado::tensaCable(long ID, long pasos){
    if (limiteConocido && posActual + pasos > posMasTenso){
        posAnterior = requestPos(ID);
        moverRelatInmediato(pasos, ID);
        delay(esperaMovimiento);
        posActual = requestPos(ID);

        if (posActual < posAnterior && posActual < posMasTenso){        //Como el tensado es con pasos negativos, 
            posMasTenso = posActual;                                    //la pos mas tensa es la mas negativa
        }
        else if (posActual > posAnterior){
            posMasTenso = posAnterior;
        }
    }
    else if (limiteConocido && posActual + pasos < posMasTenso){
        estadoTensado = 2;
    }
    else if (!limiteConocido){
        posAnterior = requestPos(ID);
        moverRelatInmediato(pasos, ID);
        delay(esperaMovimiento);
        posActual = requestPos(ID);
        
        if (posActual < posAnterior){
            posMasTenso = posActual;
        }
        else if (posActual > posAnterior){
            posMasTenso = posAnterior;
            limiteConocido = true;
            estadoTensado = 1;
        }
    }
    printStatus(ID);
    return estadoTensado;
}

void Tensado::printStatus(long ID){
    Serial.print(ID,HEX);
    Serial.print(",");
    Serial.print(posAnterior);
    Serial.print(",");
    Serial.print(posActual);
    Serial.print(",");
    Serial.print(posMasTenso);
    Serial.print(",");
    Serial.print(limiteConocido);
    Serial.print(",");
    Serial.println(estadoTensado);
}

#endif