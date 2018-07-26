#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Wire.h>
#include <utility/imumaths.h>
#include "Trigonometria.h"

// DATOS FIJOS DEL SISTEMAS DE POLEAS Y ACTUADORES
#define RESOLUCION 0.00703125  //GRADOS POR PASO
#define RADIO_POLEA 25 //mm
#define ALTURA_POLEAS 360 //mm
#define D_REF 333//mm
#define DIST 50
#define H 360
#define TOL 0.035

// CONSTANTES MATEMATICAS
#define pi 3.141592
#define deg2rad 0.017453
#define rad2deg 57.295779

Adafruit_BNO055 bno = Adafruit_BNO055(55);
//sensors_event_t event;

long pasosMotor1;
long pasosMotor2;
long pasosMotor3;
long pasosMotor4;


class IMU{
public:
  double cabeceo; //en radianes
  double alabeo;  //en radianes
  Vector3D orientacion;
  Vector3D accel;

  bool setup();
  void displayCalStatus();
  int8_t printTemp();
  void getRaw_accel();
  void update();
  void print();
  void imprimirDatos();
  void reset(int pinNumber);
  bool isAccelDataCorrect();
  bool isOrientDataCorrect();
  void getNewData();
  void orientacion2Interface();
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

int calcularPasos1D(double cabeceo, double resolucion, double radioPolea, double distCentro) {
  double PASOS;
  double tangente = tan(cabeceo);
  //PASOS=(((tangente*distCentro)/(2*pi*radioPolea))*(360/resolucion)) ;
  PASOS = 51200 * cabeceo / (2 * pi);

  int aux = int(PASOS);
  double aux2 = abs(PASOS) - abs(aux);

  if (abs(aux2) > 0.5) {
    if (aux > 0)
      aux++;
    else
      aux--;
  }
  return aux;
}

long calcularPasos2D(double cabeceo, double alabeo , double resolucion, double radioPolea, double h, double posX, double posY, double Dref) {
  double PASOS;
  double tangenteCAB = tan(cabeceo); //ES EL ANGULO RESPECTO EL EJE X
  double tangenteAL = tan(alabeo); //ES EL ANGULO RESPECTO EL EJE Y
  double numerador = (sqrt((tangenteCAB * h - posY) * (tangenteCAB * h - posY) + (tangenteAL * h - posX) * (tangenteAL * h - posX)) - Dref);

  PASOS = ((numerador / (2 * pi * radioPolea)) * (360.0 / resolucion)) ;

  long aux = (long)PASOS;
  double aux2 = PASOS - aux;

  if (abs(aux2) > 0.5) {
    if (aux > 0)
      aux++;
    else
      aux--;
  }
  return aux;
}

void IMU::imprimirDatos() {

  //Serial.print ("X: ");
  Serial.print (orientacion.z, 4);
  Serial.print (" ");
  //Serial.print ("\tY: ");
  Serial.print (orientacion.y, 4);
  Serial.print (" ");
  //Serial.print ("\tZ: ");
  //Serial.println (orientacion.z,4);


  //Serial.print ("Pasos motor 1: ");
  Serial.print (pasosMotor1);
  Serial.print (" ");
  // Serial.print ("        Pasos motor 2: ");
  Serial.print (pasosMotor2);
  Serial.print (" ");
  //Serial.print ("      Pasos motor 3: ");
  Serial.print (pasosMotor3);
  Serial.print (" ");
  //Serial.print ("    Pasos motor 4: ");
  Serial.print (pasosMotor4);
  Serial.println(" ");
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

  getRaw_accel();
}

void moverMotores(double cabeceo, double alabeo) {
  pasosMotor1 = calcularPasos2D(cabeceo, alabeo, RESOLUCION, RADIO_POLEA, H, 333, 0, D_REF);
  pasosMotor2 = calcularPasos2D(cabeceo, alabeo, RESOLUCION, RADIO_POLEA, H, 0, 333, D_REF);
  pasosMotor3 = calcularPasos2D(cabeceo, alabeo, RESOLUCION, RADIO_POLEA, H, -333, 0, D_REF);
  pasosMotor4 = calcularPasos2D(cabeceo, alabeo, RESOLUCION, RADIO_POLEA, H, 0, -333, D_REF);

  // pasosMotor1=calcularPasos1D(cabeceo,RESOLUCION,RADIO_POLEA,H);
  // pasosMotor2=calcularPasos1D(alabeo,RESOLUCION,RADIO_POLEA,H);

  //AQUI iría la accion de movimiento
  moverAbsInmediato(pasosMotor1, ID_MOTOR_1);
  moverAbsInmediato(pasosMotor2, ID_MOTOR_2);
  moverAbsInmediato(pasosMotor3, ID_MOTOR_3);
  moverAbsInmediato(pasosMotor4, ID_MOTOR_4);
}

void IMU::getRaw_accel(){
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

void IMU::reset(int pinNumber){
  Serial.println("Reset IMU");
  digitalWrite(pinNumber,LOW);
  delay(10);
  digitalWrite(pinNumber,HIGH);
  setup();
  delay(10);
}

bool IMU::isAccelDataCorrect(){
  if (accel.x == 0.0 && accel.y == 0.0 && accel.z == 0.0){
    return false;
  }
  else{
    return true;
  }
}

bool IMU::isOrientDataCorrect(){
  if (orientacion.x == 0.0 && orientacion.y == 0.0 && orientacion.z == 0.0){
    return false;
  }
  else{
    return true;
  }
}

void IMU::getNewData(){
  bool dataOK = false;
  while(!dataOK){
    update();
    if (isAccelDataCorrect()){  //&& isOrientDataCorrect() puede dar problemas
      dataOK = true;            //en el caso que realmente estuviese a 0 la orient
    }
    else{
      reset(pinResetIMU);
    }
  }
}

void IMU::orientacion2Interface(){
  Serial.print("#Orient: ");
  Serial.print (orientacion.x, 4);
  Serial.print(",");
  Serial.print (orientacion.y, 4);
  Serial.print(",");
  Serial.print (orientacion.z, 4);
  Serial.println();
}

#endif