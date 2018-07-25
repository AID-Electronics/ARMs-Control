#include "radar.h"
#include <SPI.h>
#include <Controllino.h>

#define pi 3.141592

#define VEL_TO_RPM 11.9366     //1.25  // 60 entre (0.8m que tiene de radio * 2*pi) = 60/(0.8*2*pi)



///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

//                 Funciones para el movimiento del motor trifasico ///

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#define pinFrencuencia 10
#define pinMotor 6
#define MAX_VEL 24000
#define VEL_PREDET 1440




///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

class Motor_tri 
{
  float rpm;
  int pin;

  public:
  Motor_tri();
  Motor_tri(int a){pin=a;ini_motor();}
  void ini_motor();
  void moverMotor(float vel);
  void frenado();
  void frenadoGradual();
  
};


Motor_tri::Motor_tri(){

  pin=pinMotor;
  ini_motor();
  
}
void Motor_tri::ini_motor(){
  
  pinMode(pin,OUTPUT);

 
  
  
}

void Motor_tri::moverMotor(float vel){

  int velocidad=vel; //esta es la variable global en la que se almacena la velocidad del objetivo mas cercano.

  if(velocidad==0)
    velocidad=VEL_PREDET;

   velocidad=velocidad*VEL_TO_RPM; //ya que la velocidad medida por el radar es lineal y la salida del motor es velocidad angular.
   
   velocidad=map(velocidad,0,MAX_VEL,0,255); //////////////////////////// HACER LA PRUEBA DE VELOCIDAD para determinar los parametros maximos de velocidad
  analogWrite(pinMotor,velocidad);
  
}


void Motor_tri::frenado(){

  

  analogWrite(pinMotor,0); // por ahora esta es la unica manera de frenar que conocemos
  
}

void Motor_tri::frenadoGradual(){
  analogWrite(pinMotor,50);
  //delay(2000);
  analogWrite(pinMotor,35);
  //delay(2000);
  analogWrite(pinMotor,20);
  //delay(2000);
  analogWrite(pinMotor,0);
  
}


