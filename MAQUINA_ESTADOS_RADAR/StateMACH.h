
#include "motor_tri.h"


unsigned long working_t; ///////////////////////////////////////OJOOOOOOOOOOOOOOOOo
unsigned long state_t;


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
      Serial.print("Estado Global: STANDBY,  ");
      break;
      case working:
            Serial.print("Estado Global: WORKING,  ");
            switch (state){
                case activo_CON_OBJETIVO:
                    Serial.print("Estado De trabajo: activo_CON_OBJETIVO,  ");
                    switch (mstate){
                        case acercandose:
                        Serial.print("Estado De movimiento: acercandose,  ");
                        break;
                        case aterrizando:
                        Serial.print("Estado De movimiento: aterrizando,  ");
                        break;
                        }
                    break;
                case activo_SIN_OBJETIVO:
                Serial.print("Estado De trabajo: activo_SIN_OBJETIVO,  ");
                break;
            }

      break;
      case error:
      Serial.print("Estado Global: ERROR,  ");
      break;
       case setupRadar:
      Serial.print("Estado Global: setupRadar,  ");
      break;
       case setupMotor:
      Serial.print("Estado Global: setupMotor,  ");
      break;
       case setupComs:
      Serial.print("Estado Global: setupComs,  ");
      break;
    
     }
     Serial.println("");
     

}

bool condicion_objetivo_valido(Target a)
{
  if(a.velocidad>0)
    if(a.intensidad> 345 && a.intensidad< 1345)
      return true;

  return false;
}

