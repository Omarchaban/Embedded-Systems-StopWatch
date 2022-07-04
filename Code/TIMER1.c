
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER1.h"


void TIMER1_init()
{
	/*Setting Prescaler to 1024 */
	SET_BIT(TCCR1B,TCCR1B_CS12);
	CLR_BIT(TCCR1B,TCCR1B_CS11);
	SET_BIT(TCCR1B,TCCR1B_CS10);

	/*Choosing CTC mode*/
	SET_BIT(TCCR1B,TCCR1B_WGM12);

	/*Enabling CTC interrupt*/
	SET_BIT(TIMSK,TIMSK_OCIE1A);

}
