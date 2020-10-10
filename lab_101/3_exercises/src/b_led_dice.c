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
gpio_pin_t led7 = {PI_0,  GPIOI, GPIO_PIN_0};	  //PI_0 - Top left//

// this is the main method
int main()
{
	// we need to initialise the hal library and set up the SystemCoreClock
	// properly
	HAL_Init();
	init_sysclk_216MHz();

//initialise the random number generator
	init_random();

	// initialise the gpio pins
	init_gpio(led1, OUTPUT);
	init_gpio(led2, OUTPUT);
	init_gpio(led3, OUTPUT);
	init_gpio(led4, OUTPUT);
	init_gpio(led5, OUTPUT);
	init_gpio(led6, OUTPUT);
	init_gpio(led7, OUTPUT);


	// loop forever ...
	while(1)
	{
		uint32_t rnd = (get_random_int() % 6) + 1;

if (rnd == 1)
	{
		write_gpio(led4, HIGH);
	}
	
	else if(rnd == 2) //top left + bottom right = PI0, PI1//
	{
		write_gpio(led7, HIGH);
		write_gpio(led1, HIGH);
	}
		
	else if(rnd == 3)	//same plus PI2//
	{
		write_gpio(led1, HIGH);
		write_gpio(led7, HIGH);
		write_gpio(led4, HIGH);
	}
	
	else if(rnd == 4)
	{
		write_gpio(led1, HIGH);	//bottom right//
		write_gpio(led7, HIGH);	//top left//
		write_gpio(led5, HIGH); //top right//
		write_gpio(led3, HIGH);	//bottom left//
	}
		
	else if(rnd == 5)
	{
		write_gpio(led1, HIGH);	//bottom right//
		write_gpio(led7, HIGH);	//top left//
		write_gpio(led5, HIGH); //top right//
		write_gpio(led3, HIGH);	//bottom left//
		write_gpio(led4, HIGH); //center//
	}	
		
	else if(rnd == 6)
	{
		write_gpio(led7, HIGH); //top left//
		write_gpio(led6, HIGH); //top middle//
		write_gpio(led5, HIGH);	//top right// 
		write_gpio(led3, HIGH); //bottom left//
		write_gpio(led2, HIGH);	//bottom middle//
		write_gpio(led1, HIGH);	//bottom right//
	}	
		
	else if(rnd == 7)
	{
		write_gpio(led1, HIGH);	//all active//
		write_gpio(led2, HIGH);
		write_gpio(led3, HIGH);
		write_gpio(led4, HIGH);
		write_gpio(led5, HIGH);
		write_gpio(led6, HIGH);
		write_gpio(led7, HIGH);
	}	



		HAL_Delay(3000);
		write_gpio(led1, LOW);		//reset LED's for next spin//
		write_gpio(led2, LOW);
		write_gpio(led3, LOW);
		write_gpio(led4, LOW);
		write_gpio(led5, LOW);
		write_gpio(led6, LOW);
		write_gpio(led7, LOW);
		HAL_Delay(1000);

	}
}
