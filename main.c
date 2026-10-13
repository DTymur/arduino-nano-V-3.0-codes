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
	st = 0,
	Bprest = 1;
	
	DDRB |= (1<<DDB5);
	
	DDRB &= ~(1<<DDB4);
	PORTB |= (1<<PB4);
	
	while (1){
		
		_delay_ms(50);	
		if ( (B4_curst() ^ Bprest) == 1){
			Bprest = B4_curst();
			st++;
			}
			
		if (2 == st || 1 == st){
			LEDH();
			}
			
		if (st > 2){
			LEDL();
			}
			
		if (st == 4){
			st = 0;
			}	
	}
	return 0;	
}
