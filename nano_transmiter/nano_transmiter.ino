#include "IMU.h"

#define pinReset 2

IMU IMU_movil;

void setup(){
    //Serial1.begin(4800);  
    Serial.begin(4800);
    pinMode(pinReset,OUTPUT);
    digitalWrite(pinReset,HIGH);
    IMU_movil.setup();
}
 
void loop(){
    IMU_movil.update();
    if (IMU_movil.isAccelDataCorrect()){
        Serial.print("=");
        Serial.print(IMU_movil.accel.x,4);
        Serial.print(",");
        Serial.print(IMU_movil.accel.y,4);
        Serial.print(",");
        Serial.print(IMU_movil.accel.z,4);
        Serial.println(";");
    }
    else{
        IMU_movil.reset(pinReset);
    }

    if(Serial.read()!=-1){
       IMU_movil.imprimirDatos();
       IMU_movil.reset(pinReset);
       //IMU_movil.displayCalStatus();
       //IMU_movil.printTemp();
       //IMU_movil.print();
    }
  }

