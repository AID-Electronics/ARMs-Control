#ifndef IMU_H
#define IMU_H

#include <Arduino.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Wire.h>
#include <utility/imumaths.h>

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

#endif
