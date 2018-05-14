#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#define accel_switch 9.5
#define sensibilidad 0.1

class Plataforma{
public:
  Vector3D orientacion;
  Vector3D accel;
  double zrad;
  double yrad;

  //Para calibracion
  double presentAccel;  //Para las Z
  double pastAccel;
  double presentError;  //Para X e Y
  double pastError;
  int cont;             //Para ambos
  bool sentido;
  bool eje;
  uint8_t calibState;

  Plataforma();
  double getAccel();
  double getError();
  void setAccel(Vector3D *v);
  void invierteSentido();
  void cambiaEje();
  bool calibrarPlat();
  void giraEje(float grados);
};

Plataforma::Plataforma(){
  presentAccel = 0;
  pastAccel = 0;
  cont = 0;
  sentido = false;
  eje = false;
  calibState = 0;
  
  zrad = 0;
  yrad = 0;
}

double Plataforma::getAccel(){
  return accel.z;
}

double Plataforma::getError(){
  double errorX = abs(accel.x);
  double errorY = abs(accel.y);
  return errorX + errorY;
}

void Plataforma::setAccel(Vector3D *v){
  accel.x = v->x;
  accel.y = v->y;
  accel.z = v->z;
}

void Plataforma::invierteSentido(){
  sentido = !sentido;
}

void Plataforma::cambiaEje(){
  eje = !eje;
}

bool Plataforma::calibrarPlat(){
  //Lectura de 10 acceleraciones y filtrado
  int tot = 10;
  Vector3D aux[tot];
  for(int i=0; i<tot; i++){
    bool RF_ok = getOrientRF(&aux[i]);
    while(RF_ok != 1){
      RF_ok = getOrientRF(&aux[i]);
    }
  }
  Vector3D media = V3D_media(aux,tot);
  setAccel(&media);

  //Inicio del algoritmo de calibracion
  if (calibState == 0){
    pastAccel = getAccel();
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
        if (presentAccel > accel_switch){
          calibState = 2;
        }
        else{
          calibState = 0;
        }
      }
    }
    pastAccel = presentAccel;
  }
  else if (calibState == 2){
    pastError = getError();
    cont = 0;
    calibState = 3;
  }
  else if (calibState == 3){
    presentError = getError();
    if (presentError < pastError){
      cont = 1;
    }
    else{
      if(cont == 0){
        invierteSentido();
      }
      else{
        cambiaEje();
        calibState = 2;
      }
    }
    pastError = presentError;
  }
  
  //Serial.println(accel.z);
  if(abs(accel.z) < accel_switch){
    //Mover los motores, y comprobar  que corresponde con respecto al giro de la 
    //plataforma. Segun eso, mover los motores de forma que el gradiente de gravedad 
    //en el eje Z sea ascendente hasta llegar a 10m/s^2
    
    giraEje(1);
    
    return false;  
  }
  else if (presentError > sensibilidad){
    giraEje(1);
    
    return false;
  }
  else{
    //apagar motores()//funcion para apagar motores para que la posicien absoluta de cero pasos coincida con al horizonte
    //Se hara con un relé 
    //Despues se debe hacer el setup de nuevo
    //setupMotor(ID_MOTOR_1,1000000,1000000,100,512000);
    //setupMotor(ID_MOTOR_2,1000000,1000000,100,512000);
    return true;
  } 
}

void Plataforma::giraEje(float grados){
  float rad = grados * deg2rad;
  if(!eje && !sentido){
      yrad = rad;
      zrad = 0;
    }
    else if(eje && !sentido){
      yrad = 0;
      zrad = rad;
    }
    else if(!eje && sentido){
      yrad = -rad;
      zrad = 0;
    }
    else if(eje && sentido){
      yrad = 0;
      zrad = -rad;
    }
    
  pasosMotor1 = calcularPasos2D(yrad, zrad, RESOLUCION, RADIO_POLEA, H, 333, 0, D_REF);
  pasosMotor2 = calcularPasos2D(yrad, zrad, RESOLUCION, RADIO_POLEA, H, 0, 333, D_REF);
  pasosMotor3 = calcularPasos2D(yrad, zrad, RESOLUCION, RADIO_POLEA, H, -333, 0, D_REF);
  pasosMotor4 = calcularPasos2D(yrad, zrad, RESOLUCION, RADIO_POLEA, H, 0, -333, D_REF);
  
  Serial.print("pasosMotor1: ");
  Serial.println(pasosMotor1);
  Serial.print("pasosMotor2: ");
  Serial.println(pasosMotor2);
  Serial.print("pasosMotor3: ");
  Serial.println(pasosMotor3);
  Serial.print("pasosMotor4: ");
  Serial.println(pasosMotor4);

  long maxVel1 = requestMaxVel(ID_MOTOR_1);
  long maxVel2 = requestMaxVel(ID_MOTOR_2);
  Serial.print("Max Velocity 1: ");
  Serial.println(maxVel1);
  Serial.print("Max Velocity 2: ");
  Serial.println(maxVel2);

  moverRelatEspera(pasosMotor1, ID_MOTOR_1); //movimientos relativos con espera
  moverRelatEspera(pasosMotor2, ID_MOTOR_2);
  //moverRelatEspera(pasosMotor3,ID_MOTOR_3);
  //moverRelatEspera(pasosMotor4,ID_MOTOR_4);
    
}
#endif
