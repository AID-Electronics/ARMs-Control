
class Telemetria{
  PFont font;
  float posX;
  float posY;
  float nameColumnWidth;
  float dataColumnWidth;
  float rowHeight;
  int margenIzquierdo;
  int distText2upperLimmit;
  StringList name;
  StringList data;
  int textSize;
  
  Telemetria(float posX, float posY){
    this.posX = posX;
    this.posY = posY;
    this.nameColumnWidth = 160;
    this.dataColumnWidth = 40;
    rowHeight = 23;
    margenIzquierdo = 10;
    distText2upperLimmit = 18;
    
    name = new StringList();
    data = new StringList();
    textSize = 16;
    font = createFont("Arial",textSize,true);
    
    name.append("Dron");
    name.append(" - id");
    name.append(" - velocidad");
    name.append(" - distancia");
    name.append(" - angulo");
    
    name.append("Orientacion plataforma");
    name.append(" - angX");
    name.append(" - angY");
    name.append(" - angZ");
    
    name.append("Estados");
    name.append(" - global");
    name.append(" - local");
  }
  
  void update(){
    data.clear();
    data.append("");
    data.append(str(dron.id));
    data.append(str(dron.vel));
    data.append(str(dron.dist));
    data.append(str(dron.ang));
    data.append("");
    
    data.append(str(orientX));
    data.append(str(orientY));
    data.append(str(orientZ));
    
    data.append("");
    data.append(str(globalState));
    data.append(str(localState));

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
    rect(posX, posY, nameColumnWidth + dataColumnWidth, rowHeight * data.size());
    line(posX, posY, posX + nameColumnWidth + dataColumnWidth, posY);
    for (int i = 0; i<data.size(); i++){
      strokeWeight(1);
      line(posX, posY + dY * i, posX + nameColumnWidth + dataColumnWidth, posY + dY * i);
      if (i + 1 == data.size()){
        line(posX, posY + dY + dY * i, posX + nameColumnWidth + dataColumnWidth, posY + dY + dY * i);
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
      
    }
  }
}
