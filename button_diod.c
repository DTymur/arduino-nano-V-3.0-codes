#include <avr/io.h>

int main(void){
	
	DDRB |= (1<<DDB5);
	
	UBRR0H = 0;
	UBRR0L = 103;
	
	UCSR0B = (1<<RXEN0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	
	while (1){
		
		if (UCSR0A & (1<<RXC0)){
			
			char recived = UDR0;
			
			if (recived == '1'){
			PORTB |= (1<<PB5);
			}
		
			if (recived == '0'){
			PORTB &= ~(1<<PB5); 
			}
		}
	}	
	return 0;
}
