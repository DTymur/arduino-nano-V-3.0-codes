#include <avr/io.h>
#include <avr/interrupt.h>

volitale int 
counter0 = 0,
counter1 = 0,
counter3 = 0;



void LEDH (n){
	PORTB |= (1<<(n));
	}
	
void LEDL (int n){
	PORTB &= ~(1<<(n));
	}


ISR(TIMER0_COMPA_vect){
			LEDH(5);
			counter0++;
			}
	
ISR(TIMER1_COMPA_vect){
			LEDH(4);
			counter1++;
			}
			
ISR(TIMER1_COMPA_vect){
			LEDH(3);
			counter1++;
			}			
			
int main(void){
	
	//Timer 0
	DDRB |= (1<<DDB4);
	TCCR0A = 0;
	TCCR0B = 0;
	TCCR0B |= (1<<WGM02) | (1<<CS01);
	TCNT0 = 0;
	TIMSK0 = |(1<<OCIE0B);
	OCR0A = 19999;
	//
	
	//Timer 1
	DDRB |= (1<<DDB5);
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1B |= (1<<WGM12) | (1<<CS12);
	TCNT1 = 0;
	TIMSK1 |= (1<<OCIE1B);
	OCR1A = 31249;
	//
	
	//Timer3
	DDRB |= (1<<DDB3);
	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1B |= (1<<WGM32) | (1<<CS32);
	TCNT3 = 0;
	TIMSK1 |= (1<<OCIE3B);
	OCR1A = 62499;
	//
	sei();
	
	while(1) {
			
		if (counter1 & 1){
			LEDL(5);
			counter = 0;
			}
	}

	return 0;	
}
