#include <bcm2835.h>

#define PIN RPI_GPIO_P1_11


int main()
{

bcm2835_set_debug(1);

if(bcm2835_init()==0)
  return 1;

bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

while(1)
{
  bcm2835_gpio_set(PIN); 
  bcm2835_delay(500);
  bcm2835_gpio_clear(PIN);
  bcm2835_delay(500);
}

return 0;
}
