//Send and Read CAN data
//Se debe especificar en el loop la función deseada
 
#include <mcp_can.h>
#include <SPI.h>
#include "Schneider_LMD_P84.h"

#define ID_MOTOR_1 0x610
#define ID_MOTOR_2 0x611
  union
{
    byte pasosB[4];
    
    uint32_t pasos;

    
}paquet;



const char CadPos1[]={0x23,0x7A,0x60,0x00,0xA0,0x86,0x01,0x00}; //Indica la posición a la que ha de moverse
const char CadPos2[]={0x2B,0x40,0x60,0x00,0x7F,0x00,0x00,0x00}; // son cadenas complementarias para el movimiento que indican el tipo de este: 
const char CadPos3[]={0x2B,0x40,0x60,0x00,0x6F,0x00,0x00,0x00}; //El movimiento será relativo y no se espera a que acabe antes de procesar el siguiente.

int pot=0;

void mover (long pasos,long ID){ //pasos debe ser de tipo long para poder contar los suficientes pasos
  char polarity[8]={0x2F,0x7E,0x60,0x00,0xC0,0x00,0x00,0x00};
  Serial.print(pasos);
  Serial.println(" pasos");
  paquet.pasos=abs(pasos);
  Serial.println(paquet.pasos);
  

  char buffe[]={0x23,0x7A,0x60,0x00,paquet.pasosB[0],paquet.pasosB[1],paquet.pasosB[2],paquet.pasosB[3]};

  Serial.println(paquet.pasosB[0],HEX);
  Serial.println(paquet.pasosB[1],HEX);
  Serial.println(paquet.pasosB[2],HEX);
  Serial.println(paquet.pasosB[3],HEX);
  
  if(pasos<0)
   polarity[4]=0xFF;
  else
   polarity[4]=0x7F;

  EnviarMSG(polarity,ID);
  EnviarMSG(buffe,ID);
  EnviarMSG(CadPos2,ID);
  EnviarMSG(CadPos3,ID);
  
}

void setup(){
  
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_1000KBPS))  {            // init can bus : baudrate = 500k
    
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(500);
    }
    Serial.println("CAN BUS Shield init ok!");

    delay(200);

    //AHORA Procederemos a enviar las instrucciones de configuración

    
    EnviarMSG(SetcurrentUSE,ID_MOTOR_1);
    EnviarMSG(SetAccel,ID_MOTOR_1);
    EnviarMSG(SetDecel,ID_MOTOR_1);
    EnviarMSG(Maxvel,ID_MOTOR_1);

    
//ahora se envían las instrucciones de cambio de estado


    EnviarMSG(ReadytoSwitch,ID_MOTOR_1);
    EnviarMSG(SwitchON,ID_MOTOR_1);
    EnviarMSG(OpEnable,ID_MOTOR_1);
    EnviarMSG(PositionProfileSet,ID_MOTOR_1);

//-----------------------------------------
    EnviarMSG(SetcurrentUSE,ID_MOTOR_2);
    EnviarMSG(SetAccel,ID_MOTOR_2);
    EnviarMSG(SetDecel,ID_MOTOR_2);
    EnviarMSG(Maxvel,ID_MOTOR_2);

    EnviarMSG(ReadytoSwitch,ID_MOTOR_2);
    EnviarMSG(SwitchON,ID_MOTOR_2);
    EnviarMSG(OpEnable,ID_MOTOR_2);
    EnviarMSG(PositionProfileSet,ID_MOTOR_2);
}

void loop()
{
  
  mover(51200,ID_MOTOR_1);
    Serial.println("Motor 1 positivo");
  while(Serial.read()==-1){}
 // delay(1000);

  mover(51200,ID_MOTOR_2);
    Serial.println("Motor 2 positivo");
  while(Serial.read()==-1){}
  //delay(1000);

  mover(-51200,ID_MOTOR_1);
    Serial.println("Motor 1 negativo");
  while(Serial.read()==-1){}
//  delay(1000);

  mover(-51200,ID_MOTOR_2);
  Serial.println("Motor 2 negativo");
  while(Serial.read()==-1){}
  //delay(1000);

}



