#ifndef Schneider_LMD_P84_H
#define Schneider_LMD_P84_H

#include <Arduino.h>

#include <mcp_can.h>
#include <SPI.h>


unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buffRespuesta[8];
char str[20];

union Paquete{
  byte b[4];
  uint32_t i;
};

const char SetAccel[]={0x23,0x84,0x60,0x00,0x40,0x42,0x0F,0x00};
const char SetDecel[]={0x23,0x83,0x60,0x00,0x40,0x42,0x0F,0x00};


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

bool EnviarMSG(char buff[], long ID){
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
  return rec_OK;
}

bool SetCurrent (int porcentaje, long ID){
  //const byte SetcurrentUSE[]={0x2F,0x04,0x22,0x00,0x50,0x00,0x00,0x00};
  
  Paquete p;
  p.i = porcentaje;
  char SetcurrentUSE[]={0x2F,0x04,0x22,0x00,p.b[0],0x00,0x00,0x00};
  
  return EnviarMSG(SetcurrentUSE,ID);
}

bool maxVelocity (long velocity, long ID){
  //const char Maxvel[]={0x23,0x81,0x60,0x00,0x00,0xC8,0x00,0x00};
  Paquete p;
  p.i = velocity;
  char Maxvel[]={0x23,0x81,0x60,0x00,p.b[0],p.b[1],p.b[2],p.b[3]};
  
  return EnviarMSG(Maxvel,ID);
}

bool setDeccel (uint32_t decel, long ID){
  //const byte SetcurrentUSE[]={0x2F,0x04,0x22,0x00,0x50,0x00,0x00,0x00};
  
  Paquete p;
  p.i = decel;
  char SetDecel[]={0x23,0x83,0x60,0x00,p.b[0],p.b[1],p.b[2],p.b[3]};
  
  return EnviarMSG(SetDecel,ID);
}

void setupMotor(long ID_motor)
{
    //instrucciones de configuración
    SetCurrent(5, ID_motor);
    EnviarMSG(SetAccel,ID_motor);
    setDeccel(1000000,ID_motor);
    maxVelocity(51200, ID_motor);

    //instrucciones de cambio de estado
    EnviarMSG(ReadytoSwitch,ID_motor);
    EnviarMSG(SwitchON,ID_motor);
    EnviarMSG(OpEnable,ID_motor);
    EnviarMSG(PositionProfileSet,ID_motor);
}

#endif
