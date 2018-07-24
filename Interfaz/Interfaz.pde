import processing.serial.*;

Serial port;
String buff;
boolean serialError = false;

Button buttonEncendido;
Button buttonTest;
Button buttonStart;
Button buttonStop;
Button botonAterrizaje;
Button closeButton;
Button resetButton;
Button buttonDebug1;
Button buttonDebug2;

Radar radar;
Objetivo dron;
Telemetria telemetria;
Alarmas alarmas;
Gauge gauge1;
Gauge dronVelGuage;
Acelerometro accelPlatform;

PImage logoAID;

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

//Plataforma
int state; //del maxi
float velGiro;
float accelX = 0;
float accelY = 0;
float accelZ = 0;

void setup(){
  //size(1100,600);
  fullScreen();
  
  try{
    println(Serial.list());
    port = new Serial (this, Serial.list()[0], 250000);
    port.bufferUntil('\n');
  }
  catch(ArrayIndexOutOfBoundsException a){
    println("PLC no conectado al PC");
    serialError = true;
  }
  
  buttonEncendido = new Button (50,50,85,85);
  buttonEncendido.text = "ENCENDIDO";
  buttonEncendido.setColor(0,255,0);
  
  buttonTest = new Button (150,50,85,85);
  buttonTest.text = "SYS TEST";
  buttonTest.setColor(255,150,50);
  
  buttonStart = new Button (250,50,85,85);
  buttonStart.text = "START";
  buttonStart.setColor(200,255,50);
  
  buttonStop = new Button (350,50,85,85);
  buttonStop.text = "STOP";
  buttonStop.setColor(255,0,0);
  
  botonAterrizaje = new Button (450,50,85,85);
  botonAterrizaje.text = "ATERRIZAJE";
  botonAterrizaje.setColor(0,100,255);
  
  closeButton = new Button (displayWidth - 30,10,50,30);
  closeButton.text = "Exit";
  closeButton.setColor(255,0,0);
  closeButton.setVertex(5);
  
  resetButton = new Button (displayWidth-60,displayHeight-60,60,60);
  resetButton.text = "RESET";
  resetButton.setColor(255,0,0);
  resetButton.setVertex(15);
  
  buttonDebug1 = new Button (650,50,85,85);
  buttonDebug1.text = "State8";
  buttonDebug1.setColor(10,200,255);
  
  buttonDebug2 = new Button (750,50,85,85);
  buttonDebug2.text = "State10";
  buttonDebug2.setColor(50,100,100);
  
  radar = new Radar(700,250,400,40,150);
  dron = new Objetivo();
  telemetria = new Telemetria(20,130);
  alarmas = new Alarmas(400,130);
  
  gauge1 = new Gauge(500,610);
  gauge1.setLimits(0,100);
  gauge1.setColor(185,92,200);
  gauge1.setName("VELOCIDAD GIRO (RPM)");
  
  dronVelGuage = new Gauge(800,610);
  dronVelGuage.setLimits(0,50);
  dronVelGuage.setColor(185,92,200);
  dronVelGuage.setName("VELOCIDAD DRON (km/h)");
  
  accelPlatform = new Acelerometro(1000,550);
  
  logoAID = loadImage("C:/Users/AID_1/Desktop/AID-Logo.png");
}

void draw(){  
  velGiro = dron.vel * 11.9366;
  background(200);
  //tint(255, 127);
  //image(logoAID,600,0);
  buttonEncendido.draw();
  buttonTest.draw();
  buttonStart.draw();
  buttonStop.draw();
  botonAterrizaje.draw();
  closeButton.draw();
  resetButton.draw();
  buttonDebug1.draw();
  buttonDebug2.draw();
  
  radar.draw(dron);
  telemetria.draw();
  alarmas.draw();
  gauge1.draw(velGiro);
  dronVelGuage.draw(dron.vel);
  accelPlatform.draw();
}

void serialEvent(Serial port) {
  try{
    serialError = false;
    buff += port.readString();
    //print(buff);
    stringParse(buff);
    buff = "";
  }catch(Exception e){
    println("Error serial event");
    serialError = true;
  }
}

void mousePressed(){
  if(buttonEncendido.isMouseOver()){
    port.write("1");
  }
  if (buttonTest.isMouseOver()){
    port.write("C");
  }
  if (buttonStart.isMouseOver()){
    port.write("S");
  }
  if (buttonStop.isMouseOver()){
    port.write("0");
  }
  if (botonAterrizaje.isMouseOver()){
    port.write("A");
  }
  if (closeButton.isMouseOver()){
    exit();
  }
  if (resetButton.isMouseOver()){
    port.write("R");
  }
  if (buttonDebug1.isMouseOver()){
    port.write("E");
  }
  if (buttonDebug2.isMouseOver()){
    port.write("F");
  }
}
