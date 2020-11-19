/*
 * main.c
 *
 * this is the skeleton for task 2
 *
 * author:    Dr. Alex Shenfield
 * date:      04/09/2018
 * purpose:   55-604481 embedded computer networks : lab 102
 */

// include the c standard io functions
#include <stdio.h>

// include the basic headers and hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "stm32746g_discovery_lcd.h"
#include "adc.h"
#include "gpio.h"

// stdout_init is defined in our configuration file (as part of the ARM
// Compiler user code template
//extern int stdout_init(void);

//activating Potentiometer Pin PA_0
gpio_pin_t pot = {PA_0, GPIOA, GPIO_PIN_0};

// defining LEDs// 
gpio_pin_t led = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t led2 = {PB_14, GPIOB, GPIO_PIN_14};

// declare our utility functions
void configure_gpio(void);

// LCD DEFINES

// define a message boarder (note the lcd is 28 characters wide using Font24)
#define BOARDER     "****************************"

// specify a welcome message
const char * welcome_message[1] = 
{
  "*     ADC Value (Pot) Is:     *",
};

// CODE

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	
	// initialise the uart, adc and gpio pins	
	//stdout_init();	
  init_adc(pot);
  init_gpio(led, OUTPUT);
	
	// initialise the lcd
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
	
	// set the background colour to blue and clear the lcd
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_Clear(LCD_COLOR_BLUE);
	
	// set the font to use
  BSP_LCD_SetFont(&Font24); 
	
	 // print message based on text array...
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAtLine(0, (uint8_t *)BOARDER);
	BSP_LCD_DisplayStringAtLine(1, (uint8_t *)welcome_message[0]);
	//adc readout value goes here//
	 BSP_LCD_DisplayStringAtLine(4, (uint8_t *)BOARDER); 
	
	
	   
  // delay a little ...
  HAL_Delay(5000);

	// display an "ADC Value" counter
  BSP_LCD_DisplayStringAtLine(2, (uint8_t *)"Current uptime ="); //Will draw adc readout value in the 2nd space underneath welcome message 1
  int counter = 0;
  while(1) 
  {
		// read the potentiometer and echo that value to the terminal
    uint16_t adc_val = read_adc(pot);
   // printf("potentiometer value = %d : delay time = %d ms\r\n", //using this printf statement generates errors in char
   // format a string based around the uptime counter
    char strcnt[20];
    sprintf(strcnt, "%d s", counter++);
		
		char str[20];
		sprintf(str, "ADC = %d", adc_val);	
		
		// print the Counter value to the lcd
    BSP_LCD_ClearStringLine(3);
    BSP_LCD_DisplayStringAtLine(3, (uint8_t *)strcnt);
    
    
    // print the ADC to the lcd
    BSP_LCD_ClearStringLine(6);
    BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str);
    
    HAL_Delay(1000);
		
		//REMAP POT BOUNDS
		
		//Create min and max pot floats
		float pot_max = 100;
		float pot_min = 0;
		//(ADC value/Max ADC value )*(upper bound - lower bound) + lower bound
		float pcent = ((adc_val/4095.0)*(pot_max - pot_min))+ pot_min; //value will be different
		
		// print the percentage value to the lcd
		 char str2[20];	//secondary character with percentage data//
	  sprintf(str2, "percentage is = %f", pcent);	
    BSP_LCD_ClearStringLine(7);
    BSP_LCD_DisplayStringAtLine(7, (uint8_t *)str2);
		
		//TASK 2.2. 
			
			if (pcent > 75) //activate LED's when above 75 percent voltage value//
			{
				write_gpio(led, HIGH);
				write_gpio(led2, LOW);
				
				char led1_on [20];
				sprintf(led1_on, "LED 1 Active");
				BSP_LCD_ClearStringLine(9);
				BSP_LCD_ClearStringLine(10); //Clear LED 2 active Line
				BSP_LCD_DisplayStringAtLine(9, (uint8_t *)led1_on);
			}
		
				if (pcent < 75) 
			{
				write_gpio(led, LOW);
				write_gpio(led2, HIGH);
				
				char led2_on [20];
				sprintf(led2_on, "LED 2 Active");
				BSP_LCD_ClearStringLine(9); //clear previous LED 1 active Line//
				BSP_LCD_ClearStringLine(10);
				BSP_LCD_DisplayStringAtLine(10, (uint8_t *)led2_on);
			}	
			
				//BSP_LCD_FillRect(uint16_t xpos, uint16_t ypos, uint16_t Width, uint16_t Height); //wiriting out rectangle codes//
			
		//generating LCD bar scales...//
				float bar_max = 400;
				float bar_min = 0;
				//(ADC value/Max ADC value )*(upper bound - lower bound) + lower bound
				float bar = ((adc_val/4095.0)*(bar_max - bar_min))+ bar_min; //value will be different
			
				char lcd_bar [20];
			  BSP_LCD_FillRect(0, 190, bar , 20);
		  	HAL_Delay(1);
			  BSP_LCD_ClearStringLine(8); //clears last bar string/ //poor code implementation 
				
  }
	
}

