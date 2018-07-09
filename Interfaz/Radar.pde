
class Radar{
  float r;
  float amplitud; //rad
  int posX;
  int posY;
  
  Objetivo obj;
  
  Radar(int posX, int posY, float radio, float angAmplitud){
    this.posX = posX;
    this.posY = posY;
    this.r = radio;
    this.amplitud = radians(angAmplitud);
  }
  
  void draw(){
    noStroke();
    fill(50,255,50);
    arc(posX, posY, r, r, -amplitud/2, amplitud/2, PIE);
    fill(0,240,0);
    arc(posX, posY, r/3*2, r/3*2, -amplitud/2, amplitud/2, PIE);
    fill(50,255,50);
    arc(posX, posY, r/3, r/3, -amplitud/2, amplitud/2, PIE);
    stroke(0);
    noFill();
    arc(posX, posY, r, r, -amplitud/2, amplitud/2, PIE);
  }
}
