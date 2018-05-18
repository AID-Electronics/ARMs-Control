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

uint8_t globalState;

bool errorIMU = false;
bool errorCAN = false;
bool errorMotoresON = false;
bool errorMotoresSetup = false;
bool errorComunicRadar = false;
bool errorComunicRF = false;

void setup(){
  Serial.begin(1000000);
  Serial1.begin(4800);
  globalState = 0;
  
  pinMode(CONTROLLINO_R0, OUTPUT);
  pinMode(CONTROLLINO_R1, OUTPUT);
  digitalWrite(CONTROLLINO_R0, LOW);
  digitalWrite(CONTROLLINO_R1, LOW);

  Serial.println ("Setup Controllino Finalizado");
  Serial.println ("Pulse una tecla para continuar");
}

char a;
long pos;

void loop(){

  if (globalState == 0){
    if (Serial.available()){
      globalState = 1;
    }
  }
  else if (globalState == 1){
    bool OK;
    OK = IMU_fija.setup();
    if(OK){
      globalState = 2;
    }
    else{
      errorIMU = true;
    }
  }
  else if (globalState == 2){
    bool setupCAN_ok = setupCAN();
    errorCAN = !setupCAN_ok;

    if(setupCAN_ok){
      globalState = 3;
    }
    else{
      globalState = 10; //Estado error
    }
  }
  else if (globalState == 3){
    //Encendido de motores
    digitalWrite(CONTROLLINO_R0, HIGH);
    digitalWrite(CONTROLLINO_R1, HIGH);
    delay(1000);

    float tensionM1 = (float)requestVin(ID_MOTOR_1) / 10;
    float tensionM2 = (float)requestVin(ID_MOTOR_2) / 10;
    
    Serial.print("Tension M1: ");
    Serial.println(tensionM1);
    Serial.print("Tension M2: ");
    Serial.println(tensionM2);

    if (tensionM1 > 23.5 && tensionM1 < 24.5){
      if (tensionM2 > 23.5 && tensionM2 < 24.5){
        globalState = 4;
      }
    }
    if(globalState != 4){
      Serial.println("Motores sin alimentacion");
    }
  }

  else if (globalState == 4){
    //Setup de motores
    Serial.println("Setup motores");
    setupMotor(ID_MOTOR_1,1000000,1000000,100,velocidad); //(long ID_motor,uint32_t Acel,uint32_t Decel, int current ,uint32_t MaxVel )
    setupMotor(ID_MOTOR_2,1000000,1000000,100,velocidad);

    Serial.print("\tAceleracion: ");
    Serial.println(requestAccel(ID_MOTOR_1));
    Serial.print("\tDeceleracion: ");
    Serial.println(requestDecel(ID_MOTOR_1));
    Serial.print("\tMax Velocity: ");
    Serial.println(requestMaxVel(ID_MOTOR_1));

    Serial.print("\tAceleracion: ");
    Serial.println(requestAccel(ID_MOTOR_2));
    Serial.print("\tDeceleracion: ");
    Serial.println(requestDecel(ID_MOTOR_2));
    Serial.print("\tMax Velocity: ");
    Serial.println(requestMaxVel(ID_MOTOR_2));

    globalState = 5;
  }

  else if (globalState == 5){
    bool calibState;
    calibState = platform.calibrarPlat();

    String serialBuff;
    serialBuff += (String)calibState + " accelX: " + (String)platform.accel.x + " accelY: " + (String)platform.accel.y + " accelZ: " + (String)platform.accel.z ;
    Serial.println(serialBuff);
  
    if(calibState == 1){
      //Apaga el motor y vuelve a encenderlo
      digitalWrite(CONTROLLINO_R0, LOW);
      digitalWrite(CONTROLLINO_R1, LOW);
      delay(500);
      digitalWrite(CONTROLLINO_R0, HIGH);
      digitalWrite(CONTROLLINO_R1, HIGH);
      
      //Se vuelve a hacer el setup
      setupMotor(ID_MOTOR_1,1000000,1000000,100,51200);
      setupMotor(ID_MOTOR_2,1000000,1000000,100,51200);

      globalState = 6;
    }
  }

  else if (globalState = 6){
    IMU_fija.update();
    moverMotores(IMU_fija.cabeceo, IMU_fija.alabeo);
  
    if(Serial.read()!=-1){
      IMU_fija.imprimirDatos();
      IMU_fija.displayCalStatus();
      IMU_fija.printTemp();
      IMU_fija.print();
    }
  }
  
  if (Serial.available()){
    if (Serial.read() == '0'){
      while(1);
    }
  }
}

