
Estructura estruc;
Plataforma plat;
IMU imuFija;

void setup() {
  size(800, 600, P3D);
  estruc = new Estructura(0, 0, 0); // Z -> mitad del cubo
  plat = new Plataforma(0, 0, 100);
  imuFija = new IMU ();
  rectMode(CENTER);
}


void draw() {
  background(200);
  
  translate(width/2, height/1.5, 0);
  rotateX(PI/2.6); //2.6
  rotateZ(PI/8);
  coordinates(200);
  float rotX = (mouseX-width/2)/2;
  float rotY = (mouseY-height/1.5)/2;
  estruc.orientacion(rotX,rotY);
  estruc.show();
  imuFija.show();
  plat.orientacion(-rotX,-rotY);
  plat.show();
  
  imuFija.computeAccel(estruc.angX,estruc.angY);
  println("X: " + imuFija.accelX + "\tY: " + imuFija.accelY + "\tZ: " + imuFija.accelZ);
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
    //rotateX(angX);
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
  }
}

void coordinates(int longitud){
  strokeWeight(4);
  stroke(255, 0, 0);    //X rojo
  line(0,0,0,longitud,0,0);
  stroke(0, 255, 0);    //Y verde
  line(0,0,0,0,longitud,0);
  stroke(0, 0, 255);    //Z azul
  line(0,0,0,0,0,longitud);
  stroke(0);
  strokeWeight(1);
}

class IMU {
  float accelX;
  float accelY;
  float accelZ;
  
  void computeAccel(float angX, float angY){
    accelX = 10*sin(angY);
    accelY = 10*sin(angX);
    accelZ = 10*cos(angX)*cos(angY);
  }
  void show(){
    coordinates(100);
  }
}
