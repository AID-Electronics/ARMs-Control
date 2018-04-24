#ifndef PLATAFORMA_H
#define PLATAFORMA_H

class Plataforma{
public:
  Vector3D orientacion;
  Vector3D accel;
  double zrad;
  double yrad;

  bool calibrarPlat();
};

bool Plataforma::calibrarPlat(){
  while(abs(orientacion.y)>0.5 || abs(orientacion.z)>0.5){

    Vector3D aux;
    getOrientRF(&aux);
    yrad = (-orientacion.y )* deg2rad;
    zrad = (-orientacion.z )* deg2rad;
    
    pasosMotor1 = calcularPasos2D(yrad, zrad, RESOLUCION, RADIO_POLEA, H, 333, 0, D_REF);
    pasosMotor2 = calcularPasos2D(yrad, zrad, RESOLUCION, RADIO_POLEA, H, 0, 333, D_REF);
    pasosMotor3 = calcularPasos2D(yrad, zrad, RESOLUCION, RADIO_POLEA, H, -333, 0, D_REF);
    pasosMotor4 = calcularPasos2D(yrad, zrad, RESOLUCION, RADIO_POLEA, H, 0, -333, D_REF);
  
    moverRelatEspera(pasosMotor1, ID_MOTOR_1); //movimientos relativos con espera
    moverRelatEspera(pasosMotor2, ID_MOTOR_2);
    //moverRelatEspera(pasosMotor3,ID_MOTOR_3);
    //moverRelatEspera(pasosMotor4,ID_MOTOR_4);
  
  }
     //apagar motores()//funcion para apagar motores para que la posicien absoluta de cero pasos coincida con al horizonte 
    setupMotor(ID_MOTOR_1,1000000,1000000,100,512000);
    setupMotor(ID_MOTOR_2,1000000,1000000,100,512000);
 return true;
}

#endif
