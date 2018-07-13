
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
  
  Gauge(float posX, float posY){
    this.posX = posX;
    this.posY = posY;
    
    //Default
    innerDiameter = 100;
    outerDiameter = 150;
    startAngle = radians(150);
    endAngle = radians(390);
  }
  
  void setSize(float innerDiam, float outerDiam){
    this.innerDiameter = innerDiam;
    this.outerDiameter = outerDiam;
  }
  
  void setLimits(float min, float max){
    minValue = min;
    maxValue = max;
  }
  
  void draw(float inputValue){
    value = map(inputValue,minValue,maxValue,150,390);
    value = radians(value);
    if (value > endAngle){
      value = endAngle;
    }
    
    noStroke();
    fill(0,255,0);
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
    //line(posX, posY, posX + outerDiameter * cos(radians(150)), posY + outerDiameter * sin(radians(150)));
    //line(posX, posY, posX + outerDiameter * cos(radians(390)), posY + outerDiameter * sin(radians(390)));
    strokeWeight(1);
    stroke(0);
  }
}
