#include "IMU.h"

#define pinReset 2

IMU IMU_movil;
 int i=0;

void setup(){
    //Serial1.begin(4800);  
    Serial.begin(4800);
    pinMode(pinReset,OUTPUT);
    digitalWrite(pinReset,HIGH);
    IMU_movil.setup();

}
 
void loop(){
   IMU_movil.update();
  Serial.print("=");
   Serial.print(IMU_movil.accel.x,4);
   Serial.print(",");
   Serial.print(IMU_movil.accel.y,4);
   Serial.print(",");
   Serial.print(IMU_movil.accel.z,4);
   Serial.println(";");
//SERIAL 1
//  Serial1.print("=");
//   Serial1.print(IMU_movil.accel.x,4); 
//   Serial1.print(",");
//   Serial1.print(IMU_movil.accel.y,4);
//   Serial1.print(",");
//   Serial1.print(IMU_movil.accel.z,4);
//   Serial1.println(";");

    if(Serial.read()!=-1){
       IMU_movil.imprimirDatos();
       IMU_movil.reset(pinReset);
    //IMU_movil.displayCalStatus();
    //IMU_movil.printTemp();
    //IMU_movil.print();
    }
  }

