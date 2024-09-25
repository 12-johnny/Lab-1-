/**
 * @file Buzzer.c
 *
 * @brief Source code for the Buzzer driver.
 *
 * This file contains the function definitions for the Buzzer driver.
 * It interfaces with the following:
 *	- DMT-1206 Magnetic Buzzer
 *
 * To verify the pinout of the user LED, refer to the Tiva C Series TM4C123G LaunchPad User's Guide
 * Link: https://www.ti.com/lit/pdf/spmu296
 *
 * @author Aaron Nanas
 */
 
#include "Buzzer.h"

// Constant definitions for the buzzer
const uint8_t BUZZER_OFF 		= 0x00;
const uint8_t BUZZER_ON			= 0x10;

// Constant definitions for musical notes
const double C4_NOTE = 261.6;
const double D4_NOTE = 293.7;
const double E4_NOTE = 329.6;
const double F4_NOTE = 349.2;
const double G4_NOTE = 392.0;
const double A4_NOTE = 440.0;
const double B4_NOTE = 493.0;
const double C5_NOTE = 523.2;


void Buzzer_Init(void)
{
  SYSCTL->RCGCGPIO |= 0x04; //ENABLE CLOCK FOR PORT C
	GPIOC->DIR |= 0x10; //SET PC4 AS AN OUTPUT GPIO PIN
	GPIOC->AFSEL &= ~0x10; //CONGIFURE PC4 AS GPIO
	GPIOC-> DEN |= 0x10; //enable digital functionality 
}
void Buzzer_Output(uint8_t buzzer_value)
{
	//set output of buzzer
	GPIOC->DATA = (GPIOC->DATA & 0xEF) | buzzer_value;
	
}

void Play_Note(double note, unsigned int duration)
{
	//calculate the period of note in microsec
	int period_us = (int) (((double)1/note) * ((double)1000000));
	
	//calculate the half period in us
	int half_period_us = period_us /2;
	
	//generate a sqw wave for a specified duration
	for (unsigned int i = 0; i < duration; i++)
	{
		Buzzer_Output(BUZZER_ON);
		SysTick_Delay1us(half_period_us);
		Buzzer_Output(BUZZER_OFF);
		SysTick_Delay1us(half_period_us);
	}
	
}
