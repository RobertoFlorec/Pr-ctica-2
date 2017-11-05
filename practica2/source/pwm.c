/*
 * pwm.c
 *
 *  Created on: Oct 25, 2017
 *      Author: Santos
 */
#include "NVIC.h"
#include "MK64F12.h"
#include "GPIO.h"
#include "FlexTimer.h"
#include "pwm.h"
void config_SW_PWM(void) {
	///Se seleciona configuracion del Mux,con alternativa 3 donde se encuentra en la tabla "K64 Signal Multiplexing and Pin Assignments"
	GPIO_pinControlRegisterType pinControlRegisterPWM = GPIO_MUX3|INTR_FALLING_EDGE;
	GPIO_clockGating(GPIO_A);										  ///Se enciende el reloj del puerto A
	GPIO_dataDirectionPIN(GPIO_A, GPIO_OUTPUT, BIT2);				 ///configura el puerto en salida del A y bit 2
	GPIO_pinControlRegister(GPIO_A, BIT2, &pinControlRegisterPWM);	///configuras el puerto como alternativa 3
}

void init_PWM(void) {
	/* habilitamos el reloj del FlexTimer 0*/
	FTM_ClockGatting(FTM_0);
	/** Si Write Protection est� habilitado (WPDIS = 0), los bits protegidos no pueden ser escritos.
	 * Si Write Protection est� DEShabilitado (WPDIS = 1), los bits protegidos no pueden ser escritos.*/
	FTM_enableWrite(FTM_0, WRITE_ENABLE);
	/**Enables the writing over all registers*/
	FTM_enableFTM(FTM_0, FTM_DISABLE);
	/**Assigning a default value for modulo register*/
	FTM_setCountOverflow(FTM_0, CiclosDuty);	//Prescalar
	/**Selects the Edge-Aligned PWM mode mode*/
	FTM_setCnPWM(FTM_0, CHANNEL_7);
	/**Assign a duty cycle of 80%*/
	FTM_updateCnValue(FTM_0, CHANNEL_7, Duty);
	/**Configure the times, ambas funciones se hacen or, divisor de frecuencia de salida(prescalar or )*/
	FTM_setClkSource(FTM_0, SYS_CLK);	//es el reloj de FLEX TIMER 1
	FTM_setPrDivider(FTM_0, DIVIDER_128);	//FLEX TIMER 128
}







