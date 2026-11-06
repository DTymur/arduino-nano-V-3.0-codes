#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile int 
	mls = 0,
	mode_st = 1,
	counter1 = 0,
	counter2 = 0,
	counterB5 = 0,
	counterB4 = 0,
	counterB3 = 0,
	speed = 1,			
	B1prest = 1,
	B2prest = 1;
	
	
ISR(TIMER1_COMPA_vect){
	
	switch (mode_st){
		
		case 1:
			PORTB |= (1<<PB5) | (1<<PB4) | (1<<PB3);
			counter1++;
			break;
			
		case 2:
			counter2++;
			break;
		
		case 3:
			counterB5++;
			counterB4++;
			counterB3++;
			break;
			
	}
}
	
ISR(TIMER2_COMPA_vect){ mls++;}
				
void LEDH (int n){
	PORTB |= (1<<(n));
	}
	
void LEDL (int n){
	PORTB &= ~(1<<(n));
	}

//mode1
void mode1(void){
	
	sei();
			
		if (counter1 == 2){
			PORTB &= ~( (1<<(5)) | (1<<(4)) | (1<<(3)) );
			counter1 = 0;
		}
}
//

// mode2	
void mode2 (void){
	
	sei();
				
		if (counter2 == 0){
			LEDL(3);
			LEDH(5);
			}
				
		if (counter2 == 1){
			LEDL(5);
			LEDH(4);
			}
		
		if (counter2 == 2){
			LEDL(4);
			LEDH(3);
			}
			
		if (counter2 == 3){
			counter2 = 0;
	
	}
}
//

//mode3
void mode3(void){
	
	sei();
			
		if (counterB5 >= ((int) 500 / speed) ){
				LEDH(5);
				}
			
		if (counterB5 >= ((int) 1000 / speed) ){
				LEDL(5);
				counterB5 = 0;
				}
			
		if (counterB4 >= ((int) 1500 / speed) ){
				LEDH(4);
				}
			
		if (counterB4 >= ((int) 3000 / speed) ){
				LEDL(4);
				counterB4 = 0;
				}
			
		
		if (counterB3 >= ((int) 2500 / speed) ){
				LEDH(3);
				}
			
		if (counterB3 >= ((int) 5000 / speed) ){
				LEDL(3);
				counterB3 = 0;
				}
}
//
			
int B2_curst (void){
	if ( !(PINB & (1<<2) )){
		return 0;
		}
	else {return 1;}	
	}
	
int B1_curst (void){
	if ( !(PINB & (1<<1) )){
		return 0;
		}
	else {return 1;}	
	}
		
	
void milis(int n){
	
		mls = 0;
		TCNT2 = 0;
		TIFR2 = (1 << OCF2A); 
		TCCR2B |= (1<<CS22);
		
		TIMSK2 |= (1<<OCIE2A);
				
		while(mls < n){continue;}
		
		TCCR2B &= ~(1<<CS22);
		TIMSK2 &= ~(1<<OCIE2A);
		
		}	
					
int main(void){
	
				DDRB |= (1<<DDB5);
				DDRB |= (1<<DDB4);
				DDRB |= (1<<DDB3);
				TCCR1A = 0;
				TCCR1B = 0;
				TCCR1B |= (1<<WGM12) | (1<<CS12);
				TCNT1 = 0;
				TIMSK1 |= (1<<OCIE1A);
				OCR1A = ((int)(31250 / speed)) - 1;
					
	
	DDRB &= ~(1<<DDB1);
	PORTB |= (1<<PB1);
	
	DDRB &= ~(1<<DDB2);
	PORTB |= (1<<PB2);
	
	TCCR2A |= (1<<WGM21);
	TCCR2B = 0;
	OCR2A = 249;
	TCNT2 = 0;
	
	sei();
	while (1){
			
		if ( (B1_curst() == 0) & (B1prest == 1) ){
			milis(20);
			mode_st++;
			B1prest = B1_curst();
			
			switch(mode_st){
				
			case 1:
			
				DDRB |= (1<<DDB5);
				DDRB |= (1<<DDB4);
				DDRB |= (1<<DDB3);
				TCCR1A = 0;
				TCCR1B = 0;
				TCCR1B |= (1<<WGM12) | (1<<CS12);
				TCNT1 = 0;
				TIMSK1 |= (1<<OCIE1A);
				OCR1A = ((int)(31250 / speed)) - 1;
				
				break;
		
			case 2:
				
				DDRB |= (1<<DDB5);
				DDRB |= (1<<DDB4);
				DDRB |= (1<<DDB3);
				TCCR1A = 0;
				TCCR1B = 0;
				TCCR1B |= (1<<WGM12) | (1<<CS12);
				TCNT1 = 0;
				TIMSK1 |= (1<<OCIE1A);
				OCR1A = ((int)(31250 / speed)) - 1;
					
				break;
			
			case 3:
				
				DDRB |= (1<<DDB5);
				DDRB |= (1<<DDB4);
				DDRB |= (1<<DDB3);
				
				//Timer 1
				TCCR1A = 0;
				TCCR1B = 0;
				TCCR1B |= (1<<CS10);
				TCCR1B |= (1<<WGM12);
				TCNT1 = 0;
				TIMSK1 |= (1<<OCIE1A);
				OCR1A = ((int)(16000 / speed)) - 1;
				//

				break;	
			}
			}
		
		B1prest = B1_curst();
		
		switch(mode_st){
			
			case 1:
			
				mode1();
				break;
		
			case 2:
				
				mode2();
				break;
			
			case 3:
				
				mode3();
				break;	
			
			case 4:
			
				DDRB |= (1<<DDB5);
				DDRB |= (1<<DDB4);
				DDRB |= (1<<DDB3);
				TCCR1A = 0;
				TCCR1B = 0;
				TCCR1B |= (1<<WGM12) | (1<<CS12);
				TCNT1 = 0;
				TIMSK1 |= (1<<OCIE1A);
				OCR1A = ((int)(31250 / speed)) - 1;
				
				mode_st = 1;
				break;
			}
			
		
		milis(20);	
		if ( (B2_curst() == 0) & (B2prest == 1) ){
				
			B2prest = B2_curst();
			
			if (speed == 3){
			speed = 0;
			}
			
			if (speed < 3){
			speed++;
			TCNT1 = 0;
			OCR1A = ((int)(31250 / speed)) - 1;
			}
			
			
			}
			
		B2prest = B2_curst();
				
		}
		
	return 0;	
}
