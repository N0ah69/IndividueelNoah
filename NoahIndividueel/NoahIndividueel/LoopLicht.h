/*
 * LoopLicht.h
 * Header for the lightshow in general
 * Created: 23/06/2020 14:42:33
 *  Author: noahv
 */ 


#ifndef LOOPLICHT_H_
#define LOOPLICHT_H_

#define powerOn 1 //CREATED TO AVOID MAGIC NUMBERS IN THE FILL LIGHT FUNCTION
#define powerOff 0 //CREATED TO AVOID MAGIC NUMBERS IN THE FILL LIGHT FUNCTION

//NUMBER OF THE ROWS IN THE ARRAYLIST. CREATED TO AVOID MAGIC NUMBERS
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define numOfRows 5 //THE TOTAL NUMBER OF ROWS (-1)

//STRUCT THAT STORES ALL THE INFROMATION FOR A LED OW
typedef struct led_t
{
	volatile uint8_t *port_d; // Port refrence to instantly change LED info	
	int boolStates; // True/False for every led in a row.
} LED_INFO;

//THE LED_INFO STRUCTS USED
struct led_t ledsA;
struct led_t ledsB;
struct led_t ledsC;
struct led_t ledsD;
struct led_t ledsE;
struct led_t ledsF;
//ARRAY LIST WITH ALL THE STRUCTS USED
LED_INFO rows[numOfRows];

//FUNCTIONS USED BY THE PROGRAMM
void f_Init();
void f_blinkLight(LED_INFO *info, int time);
void f_scrollLight(volatile uint8_t *port_d);
void f_fillLight(int time, int power);
void f_flagLight(int time);
void f_comboLight(int row, int time);
void f_show();

#endif /* LOOPLICHT_H_ */