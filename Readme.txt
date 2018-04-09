Funciones diseñadas:
 - sending (char buff [ ], long ID) ;
	Se encarga de juntar la cadena de caracteres (buff) al ID y pasárselo a la tarjeta CAN-SPI para su transmisión por el puerto CAN.
 - receive (bool observador = 0);
	Si llega algo por el puerto CAN, lo guarda en una variable global, para su posterior uso. En caso contrario no hace nada y devuelve un 0.
	Si se le pasa un 1 como parámetro, llamará a la función traduce (explicada más adelante).
 - comprobarRespuesta ( );
	Espera un cierto tiempo hasta la llegada de un mensaje. Si recibe la respuesta comprueba si es un mensaje de error o no. Si no recibe mensaje o este es erróneo la función devuelve un false, si recibe un mensaje correcto de confirmación, devuelve un true.
 - EnviarMSG (char buff[], long ID);
	Llama a la función sending para enviar el mensaje y a la función comprobarRespuesta. Si no recibe el mensaje de confirmación, vuelve a enviar el mensaje. Esto lo hace hasta 3 veces si el mensaje de confirmación no llega.
 - SetCurrent (int porcentaje, long ID);
	Recibe el porcentaje en decimal del máximo de corriente consumida por los motores. Transforma este valor a hexadecimal y lo introduce en una cadena. Para acabar, llama a la función EnviarMSG para enviar por el CANbus la cadena.
 - maxVelocity (long velocity, long ID);
	Recibe la velocidad máxima de los motores en pasos por segundo, lo pasa a hexadecimal y lo introduce en una cadena que envía al CANbus llamando a la función EnviarMSG.
 - setDeccel (uint32_t decel, long ID);
	Recibe la deceleración de los motores en pasos/s², lo pasa a hexadecimal y lo introduce en una cadena que envía al CANbus llamando a la función EnviarMSG.
 - SetAccel (long accel, long ID);
	Recibe la aceleración de los motores en pasos/s², lo pasa a hexadecimal y lo introduce en una cadena que envía al CANbus llamando a la función EnviarMSG.
 - SetProfile (int profile, long ID );
	Establece el perfil en el que se desea que funcione el motor.
	1 -> posicion, 2 -> velocidad, 3 -> homing mode y 4 -> par (torque) 
 - setupMotor (long ID_motor, uint32_t Acel, uint32_t Decel, int current ,uint32_t MaxVel );
	Con los parametros que recibe la función, va llamando a las funciones: SetAccel, setDeccel, maxVelocity y setCurrent, quedando de esta forma el motor configurado.
	Posteriormente se envian al CANbus las siguentes cadenas:
	 - const char ReadytoSwitch[ ]={0x2B,0x40,0x60,0x00,0x06,0x00,0x00,0x00};
	 - const char SwitchON[ ]={0x2B,0x40,0x60,0x00,0x07,0x00,0x00,0x00};
	 - const char OpEnable[ ]={0x2B,0x40,0x60,0x00,0x0F,0x00,0x00,0x00};
	utilizando la función EnviarMSG.
	Por último con la función SetProfile determina el modo de operación del motor. Con todo esto, el motor queda preparado para poder moverse a la posición que se le indique.
 - setPolarity (long pasos, long ID);
	Cambia la polaridad del motor según sea positivo o negativo el número de pasos que recibe la función.
 - moverAbsEspera (long pos,long ID);
	Se utiliza para que el motor se mueva en posición absoluta una vez que el anterior movimiento ha acabado.
 - moverAbsInmediato (long pos,long ID);
	Se utiliza para que el motor se mueva en posición absoluta inmediatamente, aunque no haya acabado el anterior movimiento.
 - moverRelatEspera (long pasos,long ID);
	Se utiliza para que el motor se mueva en posiciones relativas una vez que el anterior movimiento ha acabado.
 - moverRelatInmediato (long pasos,long ID);
	Se utiliza para que el motor se mueva en posiciones relativas inmediatamente, sin esperar a que el anterior movimiento haya terminado.
 - traduce (byte *leng, byte *buf, unsigned long ID);
	Esta función se encarga de mostrar por pantalla la información que lleva un cierta cadena (que recibe como parámetro). Es útil para leer de forma natural los mensajes que se envían por el CANbus.
