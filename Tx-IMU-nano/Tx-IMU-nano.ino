#include <VirtualWire.h>

void setup()
{
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec -->150m
  vw_set_tx_pin(3);//pin digital al que se envía la información
}

void loop()
{
  send("--INCLINACIÓN IMU2--");//aqui se deberan poner los angulos de euler de la imu
  delay(1000);
}

void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}

