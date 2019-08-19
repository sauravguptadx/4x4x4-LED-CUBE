#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#define D4 eS_PORTB4
#define D5 eS_PORTB5
#define D6 eS_PORTB6
#define D7 eS_PORTB7
#define RS eS_PORTB2
#define EN eS_PORTB3

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>

int Min = 5;
int inc = 5;

static volatile int pulse = 0;//interger  to access all though the program

static volatile int i = 0;// interger  to access all though the program


volatile char c;
void designs(int design);

int design=0;

ISR(INT2_vect)
{
	int n = 0;
	//PORTC = 0x01;
	design--;
	if(design<0)
	design=8;
	designs(n);
	GIFR = 0xFF;

}

ISR(INT1_vect)
{
	//PORTC = 0x00;
	int n = 0;
	design++;
	if(design>8)
	design=0;
	designs(n);
	GIFR = 0xFF;
}

int main(void)
{

	DDRA = 0xff;
	DDRC = 0xff;
	DDRB= 0b11110011;
	//DDRD &= ~(1<<PD0);//Makes firs pin of PORTD as Input
	DDRD = 0b11110011; //Makes all pins of PORTD input
	//PORTA=0xff;
	PORTC=0xff;
	//designs(design);
	GICR = (1 << INT2) | (1 << INT1)| (1 << INT0);

	//MCUCR = MCUCR | 0x0a;
	//MCUCSR = MCUCSR | 0x0a;
	int n = 0;
	MCUCR|=(1<<ISC00);
	MCUCR =MCUCR | 0x0E;
	MCUCSR = MCUCSR & 0xBf;



	sei();// enabling global interrupts

	while(1)
	{
		int16_t COUNTA = 0;//storing digital output


		sei();// enabling global interrupts
		PORTD|=(1<<PIND0);

		_delay_us(15);///triggering the sensor for 15usec

		PORTD &=~(1<<PIND0);
		PORTC = 0xC3;
		COUNTA = pulse/58;//getting the distance based on formula on introduction
		if( COUNTA>=Min + 3*inc && COUNTA<=Min + 5*inc){
			PORTB = (0x80);
			PORTD = (0x80);
			PORTA = (0x88);
		}
		else if( COUNTA>Min && COUNTA<=Min + inc){
			PORTB = (0x10);
			PORTD = (0x10);
			PORTA = (0x11);
		}
		else if(COUNTA>Min+ inc && COUNTA<=Min + 2*inc ){
			PORTB = (0x20);
			PORTD = (0x20);
			PORTA = (0x22);
		}
		else if(COUNTA>Min+ 2*inc && COUNTA<=Min + 3*inc){
			PORTB = (0x40);
			PORTD = (0x40);
			PORTA = (0x44);
		}
		else{
			while(1) designs( n);

		}
		_delay_ms(200);
	}
}
void designs(int n){
	if (design == 0)
	{
		//begin design 0
		PORTC = (0xff);
		for(int i=0; i<1; i++)
		{
			PORTB = (0xf0);
			PORTA = (0x00);
			PORTD = (0x00);
			_delay_ms(200);
			if (design != 0) break;
			PORTD = (0xf0);
			PORTB = (0x00);
			_delay_ms(200);

			if (design != 0) break;
			PORTA = (0x0f);
			PORTD = (0x00);
			_delay_ms(200);
			if (design != 0) break;
			PORTA = (0xf0);
			_delay_ms(200);
			if (design != 0) break;
			PORTA = (0xff);
			_delay_ms(200);
			if (design != 0) break;
			PORTD = (0xf0);
			PORTA = (0xff);
			_delay_ms(200);
			if (design != 0) break;
			PORTB = (0xf0);
			PORTD = (0xf0);
			PORTA = (0xff);
			_delay_ms(200);
			if (design != 0) break;
			PORTB = (0xf0);
			PORTD = (0xf0);
			PORTA = (0x0f);
			_delay_ms(200);
			if (design != 0) break;
			PORTB = (0xf0);
			PORTD = (0xf0);
			PORTA = (0x00);
			_delay_ms(200);
			if (design != 0) break;
		}
	}
	else if (design == 1)
	{
		//begin design 1
		PORTC = (0xff);
		for(int i=0; i<1; i++)
		{
			PORTB = (0x80);
			PORTD = (0x80);
			PORTA = (0x88);
			_delay_ms(200);
			if (design != 1) break;

			PORTB= (0x40);
			PORTD = (0x40);
			PORTA = (0x44);
			_delay_ms(200);
			if (design != 1) break;

			PORTB= (0x20);
			PORTD = (0x20);
			PORTA = (0x22);
			_delay_ms(200);
			if (design != 1) break;

			PORTB= (0x10);
			PORTD = (0x10);
			PORTA = (0x11);
			_delay_ms(200);
			if (design != 1) break;

			PORTB = (0x30);
			PORTD = (0x30);
			PORTA = (0x33);
			_delay_ms(200);
			if (design != 1) break;

			PORTB = (0x70);
			PORTD = (0x70);
			PORTA = (0x77);
			_delay_ms(200);
			if (design != 1) break;

			PORTB = (0xf0);
			PORTD = (0xf0);
			PORTA = (0xff);
			_delay_ms(200);
			if (design != 1) break;

			PORTB = (0xe0);
			PORTD = (0xe0);
			PORTA = (0xee);
			_delay_ms(200);
			if (design != 1) break;

			PORTB = (0xc0);
			PORTD = (0xc0);
			PORTA = (0xcc);
			_delay_ms(200);
			if (design != 1) break;
		}
	}
	else if (design == 2)
	{
		//begin Design 2
		PORTB = (0xf0);
		PORTD = (0xf0);
		PORTA = (0xff);
		for (int i=0; i<1; i++)
		{
			PORTC = (0x80);
			_delay_ms(100);
			if (design != 2) break;

			PORTC = (0xc0);
			_delay_ms(100);
			if (design != 2) break;
			PORTC = (0xc2);
			_delay_ms(100);
			if (design != 2) break;
			PORTC = (0xc3);
			_delay_ms(100);
			if (design != 2) break;
			PORTC = (0x01);
			_delay_ms(100);
			if (design != 2) break;
			PORTC = (0x02);
			_delay_ms(100);
			if (design != 2) break;
			PORTC = (0x40);
			_delay_ms(100);
			if (design != 2) break;
			PORTC = (0x80);
			_delay_ms(100);
			if (design != 2) break;
		}

	}
	else if (design == 3)
	{
		PORTC = (0xff);
		for(int i=0; i<1; i++)
		{
			PORTB= (0x10);
			PORTD = (0x00);
			_delay_ms(100);
			if (design != 3) break;
			PORTD = (0x10);
			PORTB= (0x20);
			_delay_ms(100);
			if (design != 3) break;
			PORTA = (0x01);
			PORTD = (0x20);
			PORTB= (0x40);
			_delay_ms(100);
			if (design != 3) break;
			PORTA = (0x12);
			PORTD = (0x40);
			PORTB= (0x80);
			_delay_ms(100);
			if (design != 3) break;
			PORTA = (0x24);
			PORTD = (0x80);
			PORTB= (0x00);
			_delay_ms(100);
			if (design != 3) break;
			PORTD = (0x00);
			PORTA = (0x48);
			_delay_ms(100);
			if (design != 3) break;
			PORTA = (0x80);
			_delay_ms(100);
			if (design != 3) break;

			PORTA = (0x48);
			_delay_ms(100);
			if (design != 3) break;
			PORTA = (0x24);
			PORTD = (0x80);
			_delay_ms(100);
			if (design != 3) break;
			PORTA = (0x12);
			PORTD = (0x40);
			_delay_ms(100);
			PORTB= (0x80);
			if (design != 3) break;
			PORTA = (0x01);
			PORTD = (0x20);
			PORTB= (0x40);
			_delay_ms(100);
			if (design != 3) break;
			PORTA = (0x00);
			PORTD = (0x10);
			PORTB= (0x20);
			_delay_ms(100);
			if (design != 3) break;
			PORTD = (0x00);
			PORTB= (0x10);
			_delay_ms(100);
			if (design != 3) break;


			//PORTC = (0x00);
		}
	}
	else if (design == 4)
	{
		PORTD = (0xff);
		PORTD = (0x00);
		for(int i=0; i<1; i++)
		{
			PORTD = (0x20);
			PORTB= (0x10);
			PORTA = (0x84);
			_delay_ms(100);
			if (design != 4) break;
			PORTD = (0x20);
			PORTB= (0x20);
			PORTA = (0x44);
			_delay_ms(100);
			if (design != 4) break;

			PORTD = (0x40);
			PORTB= (0x40);
			PORTA = (0x22);
			_delay_ms(100);
			if (design != 4) break;

			PORTD = (0x40);
			PORTB= (0x80);
			PORTA = (0x12);
			_delay_ms(100);
			if (design != 4) break;

			PORTD = (0xc0);
			PORTB= (0x00);
			PORTA = (0x03);
			_delay_ms(100);
			if (design != 4) break;
			PORTD = (0x30);
			PORTA = (0x0C);
			_delay_ms(100);
			if (design != 4) break;
			//PORTA = (0x00);
		}
	}
	else if (design == 5)
	{
		//begin Design 5
		PORTC = (0xff);
		for(int i=0; i<1; i++)
		{
			PORTB = (0x10);
			PORTA = (0x00);
			PORTD = (0x00);
			_delay_ms(100);
			if (design != 5) break;
			PORTB = (0x30);
			_delay_ms(100);
			if (design != 5) break;
			PORTB = (0x70);
			_delay_ms(100);
			if (design != 5) break;
			PORTB = (0xf0);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x80);
			PORTB = (0xf0);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x80);
			PORTB = (0xf0);
			PORTA = (0x08);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x80);
			PORTB = (0xf0);
			PORTA = (0x88);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x80);
			PORTB = (0xf0);
			PORTA = (0xC8);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x80);
			PORTB = (0xf0);
			PORTA = (0xE8);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x80);
			PORTB = (0xf0);
			PORTA = (0xf8);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x80);
			PORTB = (0xf0);
			PORTA = (0xf9);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x90);
			PORTB = (0xf0);
			PORTA = (0xf9);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0xB0);
			PORTB = (0xf0);
			PORTA = (0xf9);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0xf0);
			PORTB = (0xf0);
			PORTA = (0xf9);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0xf0);
			PORTB = (0xf0);
			PORTA = (0xfD);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0xf0);
			PORTB = (0xf0);
			PORTA = (0xff);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0xd0);
			PORTB = (0xf0);
			PORTA = (0xff);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x90);
			PORTB = (0xf0);
			PORTA = (0xff);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x90);
			PORTB = (0xf0);
			PORTA = (0xfb);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x90);
			PORTB = (0xf0);
			PORTA = (0xf9);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x90);
			PORTB = (0xf0);
			PORTA = (0xf8);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x80);
			PORTB = (0xf0);
			PORTA = (0xf8);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x80);
			PORTB = (0xe0);
			PORTA = (0xf8);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x80);
			PORTB = (0xc0);
			PORTA = (0xf8);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x80);
			PORTB = (0x80);
			PORTA = (0xf8);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x80);
			PORTB = (0x00);
			PORTA = (0xf8);
			_delay_ms(100);
			if (design != 5) break;
			PORTD = (0x00);
			PORTA = (0xf8);
			_delay_ms(100);
			if (design != 5) break;
			PORTA = (0xf0);
			_delay_ms(100);
			if (design != 5) break;
			PORTA = (0x70);
			_delay_ms(100);
			if (design != 5) break;
			PORTA = (0x30);
			_delay_ms(100);
			if (design != 5) break;
			PORTA = (0x10);
			_delay_ms(100);
			if (design != 5) break;
		}
	}
	else if (design == 6)
	{
		//begin Design 6
		PORTA = (0x00);
		PORTC = (0x00);
		PORTD = (0x00);
		for(int i=0; i<1; i++)
		{
			for(int j=0; j<3; j++)
			{
				PORTC = (0x01);
				PORTD = (0x00);
				PORTB = (0x00);
				PORTA = (0x80);
				_delay_ms(100);
				if (design != 6) break;
				PORTC = (0x03);
				PORTD = (0x00);
				PORTA = (0xcc);
				_delay_ms(100);
				if (design != 6) break;
				PORTC = (0x43);
				PORTD = (0xE0);
				PORTA = (0xee);
				_delay_ms(100);
				if (design != 6) break;
				PORTC = (0xC3);
				PORTD = (0xf0);
				PORTB = (0xf0);
				PORTA = (0xff);
				_delay_ms(100);
				if (design != 6) break;
				PORTC = (0x43);
				PORTD = (0xE0);
				PORTB = (0xE0);
				PORTA = (0xee);
				_delay_ms(100);
				if (design != 6) break;
				PORTC = (0x03);
				PORTD = (0x00);
				PORTA = (0xcc);
				_delay_ms(100);
				if (design != 6) break;
				PORTC = (0x01);
				PORTD = (0x00);
				PORTA = (0x80);
				_delay_ms(100);
				if (design != 6) break;
			}
			PORTC = (0x01);
			PORTD = (0x00);
			PORTB = (0x00);
			PORTA = (0x80);
			_delay_ms(100);
			if (design != 6) break;
			PORTC = (0x03);
			PORTD = (0x00);
			PORTA = (0xcc);
			_delay_ms(100);
			if (design != 6) break;
			PORTC = (0x43);
			PORTD = (0xE0);
			PORTA = (0xee);
			_delay_ms(100);
			if (design != 6) break;
			PORTC = (0xC3);
			PORTD = (0xf0);
			PORTB = (0xf0);
			PORTA = (0xff);
			_delay_ms(100);
			if (design != 6) break;
			PORTC = (0xc2);
			PORTB = (0x70);
			PORTD = (0x70);
			PORTA = (0x07);
			_delay_ms(100);
			if (design != 6) break;
			PORTC = (0xc0);
			PORTB = (0x30);
			PORTD = (0x30);
			PORTA = (0x00);
			_delay_ms(100);
			if (design != 6) break;
			PORTC = (0x80);
			PORTB = (0x10);
			PORTD = (0x00);
			_delay_ms(100);
			if (design != 6) break;
			for(int j=0; j<3; j++)
			{
				PORTC = (0x80);
				PORTB = (0x10);
				PORTD = (0x00);
				PORTA = (0x00);
				_delay_ms(100);
				if (design != 6) break;
				PORTC = (0xc0);
				PORTB = (0x30);
				PORTD = (0x30);
				_delay_ms(100);
				if (design != 6) break;
				PORTC = (0xc2);
				PORTB = (0x70);
				PORTD = (0x70);
				PORTA = (0x07);
				_delay_ms(100);
				if (design != 6) break;
				PORTC = (0xc3);
				PORTB = (0xf0);
				PORTD = (0xf0);
				PORTA = (0xff);
				_delay_ms(100);
				if (design != 6) break;
				PORTC = (0xc2);
				PORTB = (0x70);
				PORTD = (0x70);
				PORTA = (0x07);
				_delay_ms(100);
				if (design != 6) break;
				PORTC = (0xc0);
				PORTB = (0x30);
				PORTD = (0x30);
				PORTA = (0x00);
				_delay_ms(100);
				if (design != 6) break;
				PORTC = (0x80);
				PORTB = (0x10);
				PORTD = (0x00);
				_delay_ms(100);
				if (design != 6) break;
			}

		}
	}
	else if (design == 7)
	{
		//begin Design 7
		for(int i=0; i<1; i++)
		{
			PORTC = (0xc0);
			PORTD = (0xf0);
			PORTB = (0xf0);
			PORTA = (0x00);
			_delay_ms(200);
			if (design != 7) break;

			PORTC = (0xc0);
			PORTD = (0xf0);
			PORTB = (0x00);
			PORTA = (0x0f);
			_delay_ms(200);
			if (design != 7) break;

			PORTC = (0xc0);
			PORTD = (0x00);
			PORTB = (0x00);
			PORTA = (0xff);
			_delay_ms(200);
			if (design != 7) break;

			PORTC = (0x42);
			PORTD = (0xf0);
			PORTB = (0xf0);
			PORTA = (0x00);
			_delay_ms(200);
			if (design != 7) break;

			PORTC = (0x42);
			PORTD = (0xf0);
			PORTB = (0x00);
			PORTA = (0x0f);
			_delay_ms(200);
			if (design != 7) break;

			PORTC = (0x42);
			PORTD = (0x00);
			PORTB = (0x00);
			PORTA = (0xff);
			_delay_ms(200);
			if (design != 7) break;

			PORTC = (0x03);
			PORTD = (0xf0);
			PORTB = (0xf0);
			PORTA = (0x00);
			_delay_ms(200);
			if (design != 7) break;

			PORTC = (0x03);
			PORTD = (0xf0);
			PORTB = (0x00);
			PORTA = (0x0f);
			_delay_ms(200);
			if (design != 7) break;

			PORTC = (0x03);
			PORTD = (0x00);
			PORTB = (0x00);
			PORTA = (0xff);
			_delay_ms(200);
			if (design != 7) break;

		}
	}
	else if (design == 8)
	{
		//begin Design 8
		for(int i=0; i<1; i++)
		{
			for (int i=0; i <4; i++)
			{
				if (i==0)
				PORTC=0x80;
				else if (i==1)
				PORTC=0xc0;
				else if (i==2)
				PORTC=0xc2;
				else if (i==3)
				PORTC=0xc3;
				//else if (i=4)PORTC=0x81;
				//else if (i=5)PORTC=0x82;
				//else if (i=6)PORTC=0xc0;
				//else if (i=7)PORTC=0xc1;
				//else if (i=8)PORTC=0xc2;
				PORTD = (0x60);
				PORTB = (0x10);
				PORTA = (0x06);
				_delay_ms(100);
				if (design != 8) break;

				PORTD = (0x60);
				PORTB = (0x20);
				PORTA = (0x06);
				_delay_ms(100);
				if (design != 8) break;

				PORTD = (0x60);
				PORTB = (0x40);
				PORTA = (0x06);
				_delay_ms(100);
				if (design != 8) break;

				PORTD = (0x60);
				PORTB = (0x80);
				PORTA = (0x06);
				_delay_ms(100);
				if (design != 8) break;

				PORTD = (0xe0);
				PORTB = (0x00);
				PORTA = (0x06);
				_delay_ms(100);
				if (design != 8) break;

				PORTD = (0x60);
				PORTB = (0x00);
				PORTA = (0x0e);
				_delay_ms(100);
				if (design != 8) break;

				PORTD = (0x60);
				PORTB = (0x00);
				PORTA = (0x06);
				_delay_ms(100);
				if (design != 8) break;

				PORTD = (0x60);
				PORTB = (0x00);
				PORTA = (0x86);
				_delay_ms(100);
				if (design != 8) break;

				PORTD = (0x60);
				PORTB = (0x00);
				PORTA = (0x46);
				_delay_ms(100);
				if (design != 8) break;

				PORTD = (0x60);
				PORTB = (0x00);
				PORTA = (0x26);
				_delay_ms(100);
				if (design != 8) break;

				PORTD = (0x60);
				PORTB = (0x00);
				PORTA = (0x16);
				_delay_ms(100);
				if (design != 8) break;

				PORTD = (0x60);
				PORTB = (0x00);
				PORTA = (0x07);
				_delay_ms(100);
				if (design != 8) break;

				PORTD = (0x70);
				PORTB = (0x00);
				PORTA = (0x06);
				_delay_ms(100);
				if (design != 8) break;
			}

		}
	}

}




