
class Acelerometro{
  float posX;
  float posY;
  
  BarIndicator bar1;
  BarIndicator bar2;
  BarIndicator bar3;
  
  PFont font;
  String str;
  int txtSize;
  
  
  Acelerometro(float posx, float posy){
    this.posX = posx;
    this.posY = posy;
    
    bar1 = new BarIndicator(posX,posY,200,15);
    bar1.setLimits(-10,10);
    bar1.setColor(255,164,032);
    bar2 = new BarIndicator(posX,posY+50,200,15);
    bar2.setLimits(-10,10);
    bar2.setColor(255,164,032);
    bar3 = new BarIndicator(posX,posY+100,200,15);
    bar3.setLimits(-10,10);
    bar3.setColor(255,164,032);
    
    txtSize = 20;
    font = createFont("Arial",txtSize,true);
  }
  
  void draw(){
    bar1.draw(accelX);
    bar2.draw(accelY);
    bar3.draw(accelZ);
    
    str = "IMU PLATAFORMA";
    textFont(font,txtSize);
    text(str, posX + 100, posY+150);
    
    str = "m/s²";
    textFont(font,16);
    text(str, posX + 100, posY-30);
    
    textAlign(RIGHT,TOP);
    str = "X";
    textFont(font,16);
    text(str, posX-20, posY);
    str = "Y";
    text(str, posX-20, posY+50);
    str = "Z";
    text(str, posX-20, posY+100);
  }
}
