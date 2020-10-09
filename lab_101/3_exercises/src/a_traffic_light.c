/*
 * a_traffic_lights.c
 *
 * this is the main application skeleton for the student exercises in task 3
 *
 */

// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"

// map the led to gpio pins

//example = gpio_pin_t leda = {PA_8,  GPIOA, GPIO_PIN_8}; for pin PA_8

gpio_pin_t ledr = {PI_1,  GPIOI, GPIO_PIN_1};		//red//
gpio_pin_t leda = {PB_14, GPIOB, GPIO_PIN_14};	//amber//
gpio_pin_t ledg = {PB_15, GPIOB, GPIO_PIN_15};	//green//

// this is the main method
int main()
{
	 /* USER CODE BEGIN 1 */
	uint32_t OldSysTick, state;
	OldSysTick = HAL_GetTick(); state = 1;
  /* USER CODE END 1 */
	
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	
	// initialise the gpio pins as outputs to drive LED//
	init_gpio(ledr, OUTPUT);	//red//
	init_gpio(leda, OUTPUT);	//amber//
	init_gpio(ledg, OUTPUT);	//green//
	
	 while(1)
  {
    // toggle the RED led on the gpio pin//
    toggle_gpio(ledr);
			// wait for 1 second
    HAL_Delay(1000);
		toggle_gpio(ledr); //shut down red//
		
		// toggle amber LED//
    toggle_gpio(leda);
			// wait for 1 second
    HAL_Delay(1000);
		toggle_gpio(leda);	//shut down amber//
		
		// toggle green LED
    toggle_gpio(ledg);
			// wait for 1 second
    HAL_Delay(1500);
		toggle_gpio(ledg);	//shut down green//
		
		
		
		
	
		
		
  }

}
