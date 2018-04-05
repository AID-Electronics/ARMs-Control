//Programa con las funciones preparadas para configurar y mover los motores
 
#include <mcp_can.h>
#include <SPI.h>
#include "Schneider_LMD_P84.h"

#define ID_MOTOR_1 0x610
#define ID_MOTOR_2 0x611

void setup(){
  
    Serial.begin(1000000);

    while (CAN_OK != CAN.begin(CAN_1000KBPS))  {            // init can bus : baudrate = 1000k
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(500);
    }
    Serial.println("CAN BUS Shield init ok!");
    Serial.println();

    delay(200);
  
    setupMotor(ID_MOTOR_1,1000000,1000000,100,512000); //(long ID_motor,uint32_t Acel,uint32_t Decel, int current ,uint32_t MaxVel )
    setupMotor(ID_MOTOR_2,1000000,1000000,80,512000);
}

char a;
long pos;

void loop(){

  a=Serial.read();
  while(a==-1){
    a=Serial.read();
    }

    switch(a)
    {
      case '0':
          mover(0,ID_MOTOR_1);
          break;
      
      case '1':

          pos = requestPos(ID_MOTOR_1);
          Serial.print ("Actual position: ");
          Serial.println (pos);
          break;

      case '2':

          mover(1000,ID_MOTOR_1);
          break;

      case '3':

          mover(-1000,ID_MOTOR_1);
          break;
          
      default:
               mover(0,ID_MOTOR_1);
               break;
               
    }
}

