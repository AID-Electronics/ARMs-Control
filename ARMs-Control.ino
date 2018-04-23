#include "Schneider_LMD_P84.h"
#include "Radiofrecuencia.h"

#define ID_MOTOR_1 0x610
#define ID_MOTOR_2 0x611
//#define ID_MOTOR_3 0x612
//#define ID_MOTOR_4 0x613

#include "IMU.h"

IMU IMU_fija;
double IMU_movil_Z;
double IMU_movil_Y;
double zrad;
double yrad;

bool calibrarPlat(){
  while(abs(IMU_movil_Y)>0.5 || abs(IMU_movil_Z)>0.5){
    //leerRF(); //funcion que no existe aun
    yrad = (-IMU_movil_Y )* deg2rad;
    zrad = (-IMU_movil_Z )* deg2rad;
    
    pasosMotor1 = calcularPasos2D(yrad, zrad, RESOLUCION, RADIO_POLEA, H, 333, 0, D_REF);
    pasosMotor2 = calcularPasos2D(yrad, zrad, RESOLUCION, RADIO_POLEA, H, 0, 333, D_REF);
    pasosMotor3 = calcularPasos2D(yrad, zrad, RESOLUCION, RADIO_POLEA, H, -333, 0, D_REF);
    pasosMotor4 = calcularPasos2D(yrad, zrad, RESOLUCION, RADIO_POLEA, H, 0, -333, D_REF);
  
  moverRelatEspera(pasosMotor1, ID_MOTOR_1); //movimientos relativos con espera
  moverRelatEspera(pasosMotor2, ID_MOTOR_2);
  //moverRelatEspera(pasosMotor3,ID_MOTOR_3);
  //moverRelatEspera(pasosMotor4,ID_MOTOR_4);
  
   //leerRF(); //funcion que no existe aun
  }
     //apagar motores()//funcion para apagar motores para que la posicien absoluta de cero pasos coincida con al horizonte 
    setupMotor(ID_MOTOR_1,1000000,1000000,100,512000);
    setupMotor(ID_MOTOR_2,1000000,1000000,100,512000);
 return true;
}

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


void loop(){
 /* IMU_fija.update();
  moverMotores(IMU_fija.cabeceo, IMU_fija.alabeo);
  
  if(Serial.read()!=-1){
    IMU_fija.imprimirDatos();
    IMU_fija.displayCalStatus();
    IMU_fija.printTemp();
    IMU_fija.print();
  }*/

  getOrientExterna();
  
}

