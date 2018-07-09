
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
    String str[] = new String[5];
    str[0] = "Dron";
    str[1] = "id: " + dron.id;
    str[2] = "velocidad: " + dron.vel;
    str[3] = "distancia: " + dron.dist;
    str[4] = "angulo: " + dron.ang;
    
    data.clear();
    for(int i = 0; i < 5; i++){
      data.append(str[i]);
    }
  }
  
  void draw(){
    update();
    textAlign(LEFT);
    fill(0);
    float dY = 16;
    textFont(font,16);
    for (int i = 0; i<5; i++){
      String str = data.get(i);
      text(str, posX, posY + dY * i);
    }    
  }
}
