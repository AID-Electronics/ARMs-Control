//#include <VirtualWire.h>
 
//const int dataPin = 3;

 int i=0;
void setup(){
    Serial1.begin(4800);     
    Serial.begin(115200);
    //vw_setup(2000);
    //vw_set_tx_pin(dataPin);  // no estoy seguro de que sea necesario
  
}
 
void loop(){
 // if(Serial1.available()){
     //Serial1.print(i);
     Serial1.println("hola caracola");
     //Serial.println(i);
     Serial.println("hola caracola ");
     //i++;
    // delay(100);  
  //} 
 }
