class Calibracion {
  float accel;
  float past_accel;
  int cont = 0;
  boolean invSentido = false;
  
  float getAccel(){
    accel = imuMovil.accelZ;
    return(accel);
  }
  
  void mueveEje(char c, float ang){
    
    if (c == 'X'){
      float dAng;
      if (invSentido == false){
        dAng = radians(ang);
      }else{
        dAng = -radians(ang);
      }
      plat.orientacion(plat.angX + dAng, plat.angY);
    }
    
    else if (c == 'Y'){
      float dAng;
      if (invSentido == false){
        dAng = radians(ang);
      }else{
        dAng = -radians(ang);
      }
      plat.orientacion(plat.angX, plat.angY + dAng);
    }
  }
  
  void invierteSentido(){
    invSentido = !invSentido;
  }
}
