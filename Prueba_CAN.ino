//Send and Read CAN data
//Se debe especificar en el loop la función deseada
 
#include <mcp_can.h>
#include <SPI.h>

  union
{
    byte pasosB[2];
    
    uint16_t pasos;

    
}paquet;


 
unsigned char Flag_Recv = 0;
unsigned char len = 0;
unsigned char buffRespuesta[8];
char str[20];

const byte SetcurrentUSE[]={0x2F,0x04,0x22,0x00,0x50,0x00,0x00,0x00};
const char SetAccel[]={0x23,0x84,0x60,0x00,0x40,0x42,0x0F,0x00};
const char SetDecel[]={0x23,0x83,0x60,0x00,0x40,0x42,0x0F,0x00};
const char Maxvel[]={0x23,0x81,0x60,0x00,0x00,0xD0,0x07,0x00};

const char ReadytoSwitch[]={0x2B,0x40,0x60,0x00,0x06,0x00,0x00,0x00};
const char SwitchON[]={0x2B,0x40,0x60,0x00,0x07,0x00,0x00,0x00};
const char OpEnable[]={0x2B,0x40,0x60,0x00,0x0F,0x00,0x00,0x00};

const char PositionProfileSet[]={0x2F,0x60,0x60,0x00,0x01,0x00,0x00,0x00};

const char CadPos1[]={0x23,0x7A,0x60,0x00,0xA0,0x86,0x01,0x00};  //Indica la posición a la que ha de moverse
const char CadPos2[]={0x2B,0x40,0x60,0x00,0x5F,0x00,0x00,0x00}; // son cadenas complementarias para el movimiento que indican el tipo de este:
  
const char CadPos3[]={0x2B,0x40,0x60,0x00,0x4F,0x00,0x00,0x00}; //Absoluto, relativo, etc etc


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
        CAN.readMsgBuf(&len, buffRespuesta);    // read data,  len: data length, buf: data buf

        Serial.print("ID: ");

        Serial.print(CAN.getCanId(),HEX);

       Serial.print(" / ");

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(buffRespuesta[i],HEX);
            Serial.print(",");
        }
        Serial.println();

        return true;
    }
    else
    return false;
}

bool comprobarRespuesta()
{
  int flag_receive=0;
  int i=0;
  
  while(!flag_receive)
  {
    Serial.print(" ");
    Serial.print(i);
    flag_receive=receive();
    i++;
  }
  
  if(buffRespuesta[0]==0x80){
    return false;
  }
  else if(buffRespuesta[0]==0x60){
    return true;
  }
  //return true; 
  
}

void EnviarMSG(char buff[], long ID)
{
  sending(buff,ID);

  if(comprobarRespuesta())
  {
    Serial.println("");
    Serial.println("MSG RECIBIDO CORRECTAMENTE");
  }
  else
  {
    Serial.println("");
    Serial.println("ERROR EN MSG");
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

    delay(200);

    //AHORA Procederemos a enviar las instrucciones de configuración

    
    EnviarMSG(SetcurrentUSE,0x610);
    EnviarMSG(SetAccel,0x610);
    EnviarMSG(SetDecel,0x610);
    EnviarMSG(Maxvel,0x610);

    
//ahora se envían las instrucciones de cambio de estado


    EnviarMSG(ReadytoSwitch,0x610);
    EnviarMSG(SwitchON,0x610);
    EnviarMSG(OpEnable,0x610);
    EnviarMSG(PositionProfileSet,0x610);




   
}

void loop(){
 

<<<<<<< HEAD
  mover(10000,0x610);

  delay(1000);

}




=======
  //receive();
>>>>>>> b2bc6cfdcc096f7003d800b2ab81e4c9fee2970e





void mover (int pasos,long ID)
{ 

  paquet.pasos=pasos;

  char buffe[]={0x2B/*27*/,0x7A,0x60,0x00,paquet.pasosB[0],paquet.pasosB[1],0x00,0x00};

  EnviarMSG(buffe,ID);
  EnviarMSG(CadPos2,ID);
  EnviarMSG(CadPos3,ID);
  
}

