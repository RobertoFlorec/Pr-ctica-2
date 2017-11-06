/*
 * LCDFunctions.h
 *
 *  Created on: 23/10/2017
 *      Author: Roberto
 */

#ifndef LCDFUNCTIONS_H_
#define LCDFUNCTIONS_H_
#include "DataTypeDefinitions.h"
#include "GPIO.h"
#include "NVIC.h"

#define ZERO 0x30
#define ONE 0x31
#define TWO 0x32
#define THREE 0x33
#define FOUR 0x34
#define FIVE 0x35
#define SIX 0x36
#define SEVEN 0x37
#define EIGHT 0x38
#define NINE 0x39
#define PUNTO 0x20

typedef struct{
	uint8 BTN0: 1;
	uint8 BTN1: 1;
	uint8 BTN2: 1;
	uint8 BTN3: 1;
	uint8 BTN4: 1;
	uint8 BTN5: 1;
}BTNType;

typedef struct{
	uint8 BTN0_flag: 1;
	uint8 BTN1_flag: 1;
	uint8 BTN2_flag: 1;
	uint8 BTN3_flag: 1;
	uint8 BTN4_flag: 1;
	uint8 BTN5_flag: 1;
	uint8 BTN_flag: 1;
}BtnFlagType;

/**This function displays the first screen to be seen*/
void pantallaInicial(void);
/**This function displays the main menu and allow its functions to be active*/
void menu(void);
/**Displays the alarm menu, and let its functions to be active*/
void pantallaAlarma(void);
/**Displays the temperature format screen and allow its functions to be active*/
void pantallaFormatoTemp(void);
/**Displays the increase/decrease screen and allow its functions to be active*/
void pantallaDecremento(void);
/**Displays the manual control screen and allow its functions to be active*/
void pantallaCtrlManual(void);
/**Displays the frequency screen and allow its functions to be active*/
void pantallaFrecuancia(void);
/**It configures the buttons*/
void buttonsInit(void);
/**It clears the button interruption flag*/
void clearFlagC(void);
/**/
void convierteACelcius(void);
void convierteAFahrenheit(uint8 decenaTeperatura, uint8 unidadTemperatura);
#endif /* LCDFUNCTIONS_H_ */
