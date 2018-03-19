#ifndef Schneider_LMD_P84_H
#define Schneider_LMD_P84_H

#include <Arduino.h>

#include <mcp_can.h>
#include <SPI.h>

#define ID_MOTOR_1 0x610

unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buffRespuesta[8];
char str[20];

const byte SetcurrentUSE[]={0x2F,0x04,0x22,0x00,0x50,0x00,0x00,0x00};
const char SetAccel[]={0x23,0x84,0x60,0x00,0x40,0x42,0x0F,0x00};
const char SetDecel[]={0x23,0x83,0x60,0x00,0x40,0x42,0x0F,0x00};
const char Maxvel[]={0x23,0x81,0x60,0x00,0x00,0xC8,0x00,0x00};

const char ReadytoSwitch[]={0x2B,0x40,0x60,0x00,0x06,0x00,0x00,0x00};
const char SwitchON[]={0x2B,0x40,0x60,0x00,0x07,0x00,0x00,0x00};
const char OpEnable[]={0x2B,0x40,0x60,0x00,0x0F,0x00,0x00,0x00};

const char PositionProfileSet[]={0x2F,0x60,0x60,0x00,0x01,0x00,0x00,0x00};

MCP_CAN CAN(53);                                      // Set CS to pin 53

void sending( char buff[], long ID) {
        Serial.print("(SENT)ID: ");
        Serial.print(ID,HEX);
        Serial.print(" / ");

    for(int i=0; i<8;i++){
      Serial.print(buff[i],HEX);
      Serial.print(",");
    }
    Serial.print("\n");
    CAN.sendMsgBuf(ID, 0, 8, buff);
    
}

bool receive(){
    if(CAN_MSGAVAIL == CAN.checkReceive()){          // check if data coming
    
        CAN.readMsgBuf(&len, buffRespuesta);    // read data,  len: data length, buf: data buf

        Serial.print("(RECEIVED)ID: ");

        Serial.print(CAN.getCanId(),HEX);

       Serial.print(" / ");

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(buffRespuesta[i],HEX);
            Serial.print(",");
        }
        Serial.println();

        return true;
    }else
    
    return false;
}

bool comprobarRespuesta(){
  int flag_receive=0;
  int i=0;
  
  while(!flag_receive && i<50){
    flag_receive=receive();
    i++;
  }
  
  Serial.println(i);
  
  if (flag_receive == 1){
    if(buffRespuesta[0]==0x80){
      return false;
    }
    else if(buffRespuesta[0]==0x60){
      return true;
    }
  }
  else{
    return false;
  }
}

void EnviarMSG(char buff[], long ID){
  bool rec_OK = 0; 
  
  for (int contError = 0; contError < 3 && rec_OK == 0; contError++){
    sending(buff,ID);
    
    if(comprobarRespuesta() == 1){
      rec_OK = 1;
      Serial.println("MSG RECIBIDO CORRECTAMENTE");
      Serial.println("");
    }
    else {
      Serial.println("ERROR EN MSG");
      Serial.println("");
    }
  }

  if (rec_OK == 0){
    Serial.println ("Mensaje erroneo");
  }
}

void setupMotor1(){

    //instrucciones de configuración
    EnviarMSG(SetcurrentUSE,ID_MOTOR_1);
    EnviarMSG(SetAccel,ID_MOTOR_1);
    EnviarMSG(SetDecel,ID_MOTOR_1);
    EnviarMSG(Maxvel,ID_MOTOR_1);

    //instrucciones de cambio de estado
    EnviarMSG(ReadytoSwitch,ID_MOTOR_1);
    EnviarMSG(SwitchON,ID_MOTOR_1);
    EnviarMSG(OpEnable,ID_MOTOR_1);
    EnviarMSG(PositionProfileSet,ID_MOTOR_1);
}

#endif
