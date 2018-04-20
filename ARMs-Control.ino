#include "Schneider_LMD_P84.h"

#define ID_MOTOR_1 0x610
#define ID_MOTOR_2 0x611
//#define ID_MOTOR_3 0x612
//#define ID_MOTOR_4 0x613

#include "IMU.h"

IMU IMU_fija;

void setup(){
  Serial.begin(1000000);
  Serial1.begin(4800);
  IMU_fija.setup();
  setupCAN();

    setupMotor(ID_MOTOR_1,1000000,1000000,100,512000); //(long ID_motor,uint32_t Acel,uint32_t Decel, int current ,uint32_t MaxVel )
    setupMotor(ID_MOTOR_2,1000000,1000000,100,512000);
}

char a;
long pos;

bool RxStart = 0;
bool RxEnd = 0;
unsigned int RxCont = 0;
String RxBuff[8];
bool negativo;
double alabeo;

void loop(){
 /* IMU_fija.update();
  moverMotores(IMU_fija.cabeceo, IMU_fija.alabeo);
  
  if(Serial.read()!=-1){
    IMU_fija.imprimirDatos();
    IMU_fija.displayCalStatus();
    IMU_fija.printTemp();
    IMU_fija.print();
  }*/

  if (Serial1.available()){
    char token = Serial1.read();
    Serial.print(token);
    if(token == '='){
      RxStart = 1;
      RxCont = 0;
      negativo = 0;
    }
    else{
      if(token = ';'){
        RxBuff[RxCont] = NULL;
        RxCont = 0;
        alabeo = RxBuff.toDouble();
        if (negativo == true){
          alabeo = 0 - alabeo;
        }
      }
      else if (token == '-'){
        negativo = true;
      }
      else if (RxStart == true){
        RxBuff[RxCont] = token;
        RxCont++;
      }
    }
    
    
  }
  
}

