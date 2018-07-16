
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
  
  String name;
  PFont text;
  int limitText_size;
  
  BarIndicator(float posx, float posy){
    this.posX = posx;
    this.posY = posy;
    this.startPos = 0;
    this.endPos = sizeX;
    
    text = createFont("Arial",14,true);
    limitText_size = 16;
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
    
    text = createFont("Arial",14,true);
    limitText_size = 16;
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
    
    boolean isPositive;
    float reff = posX + map(0,minValue,maxValue,startPos,endPos);
    println(reff);
    if (value < 0){
      isPositive = false;
    }
    else{
      isPositive = true;
    }
    
    noStroke();
    fill(200);
    rect(posX,posY,sizeX,sizeY);
    stroke(0);
    strokeWeight(1);
    fill(red,green,blue);
    if (isPositive){
      rect(reff,posY,value,sizeY);
    }else{
      rect(reff,posY,value,sizeY);
    }
    strokeWeight(1.5);
    noFill();
    rect(posX,posY,sizeX,sizeY);
    strokeWeight(1);
    
    //Text
    fill(0);
    textAlign(CENTER,BOTTOM);
    String str = str(minValue);
    textFont(text,limitText_size);
    text(str, posX, posY);
    str = str(maxValue);
    text(str, posX + sizeX, posY);
  }
}
