
class Acelerometro{
  BarIndicator bar1;
  BarIndicator bar2;
  BarIndicator bar3;
  
  
  Acelerometro(){
    bar1 = new BarIndicator(700,450,200,15);
    bar1.setLimits(-10,10);
    bar1.setColor(255,164,032);
    bar2 = new BarIndicator(700,500,200,15);
    bar2.setLimits(-10,10);
    bar2.setColor(255,164,032);
    bar3 = new BarIndicator(700,550,200,15);
    bar3.setLimits(-10,10);
    bar3.setColor(255,164,032);
  }
  
  void draw(){
    bar1.draw(accelX);
    bar2.draw(accelY);
    bar3.draw(accelZ);
  }
}
