#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Wire.h>
#include <utility/imumaths.h>

// CONSTANTES MATEMATICAS
#define pi 3.141592
#define deg2rad 0.017453
#define rad2deg 57.295779

Adafruit_BNO055 bno = Adafruit_BNO055(55);
//sensors_event_t event;


typedef struct Vector3D{
  double x;
  double y;
  double z;
};

class IMU{
public:
  double cabeceo; //en radianes
  double alabeo;  //en radianes
  Vector3D orientacion;
  Vector3D accel;

  bool setup();
  void displayCalStatus();
  int8_t printTemp();
  void raw_accel();
  void update();
  void print();
  void imprimirDatos();
};

void IMU::displayCalStatus () {
  /* Get the four calibration values (0..3) */
  /* Any sensor data reporting 0 should be ignored, */
  /* 3 means 'fully calibrated" */
  uint8_t sys, gyro, accel, mag;
  sys = gyro = accel = mag = 0;
  bno.getCalibration(&sys, &gyro, &accel, &mag);

  /* The data should be ignored until the sys calibration is > 0 */
  Serial.print("\t");
  if (sys == 0) {
    Serial.print("! ");
  }

  /* Display the individual values */
  Serial.print("Sys:");
  Serial.print(sys, DEC);
  Serial.print(" G:");
  Serial.print(gyro, DEC);
  Serial.print(" A:");
  Serial.print(accel, DEC);
  Serial.print(" M:");
  Serial.println(mag, DEC);
}

bool IMU::setup() {
  Serial.println("Setup IMU");
  int cont = 0;
  while (!bno.begin() && cont<10) {
    Serial.print("\tIMU no detectada ");
    Serial.println(cont+1);
    delay(500);
    cont++;
  }
  if (cont == 10){
    Serial.println("\tErrror setup IMU");
    return false;
  }
    Serial.println("\t1/3 - IMU detectada");
    delay(1000);
    bno.setExtCrystalUse(true);
    Serial.println("\t2/3 - IMU activada");
    delay(1000);
    Serial.print("\t3/3 - Calibracion :");
    displayCalStatus();
    return true;  
}

void IMU::imprimirDatos() {

  //Serial.print ("X: ");
  Serial.print (orientacion.z, 4);
  Serial.print (" ");
  //Serial.print ("\tY: ");
  Serial.print (orientacion.y, 4);
  Serial.println (" ");
  //Serial.print ("\tZ: ");
  //Serial.println (orientacion.z,4);
  //delay (2);
}

void IMU::update(){
  sensors_event_t event;
  bno.getEvent (&event);
  orientacion.x = event.orientation.x;
  orientacion.y = event.orientation.y;
  orientacion.z = event.orientation.z;
  
  cabeceo = orientacion.y * deg2rad; //No estoy demasiado seguro de que sea el eje correcto
  alabeo = orientacion.z * deg2rad;

  raw_accel();
}
void IMU::raw_accel(){
  imu::Vector<3> acceleration = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  
  accel.x = acceleration.x();
  accel.y = acceleration.y();
  accel.z = acceleration.z();
}

int8_t IMU::printTemp(){
  int8_t temp = bno.getTemp();
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  return temp;
}

void IMU::print(){
  Serial.print ("Cabeceo: ");
  Serial.print (cabeceo,4);
  Serial.print ("\tAlabeo: ");
  Serial.println (alabeo,4);
  
  Serial.print ("Orientacion ");
  Serial.print ("\tX: ");
  Serial.print (orientacion.x, 4);
  Serial.print (" ");
  Serial.print ("\tY: ");
  Serial.print (orientacion.y, 4);
  Serial.print (" ");
  Serial.print ("\tZ: ");
  Serial.println (orientacion.z,4);

  Serial.print ("Aceleracion ");
  Serial.print ("\tX: ");
  Serial.print (accel.x, 4);
  Serial.print (" ");
  Serial.print ("\tY: ");
  Serial.print (accel.y, 4);
  Serial.print (" ");
  Serial.print ("\tZ: ");
  Serial.println (accel.z,4);
}
#endif
