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
#endif /* LCDFUNCTIONS_H_ */
