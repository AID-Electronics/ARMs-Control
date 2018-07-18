
class Telemetria{
  PFont font;
  float posX;
  float posY;
  float nameColumnWidth;
  float dataColumnWidth;
  float unitsColumnWidth;
  float rowHeight;
  int margenIzquierdo;
  int distText2upperLimmit;
  StringList name;
  StringList data;
  StringList units;
  int textSize;
  
  Telemetria(float posX, float posY){
    this.posX = posX;
    this.posY = posY;
    this.nameColumnWidth = 160;
    this.dataColumnWidth = 80;
    this.unitsColumnWidth = 60;
    rowHeight = 23;
    margenIzquierdo = 10;
    distText2upperLimmit = 18;
    
    name = new StringList();
    data = new StringList();
    units = new StringList();
    textSize = 16;
    font = createFont("Arial",textSize,true);
    
    name.append("Dron");
    name.append(" - id");
    name.append(" - velocidad");
    name.append(" - distancia");
    name.append(" - angulo");
    name.append(" - intensidad");
    
    name.append("Orientacion plataforma");
    name.append(" - angX");
    name.append(" - angY");
    name.append(" - angZ");
    
    name.append("Estados");
    name.append(" - global");
    name.append(" - local");
    
    name.append("Temperatura");
    name.append(" - motor 1");
    name.append(" - motor 2");
    
    name.append(" Velocidad giro");
    name.append(" Estado Maxi");
    
    units.append("Units");
    units.append("");
    units.append("km/h");
    units.append("m");
    units.append("deg");
    units.append("");
    units.append("");
    
    units.append("deg");
    units.append("deg");
    units.append("deg");
    
    units.append("");
    units.append("");
    units.append("");
    
    units.append("");
    units.append("°C");
    units.append("°C");
    
    units.append("");
    units.append("");
    
  }
  
  void update(){
    data.clear();
    data.append("");
    data.append(str(dron.id));
    data.append(str(dron.vel));
    data.append(str(dron.dist));
    data.append(str(dron.ang));
    data.append(str(dron.intensidad));
    data.append("");
    
    data.append(nf(orientX,0,2));
    data.append(nf(orientY,0,2));
    data.append(nf(orientZ,0,2));
    
    data.append("");
    data.append(str(globalState));
    data.append(str(localState));
    
    data.append("");
    data.append(str(tempM1));
    data.append(str(tempM2));
    
    data.append(str(velGiro));
    data.append(str(state));

  }
  
  void draw(){
    update();
    textAlign(LEFT);
    fill(0);
    float dY = rowHeight;
    textFont(font,textSize);
    
    //Creacion de la tabla
    fill(255);
    rectMode(CORNER);
    rect(posX, posY, nameColumnWidth + dataColumnWidth + unitsColumnWidth, rowHeight * data.size());
    line(posX, posY, posX + nameColumnWidth + dataColumnWidth + unitsColumnWidth, posY);
    for (int i = 0; i<data.size(); i++){
      strokeWeight(1);
      line(posX, posY + dY * i, posX + nameColumnWidth + dataColumnWidth + unitsColumnWidth, posY + dY * i);
      if (i + 1 == data.size()){
        line(posX, posY + dY + dY * i, posX + nameColumnWidth + dataColumnWidth + unitsColumnWidth, posY + dY + dY * i);
      }
    }
    line(posX, posY, posX, posY + rowHeight * data.size());
    line(posX + nameColumnWidth, posY, posX + nameColumnWidth, posY + rowHeight * data.size());
    line(posX + nameColumnWidth + dataColumnWidth, posY, posX + nameColumnWidth + dataColumnWidth, posY + rowHeight * data.size());
    
    //Se rellena con los datos
    fill(0);
    for (int i = 0; i<data.size(); i++){
      String str = name.get(i);
      text(str, posX + margenIzquierdo, posY + distText2upperLimmit + dY * i);
      str = data.get(i);
      text(str, posX + nameColumnWidth + margenIzquierdo, posY + distText2upperLimmit + dY * i);
      str = units.get(i);
      text(str, posX + nameColumnWidth + dataColumnWidth + margenIzquierdo, posY + distText2upperLimmit + dY * i);
    }
  }
}
