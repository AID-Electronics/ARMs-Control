#ifndef PLATAFORMA_H
#define PLATAFORMA_H

class Plataforma{
public:
  Vector3D orientacion;
  Vector3D accel;
  double zrad;
  double yrad;

  //Para calibracion
  double presentAccel;
  double pastAccel;
  int cont;
  bool invSentido;
  bool eje;
  uint8_t calibState;

  Plataforma();
  double getAccel();
  void setAccel(Vector3D *v);
  bool calibrarPlat();
};

Plataforma::Plataforma(){
  presentAccel = 0;
  pastAccel = 0;
  cont = 0;
  invSentido = 0;
  eje = 0;
  calibState = 0;
  
  zrad = 0;
  yrad = 0;
}

double Plataforma::getAccel(){
  return accel.z;
}

void Plataforma::setAccel(Vector3D *v){
  accel.x = v->x;
  accel.y = v->y;
  accel.z = v->z;
}

bool Plataforma::calibrarPlat(){
  Vector3D aux;
  bool orient = getOrientRF(&aux);
  
  setAccel(&aux);
  if (calibState == 0){
    pastAccel = getAccel();
    //Mueve eje unos grados
    cont = 0;
    calibState = 1;
  }
  else if (calibState == 1){
    presentAccel = getAccel();
    if (presentAccel > pastAccel){
      cont = 1;
    }
    else{
      if(cont == 0){
        invierteSentido();
      }
      else{
        cambiaEje();
        state = 0;
      }
    }
  }
  
  Serial.println(accel.z);
  if(abs(accel.z)<9.9){
    //Mover los motores, y comprobar a que corresponde con respecto al giro de la 
    //plataforma. Segun eso, mover los motores de forma que el gradiente de gravedad 
    //en el eje Z sea ascendente hasta llegar a 10m/s^2
    
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

    return false;  
  }
  else{
    return true;
  }
     //apagar motores()//funcion para apagar motores para que la posicien absoluta de cero pasos coincida con al horizonte
     //Se hara con un relé 
     //Despues se debe hacer el setup de nuevo
    //setupMotor(ID_MOTOR_1,1000000,1000000,100,512000);
    //setupMotor(ID_MOTOR_2,1000000,1000000,100,512000);
 
}

#endif
