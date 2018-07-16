#include "StateMACH.h"

Target b;



void enter_GL_State() {
  switch (currentState)
  {
    case setupRadar: setup_Radar(); break;
    case setupMotor: setup_Motor(); break;
    case setupComs: setup_Coms(); break;
    case Standby: StandbyF(); break;
    case working: workingF(); break;
    case error: errorF(); break;
  }
}
 
void setup_Radar()
{

  
  if (inicializar_radar())
  {
    nextState = setupMotor;
     radar_error = false;
  }
    else
  {
    nextState = setupMotor;
    radar_error = true;
    Serial.println("ERROR INICIAL DE RADAR");
  }
}

void setup_Motor()
{
  Serial.println("Iniciando MOTOR TRI");
  nextState = setupComs;


}

void setup_Coms()
{
  int flag = 0;
  int present;
  int past;
  //Serial.println("Iniciando comunicaciones");

  if (!digitalRead(pinState)) {

    setupCOMMS();
    enviar_data_error();
    while (flag != 2)
    {
      if (digitalRead(pinState) && flag == 0)
      {
        flag = 1;
        past = millis();

        //sendMSG("$C01;");

        Serial.println("YA ME HA llegado");
      }

      if (flag == 1)
      {

        present = millis();
        /*if ((present - past) > tiempoEspera )
        {
          Serial.println(present - past);
          sendMSG("$E001;");
          flag = 2;
          nextState = Standby;
        }*/
        if (!digitalRead(pinState))
        {
          Serial.print((present - past));
          if (((present - past) < (tiempoEspera + time_tol)) && ((present - past) > (tiempoEspera - time_tol)) )
          {
            sendMSG("$C001;");
            flag = 2;
            nextState = Standby;
            Serial.print("VOY A Standby");
          }
          else
          {
            Serial.println(present - past);
            sendMSG("$E001;");
            flag = 2;
            nextState = Standby;
          }

        }

      }



    }


  }
}


void StandbyF() {
  //   moverMotor(0);
  if (digitalRead(pinState) == HIGH)
  {
    nextState = working;
    Serial.print("VOY A WORKING");
  }
  else
    nextState = Standby;


sacar_Velocidad();
//if(Count_Target_tiempoReal)
//printTargets();

CheckRST();
  
  if (CheckSendData())
  {
    if(Count_Target_tiempoReal)
    enviar_data_radar(closest_target);
   else
    enviar_data_radar(b);
  }
    

}




unsigned long working_t; ///////////////////////////////////////OJOOOOOOOOOOOOOOOOo
void workingF() {

 
  if (CheckSendData())              // COMPROBAR SI EL MAESTRO PIDE DATOS
    enviar_data_radar(Real_target);
  
  /*
//printTargets();
Serial.print(" ");
Serial.print(Count_Target_tiempoReal);
Serial.print(" ");
Serial.println(sacar_Velocidad());*/
sacar_Velocidad();
if(Count_Target_tiempoReal)
{
    if(((millis()-working_t)>500))
    {

      
       working_t=millis();
      Serial.print(" ESTE ES EL CLOSEST TARGET");
      print_target(Real_target);
     
    
    }
  
}

  switch (state)
  {
    case activo_SIN_OBJETIVO: activo_sin(); break;

    case activo_CON_OBJETIVO: activo_con(); break;


  }
  
  CheckRST(); // COMANDO DEL RESET DESDE EL MAESTRO
  
  
  
  
  if(Count_Target_tiempoReal)//asignamos los datos leidos a la variable que se mandará al maestro
  {
    if(closest_target.velocidad>0)
      Real_target=closest_target;
      else
      Real_target=b;                                    
  }
    else
    Real_target=b;
  

  if (digitalRead(pinState) == LOW)
  {
    nextState = Standby;
    Serial.print("VOY A standby");
    mstate = acercandose;
    state = activo_SIN_OBJETIVO;
  }


}

void errorF() {
  CheckRST();
  //Serial.print("AS");

}

void update_GL_State() {

  currentState = nextState;
}


void acercandoseF() {


 

  VEL_GIRO = sacar_Velocidad();
  //  motor.moverMotor();
  Serial.println(VEL_GIRO);

  if (closest_target.distancia <= Distacia_minima)
  {
     Serial.print(closest_target.distancia);
    Serial.println("Objetivo va a aterrizar");
    mstate = aterrizando;
    aux_target = closest_target;
    VEL_GIRO = aux_target.velocidad;
    motor.moverMotor(VEL_GIRO);
    return;
  }
  else if (VEL_GIRO<=1.0 && VEL_GIRO>-3.0F)
  {
    Serial.print(VEL_GIRO);
     state = activo_SIN_OBJETIVO;
     Serial.println("VUELVO A activo_SIN_OBJETIVO");
  }

  else if(VEL_GIRO<=-4.0f)
  {
    Serial.print("  no recibo datos  ");
  }

////////////////////////////////////////////////////////////// 09/07
  else
    motor.moverMotor(VEL_GIRO); /////////EL motor se queda fijado si le envio velocidad 0?

    
}

void aterrizandoF() {


  Serial.print(" Aterrizando ");
  if (!aterrizaje_flag)
  {
    aterrizaje_t1 = millis();
    aterrizaje_flag = true;
  }
  int aterrizaje_t2=millis();
  if ( (aterrizaje_flag == true) && (aterrizaje_t2 - aterrizaje_t1) >= tiempo_aterrizaje)
  {
    
    Serial.println(aterrizaje_t2 - aterrizaje_t1);
    Serial.println("Objetivo aterrizado");
    
    int t1,a;
    state = activo_SIN_OBJETIVO;
    mstate = acercandose;
    aterrizaje_flag = false;
    
    motor.frenado();  //funcion para frenar

//comunicacion con MEGA
    digitalWrite(pinAterrizaje,HIGH);
   // enviar_aterrizaje();//////////// no hace falta.

    
    a=1;
    t1=millis();
    
    while(a==1)
    {
      int b= millis();
      if(digitalRead(pinState)==LOW)// en realidad es LOW pero para las prueba vale
      {
        Serial.println("VOY A standby");
        a=0;
        nextState=Standby;
        digitalWrite(pinAterrizaje,LOW);
      }
      if((b-t1)>=tiempo_espera_postAterrizaje)
      {
        Serial.println(b-t1);
        Serial.println("  HA TARDADO DEMASIADO; NOS VAMOS A ERROR ");
        a=2;
        enviar_error_state();
        nextState=error;
        digitalWrite(pinAterrizaje,LOW);
      }
    }
  }


}

void activo_con() {

  switch (mstate)
  {
    case acercandose: acercandoseF(); break;

    case aterrizando: aterrizandoF(); break;


  }

}

void activo_sin() {

  //VEL_GIRO = sacar_Velocidad();

  if (VEL_GIRO > 1)
    {state = activo_CON_OBJETIVO; Serial.print(VEL_GIRO); Serial.print("   VOY A activo_CON_OBJETIVO   ");}
  else
    motor.moverMotor(0); // para que se quede quieto.


}

void init_Gl_variables()
{
  currentState = setupRadar;
  nextState = setupRadar;
  Count_Target = 0;
  flag = 0;
  Count_Target_tiempoReal = 0;
  state = activo_SIN_OBJETIVO;
  mstate = acercandose;
   b.ID = 0;
  b.velocidad = 0.0f;
  b.distancia =0.0f;
  b.angulo = 0.0f;
  b.intensidad = 0.0f;
  VEL_GIRO = 0;
  working_t=0;
}

void reset_States()
{
  currentState=Standby;
  state = activo_SIN_OBJETIVO;
  mstate = acercandose;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(2000000);
  pinMode(pinState, INPUT);
  pinMode(pinData, INPUT);
  pinMode(pinAterrizaje, OUTPUT);
  pinMode(pinRadar, OUTPUT);
  digitalWrite(pinAterrizaje, LOW);
  digitalWrite(pinRadar, HIGH); // HAY QUE CAMBIARLO 09/07 En teoría lo alimentaremos solo en el estado de working

  //setupCOMMS();

  init_Gl_variables();  // inicializamos las variables globales en esta función
 



  //enviar_data_radar(b);
  //setup_Coms();


}

void loop() {
  
    update_GL_State();

    enter_GL_State();

  //motor.moverMotor();
  //enviar_data_radar(b);

  if (Serial.available() > 0)
  {
    switch (Serial.read())
    {
      case '1':
        nextState = working;
        Serial.println("VOY A WORKING");
        break;

      case '2':
        nextState = Standby;
        Serial.println("VOY A standby");
        mstate = acercandose;
        state = activo_SIN_OBJETIVO;
        break;

      case '3':
        nextState = working;
        mstate = acercandose;
        state = activo_CON_OBJETIVO;
        Serial.println("estoy en WORKING y viene objetivo");
        break;

        case '4':
        nextState = working;
        mstate = aterrizando;
        state = activo_CON_OBJETIVO;
        Serial.println("estoy en WORKING y va a aterrizar");
        break;
        
        case '5':
        enviar_data_radar(b);
        break;

        default:
        nextState = setupRadar;
        Serial.println("VOY al comienzo");
        mstate = acercandose;
        state = activo_SIN_OBJETIVO;
        break;
    }
  }


}
