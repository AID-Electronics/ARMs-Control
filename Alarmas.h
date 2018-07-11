#ifndef Alarmas_H
#define Alarmas_H

#include <Arduino.h>
#include "Comunicacion_MAXI.h"

class Alarmas{
public:
    bool IMU;
    bool CAN;
    bool motoresON;
    bool motoresSetup;
    bool comunicPLCs;
    bool comunicRF;
    bool motorTrif;
    bool radar;
    bool comPLCs;

    Alarmas();
    void update(Comunicacion_MAXI& maxi);
    void send2Interface();
};

Alarmas::Alarmas(){
    IMU = false;
    CAN = false;
    motoresON = false;
    motoresSetup = false;
    comunicPLCs = false;
    comunicRF = false;
    motorTrif = false;
    radar = false;
    comPLCs = false;
}

void Alarmas::update(Comunicacion_MAXI& maxi){
    motorTrif = maxi.errorMotor;
    radar = maxi.errorRadar;
    comPLCs = maxi.errorCom;
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