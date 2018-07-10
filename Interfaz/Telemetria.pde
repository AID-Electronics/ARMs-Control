
class Telemetria{
  PFont font;
  float posX;
  float posY;
  float columnWidth;
  StringList name;
  StringList data;
  
  Telemetria(float posX, float posY, float columnWidth){
    this.posX = posX;
    this.posY = posY;
    this.columnWidth = columnWidth;
    font = createFont("Arial",14,true);
    name = new StringList();
    data = new StringList();
    
    name.append("Dron");
    name.append(" - id");
    name.append(" - velocidad");
    name.append(" - distancia");
    name.append(" - angulo");
    name.append("");
    
    name.append("Estado global");
    name.append("Estado local");
    name.append("");
    
    name.append("Orientacion plataforma");
    name.append(" - angX");
    name.append(" - angY");
    name.append(" - angZ");
  }
  
  void update(){
    data.clear();
    data.append("");
    data.append(str(dron.id));
    data.append(str(dron.vel));
    data.append(str(dron.dist));
    data.append(str(dron.ang));
    data.append("");
    
    data.append(str(globalState));
    data.append(str(localState));
    data.append("");
    
    data.append("");
    data.append(str(orientX));
    data.append(str(orientY));
    data.append(str(orientZ));

  }
  
  void draw(){
    update();
    textAlign(LEFT);
    fill(0);
    float dY = 16+3;
    textFont(font,16);
    for (int i = 0; i<data.size(); i++){
      String str = name.get(i);
      text(str, posX, posY + dY * i);
      str = data.get(i);
      text(str, posX + columnWidth, posY + dY * i);
    }    
  }
}
