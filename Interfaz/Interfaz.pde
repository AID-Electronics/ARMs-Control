import processing.serial.*;

Serial port;
String buff;

Button button1;
Button button2;
Button button3;
Radar radar;
Objetivo dron;
Telemetria telemetria;

//Datos PLC
int globalState;
int localState;

//IMU plataforma
float orientX;
float orientY;
float orientZ;

//Temperatura motores
float tempM1;
float tempM2;

void setup(){
  size(1000,500);
  

  boolean serialError = false;
  try{
    println(Serial.list());
    port = new Serial (this, Serial.list()[0], 250000);
    port.bufferUntil('\n');
  }
  catch(ArrayIndexOutOfBoundsException a){
    println("PLC no conectado al PC");
    serialError = true;
  }
  
  button1 = new Button (50,50,75,75);
  button1.text = "START";
  button1.setColor(0,255,0);
  
  button2 = new Button (150,50,75,75);
  button2.text = "NOTOCAR";
  button2.setColor(255,150,50);
  
  button3 = new Button (250,50,75,75);
  button3.text = "STOP";
  button3.setColor(255,0,0);
  
  radar = new Radar(500,250,600,40);
  dron = new Objetivo();
  telemetria = new Telemetria(10,110,120);
}

void draw(){  
  background(200);
  button1.draw();
  button2.draw();
  button3.draw();
  radar.draw(dron);
  telemetria.draw();
}

void serialEvent(Serial port) {
  buff += port.readString();
  //print(buff);
  stringParse(buff);
  buff = "";
}

void mousePressed(){
  if(button1.isMouseOver()){
    port.write("1");
  }
  if (button2.isMouseOver()){
    port.write("E");
  }
  if (button3.isMouseOver()){
    port.write("0");
  }
}
