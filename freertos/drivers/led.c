#include <stdint.h>

#include "led.h"
#include "gpio.h"

#define PORT_LED      ( GPIO_PORTF )
#define LED_MASK      ( LED_RED | LED_GREEN | LED_BLUE )
#define PIN_RED       ( 1 )
#define PIN_BLUE      ( 2 )
#define PIN_GREEN     ( 3 )

void led_config(void)
{
    gpio_configGpioPin ( PORT_LED ,PIN_RED   ,1 );
    gpio_configGpioPin ( PORT_LED ,PIN_BLUE  ,1 );
    gpio_configGpioPin ( PORT_LED ,PIN_GREEN ,1 );
}
void led_allOff(void)
{
    led_off(PIN_RED | PIN_BLUE | PIN_GREEN);
}
void led_on(uint32_t leds)
{
   (void)leds;
    gpio_setPins(PORT_LED, leds & LED_MASK);
}
void led_off(uint32_t leds)
{
   (void)leds;
    gpio_clearPins(PORT_LED, leds & LED_MASK);
}
