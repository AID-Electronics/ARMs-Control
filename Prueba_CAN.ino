//Send and Read CAN data
//Se debe especificar en el loop la función deseada
 
#include <mcp_can.h>
#include <SPI.h>
 
unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];

MCP_CAN CAN(53);                                      // Set CS to pin 53
int pot=0;

void sending() {
    // send data:  id = 0x00, standrad flame, data len = 8, stmp: data buf
    pot=map(analogRead(0),0,1024,0,100);
    Serial.print(pot);
    Serial.println("%");
    unsigned char stmp[8] = {pot, 1, 2, 3, 4, 5, 6, 7};
    for(int i=0; i<8;i++){
      Serial.print(stmp[i]);
    }
   Serial.println("");

    CAN.sendMsgBuf(0x00, 0, 8, stmp);
    delay(100);                       // send data per 100ms
}

void receive(){
    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        Serial.print("ID: ");

        Serial.print(CAN.getCanId(),HEX);

       Serial.print(" / ");

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(buf[i]);
            Serial.print(",");
        }
        Serial.println();
    }
}

void setup()
{
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_1000KBPS))              // init can bus : baudrate = 1000k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(500);
    }
    Serial.println("CAN BUS Shield init ok!");
}

void loop(){
//  sending();
  receive();
}

