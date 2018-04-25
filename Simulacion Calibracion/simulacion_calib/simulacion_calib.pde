
Estructura estruc;
Plataforma plat;

void setup() {
  size(600, 400, P3D);
  estruc = new Estructura(0, 0, 50);
  plat = new Plataforma(width/2.0, height/2.0, 100);
  rectMode(CENTER);
}


void draw() {
  background(200);
  translate(width/2, height/2, 0);
  rotateX(PI/2.6);
  rotateZ(PI/8);
  coordinates();
  //rotateX(PI/3);
  //rotateZ(PI/8);
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
    posZ = z;
  }

  void show() {
    translate(posX, posY, posZ);
    rotateX(PI/2.6);
    rotateZ(PI/8);
    box(100);
    rotateZ(-PI/8);
    translate(-posX, -posY, -posZ);
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
    translate(this.posX, this.posY, this.posZ);
    //rotateX(PI/3);
    rotateZ(PI/8);
    box(200, 200, 10);
    strokeWeight(2);
    translate(0,0,-40);
    box(10, 10, 80);
    translate(0,0,-40);
    strokeWeight(1);
    translate(-posX, -posY, -posZ);
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
