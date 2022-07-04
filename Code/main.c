/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: eng Ahmed
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER1.h"
#include<util/delay.h>

#include "DIO.h"
#include "EXTI.h"

u8 second=0;
u8 Min=0;
u8 Hour =0;

void INT0_Reset(void)
{
	SET_BIT(MCUCR,MCUCR_ISC01);
	SET_BIT(GICR,GICR_INT0);
	SetPinDirection(DIO_PORTD,PIN2,INPUT);
	SetPinValue(DIO_PORTD,PIN2,HIGH);
}

void INT1_Pause(void)
{
	SET_BIT(MCUCR,MCUCR_ISC11);
	SET_BIT(GICR,GICR_INT1);

	SetPinDirection(DIO_PORTD,PIN3,INPUT);
	SetPinValue(DIO_PORTD,PIN3,HIGH);
}

void INT2_Start(void)
{  CLR_BIT(MCUCSR,MCUCSR_ISC0);
SET_BIT(GICR,GICR_INT2);

SetPinDirection(DIO_PORTB,PIN2,INPUT);
SetPinValue(DIO_PORTB,PIN2,HIGH);
}

void main()
{   SET_BIT(SREG,SREG_I);  	//Global interrupt Enable
TIMER1_init();  			// TIMER1 initialization
INT0_Reset();				//External interrupt 0
INT1_Pause();				//External interrupt 1
INT2_Start();				//External intterupt 2
/*Putting compare value 1000 in OCR1 registers
 	  Tick Time = 1M /1024
	  Compare Value = 1sec/Tick Time =1000
 */
OCR1AH =0b00000011;
OCR1AL =0b11101000;

SetPortDirection(DIO_PORTC,0x0F);	// Configure first 4 Pins in PORTC as output pins >> for decoder

SetPortDirection(DIO_PORTA,0x3f);      // Configure first 6 Pins in PORTA as output pins >> for seven segment
SetPortValue(DIO_PORTA,0x3f); 		//initializing PORTA
while(1)
{
	SetPortValue(DIO_PORTA,1<<PIN5);
	SetPortValue(DIO_PORTC,second%10);
	// Show the first digit of seconds
	_delay_ms(5);
	SetPortValue(DIO_PORTA,1<<PIN4);
	SetPortValue(DIO_PORTC,second/10);
	// Show the second digit of seconds
	_delay_ms(5);
	SetPortValue(DIO_PORTA,1<<PIN3);
	SetPortValue(DIO_PORTC,Min%10);
	//Show the first digit on Minutes
	_delay_ms(5);
	SetPortValue(DIO_PORTA,1<<PIN2);
	SetPortValue(DIO_PORTC,Min/10);
	// Show the Second digit of Minutes
	_delay_ms(5);
	SetPortValue(DIO_PORTA,1<<PIN1);
	SetPortValue(DIO_PORTC,Hour%10);
	// Show the First digit of Hours
	_delay_ms(5);
	SetPortValue(DIO_PORTA,1<<PIN0);
	SetPortValue(DIO_PORTC,Hour/10);
	// Show the Second digit of Hours
	_delay_ms(5);
}



}

void __vector_7(void) __attribute__((signal)); //Timer1 CTC ISR
void __vector_7(void)
{
	second++;
	if(second ==60)
	{
		Min++;
		second =0;
	}
	if(Min ==60)
	{
		Hour++;
		Min=0;
		second =0;
	}
}
void __vector_1(void) __attribute__((signal)); //External interrupt 0 ISR
void __vector_1(void)
{
	second =0;
	Min=0;
	Hour=0;
}
void __vector_2(void) __attribute__((signal)); //External interrupt 1 ISR
void __vector_2(void)
{
	CLR_BIT(TCCR1B,TCCR1B_CS12);
	CLR_BIT(TCCR1B,TCCR1B_CS10);
}
void __vector_3(void) __attribute__((signal)); //External interrupt 2 ISR
void __vector_3(void)
{

	SET_BIT(TCCR1B,TCCR1B_CS12);
	SET_BIT(TCCR1B,TCCR1B_CS10);


}




