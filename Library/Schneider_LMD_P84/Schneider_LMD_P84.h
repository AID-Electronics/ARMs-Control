#ifndef Schneider_LMD_P84_H
#define Schneider_LMD_P84_H

#include <Arduino.h>

#define ID_MOTOR_1 0x610
const byte SetcurrentUSE[]={0x2F,0x04,0x22,0x00,0x50,0x00,0x00,0x00};

void setupMotor1(){

    //instrucciones de configuración
    EnviarMSG(SetcurrentUSE,ID_MOTOR_1);
    EnviarMSG(SetAccel,ID_MOTOR_1);
    EnviarMSG(SetDecel,ID_MOTOR_1);
    EnviarMSG(Maxvel,ID_MOTOR_1);

    //instrucciones de cambio de estado
    EnviarMSG(ReadytoSwitch,ID_MOTOR_1);
    EnviarMSG(SwitchON,ID_MOTOR_1);
    EnviarMSG(OpEnable,ID_MOTOR_1);
    EnviarMSG(PositionProfileSet,ID_MOTOR_1);
}

#endif