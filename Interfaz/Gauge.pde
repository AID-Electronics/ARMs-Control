
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
    noFill();
    stroke(0);
    strokeWeight(1.5);
    arc(posX, posY, outerDiameter, outerDiameter, radians(150), radians(390),PIE);
    arc(posX, posY, innerDiameter, innerDiameter, radians(150), radians(390));
    strokeWeight(1);
    arc(posX, posY, outerDiameter, outerDiameter, radians(150), radians(mouseY), PIE);
    fill(200);
    noStroke();
    ellipse(posX, posY, innerDiameter-1, innerDiameter-1);
    //line(posX, posY, posX + outerDiameter * cos(radians(150)), posY + outerDiameter * sin(radians(150)));
    //line(posX, posY, posX + outerDiameter * cos(radians(390)), posY + outerDiameter * sin(radians(390)));
    strokeWeight(1);
    stroke(0);
  }
}
