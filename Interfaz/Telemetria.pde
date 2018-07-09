
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
}
