//Send and Read CAN data
//Se debe especificar en el loop la función deseada
 
#include <mcp_can.h>
#include <SPI.h>

  union
{
    byte buff[10];
    
    struct
    {
      byte ID[2];
      byte MODO;
      byte CMD[2];
      byte blanco;
      byte data[4];
      
    }paquete;

    
}paquet;


 
unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];

const byte SetcurrentUSE[]={0x2F,0x04,0x22,0x00,0x50,0x00,0x00,0x00};
const char SetAccel[]={0x06,0x10,0x23,0x84,0x60,0x00,0x40,0x42,0x0F,0x00};
const char SetDecel[]={0x06,0x10,0x23,0x83,0x60,0x00,0x40,0x42,0x0F,0x00};
const char Maxvel[]={0x06,0x10,0x23,0x81,0x60,0x00,0x00,0xD0,0x07,0x00};

const char ReadytoSwitch[]={0x06,0x10,0x2B,0x40,0x60,0x00,0x06,0x00,0x00,0x00};
const char SwitchON[]={0x06,0x10,0x2B,0x40,0x60,0x00,0x07,0x00,0x00,0x00};
const char OpEnable[]={0x06,0x10,0x2B,0x40,0x60,0x00,0x0F,0x00,0x00,0x00};

const char PositionProfileSet[]={0x06,0x10,0x2F,0x60,0x60,0x00,0x01,0x00,0x00,0x00};


MCP_CAN CAN(53);                                      // Set CS to pin 53
int pot=0;

void sending() {
    // send data:  id = 0x00, standrad flame, data len = 8, stmp: data buf
    unsigned char stmp[8] = {pot, 1, 2, 3, 4, 5, 6, 7};
    for(int i=0; i<8;i++){
      Serial.print(SetcurrentUSE[i],HEX);
    }
    Serial.print("\n");
    CAN.sendMsgBuf(0x610, 0, 8, SetcurrentUSE);
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
            Serial.print(buf[i],HEX);
            Serial.print(",");
        }
        Serial.println();
    }
}

void setup()
{
  
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_1000KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(500);
    }
    Serial.println("CAN BUS Shield init ok!");

     sending();
   
}

void loop(){
 

  receive();

}

