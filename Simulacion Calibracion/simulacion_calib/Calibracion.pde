class Calibracion {
  float accel;
  float past_accel;
  int cont = 0;
  boolean invSentido = false;
  boolean eje = false;
  int state;

  float getAccel() {
    accel = imuMovil.accelZ;
    return(accel);
  }

  void mueveEje(float ang) {

    float dAng;
    if (invSentido == false) {
      dAng = ang;
    } else {
      dAng = -ang;
    }
    float angX = degrees(plat.angX);
    float angY = degrees(plat.angY);

    if (eje == false) {
      plat.orientacion(angX + dAng, angY);
    } else {
      plat.orientacion(angX, angY + dAng);
    }
  }

  void invierteSentido() {
    invSentido = !invSentido;
  }
  void cambiaEje() {
    eje = !eje;
  }

  void doCalib() {
    if (state == 0) {              //Estado 0
      past_accel = getAccel();
      mueveEje(1);
      cont = 0;
      state = 1;
    } else if (state == 1) {      //Estado 1
      getAccel();
      if (accel > past_accel) {
        cont = 1;
      } else if (accel < past_accel) {
        if (cont == 0) {
          invierteSentido();
        } else {
          cambiaEje();
          state = 0;
        }
      }
      past_accel = accel;
      if (accel >=9.9){
        mueveEje(0.05);
      }else if(accel >= 9){
        mueveEje(0.1);
      }else{
      mueveEje(0.5);
      }
    }
  }
}
