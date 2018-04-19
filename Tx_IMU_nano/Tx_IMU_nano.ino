#include <VirtualWire.h>

void setup()
{
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec -->150m
  vw_set_tx_pin(3);//Aqeui se selecciona el pin digital que manda la información
}

void loop()
{
  send("--INCINACIÓN IMU2--");
  delay(1000);
}

void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}

