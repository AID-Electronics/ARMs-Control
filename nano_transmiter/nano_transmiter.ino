//#include <VirtualWire.h>
 
//const int dataPin = 9;
 
void setup()
{
    Serial.begin(2400);     
    //vw_setup(2000);
    //vw_set_tx_pin(dataPin);  // no estoy seguro de que sea necesario

    for (int i=0;i<100;i++)
    {
      Serial.write(i);
    }
}
 
void loop()
{
  if(Serial.available())
   {
    switch (Serial.read())
   {
    case '1':
      Serial.write("hola caracola");
      break;
    case '2':
      Serial.write("adios pardiez");
      break;
    case '3':
    Serial.write("hasta luego que me muero"); 
    break;

    default:
    Serial.write("default value adquired"); 
    break;
   }
   }
}
