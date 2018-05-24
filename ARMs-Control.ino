#include <Controllino.h>
#include "Schneider_LMD_P84.h"
#include "Radiofrecuencia.h"

#define ID_MOTOR_1 0x610
#define ID_MOTOR_2 0x611
//#define ID_MOTOR_3 0x612
//#define ID_MOTOR_4 0x613

#define velocidad 5120
#define aceleracion 1000000
#define deceleracion 1000000

#include "IMU.h"
#include "Plataforma.h"
#include "Comunicacion_MAXI.h"


IMU IMU_fija;
Plataforma platform;
Comunicacion_MAXI com_maxi;

uint8_t globalState;

bool errorIMU = false;
bool errorCAN = false;
bool errorMotoresON = false;
bool errorMotoresSetup = false;
bool errorComunicRadar = false;
bool errorComunicRF = false;

bool entradaEstadoError = true;

void errorSolucionado (uint8_t estado){
  if (Serial.available()){
    if (Serial.read() == 'C'){
      globalState = estado;
      Serial.print ("Paso al estado ");
      Serial.println (estado);
    }
  }
}

void setup(){
  Serial.begin(1000000);
  Serial1.begin(4800);
  globalState = 0;

  //Alimentacion motores
  pinMode(CONTROLLINO_R0, OUTPUT);
  pinMode(CONTROLLINO_R1, OUTPUT);
  digitalWrite(CONTROLLINO_R0, LOW);
  digitalWrite(CONTROLLINO_R1, LOW);
  
  //Alimentacion MAXI
  pinMode(CONTROLLINO_R4, OUTPUT);
  digitalWrite(CONTROLLINO_R4, LOW);

  Serial.println ("Setup Controllino Finalizado");
  Serial.println ("Pulse una tecla para continuar");
}

char a;
long pos;

void loop(){

  if (globalState == 0){
    if (Serial.available()){
      globalState = 1;
      Serial.println("Paso al estado 1");
    }
  }
  else if (globalState == 1){
    bool OK;
    OK = IMU_fija.setup();
    errorIMU = !OK;
    globalState = 2;
    Serial.println("Paso al estado 2");
  }
  else if (globalState == 2){
    bool setupCAN_ok = setupCAN();
    errorCAN = !setupCAN_ok;

    if(setupCAN_ok){
      globalState = 3;
      Serial.println("Paso al estado 3");
    }
    else{
      Serial.println("Paso al estado 5");
      globalState = 5;
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
        errorMotoresON = false;
        globalState = 4;
        Serial.println("Paso al estado 4");
      }
    }
    if(globalState != 4){
      Serial.println("Motores sin alimentacion");
      errorMotoresON = true;
      globalState = 5;
    }
  }

  else if (globalState == 4){
    //Setup de motores
    Serial.println("Setup motores");
    setupMotor(ID_MOTOR_1,aceleracion,deceleracion,100,velocidad); //(long ID_motor,uint32_t Acel,uint32_t Decel, int current ,uint32_t MaxVel )
    setupMotor(ID_MOTOR_2,aceleracion,deceleracion,100,velocidad);

    long m1_Accel = requestAccel(ID_MOTOR_1);
    long m1_Decel = requestDecel(ID_MOTOR_1);
    long m1_Vel = requestMaxVel(ID_MOTOR_1);

    long m2_Accel = requestDecel(ID_MOTOR_2);
    long m2_Decel = requestDecel(ID_MOTOR_2);
    long m2_Vel = requestMaxVel(ID_MOTOR_2);

    
    Serial.print("\tAceleracion: ");
    Serial.println(m1_Accel);
    Serial.print("\tDeceleracion: ");
    Serial.println(m1_Decel);
    Serial.print("\tMax Velocity: ");
    Serial.println(m1_Vel);

    Serial.print("\tAceleracion: ");
    Serial.println(m2_Accel);
    Serial.print("\tDeceleracion: ");
    Serial.println(m2_Decel);
    Serial.print("\tMax Velocity: ");
    Serial.println(m2_Vel);

    if (m1_Vel == velocidad && m2_Vel == velocidad){
      //Por ahora no tenemos en cuenta aceleraciones
      errorMotoresSetup = false;
      Serial.println("Paso al estado 5");
      globalState = 5;
    }
    else{
      Serial.println("Fallo setup motores");
      Serial.println("Paso al estado 5");
      errorMotoresSetup = true;
      globalState = 5;
    }
  }
  
  else if (globalState == 5){
    Vector3D test;
    if (getOrientRF(&test)){
      errorComunicRF = false;
      Serial.println("Recepcion RF OK");
      Serial.println("Paso al estado 6");
      globalState = 6;
    }
    else{
      //comprobar tiempo de espera
      errorComunicRF = true;
    }
  }

  else if (globalState == 6){
    //Test comunicacion MAXI
    digitalWrite(CONTROLLINO_R0, HIGH);
    com_maxi.setup();
    com_maxi.receive();
    
    //Si OK
    Serial.println("Paso al estado 7");
    globalState = 7;
    entradaEstadoError = true;
  }

  else if (globalState == 7){
    if (entradaEstadoError == true){
      Serial.print("errorIMU: ");
      Serial.println(errorIMU);
      Serial.print("errorCAN: ");
      Serial.println(errorCAN);
      Serial.print("errorMotoresON: ");
      Serial.println(errorMotoresON);
      Serial.print("errorMotoresSetup: ");
      Serial.println(errorMotoresSetup);
      Serial.print("errorComunicRadar: ");
      Serial.println(errorComunicRadar);
      Serial.print("errorComunicRF: ");
      Serial.println(errorComunicRF);

      entradaEstadoError = false;
    }
    if (errorIMU){
      errorSolucionado (1);
    }
    else if (errorCAN){
      errorSolucionado (2);
    }
    else if (errorMotoresON){
      errorSolucionado (3);
    }
    else if (errorMotoresSetup){
      errorSolucionado (4);
    }
    else if (errorComunicRF){
      errorSolucionado (5);
    }
    else if (errorComunicRadar){
      errorSolucionado (6);
    }
    else {
      globalState = 8;
    }
  }

  else if (globalState == 8){
    bool calibState;
    calibState = platform.calibrarPlat();

    String serialBuff;
    serialBuff += (String)calibState + " accelX: " + (String)platform.accel.x + " accelY: " + (String)platform.accel.y + " accelZ: " + (String)platform.accel.z ;
    Serial.println(serialBuff);
  
    if(calibState == 1){
      

      globalState = 9;
      Serial.println("Paso al estado 9");
    }
  }

  else if (globalState == 9){
    //Apaga el motor y vuelve a encenderlo
    digitalWrite(CONTROLLINO_R0, LOW);
    digitalWrite(CONTROLLINO_R1, LOW);
    delay(500);
    digitalWrite(CONTROLLINO_R0, HIGH);
    digitalWrite(CONTROLLINO_R1, HIGH);
      
    //Se vuelve a hacer el setup
    setupMotor(ID_MOTOR_1,1000000,1000000,100,51200);
    setupMotor(ID_MOTOR_2,1000000,1000000,100,51200);

    Serial.println("Paso al estado 10");
    globalState = 10;
  }

  else if (globalState == 10){
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
      Serial.print("STOP");
      while(1);
    }
  }
}

