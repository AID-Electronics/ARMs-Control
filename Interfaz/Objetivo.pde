
class Objetivo{
  int id;
  float vel;
  float dist;
  float ang;
  float intensidad;
  
  void draw(float posRadarX, float posRadarY){
    if (id != 0){
      float posX = dist*cos(radians(ang));
      float posY = dist*sin(radians(ang));
      fill(255, 0, 0);
      ellipse(posRadarX + posX, posRadarY + posY, 10, 10);
    }
  }
}
