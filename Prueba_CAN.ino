//Send and Read CAN data
//Se debe especificar en el loop la función deseada
 
#include <mcp_can.h>
#include <SPI.h>
#include "Schneider_LMD_P84.h"

#define ID_MOTOR_1 0x610
#define ID_MOTOR_2 0x611


int pot=0;



void setup(){
  
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_1000KBPS))  {            // init can bus : baudrate = 500k
    
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(500);
    }
    Serial.println("CAN BUS Shield init ok!");
    Serial.println();

    delay(200);

    setupMotor(ID_MOTOR_1);
    setupMotor(ID_MOTOR_2);

}

void loop()
{
  
  
  Serial.println("Motor 1 positivo");
  while(Serial.read()==-1){}
    mover(51200,ID_MOTOR_1);//una vuelta
    //mover(25600,ID_MOTOR_1);//Media vuelta
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



