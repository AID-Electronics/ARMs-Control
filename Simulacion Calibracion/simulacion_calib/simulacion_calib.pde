
Estructura estruc;
Plataforma plat;

void setup() {
  size(600, 400, P3D);
  estruc = new Estructura(0, 0, 0); // Z -> mitad del cubo
  plat = new Plataforma(0, 0, 100);
  rectMode(CENTER);
}


void draw() {
  background(200);
  
  translate(width/2, height/1.5, 0);
  rotateX(PI/2.6); //2.6
  rotateZ(PI/8);
  coordinates();
  float rotX = (mouseX-width/2)/2;
  float rotY = (mouseY-height/1.5)/2;
  estruc.orientacion(rotX,rotY);
  estruc.show();
  plat.orientacion(-rotX,-rotY);
  plat.show();
}

class Estructura {
  float posX;
  float posY;
  float posZ;
  
  float angX;
  float angY;
  //No gira en Z

  Estructura(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
    
    angX = 0;
    angY = 0;
  }
  
  void orientacion(float x, float y){
    angX = radians(x);
    angY = radians(y);
  }

  void show() {
    translate(posX, posY, posZ);
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
    rotateX(angX);
    rotateY(angY);
    rotateZ(angZ);
    
    translate(0,0,25);
    box(10, 10, 50);
    translate(0, 0, 30);
    box(200, 200, 10);  
  }
}

void coordinates(){
  strokeWeight(4);
  stroke(255, 0, 0);
  line(0,0,0,100,0,0);
  stroke(0, 255, 0);
  line(0,0,0,0,100,0);
  stroke(0, 0, 255);
  line(0,0,0,0,0,100);
  stroke(0);
  strokeWeight(1);
}
