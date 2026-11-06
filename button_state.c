#include <avr/io.h>
#include <util/delay.h>

int B4_curst (void){
	if ( (PINB & (1<<4)) == 0){
		return 0;
		}
	else {return 1;}	
	}
	
void LEDH (void){
	PORTB |= (1<<PB5);
	}
	
void LEDL (void){
	PORTB &= ~(1<<PB5);
	}
		
	
int main(void){
	
	unsigned int 
	st = 1,
	Bprest = 1;
	
	DDRB |= (1<<DDB5);
	
	DDRB &= ~(1<<DDB4);
	PORTB |= (1<<PB4);
	
	while (1){
		
		_delay_ms(50);	
		if ( (B4_curst() == 0) & (Bprest == 1) ){
			Bprest = B4_curst();
			st++;
			}
		
		Bprest = B4_curst();
			
		if (st == 1){
			LEDH();
			}
			
		if (st == 2){
			LEDL();
			}
			
		if (st == 3){
			st = 1;
			}	
	}
	return 0;	
}
