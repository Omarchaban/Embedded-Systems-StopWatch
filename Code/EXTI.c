/*
 * EXTI.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: eng Ahmed
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI.h"
#include "DIO_reg2.h"
void EXTI_Int0Init(void)
{
	/*initialize INT0 to operate at falling edge*/

   SET_BIT(MCUCR,MCUCR_ISC01);

   CLR_BIT(MCUCR,MCUCR_ISC00);

   /*Enabling peripheral interrupt enable*/
   SET_BIT(GICR,GICR_INT0);

}
