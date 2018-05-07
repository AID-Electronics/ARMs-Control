class Estructura {
  float posX;
  float posY;
  float posZ;
  
  float angX;
  float angY;
  float angZ;  //No gira en Z siempre 0

  Estructura(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
    
    angX = 0;
    angY = 0;
    angZ = 0;
  }
  
  void orientacion(float x, float y){
    angX = radians(x);
    angY = radians(y);
  }

  void show() {
    translate(posX, posY, posZ);
    
    //--Rotaacion intrínseca--
    /*
    float c1 = cos(angX);
    float s1 = sin(angX);
    float c2 = cos(angY);
    float s2 = sin(angY);
    float c3 = cos(angZ);
    float s3 = sin(angZ);
    applyMatrix( c2*c3, s1*s3+c1*c3*s2, c3*s1*s2-c1*s3, 0,
               -s2, c1*c2, c2*s1, 0,
               c2*s3, c1*s2*s3-c3*s1, c1*c3+s1*s2*s3, 0,
               0, 0, 0, 1);
    */
    //--Rotacion extrínseca--
    rotateX(angX);
    rotateY(angY);
    
    translate(0, 0, 50);
    box(100);
    translate(-posX, -posY, -posZ-50);
  }
}

class Plataforma {
  float posX;
  float posY;
  float posZ;
  
  float angX;
  float angY;
  float angZ;
  
  float velZ;  // En rad/img

  Plataforma(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
    
    angX = 0;
    angY = 0;
    angZ = 0;
    
    velZ = 0.1;
  }
  
  void orientacion(float x, float y){
    angX = radians(x);
    angY = radians(y);
    angZ = angZ + velZ;
  }

  void show() {
    //Altura barra 50
    translate(posX, posY, posZ);
    //rotateX(angX);
    rotateY(angY);
    rotateX(angX);
    rotateZ(angZ);
    
    translate(0,0,25);
    box(10, 10, 50);
    translate(0, 0, 30);
    box(200, 200, 10);
    translate(0,0,5);
  }
}
