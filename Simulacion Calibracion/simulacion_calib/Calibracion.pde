class Calibracion {
  float accel;
  float past_accel;
  int cont;
  
  float getAccel(){
    accel = imuMovil.accelZ;
    return(accel);
  }
  
  
}
