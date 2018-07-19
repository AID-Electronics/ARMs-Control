
class Objetivo{
  int id;
  float vel;
  float dist;
  float ang;
  float intensidad;
  
  PFont font;
  String data;
  int txtSize;
  
  Objetivo(){
    txtSize = 16;
    font = createFont("Arial",txtSize,true);
  }
  
  void draw(float posRadarX, float posRadarY, float escaleFactor){
    if (id != 0){
      float posX = dist*cos(radians(ang));
      float posY = dist*sin(radians(ang));
      posX /= escaleFactor;
      posY /= escaleFactor;
      
      fill(255, 0, 0);
      ellipse(posRadarX + posX, posRadarY + posY, 10, 10);
      
      //Text
      data = "Vel:" + str(vel);
      fill(0);
      textFont(font,txtSize);
      text(data, posX + 100, posY+150);
    }
  }
}
