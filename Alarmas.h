#ifndef Alarmas_H
#define Alarmas_H

class Alarmas{
public:
    bool IMU;
    bool CAN;
    bool motoresON;
    bool motoresSetup;
    bool comunicPLCs;
    bool comunicRF;

    Alarmas();
};

Alarmas::Alarmas(){
    IMU = false;
    CAN = false;
    motoresON = false;
    motoresSetup = false;
    comunicPLCs = false;
    comunicRF = false;
}

#endif