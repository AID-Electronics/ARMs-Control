
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
  
  estruc.show();
  plat.show();
}

class Estructura {
  float posX;
  float posY;
  float posZ;

  Estructura(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z+50;
  }

  void show() {
    translate(posX, posY, posZ);
    box(100);
    translate(-posX, -posY, -(posZ));
  }
}

class Plataforma {
  float posX;
  float posY;
  float posZ;

  Plataforma(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
  }

  void show() {
    //Altura barra 50
    translate(posX, posY, posZ+25);
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
