/*
 * pwm.c
 *
 *  Created on: Nov 8, 2017
 *      Author: Santos
 */


#include <PWM.h>
#include "NVIC.h"
#include "MK64F12.h"
#include "GPIO.h"
#include "FlexTimer.h"

void config_SW_PWM(void) {
	///Se seleciona configuracion del Mux,con alternativa 3  que pone el pin en modo FTM0
	GPIO_pinControlRegisterType pinControlRegisterPWM = GPIO_MUX3|INTR_FALLING_EDGE;
	GPIO_clockGating(GPIO_A);										  ///Se enciende el reloj del puerto A
	GPIO_dataDirectionPIN(GPIO_A, GPIO_OUTPUT, BIT2);				 ///configura el puerto en salida del A y bit 2
	GPIO_pinControlRegister(GPIO_A, BIT2, &pinControlRegisterPWM);	///configuras el puerto como alternativa 3

}

void init_PWM(void) {
	/* habilitamos el reloj del FlexTimer 0*/
	FTM_ClockGatting(FTM_0);
	/* Si Write Protection esta habilitado (WPDIS = 0), los bits protegidos no pueden ser escritos.
	   Si Write Protection esta deshabilitado (WPDIS = 1), los bits protegidos no pueden ser escritos.*/
	FTM_enableWrite(FTM_0, WRITE_ENABLE);
	/*habilita la escritura de los registros en general */
	FTM_enableFTM(FTM_0, FTM_DISABLE);
	/* establecemos la resolucion de ftm*/
	FTM_setCountOverflow(FTM_0, CiclosDuty);
	/*Selecionamos el canal del ftm*/
	FTM_setCnPWM(FTM_0, CHANNEL_7);
	/**Aignamos el valor de 80% del duty que lo definimos como 219 decimal*/
	FTM_updateCnValue(FTM_0, CHANNEL_7, Duty);
	FTM_setClkSource(FTM_0, SYS_CLK);	//es el reloj de FLEX TIMER
	FTM_setPrDivider(FTM_0, DIVIDER_128);	//FLEX TIMER 128
}

sint16 incrementaPWM(sint16 dutyCycle){
	dutyCycle += 9;
	if(255 < dutyCycle){
		dutyCycle = 255;
	}
	return dutyCycle;
}
sint16 decrementaPWM(sint16 dutyCycle){
	dutyCycle -= 9;
	if(85 > dutyCycle){
		dutyCycle = 85;
	}
	return dutyCycle;

}


void BuzzerInit(void){
	GPIO_pinControlRegisterType pinControlRegisterBUZZER = GPIO_MUX1;
	GPIO_clockGating(GPIO_B);										  ///Se enciende el reloj del puerto A
	GPIO_dataDirectionPIN(GPIO_B, GPIO_OUTPUT, BIT23);				 ///configura el puerto en salida del A y bit 2
	GPIO_pinControlRegister(GPIO_B, BIT23, &pinControlRegisterBUZZER);
	GPIO_clearPIN(GPIO_B, BIT23);
}
