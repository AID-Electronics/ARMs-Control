#ifndef COMUNICACION_MAXI_H
#define COMUNICACION_MAXI_H

#define pinEstado A0

class Comunicacion_MAXI{
public:
  char buff[];
  
  void setup();
  bool receive();
};

void Comunicacion_MAXI::setup(){
  Serial3.begin(115200);
  Controllino_RS485Init();
  pinMode(pinEstado,OUTPUT);
}

bool Comunicacion_MAXI::receive() {
  // PORTJ = PORTJ & B10011111; // Ponemos nuestro puerto RS485 en modo lectura.

  bool flag = false;
  int i = 0;

  while (Serial3.available()){
  
    char token = Serial3.read();
    Serial.print (token);
    buff[i] = token;
    i++;

    if (!flag)
      flag = true;
  }
  
  buff[i] = '\0';
  return flag;

}

#endif
