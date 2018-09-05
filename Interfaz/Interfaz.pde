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

Button botonTensadoAuto;

Button botonTensado;
Button botonTensado1;
Button botonTensado2;
Button botonTensado3;
Button botonTensado4;

Button botonDestensado;
Button botonDestensado1;
Button botonDestensado2;
Button botonDestensado3;
Button botonDestensado4;

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
  buttonDebug1.text = "Calibrar";
  buttonDebug1.setColor(10,200,255);
  
  buttonDebug2 = new Button (750,50,85,85);
  buttonDebug2.text = "Radar";
  buttonDebug2.setColor(50,100,100);
  
  botonTensadoAuto =  new Button (1200,75,75,75);
  botonTensadoAuto.text = "Tens.Auto";
  botonTensadoAuto.setColor(24, 226, 35);
  
  botonTensado =  new Button (1200,200+80,75,75);
  botonTensado.text = "Tensado";
  botonTensado.setColor(100,100,100);
  
  botonTensado1 = new Button (1200,200,75,75);
  botonTensado1.text = "M1";
  botonTensado1.setColor(100,100,100);
  
  botonTensado2 = new Button (1200+80,200+80,75,75);
  botonTensado2.text = "M2";
  botonTensado2.setColor(100,100,100);
  
  botonTensado3 = new Button (1200,200+80+80,75,75);
  botonTensado3.text = "M3";
  botonTensado3.setColor(100,100,100);
  
  botonTensado4 = new Button (1200-80,200+80,75,75);
  botonTensado4.text = "M4";
  botonTensado4.setColor(100,100,100);
  
  botonDestensado =  new Button (1200,500+80,75,75);
  botonDestensado.text = "Destensado";
  botonDestensado.setColor(100,100,100);
  
  botonDestensado1 = new Button (1200,500,75,75);
  botonDestensado1.text = "M1";
  botonDestensado1.setColor(100,100,100);
  
  botonDestensado2 = new Button (1200+80,500+80,75,75);
  botonDestensado2.text = "M2";
  botonDestensado2.setColor(100,100,100);
  
  botonDestensado3 = new Button (1200,500+80+80,75,75);
  botonDestensado3.text = "M3";
  botonDestensado3.setColor(100,100,100);
  
  botonDestensado4 = new Button (1200-80,500+80,75,75);
  botonDestensado4.text = "M4";
  botonDestensado4.setColor(100,100,100);
  
  radar = new Radar(600,300,400,40,150);
  dron = new Objetivo();
  telemetria = new Telemetria(20,130);
  alarmas = new Alarmas(400,130);
  
  gauge1 = new Gauge(450,610);
  gauge1.setLimits(0,1000);
  gauge1.setColor(185,92,200);
  gauge1.setName("VELOCIDAD GIRO\n(RPM)");
  
  dronVelGuage = new Gauge(650,610);
  dronVelGuage.setLimits(0,140);
  dronVelGuage.setColor(185,92,200);
  dronVelGuage.setName("VELOCIDAD DRON\n(km/h)");
  
  accelPlatform = new Acelerometro(800,540);
  
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
  
  botonTensadoAuto.draw();
  
  botonTensado.draw();
  botonTensado1.draw();
  botonTensado2.draw();
  botonTensado3.draw();
  botonTensado4.draw();
  
  botonDestensado.draw();
  botonDestensado1.draw();
  botonDestensado2.draw();
  botonDestensado3.draw();
  botonDestensado4.draw();
  
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
  if (!serialError){
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
    if (resetButton.isMouseOver()){
      port.write("R");
    }
    if (buttonDebug1.isMouseOver()){
      port.write("E");
    }
    if (buttonDebug2.isMouseOver()){
      port.write("F");
    }
    if (botonTensadoAuto.isMouseOver()){
      port.write("U");
    }
    if (botonTensado.isMouseOver()){
      port.write("T");
    }
    if (botonTensado1.isMouseOver()){
      port.write("6");
    }
    if (botonTensado2.isMouseOver()){
      port.write("7");
    }
    if (botonTensado3.isMouseOver()){
      port.write("8");
    }
    if (botonTensado4.isMouseOver()){
      port.write("9");
    }
    if (botonDestensado.isMouseOver()){
      port.write("Y");
    }
    if (botonDestensado1.isMouseOver()){
      port.write("2");
    }
    if (botonDestensado2.isMouseOver()){
      port.write("3");
    }
    if (botonDestensado3.isMouseOver()){
      port.write("4");
    }
    if (botonDestensado4.isMouseOver()){
      port.write("5");
    }
  }
  if (closeButton.isMouseOver()){
    exit();
  }
}
