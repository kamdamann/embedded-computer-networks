/*
 * b_led_dice.c
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
#include "random_numbers.h"

// map the led to gpio pins

//the following assignments assumes breadboard is horizontal with P1_1 signifying a dice digit being on the far bottom right//

gpio_pin_t led1 = {PI_1,  GPIOI, GPIO_PIN_1};		//P1_1 - bottom right//
gpio_pin_t led2 = {PB_14, GPIOB, GPIO_PIN_14};	//PB_14 - bottom middle//
gpio_pin_t led3 = {PB_15, GPIOB, GPIO_PIN_15};	//PB_15 - bottom left//
gpio_pin_t led4 = {PI_2,  GPIOI, GPIO_PIN_2};	  //PI_2 - center//
gpio_pin_t led5 = {PI_3,  GPIOI, GPIO_PIN_3};	  //PI_3 - Top Right//
gpio_pin_t led6 = {PH_6,  GPIOH, GPIO_PIN_6};	  //PH_6 - Top Middle//
gpio_pin_t led7 = {PI_0,  GPIOI, GPIO_PIN_0};	  //PI_0 - Top Right//

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	
	//initialise the random number generator//
	init_random();

	// initialise the gpio pins as outputs to drive LED// //registers pins as outputs to drive appropriate LEDS//
	init_gpio(led1, OUTPUT);	
	init_gpio(led2, OUTPUT);	
	init_gpio(led3, OUTPUT);	
	init_gpio(led4, OUTPUT);	
	init_gpio(led5, OUTPUT);	
	init_gpio(led6, OUTPUT);	
	init_gpio(led7, OUTPUT);	
	

	
	 while(1)
  {
		//random number generation goes here, we want if statements or case statements with 36 different possibilities//
		 HAL_Delay(3000);
     uint32_t rnd = (get_random_int() % 6) + 1;


//		 toggle_gpio(led1);
//		 toggle_gpio(led2);
//		 toggle_gpio(led3);
//		 toggle_gpio(led4);
//		 toggle_gpio(led5);
//		 toggle_gpio(led6);
//		 toggle_gpio(led7);
//		 
//			HAL_Delay(5000);
//		
//		 toggle_gpio(led1);
//		 toggle_gpio(led2);
//		 toggle_gpio(led3);
//		 toggle_gpio(led4);
//		 toggle_gpio(led5);
//		 toggle_gpio(led6);
//		 toggle_gpio(led7);

	}
}