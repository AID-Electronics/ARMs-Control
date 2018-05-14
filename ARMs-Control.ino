#include <Controllino.h>
#include "Schneider_LMD_P84.h"
#include "Radiofrecuencia.h"

#define ID_MOTOR_1 0x610
#define ID_MOTOR_2 0x611
//#define ID_MOTOR_3 0x612
//#define ID_MOTOR_4 0x613

#define velocidad 5120

#include "IMU.h"
#include "Plataforma.h"


IMU IMU_fija;
Plataforma platform;

void setup(){
  Serial.begin(1000000);
  Serial1.begin(4800);
  IMU_fija.setup();
  setupCAN();

  //Encendido del motor 1 y 2
  pinMode(CONTROLLINO_R0, OUTPUT);
  pinMode(CONTROLLINO_R1, OUTPUT);
  digitalWrite(CONTROLLINO_R0, HIGH);
  digitalWrite(CONTROLLINO_R1, HIGH);
  delay(500);

    setupMotor(ID_MOTOR_1,1000000,1000000,100,velocidad); //(long ID_motor,uint32_t Acel,uint32_t Decel, int current ,uint32_t MaxVel )
    setupMotor(ID_MOTOR_2,1000000,1000000,100,velocidad);

  Serial.print("Aceleracion: ");
  Serial.println(requestAccel(ID_MOTOR_1));
  Serial.print("Deceleracion: ");
  Serial.println(requestDecel(ID_MOTOR_1));
  Serial.print("Max Velocity: ");
  Serial.println(requestMaxVel(ID_MOTOR_1));

  
}

char a;
long pos;


void loop(){
  
  bool calibState;
  calibState = platform.calibrarPlat();
  if(calibState == 1){
    //Apaga el motor y vuelve a encenderlo
    digitalWrite(CONTROLLINO_R0, LOW);
    digitalWrite(CONTROLLINO_R1, LOW);
    delay(500);
    digitalWrite(CONTROLLINO_R0, HIGH);
    digitalWrite(CONTROLLINO_R1, HIGH);

    //Se vuelve a hacer el setup
    setupMotor(ID_MOTOR_1,1000000,1000000,100,velocidad);
    setupMotor(ID_MOTOR_2,1000000,1000000,100,velocidad);
  }
  String serialBuff;
  serialBuff += (String)calibState + " accelX: " + (String)platform.accel.x + " accelY: " + (String)platform.accel.y + " accelZ: " + (String)platform.accel.z ;
  Serial.println(serialBuff);
 /* IMU_fija.update();
  moverMotores(IMU_fija.cabeceo, IMU_fija.alabeo);
  
  if(Serial.read()!=-1){
    IMU_fija.imprimirDatos();
    IMU_fija.displayCalStatus();
    IMU_fija.printTemp();
    IMU_fija.print();
  }*/
  if (Serial.available()){
    while(1);
  }
}

