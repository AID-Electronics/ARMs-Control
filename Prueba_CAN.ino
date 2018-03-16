//Send and Read CAN data
//Se debe especificar en el loop la función deseada
 
#include <mcp_can.h>
#include <SPI.h>

#define ID_MOTOR_1 0x610
#define ID_MOTOR_2 0x611
  union
{
    byte pasosB[4];
    
    uint32_t pasos;

    
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

const char CadPos1[]={0x23,0x7A,0x60,0x00,0xA0,0x86,0x01,0x00}; //Indica la posición a la que ha de moverse
const char CadPos2[]={0x2B,0x40,0x60,0x00,0x7F,0x00,0x00,0x00}; // son cadenas complementarias para el movimiento que indican el tipo de este: 
const char CadPos3[]={0x2B,0x40,0x60,0x00,0x6F,0x00,0x00,0x00}; //El movimiento será relativo y no se espera a que acabe antes de procesar el siguiente.


MCP_CAN CAN(53);                                      // Set CS to pin 53
int pot=0;

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
  
  while(!flag_receive && i<10){
    //Serial.print(" ");
   // Serial.print(i);
    flag_receive=receive();
    i++;
  }
  
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



