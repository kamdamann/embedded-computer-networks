/*
 * main.c
 *
 * this is the skeleton for task 3
 *
 * author:    Dr. Alex Shenfield
 * date:      04/09/2018
 * purpose:   55-604481 embedded computer networks : lab 102
 */

// include the basic headers and hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "stm32746g_discovery_lcd.h"
#include "adc.h"

// LCD DEFINES

// define a message boarder (note the lcd is 28 characters wide using Font24)
#define BOARDER     "****************************"

// specify a welcome message
const char * welcome_message[2] = 
{
  "*     Hello LCD World!     *",
  "*      Welcome to SHU      *"
};


// (the user button)
gpio_pin_t ldr = {PF_10, GPIOF, GPIO_PIN_10}; //stm + breadboard LED//`//ldr may not work//
gpio_pin_t pb1 = {PI_11, GPIOI, GPIO_PIN_11};	//blue pushbutton stmboard//
gpio_pin_t thr = {PA_0, GPIOA, GPIO_PIN_0}; //pushbutton breadboard//

// CODE

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	
	  // initialise the lcd
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

  // set the background colour to blue and clear the lcd
  BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
  BSP_LCD_Clear(LCD_COLOR_BLUE);
  
  // set the font to use
  BSP_LCD_SetFont(&Font24); 
  
  // print the welcome message ...
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_DisplayStringAtLine(0, (uint8_t *)BOARDER);
  BSP_LCD_DisplayStringAtLine(1, (uint8_t *)welcome_message[0]);
  BSP_LCD_DisplayStringAtLine(2, (uint8_t *)welcome_message[1]);
  BSP_LCD_DisplayStringAtLine(3, (uint8_t *)BOARDER);    
  
  // initialise the adc for the sensors
  init_adc(thr);
  init_adc(ldr);
	HAL_Delay(1000);
  
  // main loop
  while(1)
  {
    // read the tmp36 and ldr
    uint16_t tmp_val = read_adc(thr);
		tmp_val = read_adc(thr);				
    uint16_t ldr_val = read_adc(ldr);
		
		// do the temperature conversion
		float tmp = ((((tmp_val * 3.3) / 4095.0) - 0.5) * 1000) / 10.0;
		//multiplies by 3.3 as that is voltage, divides by 4095 (12 bit adc), and removes 0.5 offset
		//10mv by degree which is why the 10 division is at the end//
    
    // format a string based around the temperature value and print to lcd
    char str[12];
    sprintf(str, "Temperature = %3.2f", tmp);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAtLine(5, (uint8_t *)str);
    
    // format a string based around the light value and print to lcd
    sprintf(str, "Light = %04d", ldr_val);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str);
    
    // delay a little (so the potentiometer reading doesn't flicker and jump
    // around too much)
    HAL_Delay(250);
  }
	
	

}
