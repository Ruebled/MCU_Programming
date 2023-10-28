#include <stdint.h>
#include "main.h"

int main(void) {
	// Enable GPIOC clock
	RCC->APB2ENR |= 1UL<<4;

	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_13, LL_GPIO_MODE_OUTPUT_2MHz);
	LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_13, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_13, LL_GPIO_OUTPUT_PUSHPULL);

	LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);
	
	while(1) {
		__asm__("nop");
	}

	return 0;
}
