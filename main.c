/*
 * stopWatch
 * 
 * Created: 09.02.2019 15:45:56
 * Author: Matthias Pfeifer
 */

 #include <avr/io.h>
 #include <avr/interrupt.h>
 #define F_CPU 16000000UL

 int counter = 0;
 int counter_break =1;
 int pause = 1;
 int reset = 1;

 ISR (TIMER1_COMPA_vect){
  if(counter_break){
    if(counter<63){counter ++;}
    else counter = 0;
  }
 }
int main(void)
{
  DDRD = 0xFF;
  DDRC = 0x00;

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 15000;
  TCCR1B |= (1<<WGM12);
  TCCR1B |= (1<<CS12)|(1<<CS10);
  TIMSK1 |= (1<<OCIE1A);

  sei();

  while (1)
  {
  int a0 = ~((PINC & (1<<PINC0))>>PINC0)&1;
  static int old_a0 = 0;
  int a1 = ~((PINC & (1<<PINC1))>>PINC1)&1; 
  static int old_a1 = 0;
  int a2 = ~((PINC & (1<<PINC2))>>PINC2)&1;
  static int old_a2 = 0;

  if(a0){

		if(a0!=old_a0){
			if(counter_break){counter_break=0;}
			else if (!counter_break){counter_break=1;}

  }

  }

  if (a1){
		if (a1!=old_a1){
			 if (pause){pause = 0;}
			 else if (!pause){pause=1;}
  }

  }
  if (a2){
		if(a2!=old_a2){
			if (reset&&!counter_break){reset=0;}
			else if (!reset){reset=1;}
   }

 }

 if(pause){
 for(int i=0; i<6; i++)
 {
 PORTD=(((counter>>i)&1)==1?(PORTD|(1<<(i+2))):(PORTD&~(1<<(i+2))));

 }

 }

 if(!counter_break){
		if(!reset){

 counter=0;
 reset=1;

 }

 }
 old_a0 =a0;
 old_a1=a1;
 old_a2=a2;
 }

 }
