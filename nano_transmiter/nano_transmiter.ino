 #include "IMU.h"

IMU IMU_movil;
 int i=0;

unsigned long tiempo;
unsigned long past_tiempo;
unsigned long tiempo_muestreo;

void setup(){
    Serial1.begin(4800);     
    Serial.begin(115200);
    IMU_movil.setup();
    past_tiempo = 0;
    tiempo_muestreo = 100;
}
 
void loop(){ 
   IMU_movil.update();
   tiempo = millis();
   if (tiempo - past_tiempo >= tiempo_muestreo){
    past_tiempo = tiempo;
   Serial.print(IMU_movil.accel.x,4);
   Serial.print(",");
   Serial.print(IMU_movil.accel.y,4);
   Serial.print(",");
   Serial.print(IMU_movil.accel.z,4);
   Serial.println(";");
//SERIAL 1
   Serial1.print(IMU_movil.accel.x,4); 
   Serial1.print(",");
   Serial1.print(IMU_movil.accel.y,4);
   Serial1.print(",");
   Serial1.print(IMU_movil.accel.z,4);
   Serial1.println(";");
   }

    if(Serial.read()!=-1){
       IMU_movil.imprimirDatos();
    //IMU_movil.displayCalStatus();
    //IMU_movil.printTemp();
    //IMU_movil.print();
    }
  }

