/**
 * @file main.c
 *
 * @brief Main source code for the Sound Generation program.
 *
 * This file contains the main entry point and function definitions for the Sound Generation program.
 * It interfaces with the following:
 *	- EduBase Board LEDs (LED0 - LED3)
 *	- EduBase Board Push Buttons (SW2 - SW5)
 *	- DMT-1206 Magnetic Buzzer
 *
 * To verify the pinout of the user LED, refer to the Tiva C Series TM4C123G LaunchPad User's Guide
 * Link: https://www.ti.com/lit/pdf/spmu296
 *
 * @author Aaron Nanas
 */
 
#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "GPIO.h"
#include "Buzzer.h"

int main(void)
{
	//initialize the SysTick timer used to provide a blocking delay function
	SysTick_Delay_Init();
	
	//Inialize the LED'S Port B
	EduBase_LEDs_Init();
	//Initialize Buttons (SW2-SW5) Port D
	EduBase_Button_Init();
	//Initialize buzzer
	Buzzer_Init();
	

	while(1)
	{
		uint8_t edubase_button_status = Get_EduBase_Button_Status();
		Note_Controller(edubase_button_status);

	}
}