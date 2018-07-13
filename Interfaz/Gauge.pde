
class Gauge {
  float posX;
  float posY;
  
  float innerDiameter;
  float outerDiameter;
  
  Gauge(float posX, float posY){
    this.posX = posX;
    this.posY = posY;
    
    //Default
    innerDiameter = 100;
    outerDiameter = 150;
  }
  
  void setSize(float innerDiam, float outerDiam){
    this.innerDiameter = innerDiam;
    this.outerDiameter = outerDiam;
  }
}
