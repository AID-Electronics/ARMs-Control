
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
  
  float startPos;
  float endPos;
  
  int red;
  int green;
  int blue;
  
  boolean type;
  
  BarIndicator(float posx, float posy){
    this.posX = posx;
    this.posY = posy;
    this.startPos = 0;
    this.endPos = sizeX;
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
    
    this.startPos = 0;
    this.endPos = sizeX;
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
  void setLimits(float min, float max){
    this.minValue = min;
    this.maxValue = max;
  }
  
  void draw(float inputValue){
    value = map(inputValue,minValue,maxValue,startPos,endPos);
    if (value > endPos){
      value = endPos;
    }
    
    noStroke();
    fill(200);
    rect(posX,posY,sizeX,sizeY);
    fill(red,green,blue);
    rect(posX,posY,value,sizeY);
    stroke(0);
    noFill();
    rect(posX,posY,sizeX,sizeY);
    
  }
}
