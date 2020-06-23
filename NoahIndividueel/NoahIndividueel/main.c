/*
 * NoahIndividueel.c
 * A program that creates a little lightshow with the leds on the ATmega128A microcontroler board.
 * Created: 23/06/2020 14:40:11
 * Author : noahv
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "Looplicht.h"
#include "flagDefines.h"

/*
Function not made by me. Is used to delay certain processes.
*/
void wait( int ms )

{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

//A FUNCTION THAT PREPARES EVERYTHING FOR THE PROGRAMM. TURNS ON THE PORTS AND PUTS THEM ON OUTPUT.
void f_Init()
{
		DDRA = 0b11111111;
		DDRB = 0b11111111;
		DDRC = 0b11111111;
		DDRD = 0b11111111;
		DDRE = 0b11111111;
		DDRF = 0b11111111;
		DDRG = 0b11111111;			// All pins PORTD are set to output
		
		PORTA = 0x00;
		PORTB = 0x00;
		PORTC = 0x00;
		PORTD = 0x00;
		PORTE = 0x00;
		PORTF = 0x00;
		PORTG = 0x00;
		
		ledsA.port_d = &PORTA;
		ledsA.boolStates = 0b11111111;
		rows[0] = ledsA;
		
		ledsB.port_d = &PORTB;
		ledsB.boolStates = 0b11111111;
		rows[1] = ledsB;
		
		ledsC.port_d = &PORTC;
		ledsC.boolStates = 0b11111111;
		rows[2] = ledsC;
		
		ledsD.port_d = &PORTD;
		ledsD.boolStates = 0b11111111;
		rows[3] = ledsD;
		

		ledsE.port_d = &PORTE;
		ledsE.boolStates = 0b11111111;
		rows[4] = ledsE;
		
		struct led_t ledsF;
		ledsF.port_d = &PORTF;
		ledsF.boolStates = 0b11111111;
		rows[5] = ledsF;
		
}
/*
Turns the leds up and down from up to the bottom.
@param volatile uint8_t *port_d: The port that the fucntion is going to scroll through
*/
void f_scrollLight(volatile uint8_t *port_d){
	for ( int j = 0b00000001; j <= 0b10000001; j<<=1 )
	{
		*port_d = j;
		wait(1000);
	}
}

/*METHOD TO TURN THE ENTIRE FIELD ON OR OFF
@param int time: The time applied in the wait function
@param int power: Input either powerOn or powerOff to turn the entire field on or off.
*/
void f_fillLight(int time, int power){
	if (power != 0)
	{
		for (int i = 0; i <= numOfRows; i++)
		{
			rows[i].boolStates = 0b11111111;
			*rows[i].port_d = rows[i].boolStates;
			wait(time);
		}
	}
	else
	{	
		for (int i = 0; i <= numOfRows; i++)
		{
			rows[i].boolStates = 0b00000000;
			*rows[i].port_d = rows[i].boolStates;
			wait(time);
		}
	}	
}

//FUNCTION TO make a led blink.
void f_blinkLight(LED_INFO *info, int time){
	*info->port_d = info->boolStates;
	wait(time);
}

//CREATES A STAIRCASE OF LEDS THAT RUN UP.
void f_flagLight(int time){
	//CODE ADDED TO TURN ALL LIGHTS OFF IN ORDER TO HAVE NO ODD LIGHTS STILL ON DURING THE SHOW
	for (int i = 0; i <= numOfRows; i++)
	{
		rows[i].boolStates = 0b00000000;
		*rows[i].port_d = rows[i].boolStates;
		wait(time);
	}
	//THE FOR LOOP IS STARTED TO LOOP ENOUGH TIMES TO CREATE A FULL SQUARE.
	for (int i = 0; i <= loopsNeededForFullFlag; i++)
	{
		int flagcount = i;
		for (int i = 0; i <= numOfRows; i++)
		{
			//SWITCH STATEMENT TO SEE WHICH KIND OF LED POSITION NEEDS TO BE APPLIED
			switch (flagcount){
				case 0:
				rows[i].boolStates = flagLvl0;
				break;
				case 1:
				rows[i].boolStates = flagLvl1;
				break;
				case 2:
				rows[i].boolStates = flagLvl2;
				break;
				case 3:
				rows[i].boolStates = flagLvl4;
				break;
				case 4:
				rows[i].boolStates = flagLvl4;
				break;
				case 5:
				rows[i].boolStates = flagLvl5;
				break;
				case 6:
				rows[i].boolStates = flagLvl6;
				break;
				case 7:
				rows[i].boolStates = flagLvl7;
				break;
				case 8:
				rows[i].boolStates = flagLvl8;
				break;
				default:
				if (flagcount >= 8)
				{
					rows[i].boolStates = flagLvl8;
				}
				else if (flagcount <= 0)
				{
					rows[i].boolStates = flagLvl0;
				}
				break;		
			}
			*rows[i].port_d = rows[i].boolStates;
			flagcount--;
		}
		wait(time);
	}
	
}

/*
Method that applies Scrolllight and BlinkLight at the same time and makes a little show out of it.
int row: The row that needs to be turned on. Could be done using the defined: A, B, C, D, E.
int time: The time is the time applied in the wait in every statement.
*/
void f_comboLight(int row, int time){
	
			f_scrollLight(rows[row].port_d);	
			f_blinkLight(&rows[row], time);		
			rows[row].boolStates = 0b01100110;
			f_blinkLight(&rows[row], time);	
			rows[row].boolStates = 0b00011000;
			f_blinkLight(&rows[row], time);	
			rows[row].boolStates = 0b01100110;
			f_blinkLight(&rows[row], time);	
			
			f_scrollLight(rows[row].port_d);
			
			rows[row].boolStates = 0b01100110;
			f_blinkLight(&rows[row], time);	
			rows[row].boolStates = 0b00011000;
			f_blinkLight(&rows[row], time);	
			rows[row].boolStates = 0b01100110;
			f_blinkLight(&rows[row], time);	

}


//THIS METHOD CREATES AN ENTIRE SHOW OUT OF THE IMPLEMENTED FUNCTIONS.
void f_show(){
	f_fillLight(500, powerOn);
	f_fillLight(500, powerOff);
	for (int i = 0; i <= numOfRows; i++)
	{
		f_comboLight(i, 800);
	}
	f_fillLight(500, powerOff);
	for (int i = 100; i <= 1000; i+= 100)
	{
		f_flagLight(i);
	}

}

//THE MAIN METHOD. WHAT IS STARTED.
int main(void)
{
    f_Init();
	while (1){
	f_show();
	}
}

