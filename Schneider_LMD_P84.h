#ifndef Schneider_LMD_P84_H
#define Schneider_LMD_P84_H

#include <Arduino.h>
#include "Canbus.h"

#define holdCurrent_percent 100

bool emergCAN = false;
bool motor1_ok = true;
bool motor2_ok = true;
//bool motor3_ok = true;
//bool motor4_ok = true;

union Paquete{
  byte b[4];
  int32_t i;
};

void traduce(byte *leng, byte *buf, unsigned long ID){
  bool envio = 0;   // Se pone a 1 cuando el receptor del mensaje es el motor
  // Check IDs
  if      (ID == 0x610){
    Serial.println("\t Mensaje a motor 1");
    envio = 1;
  }
  else if (ID == 0x611){
    Serial.println("\t Mensaje a motor 2");
    envio = 1;
  }
  else if (ID == 0x590){
    Serial.println("\t Respuesta motor 1");
  }
  else if (ID == 0x591){
    Serial.println("\t Respuesta motor 2");
  }
  else{
    Serial.println("\t ID recibida incorrecta");
  }

  // Check msg type - buf[0]
  if      (buf[0]==0x2F||buf[0]==0x2B||buf[0]==0x27|buf[0]==0x23){
    Serial.println("\t Write request");
  }
  else if (buf[0]==0x4F||buf[0]==0x4B||buf[0]==0x47|buf[0]==0x43){
    Serial.println("\t Read response: OK");
  }
  else if (buf[0]==0x60){
    Serial.println("\t Write response: OK");
  }
  else if (buf[0]==0x40){
    Serial.println("\t Read request");
  }
  else if (buf[0]==0x80){
    Serial.println("\t Response: ERROR");
  }
  else{
    Serial.println("\t UNKNOWN MSG TYPE");
  }

  // Check comand - buf[1] & buf[2]
  if      (buf[1]==0x83 && buf[2]==0x60){   //Profile acceleration
    if (envio == 1){
      Serial.print("\t Profile acceleracion: ");
      Paquete p;
      p.b[0] = buf[4];
      p.b[1] = buf[5];
      p.b[2] = buf[6];
      p.b[3] = buf[7];
      Serial.print(p.i);
      Serial.println(" step/sec^2");
    }
    else{
      Serial.println("\t Profile acceleracion");
    }
  }
  else if (buf[1]==0x84 && buf[2]==0x60){   //Profile deceleration
    if (envio == 1){
      Serial.print("\t Profile deceleration: ");
      Paquete p;
      p.b[0] = buf[4];
      p.b[1] = buf[5];
      p.b[2] = buf[6];
      p.b[3] = buf[7];
      Serial.print(p.i);
      Serial.println(" step/sec^2");
    }
    else{
      Serial.println("\t Profile deceleration");
    }
  }
  else if (buf[1]==0x81 && buf[2]==0x60){   //Profile velocity
    if (envio == 1){
      Serial.print("\t Profile velocity: ");
      Paquete p;
      p.b[0] = buf[4];
      p.b[1] = buf[5];
      p.b[2] = buf[6];
      p.b[3] = buf[7];
      Serial.print(p.i);
      Serial.println(" step/sec");
    }
    else{
      Serial.println("\t Profile velocity");
    }
  }
  else if (buf[1]==0x04 && buf[2]==0x22){   //Run current
    if (envio == 1){
      Serial.print("\t Run current: ");
      Paquete p;
      p.b[0] = buf[4];
      p.b[1] = buf[5];
      p.b[2] = buf[6];
      p.b[3] = buf[7];
      Serial.print(p.i);
      Serial.println(" %");
    }
    else{
      Serial.println("\t Run current");
    }
  }
  else if (buf[1]==0x40 && buf[2]==0x60){   //State machine
    if (envio == 1){
      Serial.print("\t Control word (state machine) - ");
      if      (buf[4]==0x06 && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Ready to switch on");
      }
      else if (buf[4]==0x07 && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Swiched on");
      }
      else if (buf[4]==0x0F && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Operation enable");
      }
      // Perform move
      else if (buf[4]==0x1F && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Set bit 4 to 1 (absolute mode/finish)");
      }
      else if (buf[4]==0x0F && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Set bit 4 to 0 (absolute mode/finish)");
      }
      else if (buf[4]==0x3F && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Set bit 4 to 1 (absolute mode/immediate)");
      }
      else if (buf[4]==0x2F && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Set bit 4 to 0 (absolute mode/immediate)");
      }
      else if (buf[4]==0x5F && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Set bit 4 to 1 (relative mode/finish)");
      }
      else if (buf[4]==0x4F && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Set bit 4 to 0 (relative mode/finish)");
      }
      else if (buf[4]==0x7F && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Set bit 4 to 1 (relative mode/immediate)");
      }
      else if (buf[4]==0x6F && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Set bit 4 to 0 (relative mode/immediate)");
      }
      else{
        Serial.println("\t UNKNOWN STATE MACHINE");
      }
    }
    else{
      Serial.println("\t Control word (state machine)");
    }
  }
  else if (buf[1]==0x60 && buf[2]==0x60){   //Operation mode
    if (envio == 1){
      Serial.print("\t Mode of operation: ");
      if      (buf[4]==0x01 && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Profile position");
      }
      else if (buf[4]==0x02 && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Profile velocity");
      }
      else if (buf[4]==0x03 && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Homing");
      }
      else{
        Serial.println("UNKNOWN");
      }
    }
    else{
      Serial.println("\t Mode of operation");
    }
  }
  else if (buf[1]==0x7A && buf[2]==0x60){   //Target position
    if (envio == 1){
      Serial.print("\t Target position: ");
      Paquete p;
      p.b[0] = buf[4];
      p.b[1] = buf[5];
      p.b[2] = buf[6];
      p.b[3] = buf[7];
      Serial.print(p.i);
      Serial.println(" steps");
    }
    else{
      Serial.println("\t Target position");
    }
  }
  else if (buf[1]==0x7E && buf[2]==0x60){   //Polarity
    if (envio == 1){
      Serial.print("\t Polarity: ");
      if (buf[4]==0xFF && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Reverse");
      }
      else if (buf[4]==0x7F && buf[5]==0x00 && buf[6]==0x00 && buf[7]==0x00){
        Serial.println("Forward");
      }
      else{
        Serial.println("UNKNOWN");
      }
    }
    else{
      Serial.println("\t Polarity");
    }
  }
  else if (buf[1]==0x62 && buf[2]==0x60){   //Request position
    if (envio == 1){
      Serial.println("\t Request position");
    }
    else{
      Serial.print("\t Actual position: ");
      Paquete p;
      p.b[0] = buf[4];
      p.b[1] = buf[5];
      p.b[2] = buf[6];
      p.b[3] = buf[7];
      Serial.println(p.i);
    }
  }
  else{
    Serial.println("\t UNKNOWN COMMAND");
  }

  // buf[3] is allways empty

}

bool comprobarRespuesta(long ID){
  int flag_receive=0;
  int i=0;
  
  while(!flag_receive && i<50){
    flag_receive=receive();
    i++;
  }
  
  //Serial.println(i);
  
  if (flag_receive == 1){
    //Comprobamos emergencias
    if (canID == 0x90){
      emergCAN = true;
      motor1_ok = false;
      return false;
    }
    if (canID == 0x91){
      emergCAN = true;
      motor2_ok = false;
      return false;
    }

    if (ID != canID + 128){ //128 = 16*8 (ID is HEX)
      //Serial.println("IDs no coinceden");
      return false;
    }
    else if(buffRespuesta[0]==0x80){
      return false;
    }
    else if(buffRespuesta[0]==0x60){
      return true;
    }
    else if (buffRespuesta[0]==0x4F||buffRespuesta[0]==0x4B||buffRespuesta[0]==0x47|buffRespuesta[0]==0x43){
      return true;
    }
  }
  else{
    return false;
  }
}

bool EnviarMSG(char buff[], long ID){
  bool rec_OK = 0; 
  
  for (int contError = 0; contError < 3 && !rec_OK && !emergCAN; contError++){
    sending(buff,ID);
    
    if(comprobarRespuesta(ID) == 1){
      rec_OK = 1;
//      Serial.println("MSG RECIBIDO CORRECTAMENTE");
//      Serial.println("");
    }
    else {
      if (emergCAN){
        Serial.println("Mensaje emergencia CAN");
        delay(5);
      }
      else{
        //Serial.println("ERROR EN MSG");
        limpiaBuffer();
      }
    }
  }
  return rec_OK;
}

bool SetCurrent (int porcentaje, long ID){
  Paquete p;
  p.i = porcentaje;
  char SetcurrentUSE[]={0x2F,0x04,0x22,0x00,p.b[0],0x00,0x00,0x00};
  return EnviarMSG(SetcurrentUSE,ID);
}

bool setHoldCurrent (int porcentaje, long ID){
  Paquete p;
  p.i = porcentaje;
  char holdCurrent[]={0x2F,0x05,0x22,0x00,p.b[0],0x00,0x00,0x00};
  return EnviarMSG(holdCurrent,ID);
}

bool maxVelocity (long velocity, long ID){
  Paquete p;
  p.i = velocity;
  char Maxvel[]={0x23,0x81,0x60,0x00,p.b[0],p.b[1],p.b[2],p.b[3]};
  return EnviarMSG(Maxvel,ID);
}

bool setDeccel (uint32_t decel, long ID){
  Paquete p;
  p.i = decel;
  char SetDecel[]={0x23,0x84,0x60,0x00,p.b[0],p.b[1],p.b[2],p.b[3]};
  return EnviarMSG(SetDecel,ID);
}

bool SetAccel (long accel, long ID){
  Paquete a;
  a.i = accel;
  char SetAccel[]={0x23,0x83,0x60,0x00,a.b[0],a.b[1],a.b[2],a.b[3]};
  return EnviarMSG(SetAccel,ID);
}

bool SetProfile(int profile, long ID ){
  byte pro;
  switch(profile){
    case 1:
     pro=0x01;
     break;
    case 2:
     pro=0x03;
     break;
    case 3:
     pro=0x06;
     break;
    case 4:
     pro=0x04;
     break;
    default:
      pro=0x00;
      break;  
  }
  char ProfileSet[]={0x2F,0x60,0x60,0x00,pro,0x00,0x00,0x00};
  EnviarMSG(ProfileSet,ID);
}

long requestPos(long ID){
  char leerPos[8]={0x40,0x62,0x60,0x00,0x00,0x00,0x00,0x00};
  EnviarMSG(leerPos,ID);
  
  Paquete p;
  p.b[0] = buffRespuesta[4];
  p.b[1] = buffRespuesta[5];
  p.b[2] = buffRespuesta[6];
  p.b[3] = buffRespuesta[7];
  return p.i;
}

long requestAccel (long ID){
  char GetAccel[]={0x40,0x83,0x60,0x00,0x00,0x00,0x00,0x00};
  EnviarMSG(GetAccel,ID);

  Paquete p;
  p.b[0] = buffRespuesta[4];
  p.b[1] = buffRespuesta[5];
  p.b[2] = buffRespuesta[6];
  p.b[3] = buffRespuesta[7];
  return p.i;
}

long requestDecel (long ID){
  char GetDecel[]={0x40,0x84,0x60,0x00,0x00,0x00,0x00,0x00};
  EnviarMSG(GetDecel,ID);

  Paquete p;
  p.b[0] = buffRespuesta[4];
  p.b[1] = buffRespuesta[5];
  p.b[2] = buffRespuesta[6];
  p.b[3] = buffRespuesta[7];
  return p.i;
}

long requestMaxVel (long ID){
  char GetMaxVel[]={0x40,0x81,0x60,0x00,0x00,0x00,0x00,0x00};
  EnviarMSG(GetMaxVel,ID);

  Paquete p;
  p.b[0] = buffRespuesta[4];
  p.b[1] = buffRespuesta[5];
  p.b[2] = buffRespuesta[6];
  p.b[3] = buffRespuesta[7];
  return p.i;
}

long requestVin(long ID){
  char leerVin[8]={0x40,0x15,0x20,0x01,0x00,0x00,0x00,0x00};
  EnviarMSG(leerVin,ID);
  Paquete p;
  p.b[0] = buffRespuesta[4];
  p.b[1] = buffRespuesta[5];
  p.b[2] = buffRespuesta[6];
  p.b[3] = buffRespuesta[7];
  return p.i;
}

long requestBoardTemp(long ID){
  char leerBoardTemp[8]={0x40,0x18,0x20,0x01,0x00,0x00,0x00,0x00};
  EnviarMSG(leerBoardTemp,ID);
  Paquete p;
  p.b[0] = buffRespuesta[4];
  p.b[1] = buffRespuesta[5];
  p.b[2] = buffRespuesta[6];
  p.b[3] = buffRespuesta[7];
  return p.i;
}

long requestBridgeTemp(long ID){
  char leerBridgeTemp[8]={0x40,0x19,0x20,0x01,0x00,0x00,0x00,0x00};
  EnviarMSG(leerBridgeTemp,ID);
  Paquete p;
  p.b[0] = buffRespuesta[4];
  p.b[1] = buffRespuesta[5];
  p.b[2] = buffRespuesta[6];
  p.b[3] = buffRespuesta[7];
  return p.i;
}

long requestHoldCurrent(long ID){
  char leerHoldCurrent[8]={0x40,0x05,0x22,0x00,0x00,0x00,0x00,0x00};
  EnviarMSG(leerHoldCurrent,ID);
  Paquete p;
  p.b[0] = buffRespuesta[4];
  p.b[1] = buffRespuesta[5];
  p.b[2] = buffRespuesta[6];
  p.b[3] = buffRespuesta[7];
  return p.i;
}

bool setupMotor(long ID_motor,uint32_t Acel,uint32_t Decel, int current ,uint32_t MaxVel ){
    bool bitError = false;
    //instrucciones de configuración
    //-- Aceleracion --
    SetAccel(Acel,ID_motor);
    long accel = requestAccel(ID_motor);
    Serial.print("\tAceleracion: ");
    Serial.println(accel);
    if (accel == Acel){
      //Serial.println("\tOK");
    }
    else{
      //Serial.println("\tX");
      bitError = true;
    }
    //-- Deceleracion --
    setDeccel(Decel,ID_motor);
    long decel = requestDecel(ID_motor);
    Serial.print("\tDeceleracion: ");
    Serial.println(decel);
    if (decel == Decel){
      //Serial.println("\tOK");
    }
    else{
      //Serial.println("\tX");
      bitError = true;
    }
    //-- Velocidad maxima --
    maxVelocity(MaxVel, ID_motor);
    long vel = requestMaxVel(ID_motor);
    Serial.print("\tMax Velocity: ");
    Serial.println(vel);
    if (vel == MaxVel){
      //Serial.println("\tOK");
    }
    else{
      //Serial.println("\tX");
      bitError = true;
    }
    //-- % de corriente --
    SetCurrent(current, ID_motor);
    setHoldCurrent(holdCurrent_percent,ID_motor);
    long hCurrent = requestHoldCurrent(ID_motor);
    Serial.print("\tholdCurrent: ");
    Serial.println(hCurrent);
  

    if (bitError){
      return false;
    }
    
    //instrucciones de cambio de estado
    const char ReadytoSwitch[]={0x2B,0x40,0x60,0x00,0x06,0x00,0x00,0x00};
    const char SwitchON[]={0x2B,0x40,0x60,0x00,0x07,0x00,0x00,0x00};
    const char OpEnable[]={0x2B,0x40,0x60,0x00,0x0F,0x00,0x00,0x00};
    EnviarMSG(ReadytoSwitch,ID_motor);
    EnviarMSG(SwitchON,ID_motor);
    EnviarMSG(OpEnable,ID_motor);
    SetProfile(1,ID_motor); //1=modo posición, 2=modo velocidad, 3=modo homing, 4=modo torque
    
    if (!bitError){
      return true;
    }
}

void setPolarity (long pasos, long ID){
  char polarity[8]={0x2F,0x7E,0x60,0x00,0xC0,0x00,0x00,0x00};
  if (pasos<0){
    polarity[4]=0xFF;
  }
  else {
    polarity[4]=0x7F;
  }
  EnviarMSG(polarity,ID);
}

void moverAbsEspera(long pos,long ID){
  Serial.print("Movimiento absoluto con espera \t- Posicion: ");
  Serial.println(pos);
  Paquete p;
  p.i = pos;
  
  char posicion[]={0x23,0x7A,0x60,0x00,p.b[0],p.b[1],p.b[2],p.b[3]};
  char tipo_mov1[]={0x2B,0x40,0x60,0x00,0x1F,0x00,0x00,0x00};
  char tipo_mov2[]={0x2B,0x40,0x60,0x00,0x0F,0x00,0x00,0x00};
  
  EnviarMSG(posicion,ID);
  EnviarMSG(tipo_mov1,ID);
  EnviarMSG(tipo_mov2,ID);
}

void moverAbsInmediato(long pos,long ID){
  //Serial.print("Movimiento absoluto sin espera \t- Posicion: ");
  //Serial.println(pos);
  Paquete p;
  p.i = pos;
  
  char posicion[]={0x23,0x7A,0x60,0x00,p.b[0],p.b[1],p.b[2],p.b[3]};
  char tipo_mov1[]={0x2B,0x40,0x60,0x00,0x3F,0x00,0x00,0x00};
  char tipo_mov2[]={0x2B,0x40,0x60,0x00,0x2F,0x00,0x00,0x00};
  
  EnviarMSG(posicion,ID);
  EnviarMSG(tipo_mov1,ID);
  EnviarMSG(tipo_mov2,ID);
}

void moverRelatEspera(long pasos,long ID){
  Serial.print("Movimiento relativo con espera \t- Pasos: ");
  Serial.println(pasos);
  Paquete p;
  p.i = pasos;
  
  char nPasos[]={0x23,0x7A,0x60,0x00,p.b[0],p.b[1],p.b[2],p.b[3]};
  char tipo_mov1[]={0x2B,0x40,0x60,0x00,0x5F,0x00,0x00,0x00};
  char tipo_mov2[]={0x2B,0x40,0x60,0x00,0x4F,0x00,0x00,0x00};
  
  EnviarMSG(nPasos,ID);
  EnviarMSG(tipo_mov1,ID);
  EnviarMSG(tipo_mov2,ID);
}

void moverRelatInmediato(long pasos,long ID){
  Serial.print("Movimiento relativo sin espera \t- Pasos: ");
  Serial.println(pasos);
  Paquete p;
  p.i = pasos;
  
  char nPasos[]={0x23,0x7A,0x60,0x00,p.b[0],p.b[1],p.b[2],p.b[3]};
  char tipo_mov1[]={0x2B,0x40,0x60,0x00,0x7F,0x00,0x00,0x00};
  char tipo_mov2[]={0x2B,0x40,0x60,0x00,0x6F,0x00,0x00,0x00};
  
  EnviarMSG(nPasos,ID);
  EnviarMSG(tipo_mov1,ID);
  EnviarMSG(tipo_mov2,ID);
}

bool compruebaCAN(){
  bool flag_receive = receive();
  if (flag_receive){
    if(canID == 0x710){
      motor1_ok = true;
      Serial.println("Motor 1 OK");
    }
    else if (canID == 0x711){
      motor2_ok = true;
      Serial.println("Motor 2 OK");
    }
    else if (canID == 0x90){
      emergCAN = true;
      motor1_ok = false;
      Serial.println("Motor 1 NOT OK");
    }
    else if (canID == 0x91){
      emergCAN = true;
      motor2_ok = false;
      Serial.println("Motor 2 NOT OK");
    }
      
    if (motor1_ok && motor2_ok){
      delay (100);
      limpiaBuffer();
      emergCAN = false;
      return true;
    }
  }
  return false;
}


#endif
