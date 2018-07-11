class Alarmas{
  PFont font;
  float posX;
  float posY;
  StringList alarma;
  
  Alarmas(float posX, float posY){
    this.posX = posX;
    this.posY = posY;
    alarma = new StringList();
    
    alarma.append("IMU");
    alarma.append("CANbus");
    alarma.append("Encendido Motores");
    alarma.append("Setup motores");
    alarma.append("Comunicacion RF");
    alarma.append("Comunicacion PLCs Maestro");
    alarma.append("Motor trifasico");
    alarma.append("Radar");
    alarma.append("Comunicacion PLCs Esclavo");
  }
}
