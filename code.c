//0.15 trigger, 0.16 echo
#include<lpc17xx.h>

unsigned int timeval=0;
unsigned long result=0;

void timer_init1(){
LPC_TIM0->TCR=0x02;
LPC_TIM0->PR=0x02;
LPC_TIM0->MR0=49;// 10microsec pulse
LPC_TIM0->CTCR=0x00;
LPC_TIM0->EMR=0x20;
LPC_TIM0->MCR=0x04;//EDITED 
LPC_TIM0->TCR=0x01;
}
void timer_init2(){
LPC_TIM1->TCR=0x02;
LPC_TIM1->PR=0x02;
LPC_TIM1->MR0=0;
LPC_TIM1->CTCR=0x00;
LPC_TIM1->EMR=0x10;
LPC_TIM1->MCR=0x00;
LPC_TIM1->TCR=0x01;
}

int main()
{
		SystemInit();
		SystemCoreClockUpdate();
	//WRITE THE PINCONFIGGGG! !! ! ! ! ! ! (ECHO INPUT AND TRIGGER OUTPUT)
	LPC_PINCON->PINSEL0=0x00000000;
	LPC_PINCON->PINSEL1=0x00000000;
	LPC_GPIO0->FIODIR=0xFFFEFFFF;//A trigger 1-15 output AND echo 0-16 INPUT //instead of (0<<16)|(1<<15)
	
	
	while(1)
		{
			LPC_GPIO0->FIOSET =(0x1<<15);// removed (0<<16)
			timer_init1();// TRIGGERING
	
		while(!(LPC_TIM0->EMR & (0x01)));
			
		LPC_TIM0->TCR=0x02;//stop timer when 1 pulse is done	
		LPC_GPIO0->FIOCLR =(1<<15);// THIS SETS ONLY 15 PIN TO 0************IT IS UNABLE TO SO IN THE LAST WHILE LOOP WE USE (LPC_GPIO0->FIOPIN) ==(1<<16)|(1<<15)
	
	// TIRGGER GIVEN AND TAKEN DOWN WHEN 10 microsec
	
		while(!(LPC_GPIO0->FIOPIN&(1<<16)));
		
			timer_init2();
		
		  // USING 0.16 PIN AS ECHO
		
 		while((LPC_GPIO0->FIOPIN) ==((1<<16)));// ************THIS WHILE LOOP HAS A PROBLEM*****************//PREVIOUS...|(1<<15)... LPC_GPIO0->FIOPIN|(0<<16)
		
			LPC_TIM1->TCR=0x00;
		
		// USING 0.16 PIN AS ECHO STOPING TIMER BUT NOT RESETIING IT
	
		timeval= LPC_TIM1->TC;
		result=timeval/58.82;
	
		//display();
	
		}
		return 0;
		
		
}
