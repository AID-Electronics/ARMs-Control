
class Gauge {
  float posX;
  float posY;
  float innerDiameter;
  float outerDiameter;
  float startAngle;
  float endAngle;
  
  float minValue;
  float maxValue;
  float value;
  
  int red;
  int green;
  int blue;
  
  Gauge(float posX, float posY){
    this.posX = posX;
    this.posY = posY;
    
    //Default
    innerDiameter = 100;
    outerDiameter = 150;
    startAngle = radians(150);
    endAngle = radians(390);
    red = 0;
    green = 255;
    blue = 0;
  }
  
  void setSize(float innerDiam, float outerDiam){
    this.innerDiameter = innerDiam;
    this.outerDiameter = outerDiam;
  }
  
  void setLimits(float min, float max){
    minValue = min;
    maxValue = max;
  }
  void setColor(int r, int g, int b){
    red = r;
    green = g;
    blue = b;
  }
  
  void draw(float inputValue){
    value = map(inputValue,minValue,maxValue,150,390);
    value = radians(value);
    if (value > endAngle){
      value = endAngle;
    }
    
    noStroke();
    fill(red,green,blue);
    arc(posX, posY, outerDiameter, outerDiameter, startAngle, value);
    noFill();
    stroke(0);
    strokeWeight(1.5);
    arc(posX, posY, outerDiameter, outerDiameter, startAngle, endAngle,PIE);
    arc(posX, posY, innerDiameter, innerDiameter, startAngle, endAngle);
    strokeWeight(1);
    arc(posX, posY, outerDiameter, outerDiameter, startAngle, value, PIE);
    fill(200);
    noStroke();
    ellipse(posX, posY, innerDiameter-1, innerDiameter-1);
    strokeWeight(1);
    stroke(0);
  }
}
