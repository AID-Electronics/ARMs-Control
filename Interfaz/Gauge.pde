
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
  
  void draw(){
    noStroke();
    fill(0,255,0);
    arc(posX, posY, outerDiameter, outerDiameter, radians(150), radians(mouseY));
    fill(200);
    ellipse(posX, posY, innerDiameter, innerDiameter);
    noFill();
    stroke(0);
    arc(posX, posY, outerDiameter, outerDiameter, radians(150), radians(390));
    arc(posX, posY, innerDiameter, innerDiameter, radians(150), radians(390));
    line(posX + innerDiameter * cos(radians(150)), posY + innerDiameter * sin(radians(150)), posX + outerDiameter * cos(radians(150)), posY + outerDiameter * sin(radians(150)));
    line(posX, posY, posX + outerDiameter * cos(radians(390)), posY + outerDiameter * sin(radians(390)));
  }
}
