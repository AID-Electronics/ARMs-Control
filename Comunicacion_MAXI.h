#ifndef COMUNICACION_MAXI_H
#define COMUNICACION_MAXI_H

#define pinEstado 2
#define bufferSize 10

class Comunicacion_MAXI{
public:
  char buff[bufferSize];
  int cont;
  bool startMsg;

  bool errorMotor;
  bool errorRadar;
  bool errorCom;
  bool comMotor;
  bool comRadar;
  bool comPLCs;

  Comunicacion_MAXI();
  void setup();
  bool receive();
  void printBuffer();
  void parseBuff();
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
  digitalWrite(pinEstado,LOW);
  
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

void Comunicacion_MAXI::printBuffer(){
  Serial.print(" Buffer: ");
  for (int i = 0; i < bufferSize; i++){
    Serial.print(buff[i]);
  }
  Serial.println();
}

void Comunicacion_MAXI::parseBuff(){
  if (buff[0] == 'E'){        //Error msg
    if (buff[1] == '1'){
      errorMotor = true;
    }
    else if (buff[1] == '0'){
      errorMotor = false;
    }
    if (buff[2] == '1'){
      errorRadar = true;
    }
    else if (buff[2] == '0'){
      errorRadar = false;
    }
    if (buff[3] == '1'){
      errorCom = true;
    }
    else if (buff[3] == '0'){
      errorCom = false;
    }
  }
  if (buff[0] == 'C'){        //Comunication msg
    if (buff[1] == '1'){
      comMotor = true;
    }
    else if (buff[1] == '0'){
      comMotor = false;
    }
    if (buff[2] == '1'){
      comRadar = true;
    }
    else if (buff[2] == '0'){
      comRadar = false;
    }
    if (buff[3] == '1'){
      comPLCs = true;
    }
    else if (buff[3] == '0'){
      comPLCs = false;
    }
  }
}
#endif
