  
class Radar{
  float d;
  float amplitud; //rad
  int posX;
  int posY;
  
  float maxDist;
  
  Radar(int posX, int posY, float radio, float angAmplitud, float alcance){
    this.posX = posX;
    this.posY = posY;
    this.d = radio * 2;
    this.amplitud = radians(angAmplitud);
    this.maxDist = alcance;
  }
  
  void draw(Objetivo obj){
    noStroke();
    fill(50,255,50);
    arc(posX, posY, d, d, -amplitud/2, amplitud/2, PIE);
    fill(0,240,0);
    arc(posX, posY, d/3*2, d/3*2, -amplitud/2, amplitud/2, PIE);
    fill(50,255,50);
    arc(posX, posY, d/3, d/3, -amplitud/2, amplitud/2, PIE);
    stroke(0);
    noFill();
    arc(posX, posY, d, d, -amplitud/2, amplitud/2, PIE);
    
    float factorEscala = maxDist/d*2;
    println(factorEscala);
    obj.draw(posX,posY,factorEscala);
  }
}
