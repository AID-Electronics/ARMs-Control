
class Alarmas{
  PFont font;
  int textSize;
  int distText2upperLimmit;
  int rowHeight;
  float posX;
  float posY;
  StringList alarma;
  int[] estadoAlarma;
  
  Alarmas(float posX, float posY){
    this.posX = posX;
    this.posY = posY;
    textSize = 16;
    distText2upperLimmit = 18;
    rowHeight = 23;
    font = createFont("Arial",textSize,true);
    alarma = new StringList();
    alarma.append("Puerto COM (PC<>PLC)");
    alarma.append("IMU");
    alarma.append("CANbus");
    alarma.append("Encendido Motores");
    alarma.append("Setup motores");
    alarma.append("Comunicacion RF");
    alarma.append("Comunicacion PLCs M");
    alarma.append("Motor trifasico");
    alarma.append("Radar");
    alarma.append("Comunicacion PLCs S");
    
    estadoAlarma = new int[alarma.size()];
  }
  
  void draw(){
    if (serialError){
      estadoAlarma[0] = 2;
    }else{
      estadoAlarma[0] = 1;
    }
    for (int i = 0; i < alarma.size(); i++){
      if (estadoAlarma[i] == 0){
        fill(150);
      }
      else if (estadoAlarma[i] == 2){
        fill(255,0,0);
      }
      else{
        fill(0,255,0);
      }
      ellipse(posX,posY + distText2upperLimmit - 6 + rowHeight * i,10,10);
    }
    
    //Texto
    fill(0);
    for (int i = 0; i<alarma.size(); i++){
      String str = alarma.get(i);
      text(str, posX + 10, posY + distText2upperLimmit + rowHeight * i);    
    }
  }
}
