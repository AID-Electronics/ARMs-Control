
class Telemetria{
  PFont font;
  float posX;
  float posY;
  StringList data;
  
  Telemetria(float posX, float posY){
    this.posX = posX;
    this.posY = posY;
    font = createFont("Arial",14,true);
    data = new StringList();
  }
  
  void update(){
    data.clear();
    data.append("Dron");
    data.append(" - id: " + dron.id);
    data.append(" - velocidad: " + dron.vel);
    data.append(" - distancia: " + dron.dist);
    data.append(" - angulo: " + dron.ang);
    data.append("");
    
    data.append("Estado global: " + globalState);
    data.append("Estado local: " + localState);
    data.append("");
    
    data.append("Orientacion plataforma");
    data.append(" - angX = " + orientX);
    data.append(" - angY = " + orientY);
    data.append(" - angZ = " + orientZ);

  }
  
  void draw(){
    update();
    textAlign(LEFT);
    fill(0);
    float dY = 16;
    textFont(font,16);
    for (int i = 0; i<data.size(); i++){
      String str = data.get(i);
      text(str, posX, posY + dY * i);
    }    
  }
}
