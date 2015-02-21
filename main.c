#include "msp430.h"

#define relay1 BIT0
#define relay2 BIT7
#define relay3 BIT6
#define relay4 BIT3
#define buzzer BIT2
#define LED0 BIT3
#define LED1 BIT4
#define IRLED1 BIT4
#define IRLED2 BIT5
#define IRrec BIT1

int i = 0;
int ii =0;
int iii =0;
int object =0;
int count=0;
int proxCount =0;
int finished =0;
int nowproxCount =0;
int dutysub =1;
int oncount =990;
int togglecount = 990;
int r2 =0;

void IR_prox(int LED);


void main(void){

  WDTCTL = WDTPW + WDTHOLD;                            // Stop watchdog timer

  P1DIR |= (relay1 + relay2 + relay3 + relay4 + IRLED1 + IRLED2);                            // OUTPUT
  P2DIR |= (LED0 + LED1 + buzzer);
  P1OUT |= relay2;
  P2OUT=0;

  __enable_interrupt(); // enable all interrupts                                   // Enable CPU interrupts

  while(1)
  {

	  IR_prox(1);
if(finished !=0)
{
	nowproxCount = proxCount;
	finished =0;
}
	  if(nowproxCount == 100)
	  {

		  P2OUT |= (LED0);
		  P2OUT &= ~(LED1);
		  togglecount=0;

	  }

	  else
	  {
		  oncount =0;
		  P2OUT &= ~(LED0);
		  P2OUT |= (LED1);
		  togglecount++;
		     	 if(togglecount ==5)
		     	 {
		     		if(r2 == 0)
		     		{
		     			r2 = 1;
		     			P1OUT |= (relay2);
		     			P1OUT &= ~(relay4);
		     		}
		     		else
		     		{
		     			r2=0;
		     			P1OUT |= (relay4);
		     			P1OUT &= ~(relay2);
		     		}
	  }
	  }

     _delay_cycles(200);
     if(oncount <5)
     {
    	 P1OUT |= (relay1);
    	 P1OUT &= ~(relay3);

     }
     else
     {
    	 P1OUT &= ~(relay1);
    	 P1OUT |= (relay3);
     }
if(togglecount >1000)
{
	togglecount=990;
}
     oncount++;
     if(oncount>1000)
     {
    	 oncount = 990;
     }
}
}


void IR_prox(int duty)
{
int temp =0;
dutysub = 10 - duty;
proxCount=0;

for(ii = 100;ii>0;ii--)
{
for(i=10;i>0;i--)
{

	      P1OUT |= (IRLED1 + IRLED2);
	      _delay_cycles(7);
	      P1OUT &= ~(IRLED1 + IRLED2);
	     // _delay_cycles(6);

}
temp = (P2IN & IRrec);
if (temp == IRrec)
{
	proxCount++;
}
}
finished = 1;
}
















