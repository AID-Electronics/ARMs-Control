class Calibracion {
  float accel;
  float past_accel;
  int cont = 0;
  boolean invSentido = false;
  boolean eje = false;
  
  float getAccel(){
    accel = imuMovil.accelZ;
    return(accel);
  }
  
  void mueveEje(float ang){
    
    float dAng;
    if (invSentido == false){
      dAng = radians(ang);
    }
    else{
      dAng = -radians(ang);
    }
    
    if (eje == false){
      plat.orientacion(plat.angX + dAng, plat.angY);
    } 
    else {
      plat.orientacion(plat.angX, plat.angY + dAng);
    }
  }
  
  void invierteSentido(){
    invSentido = !invSentido;
  }
  void cambiaEje(){
    eje = !eje;
  }
}
