#include "main.h"

#define LED_PORT_GPIO_ADDRESS *((uint32_t *) 0x48000014)
#define GPIO_PIN_LED 1 << 5

void secret_led_blinking(void) {
	LED_PORT_GPIO_ADDRESS ^= GPIO_PIN_LED;
}
