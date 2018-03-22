//Programa con las funciones preparadas para configurar y mover los motores
 
#include <mcp_can.h>
#include <SPI.h>
#include "Schneider_LMD_P84.h"

#define ID_MOTOR_1 0x610
#define ID_MOTOR_2 0x611

void setup(){
  
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_1000KBPS))  {            // init can bus : baudrate = 1000k
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(500);
    }
    Serial.println("CAN BUS Shield init ok!");
    Serial.println();

    delay(200);
  
    setupMotor(ID_MOTOR_1,1000000,1000000,100,512000); //(long ID_motor,uint32_t Acel,uint32_t Decel, int current ,uint32_t MaxVel )
    //setupMotor(ID_MOTOR_2,1000000,1000000,80,512000);
}

char a;

void loop(){
  Serial.println("Modo relativo sin espera");
  //Serial.println("Motor 1 positivo");

  a=Serial.read();
  while(a==-1){
    a=Serial.read();
    }

    switch(a)
    {
      case '1':
              mover(0L,ID_MOTOR_1);
              break;
              
      case '2':
               mover(25600L,ID_MOTOR_1);
                break;

      case '3':
               mover(-25600L,ID_MOTOR_1);
               break;

      case '4':
               mover(6400L+25600L,ID_MOTOR_1);
               break;

      case '5':
               mover(-51200,ID_MOTOR_1);
               break;

      case '6':
          mover(-25600,ID_MOTOR_1);
          break;
               
      default:
               mover(256000,ID_MOTOR_1);
               break;
               
    }
  
    //while(Serial.read()==-1){}
    //mover(-51200,ID_MOTOR_1);//Media vuelta
    //mover(38400,ID_MOTOR_1);//3/4 DE VUELTA
    //mover(34133,ID_MOTOR_1);//2/3 de vuelta
    

// delay(1000);
  //mover(51200,ID_MOTOR_2);
    //Serial.println("Motor 2 positivo");
  //while(Serial.read()==-1){}
  //delay(1000);

  //mover(-51200,ID_MOTOR_1);
    //Serial.println("Motor 1 negativo");
  //while(Serial.read()==-1){}
//  delay(1000);

  //mover(-51200,ID_MOTOR_2);
  //Serial.println("Motor 2 negativo");
  //while(Serial.read()==-1){}
  //delay(1000);
}

