class Alarmas{
  PFont font;
  int textSize;
  int distText2upperLimmit;
  float posX;
  float posY;
  StringList alarma;
  
  Alarmas(float posX, float posY){
    this.posX = posX;
    this.posY = posY;
    textSize = 16;
    distText2upperLimmit = 18;
    font = createFont("Arial",textSize,true);
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
  
  void draw(){
    for (int i = 0; i < alarma.size(); i++){
      fill(255,0,0);
      ellipse(posX,posY,10,10);
    }
    
    //Texto
    fill(0);
    for (int i = 0; i<alarma.size(); i++){
      String str = alarma.get(i);
      text(str, posX, posY + distText2upperLimmit + textSize * i);    
    }
  }
}
