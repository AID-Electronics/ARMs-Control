#ifndef Alarmas_H
#define Alarmas_H

#include <Arduino.h>
#include "Comunicacion_MAXI.h"

class Alarmas{
public:
    enum State { sinEvaluar, off, on };
    int totChecked;
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
    void update(Comunicacion_MAXI& maxi);
    void send2Interface();
};

Alarmas::Alarmas(){
    totChecked = sinEvaluar;
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
    motorTrif = maxi.errorMotor;
    radar = maxi.errorRadar;
    comPLCs = maxi.errorCom;
}

void Alarmas::send2Interface(){

    String alarms2interface;
    convert2exportFormat(alarms2interface);

    Serial.print("#Alarms: ");
    Serial.print(totChecked);   Serial.print(",");
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