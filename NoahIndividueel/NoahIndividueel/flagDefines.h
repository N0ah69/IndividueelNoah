/*
 * flagDefines.h
 * Header for the Flaglight function
 * Created: 23/06/2020 17:20:28
 *  Author: noahv
 */ 


#ifndef FLAGDEFINES_H_
#define FLAGDEFINES_H_

//THESE DEFINES ARE FOR THE FLAGLIGHT FUNCTION. THEY EXIST TO MAKE THE LOOPING THROUGH THE FLAGS EASY.
#define flagLvl0 0b00000000
#define flagLvl1 0b10000000
#define flagLvl2 0b11000000
#define flagLvl3 0b11100000
#define flagLvl4 0b11110000
#define flagLvl5 0b11111000
#define flagLvl6 0b11111100
#define flagLvl7 0b11111110
#define flagLvl8 0b11111111
//TITLE SPEAKS FOR ITSELF, but this is used for the flaglight function, used to not have magic numbers.
#define loopsNeededForFullFlag 14




#endif /* FLAGDEFINES_H_ */