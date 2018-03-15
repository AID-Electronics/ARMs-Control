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
const char SetAccel[]={0x23,0x84,0x60,0x00,0x40,0x42,0x0F,0x00};
const char SetDecel[]={0x23,0x83,0x60,0x00,0x40,0x42,0x0F,0x00};
const char Maxvel[]={0x23,0x81,0x60,0x00,0x00,0xD0,0x07,0x00};

const char ReadytoSwitch[]={0x2B,0x40,0x60,0x00,0x06,0x00,0x00,0x00};
const char SwitchON[]={0x2B,0x40,0x60,0x00,0x07,0x00,0x00,0x00};
const char OpEnable[]={0x2B,0x40,0x60,0x00,0x0F,0x00,0x00,0x00};

const char PositionProfileSet[]={0x2F,0x60,0x60,0x00,0x01,0x00,0x00,0x00};

const char CadPos1[]={0x23,0x7A,0x60,0x00,0xA0,0x86,0x01,0x00};
const char CadPos2[]={0x2B,0x40,0x60,0x00,0x5F,0x00,0x00,0x00};
const char CadPos3[]={0x2B,0x40,0x60,0x00,0x4F,0x00,0x00,0x00};


MCP_CAN CAN(53);                                      // Set CS to pin 53
int pot=0;

void sending( char buff[], long ID) {
  
    for(int i=0; i<8;i++){
      Serial.print(CadPos1[i],HEX);
    }
    Serial.print("\n");
    CAN.sendMsgBuf(ID, 0, 8, buff);
    
}

bool receive(){
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

