#ifndef COMUNICACION_MAXI_H
#define COMUNICACION_MAXI_H

#define pinEstado A0
#define bufferSize 10

class Comunicacion_MAXI{
public:
  char buff[bufferSize];
  int cont;
  bool startMsg;

  bool errorMotor;
  bool errorRadar;

  Comunicacion_MAXI();
  void setup();
  bool receive();
};

Comunicacion_MAXI::Comunicacion_MAXI(){
  cont = 0;
  startMsg = false;
  errorMotor = false;
  errorRadar = false;  
}

void Comunicacion_MAXI::setup(){
  Serial3.begin(115200);
  Controllino_RS485Init();
  pinMode(pinEstado,OUTPUT);
}

bool Comunicacion_MAXI::receive() {
  // PORTJ = PORTJ & B10011111; // Ponemos nuestro puerto RS485 en modo lectura.

  while (Serial3.available()){
  
    char token = Serial3.read();
    Serial.print (token);

    if (token == '$'){
      cont = 0;
      startMsg = true;
    }
    else if (token == ';'){
      buff[cont] = '\0';
      startMsg = false;
      return true;
    }
    else if (cont < bufferSize && startMsg){
      buff[cont] = token;
      cont++;
    }
  }
  return false;

}

#endif
