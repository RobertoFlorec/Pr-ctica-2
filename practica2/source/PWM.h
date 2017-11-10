/*
 * pwm.h
 *
 *  Created on: Nov 8, 2017
 *      Author: Santos
 */

#ifndef PWM_H_
#define PWM_H_


#include "DataTypeDefinitions.h"
//#include "GlobalFunctions.h"
#include "MK64F12.h"
#include "FlexTimer.h"

#define FRECUENCE_PWM   0x0A99
#define CiclosDuty 0x0FF
#define Tempu 25
#define Duty 219//para iniciar el Duty en 80%

#define dos 2
void config_SW_PWM(void);

void init_PWM(void);

void ini_values_PWM(uint32 Temperatura,BooleanType modoVelocidad);
uint16 Porsentaje(uint32 Temperatura);
uint8 Umbral();
sint16 incrementaPWM(sint16 dutyCycle);
sint16 decrementaPWM(sint16 dutyCycle);
void BuzzerInit(void);

#endif /* PWM_H_ */
