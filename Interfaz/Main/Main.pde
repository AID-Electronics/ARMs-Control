import processing.serial.*;

Serial port;

void setup(){
  size(600,300);
  println(Serial.list());
  port = new Serial (this, Serial.list()[0], 250000);
  port.bufferUntil('\n');
  
}

void draw(){
  
}

void serialEvent(Serial port) {
  String str = trim(port.readString());
  println(str);
}
