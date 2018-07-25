
//RADAR

#define TARGET_MAX_COUNT 100
#define IN_AIR_MAX_TARGETS 20
#define MAX_VEL 3000
#define Distacia_minima 5
#define intensidad_minima 50 


//STATE MACH
#define pinState A0 // entrada digital para el cambio de estado 
#define pinData A1
#define pinAterrizaje 3
#define pinRadar 9
#define tiempoEspera 100
#define tiempoEspera_reset 10
#define tiempoEspera_data 30
#define tiempo_aterrizaje 6000
#define tiempo_espera_postAterrizaje 1000
#define time_tol 2

//MOTOR TRI

#define pi 3.141592
#define VEL_TO_RPM 11.9366     //1.25  // 60 entre (0.8m que tiene de radio * 2*pi) = 60/(0.8*2*pi)
#define pinFrencuencia 10
#define pinMotor 6
#define MAX_VEL 24000
#define VEL_PREDET 1440

//COMMS
#define DATA_HEADER $D
#define MSG_ENDING ;
#define CONFIRM_HEADER $C
#define ERROR_HEADER $E
#define NO_TARGET_DETECTED_MSJ $D-1;
#define Motor_Radar_errors "$E110;"
#define Radar_error "$E010;"
#define Motor_error "$E100;"
#define NO_error "$E000;"



