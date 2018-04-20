#include <VirtualWire.h>
#include "IMU.h"

IMU IMU_movil;
void setup(){
  Serial.begin(115200);
  IMU_movil.setup();
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec -->150m
  vw_set_tx_pin(3);//Aqui se selecciona el pin digital que manda la información
}

void loop(){
  IMU_movil.update(); 
  send("JODER");
  if(Serial.read()!=-1){
    IMU_movil.imprimirDatos();
    //IMU_movil.displayCalStatus();
    //IMU_movil.printTemp();
    //IMU_movil.print();
  }
 delay(100);
}

void send (char *message){
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}

