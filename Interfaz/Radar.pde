  
class Radar{
  float d;
  float amplitud; //rad
  int posX;
  int posY;
  
  float maxDist;
  
  
  PFont font;
  String str;
  int txtSize;
  
  Radar(int posX, int posY, float radio, float angAmplitud, float alcance){
    this.posX = posX;
    this.posY = posY;
    this.d = radio * 2;
    this.amplitud = radians(angAmplitud);
    this.maxDist = alcance;
    txtSize = 16;
    font = createFont("Arial",txtSize,true);
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
    //println(factorEscala);
    obj.draw(posX,posY,factorEscala);
    
    //Texto
    float dist2reff_X = maxDist*cos(amplitud/2);
    float dist2reff_Y = maxDist*sin(amplitud/2);
    dist2reff_X /= factorEscala;
    dist2reff_Y /= factorEscala;
    str = nf(int(maxDist),0,0);
    str += "m";
    fill(0);
    textAlign(RIGHT,BOTTOM);
    textFont(font,txtSize);
    text(str, posX + dist2reff_X, posY - dist2reff_Y);
    
    dist2reff_X = maxDist/3*2*cos(amplitud/2);
    dist2reff_Y = maxDist/3*2*sin(amplitud/2);
    dist2reff_X /= factorEscala;
    dist2reff_Y /= factorEscala;
    str = nf(int(maxDist/3*2),0,0);
    str += "m";
    fill(0);
    textAlign(RIGHT,BOTTOM);
    textFont(font,txtSize);
    text(str, posX + dist2reff_X, posY - dist2reff_Y);
    
    dist2reff_X = maxDist/3*cos(amplitud/2);
    dist2reff_Y = maxDist/3*sin(amplitud/2);
    dist2reff_X /= factorEscala;
    dist2reff_Y /= factorEscala;
    str = nf(int(maxDist/3),0,0);
    str += "m";
    fill(0);
    textAlign(RIGHT,BOTTOM);
    textFont(font,txtSize);
    text(str, posX + dist2reff_X, posY - dist2reff_Y);
  }
}
