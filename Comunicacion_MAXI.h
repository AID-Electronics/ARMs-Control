#ifndef COMUNICACION_MAXI_H
#define COMUNICACION_MAXI_H

#define pinEstado A0;

class Comunicacion_MAXI{

  void setup();
}

void Comunicacion_MAXI::setup(){
  Serial3.begin(115200);
  Controllino_RS485Init();
  pinMode(pinEstado,OUTPUT);
}

#endif
