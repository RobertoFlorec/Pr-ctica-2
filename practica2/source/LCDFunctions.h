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

void pantallaInicial(void);
void menu(void);
void pantallaAlarma(void);
void pantallaFormatoTemp(void);
void pantallaDecremento(void);
void pantallaCtrlManual(void);
void pantallaFrecuancia(void);
void buttonsInit(void);
uint8 flagCStatus(void);
void clearFlagC(void);
void convierteACelcius(void);
void convierteAFahrenheit(void);
#endif /* LCDFUNCTIONS_H_ */
