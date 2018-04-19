#include "Schneider_LMD_P84.h"
#include <VirtualWire.h>
#define ID_MOTOR_1 0x610
#define ID_MOTOR_2 0x611
//#define ID_MOTOR_3 0x612
//#define ID_MOTOR_4 0x613

#include "IMU.h"

IMU IMU_fija;
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message

void leer_RF(){                                     //se pretende usar esta función solo durante la calibración
   if (vw_get_message(message, &messageLength)) // Non-blocking
  {
    Serial.print("Received: ");
    for (int i = 0; i < messageLength; i++)
    {
      Serial.write(message[i]);
    }
    Serial.println();
  }
}

void setup(){
  Serial.begin(1000000);
  IMU_fija.setup();
  setupCAN();

    setupMotor(ID_MOTOR_1,1000000,1000000,100,512000); //(long ID_motor,uint32_t Acel,uint32_t Decel, int current ,uint32_t MaxVel )
    setupMotor(ID_MOTOR_2,1000000,1000000,100,512000);

//**************************************************SETUP RF*********************************************************
  Serial.println("RF is ready");
  vw_setup(2000); // Bits per sec -->150m
  vw_set_rx_pin(3); //pin por el que llega el Rx.
  vw_rx_start(); // Start the receiver
//*******************************************************************************************************************
}
char a;
long pos;

void loop(){
  IMU_fija.update();
  moverMotores(IMU_fija.cabeceo, IMU_fija.alabeo);
  leer_RF();
  if(Serial.read()!=-1){
    IMU_fija.imprimirDatos();
    IMU_fija.displayCalStatus();
    IMU_fija.printTemp();
    IMU_fija.print();
  }
}

