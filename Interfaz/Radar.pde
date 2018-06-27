
class Radar{
  float r;
  float amplitud; //rad
  int posX;
  int posY;
  
  Radar(int posX, int posY, float radio, float angAmplitud){
    this.posX = posX;
    this.posY = posY;
    this.r = radio;
    this.amplitud = radians(angAmplitud);
  }
  
  void draw(){
    fill(50,255,50);
    arc(posX, posY, r, r, -amplitud/2, amplitud/2, PIE);
  }
}
