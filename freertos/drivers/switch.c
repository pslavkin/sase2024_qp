#include <stdint.h>

#include "switch.h"
#include "gpio.h"

#define PORT_SWITCH      ( GPIO_PORTF )
#define SWITCH1_PIN      ( 4 )
#define SWITCH2_PIN      ( 0 )

void switch_config(void)
{
    gpio_configGpioPin(PORT_SWITCH, SWITCH1_PIN, 0);
    gpio_configGpioPin(PORT_SWITCH, SWITCH2_PIN, 0);
    gpio_enablePullUp(PORT_SWITCH, SWITCH1_PIN);
    gpio_enablePullUp(PORT_SWITCH, SWITCH2_PIN);
}

uint8_t switch_statusSw1(void)
{
   uint8_t swMask = 1<<SWITCH1_PIN;
   return  !(gpio_readPins(PORT_SWITCH, swMask) & swMask);
}
uint8_t switch_statusSw2(void)
{
   uint8_t swMask = 1<<SWITCH2_PIN;
   return  !(gpio_readPins(PORT_SWITCH, swMask) & swMask);
}
