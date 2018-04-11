Funciones dise�adas:
 - sending (char buff [ ], long ID) ;
	Se encarga de juntar la cadena de caracteres (buff) al ID y pas�rselo a la tarjeta CAN-SPI para su transmisi�n por el puerto CAN.
 - receive (bool observador = 0);
	Si llega algo por el puerto CAN, lo guarda en una variable global, para su posterior uso. En caso contrario no hace nada y devuelve un 0.
	Si se le pasa un 1 como par�metro, llamar� a la funci�n traduce (explicada m�s adelante).
 - comprobarRespuesta ( );
	Espera un cierto tiempo hasta la llegada de un mensaje. Si recibe la respuesta comprueba si es un mensaje de error o no. Si no recibe mensaje o este es err�neo la funci�n devuelve un false, si recibe un mensaje correcto de confirmaci�n, devuelve un true.
 - EnviarMSG (char buff[], long ID);
	Llama a la funci�n sending para enviar el mensaje y a la funci�n comprobarRespuesta. Si no recibe el mensaje de confirmaci�n, vuelve a enviar el mensaje. Esto lo hace hasta 3 veces si el mensaje de confirmaci�n no llega.
 - SetCurrent (int porcentaje, long ID);
	Recibe el porcentaje en decimal del m�ximo de corriente consumida por los motores. Transforma este valor a hexadecimal y lo introduce en una cadena. Para acabar, llama a la funci�n EnviarMSG para enviar por el CANbus la cadena.
 - maxVelocity (long velocity, long ID);
	Recibe la velocidad m�xima de los motores en pasos por segundo, lo pasa a hexadecimal y lo introduce en una cadena que env�a al CANbus llamando a la funci�n EnviarMSG.
 - setDeccel (uint32_t decel, long ID);
	Recibe la deceleraci�n de los motores en pasos/s�, lo pasa a hexadecimal y lo introduce en una cadena que env�a al CANbus llamando a la funci�n EnviarMSG.
 - SetAccel (long accel, long ID);
	Recibe la aceleraci�n de los motores en pasos/s�, lo pasa a hexadecimal y lo introduce en una cadena que env�a al CANbus llamando a la funci�n EnviarMSG.
 - SetProfile (int profile, long ID );
	Establece el perfil en el que se desea que funcione el motor.
	1 -> posicion, 2 -> velocidad, 3 -> homing mode y 4 -> par (torque) 
 - setupMotor (long ID_motor, uint32_t Acel, uint32_t Decel, int current ,uint32_t MaxVel );
	Con los parametros que recibe la funci�n, va llamando a las funciones: SetAccel, setDeccel, maxVelocity y setCurrent, quedando de esta forma el motor configurado.
	Posteriormente se envian al CANbus las siguentes cadenas:
	 - const char ReadytoSwitch[ ]={0x2B,0x40,0x60,0x00,0x06,0x00,0x00,0x00};
	 - const char SwitchON[ ]={0x2B,0x40,0x60,0x00,0x07,0x00,0x00,0x00};
	 - const char OpEnable[ ]={0x2B,0x40,0x60,0x00,0x0F,0x00,0x00,0x00};
	utilizando la funci�n EnviarMSG.
	Por �ltimo con la funci�n SetProfile determina el modo de operaci�n del motor. Con todo esto, el motor queda preparado para poder moverse a la posici�n que se le indique.
 - setPolarity (long pasos, long ID);
	Cambia la polaridad del motor seg�n sea positivo o negativo el n�mero de pasos que recibe la funci�n.
 - moverAbsEspera (long pos,long ID);
	Se utiliza para que el motor se mueva en posici�n absoluta una vez que el anterior movimiento ha acabado.
 - moverAbsInmediato (long pos,long ID);
	Se utiliza para que el motor se mueva en posici�n absoluta inmediatamente, aunque no haya acabado el anterior movimiento.
 - moverRelatEspera (long pasos,long ID);
	Se utiliza para que el motor se mueva en posiciones relativas una vez que el anterior movimiento ha acabado.
 - moverRelatInmediato (long pasos,long ID);
	Se utiliza para que el motor se mueva en posiciones relativas inmediatamente, sin esperar a que el anterior movimiento haya terminado.
 - traduce (byte *leng, byte *buf, unsigned long ID);
	Esta funci�n se encarga de mostrar por pantalla la informaci�n que lleva un cierta cadena (que recibe como par�metro). Es �til para leer de forma natural los mensajes que se env�an por el CANbus.
