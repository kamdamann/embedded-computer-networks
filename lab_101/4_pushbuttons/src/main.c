/*
 * main.c
 *
 * this is the main push button application (this code is dependent on the
 * extra shu libraries such as the pinmappings list and the clock configuration
 * library)
 *
 * author:    Alex Shenfield
 * date:      29/09/2020
 * purpose:   55-604481 embedded computer networks : lab 101
 */

// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"

// map the led to GPIO PI_1 (the inbuilt led) and the push button to PI_11
// (the user button)
gpio_pin_t led = {PI_1, GPIOI, GPIO_PIN_1}; //stm + breadboard LED//
gpio_pin_t pb1 = {PI_11, GPIOI, GPIO_PIN_11};	//blue pushbutton stmboard//
gpio_pin_t pbb = {PA_8, GPIOA, GPIO_PIN_8}; //pushbutton breadboard//

// this is the main method
int main()
{
	/* USER CODE BEGIN 1 */
	uint32_t OldSysTick, state;
	OldSysTick = HAL_GetTick();
	state = 1;
	/* USER CODE END 1 */

// define a variable to hold our led state
  int led_state = 0;

	// we need to initialise the hal library and set up the SystemCoreClock
	// properly
	HAL_Init();
	init_sysclk_216MHz();

	// initialise the gpio pins
	init_gpio(led, OUTPUT);
	init_gpio(pb1, INPUT);	//setting blue pushbutton as input//
	init_gpio(pbb, INPUT);	//setting breadboard pushbutton as input//

	// loop forever ...
	while(1)
	{
		// if the button is pressed ...
		if((read_gpio(pb1)) || (read_gpio(pbb)))	//allows signal from both blue pushbutton and breadboard
		{
						// check what the led state is now and then if it is off turn it on
						if(led_state == 0)		
						{	
							// turn the led on on the gpio pin
						   write_gpio(led, HIGH);
							 led_state = 1;															// set the led state to "on"
						  //HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_1);	//using a toggle command is similar to using a latch, not taught method//
						  //HAL_Delay(500);													//delay prevents bouncing element, poor solution//
						}
						
						//otherwise, if it is turn it off
		}
					else
					{
						// turn the led off on the gpio pin
						   write_gpio(led, LOW);
						// set the led state to "off" for reset condition.
							 led_state = 0;
					}
				}
			}
	









//	switch (state)
//
//		{
//			case 1:
//				HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_1);
//				if (HAL_GetTick() > (OldSysTick + 500) )						//+ x determines delay time in ms//
//			