
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
  void draw(){
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
