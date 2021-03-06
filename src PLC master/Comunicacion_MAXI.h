#ifndef COMUNICACION_MAXI_H
#define COMUNICACION_MAXI_H

#define pinEstado 2
#define pinRequestData 3
#define pinAterrizaje A10
#define bufferSize 100

class Objetivo{
public:
  int32_t id;
  float vel;
  float dist;
  float ang;
  float intensidad;

  void reset(){id = 0; vel = 0; dist = 0; ang = 0; intensidad = 0;}
};

class Comunicacion_MAXI{
public:
  char buff[bufferSize];
  char auxBuff[bufferSize];
  uint8_t cont;
  uint8_t nDato;
  bool startMsg;

  bool errorMotor;
  bool errorRadar;
  bool errorCom;
  bool comMotor;
  bool comRadar;
  bool comPLCs;

  Objetivo dron;
  float velGiro;
  int estado;

  Comunicacion_MAXI();
  void setup();
  bool receive();
  void printBuffer();
  void parseBuff();
  bool printError();
  bool getError();
  void printData();
  void requestData();
  void resetMsg();
  void sendData2Interface();
  void setEstadoMarcha();
  void setEstadoParo();
  bool objAterrizado();
};

Comunicacion_MAXI::Comunicacion_MAXI(){
  cont = 0;
  nDato = 0;
  startMsg = false;
  errorMotor = false;
  errorRadar = false;
  errorCom = false;

  dron.id = 0;
  dron.vel = 0;
  dron.dist = 0;
  dron.ang = 0;
  dron.intensidad = 0;
}

void Comunicacion_MAXI::setup(){
  Controllino_RS485Init();
  pinMode(pinEstado,OUTPUT);
  digitalWrite(pinEstado,LOW);
  pinMode(pinRequestData,OUTPUT);
  digitalWrite(pinRequestData,LOW);
  pinMode(pinAterrizaje,INPUT);
}

bool Comunicacion_MAXI::receive() {
  // PORTJ = PORTJ & B10011111; // Ponemos nuestro puerto RS485 en modo lectura.

  while (Serial3.available()){
  
    char token = Serial3.read();
    //Serial.print (token);

    if (token == '$'){
      cont = 0;
      startMsg = true;
    }
    else if (token == ';'){
      buff[cont] = ',';
      buff[cont + 1] = '\0';
      cont++;
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
  Serial.print("Buffer: ");
  for (int i = 0; i < cont; i++){
    Serial.print(buff[i]);
  }
  Serial.println();
}

void Comunicacion_MAXI::parseBuff(){
  if (buff[0] == 'D'){        //Datos radar
    int j = 0;
    bool fin = false;
    for (int i = 1; i < bufferSize && !fin ; i++){
      if (buff[i] == ','){
        auxBuff[j] = '\0';
        if (nDato == 0){
          dron.id = strtod(auxBuff, NULL);
          //Serial.print("dron.id: ");
          //Serial.println(dron.id);
          nDato = 1;
          j = 0;
        }
        else if (nDato == 1){
          dron.vel = strtod(auxBuff, NULL);
          //Serial.print("dron.vel: ");
          //Serial.println(dron.vel);
          nDato = 2;
          j = 0;
        }
        else if (nDato == 2){
          dron.dist = strtod(auxBuff, NULL);
          //Serial.print("dron.dist: ");
          //Serial.println(dron.dist);
          nDato = 3;
          j = 0;
        }
        else if (nDato == 3){
          dron.ang = strtod(auxBuff, NULL);
          //Serial.print("dron.ang: ");
          //Serial.println(dron.ang);
          nDato = 4;
          j = 0;
        }
        else if (nDato == 4){
          dron.intensidad = strtod(auxBuff, NULL);
          //Serial.print("dron.intensidad: ");
          //Serial.println(dron.intensidad);
          nDato = 0;
          j = 0;
          fin = true;
        }
      }
      else {
        auxBuff[j] = buff[i];
        j++;
      }
    }
  }
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

bool Comunicacion_MAXI::printError() {
  Serial.print("\terrorMotor: ");
  Serial.println(errorMotor);
  Serial.print("\terrorRadar: ");
  Serial.println(errorRadar);
  Serial.print("\terrorCom: ");
  Serial.println(errorCom);
}

bool Comunicacion_MAXI::getError(){
  bool error = errorMotor || errorRadar || errorCom;
  return error;
}

void Comunicacion_MAXI::printData(){
  Serial.print("dron.id: ");
  Serial.println(dron.id);
  Serial.print("dron.vel: ");
  Serial.println(dron.vel);
  Serial.print("dron.dist: ");
  Serial.println(dron.dist);
  Serial.print("dron.ang: ");
  Serial.println(dron.ang);
  Serial.print("dron.intensidad: ");
  Serial.println(dron.intensidad);
}

void Comunicacion_MAXI::requestData(){
  bool msgReceived = false;
  digitalWrite(pinRequestData,HIGH);
  delay (30);
  digitalWrite(pinRequestData,LOW);
  uint32_t comienzo = millis();
  while (!msgReceived && millis() - comienzo < 100){
    if (receive()){
     parseBuff();
     msgReceived = true;
    }
  }
}

void Comunicacion_MAXI::resetMsg(){
  Serial.println("\tReset PLC MAXI");
  digitalWrite(pinEstado,LOW);
  digitalWrite(pinRequestData,HIGH);
  delay(10);
  digitalWrite(pinRequestData,LOW);
}

void Comunicacion_MAXI::sendData2Interface(){
  Serial.print("#Dron: ");
  Serial.print(dron.id);
  Serial.print(",");
  Serial.print(dron.vel);
  Serial.print(",");
  Serial.print(dron.dist);
  Serial.print(",");
  Serial.print(dron.ang);
  Serial.print(",");
  Serial.print(dron.intensidad);
  Serial.println();

  Serial.print("#Platform: ");
  Serial.print(velGiro);
  Serial.print(",");
  Serial.print(estado);
  Serial.println();
}

void Comunicacion_MAXI::setEstadoMarcha(){
  digitalWrite(pinEstado,HIGH);
}

void Comunicacion_MAXI::setEstadoParo(){
  digitalWrite(pinEstado,LOW);
}

bool Comunicacion_MAXI::objAterrizado(){
  if(digitalRead(pinAterrizaje)){
    return true;
  }
  else{
    return false;
  }
}
#endif
