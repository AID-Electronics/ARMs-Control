////////////////////////////////////////////// PARTE DE MOTORES
#include <mcp_can.h>
#include <SPI.h>
#include "Schneider_LMD_P84.h"
#define ID_MOTOR_1 0x610
#define ID_MOTOR_2 0x611
//#define ID_MOTOR_3 0x612
//#define ID_MOTOR_4 0x613

///////////////////////////////////////////////////////////////////////////// PARTE DE LA IMU
#include "IMU.h"

IMU IMU_fija;

void setup(){
  Serial.begin(1000000);
  IMU_fija.setup();
  
//////////////////////////////////////////////////////////////////// CAN BUS

    while (CAN_OK != CAN.begin(CAN_1000KBPS))  {            // init can bus : baudrate = 1000k
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(500);
    }
    Serial.println("CAN BUS Shield init ok!");
    Serial.println();

    delay(200);
  
    setupMotor(ID_MOTOR_1,100000,100000,100,51200); //(long ID_motor,uint32_t Acel,uint32_t Decel, int current ,uint32_t MaxVel )
    setupMotor(ID_MOTOR_2,100000,100000,100,51200);
}

void loop(){
  IMU_fija.update();
  moverMotores(IMU_fija.cabeceo, IMU_fija.alabeo);
  
  if(Serial.read()!=-1){
    IMU_fija.imprimirDatos();
    IMU_fija.displayCalStatus();
    IMU_fija.printTemp();
  }
  IMU_fija.print();
}

