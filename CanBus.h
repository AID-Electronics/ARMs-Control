#ifndef CANBUS_H
#define CANBUS_H

#include <mcp_can.h>
#include <SPI.h>

unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buffRespuesta[8];
uint32_t canID;


MCP_CAN CAN(53);                                      // Set CS to pin 53

bool setupCAN(){
  uint8_t cont = 0;
  while (CAN_OK != CAN.begin(CAN_1000KBPS) && cont < 5)  {            // init can bus : baudrate = 1000k
    Serial.println("\tCAN BUS Shield: Fallo inicializacion");
    Serial.println("\tInit CAN BUS Shield again");
    delay(1000);
    cont++;
  }
  if (cont < 5){
    Serial.println("CAN BUS Shield init ok!");
    Serial.println();
    delay(200);
    return true;
  }
  else{
    return false;
  }
}

void sending( char buff[], long ID) {
  /* Serial.print("(SENT)ID: ");
  Serial.print(ID,HEX);
  Serial.print(" / ");
  
  for(int i=0; i<8;i++){
    Serial.print(buff[i],HEX);
    Serial.print(",");
  }
  Serial.print("\n"); */
    
  CAN.sendMsgBuf(ID, 0, 8, buff);
}

bool receive(bool printMsg = false){
  if(CAN_MSGAVAIL == CAN.checkReceive()){          // check if data coming
    CAN.readMsgBuf(&len, buffRespuesta);    // read data,  len: data length, buf: data buf
    canID = CAN.getCanId();
    
    if (printMsg){
      Serial.print("(RECEIVED)ID: ");        
      Serial.print(canID,HEX);

      Serial.print(" / ");

      for(int i = 0; i<len; i++){    // print the data
        
        if(buffRespuesta[i]==0){
          Serial.print("00");
        }
        else{
          Serial.print(buffRespuesta[i],HEX);
        }
        Serial.print(",");
      }
      Serial.println();
    }
    return true;
  }
  else {
    return false;
  }
}

void limpiaBuffer(){
  Serial.println("Limpieza Buffer");
  while (receive(1));
  Serial.println("Fin limpieza");
}

#endif