#include <avr/interrupt.h>
#define BAUD 38400

#define PORT PORTB
#define DDR  DDRB

void main(){
    //set up PORT as output
    PORT=0x00;
    DDR=0xFF;

    //initialise the USART
    unsigned int ubrr=(F_CPU/16/BAUD-1);
    UBRR0H=(unsigned char)(ubrr>>8);
    UBRR0L=(unsigned char)ubrr;
    UCSR0B=(1<<RXEN0)|(1<<TXEN0);
    UCSR0C=(3<<UCSZ00);

    //enable USART interrupts and turn on interrupts
    UCSR0B|=(1<<RXCIE0);
    sei();

    //waste CPU cycles
    while(1);
}

//handle incoming USART bytes..
ISR(USART_RX_vect){
    PORT=UDR0; //..and stick them into PORT
}

