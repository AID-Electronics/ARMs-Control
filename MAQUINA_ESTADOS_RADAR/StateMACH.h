#include "radar.h"
#include "motor_tri.h"
#define pinState A0 // entrada digital para el cambio de estado 
#define pinData A1
#define pinAterrizaje 3
#define pinRadar 9
#define tiempoEspera 100
#define tiempoEspera_reset 10
#define tiempoEspera_data 30
#define tiempo_aterrizaje 6000
#define tiempo_espera_postAterrizaje 1000

#define time_tol 2



enum globalState{
  setupRadar, setupMotor,setupComs,Standby,working,error
};

enum workingState{

  activo_CON_OBJETIVO,activo_SIN_OBJETIVO,activo_aterrizado//errorAct
};

enum movementState{
  acercandose,aterrizando
};

//VARIALBLE DE ESTADO

bool state_flag=false;

globalState currentState;
globalState nextState;

workingState state;

movementState mstate;

Motor_tri motor(pinMotor);

bool motor_error;
bool radar_error=true;
bool coms_error;
bool working_error;
bool some_error;

bool stby_flag=false;
bool data_flag=false;
int stby_t1;
int stby_t2;
int data_t1;
int data_t2;

bool aterrizaje_flag=false;
int aterrizaje_t1;
int aterrizaje_t2;


void printState(){
  switch (currentState) {
    case Standby:
      Serial.print("Estado Global STANDBY,  ");
      break;
      case working:
      Serial.print("Estado Global WORKING,  ");
      break;
      case error:
      Serial.print("Estado Global ERROR,  ");
      break;
    
     }
     switch (state){
    case activo_CON_OBJETIVO:
      Serial.print("Estado De trabajo activo_CON_OBJETIVO,  ");
      break;
      case activo_SIN_OBJETIVO:
      Serial.print("Estado De trabajo activo_SIN_OBJETIVO,  ");
      break;
      default:
      Serial.print("Estado De trabajo WAAAT,  ");
      break;
    
}
switch (mstate){
    case acercandose:
      Serial.println("Estado De movimiento acercandose,  ");
      break;
      case aterrizando:
      Serial.println("Estado De movimiento aterrizando,  ");
      break;
      default:
      Serial.println("Estado De movimiento WAAAT,  ");
      break;
    
}
}

