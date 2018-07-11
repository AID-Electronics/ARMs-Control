#ifndef Alarmas_H
#define Alarmas_H

#include <Arduino.h>
#include "Comunicacion_MAXI.h"

enum State { sinEvaluar, off, on };

class Alarmas{
public:
    State IMU;
    State CAN;
    State motoresON;
    State motoresSetup;
    State comunicPLCs;
    State comunicRF;
    State motorTrif;
    State radar;
    State comPLCs;

    Alarmas();
    void reset();
    void update(Comunicacion_MAXI& maxi);
    void send2Interface();
};

Alarmas::Alarmas(){
    IMU = sinEvaluar;
    CAN = sinEvaluar;
    motoresON = sinEvaluar;
    motoresSetup = sinEvaluar;
    comunicPLCs = sinEvaluar;
    comunicRF = sinEvaluar;
    motorTrif = sinEvaluar;
    radar = sinEvaluar;
    comPLCs = sinEvaluar;
}

void Alarmas::reset(){
    IMU = sinEvaluar;
    CAN = sinEvaluar;
    motoresON = sinEvaluar;
    motoresSetup = sinEvaluar;
    comunicPLCs = sinEvaluar;
    comunicRF = sinEvaluar;
    motorTrif = sinEvaluar;
    radar = sinEvaluar;
    comPLCs = sinEvaluar;
}

void Alarmas::update(Comunicacion_MAXI& maxi){
    if(maxi.errorMotor){
        motorTrif = on;
    }
    else{
        motorTrif = off;
    }

    if(maxi.errorRadar){
        radar = on;
    }
    else{
        radar = off;
    }

    if(maxi.errorCom){
        comPLCs = on;
    }
    else{
        comPLCs = off;
    }
}

void Alarmas::send2Interface(){
    Serial.print("#Alarms: ");
    Serial.print(IMU);          Serial.print(",");
    Serial.print(CAN);          Serial.print(",");
    Serial.print(motoresON);    Serial.print(",");
    Serial.print(motoresSetup); Serial.print(",");
    Serial.print(comunicPLCs);  Serial.print(",");
    Serial.print(comunicRF);    Serial.print(",");
    Serial.print(motorTrif);    Serial.print(",");
    Serial.print(radar);        Serial.print(",");
    Serial.println(comPLCs);
}

#endif