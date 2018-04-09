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

void setup(){
  Serial.begin(1000000);
  setupIMU();
  
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
  bno.getEvent (&event);
  
  if(Serial.read()!=-1){
    imprimirDatos(event);
     displayCalStatus();
    }   

    cabeceo=event.orientation.y*deg2rad; //No estoy demasiado seguro de que sea el eje correcto
    alabeo=event.orientation.z*deg2rad;
  
     moverMotores();
}

