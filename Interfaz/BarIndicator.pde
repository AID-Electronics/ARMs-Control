
class BarIndicator{
  //Position
  float posX;
  float posY;
  //Size
  float sizeX;
  float sizeY;
  
  float minValue;
  float maxValue;
  float value;
  
  int red;
  int green;
  int blue;
  
  boolean type;
  
  BarIndicator(float posx, float posy){
    this.posX = posx;
    this.posY = posy;
  }
  BarIndicator(float posx, float posy, float sizex, float sizey){
    this.posX = posx;
    this.posY = posy;
    this.sizeX = sizex;
    this.sizeY = sizey;
    //defaults
    this.red = 0;
    this.green = 100;
    this.blue = 100;
  }
  void setSize(float sizex, float sizey){
    this.sizeX = sizex;
    this.sizeY = sizey;
  }
  void setColor(int red, int green, int blue){
    this.red = red;
    this.green = green;
    this.blue = blue;
  }
  
  void draw(){
    noStroke();
    fill(200);
    rect(posX,posY,sizeX,sizeY);
    fill(red,green,blue);
    rect(posX,posY,mouseX,sizeY);
    stroke(0);
    noFill();
    rect(posX,posY,sizeX,sizeY);
    
  }
}
