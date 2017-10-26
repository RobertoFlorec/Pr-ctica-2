/*
 * LCDFunctions.c
 *
 *  Created on: 23/10/2017
 *      Author: Roberto
 */

#include "LCDFunctions.h"
#include "LCDNokia5110.h"
#include <stdio.h>

extern uint8 flagC;

void pantallaInicial(void){
	uint8 velocidad[]="Velocidad"; /*! String to be printed in the LCD*/
	uint8 porcentaje[] = " %";
	uint8 temperatura[]="Temperatura"; /*! String to be printed in the LCD*/
	uint8 centigrados[] = "' C";

	LCDNokia_clear();
	LCDNokia_gotoXY(10,1);
	LCDNokia_sendString(velocidad);
	LCDNokia_gotoXY(20,2);
	LCDNokia_sendString(porcentaje);
	LCDNokia_gotoXY(5,3);
	LCDNokia_sendString(temperatura);
	LCDNokia_gotoXY(20,4);
	LCDNokia_sendString(centigrados);


}

void menu(void){

	uint8 alarma[] = "1) Alarma";
	uint8 formato[] = "2) Formato temp";
	uint8 porcentajeInc[] = "3) % de inc";
	uint8 controlManual[] = "4) Ctrl manual";
	uint8 frecuenciometro[] = "5) Frecuenciometro";

//	LCDNokia_clear();
	LCDNokia_gotoXY(0,0);
	LCDNokia_sendString(alarma);
	LCDNokia_gotoXY(0,1);
	LCDNokia_sendString(formato);
	LCDNokia_gotoXY(0,2);
	LCDNokia_sendString(porcentajeInc);
	LCDNokia_gotoXY(0,3);
	LCDNokia_sendString(controlManual);
	LCDNokia_gotoXY(0,4);
	LCDNokia_sendString(frecuenciometro);
}

void pantallaAlarma(void){
	uint8 alarma[] = "Alarma";
	uint8 porcentaje[] = "' C";
	uint8 control[] = "(-)B1(+)B2(ok)B3";

	LCDNokia_gotoXY(20,0);
	LCDNokia_sendString(alarma);
	LCDNokia_gotoXY(20,1);
	LCDNokia_sendString(porcentaje);
	LCDNokia_gotoXY(0,2);
	LCDNokia_sendString(control);


}

void pantallaFormatoTemp(void){
	uint8 formato[] = "Formato temp";
	uint8 temp[] = "Temp= ";
	uint8 control[] = "(C)B1(F)B2(ok)B3";

	LCDNokia_gotoXY(0,0);
	LCDNokia_sendString(formato);
	LCDNokia_gotoXY(10,1);
	LCDNokia_sendString(temp);
	LCDNokia_gotoXY(0,2);
	LCDNokia_sendString(control);

}

void pantallaDecremento(void){
	uint8 porcentaje[] = "% decre";
	uint8 dato[] = "dato";
	uint8 control[] = "(-)B1(+)B2(ok)B3";

	LCDNokia_gotoXY(10,0);
	LCDNokia_sendString(porcentaje);
	LCDNokia_gotoXY(20,1);
	LCDNokia_sendString(dato);
	LCDNokia_gotoXY(0,2);
	LCDNokia_sendString(control);

}

void pantallaCtrlManual(void){
	uint8 ctrlManual[] = "Ctrl Manual";
	uint8 porcentaje[] = " %";
	uint8 control[] = "(-)B1(+)B2(ok)B3";
	uint8 control2[] = "(-)B4(+)B5";

	LCDNokia_gotoXY(5,0);
	LCDNokia_sendString(ctrlManual);
	LCDNokia_gotoXY(20,1);
	LCDNokia_sendString(porcentaje);
	LCDNokia_gotoXY(0,2);
	LCDNokia_sendString(control);
	LCDNokia_gotoXY(5,4);
	LCDNokia_sendString(control2);

}

void pantallaFrecuancia(void){
	uint8 frecuencia[] = "Frencuencia";
	uint8 hz[] = "(Hz)";
	uint8 frec[] = "500.65";

	LCDNokia_gotoXY(5,0);
	LCDNokia_sendString(frecuencia);
	LCDNokia_gotoXY(20,1);
	LCDNokia_sendString(hz);
	LCDNokia_gotoXY(15,2);
	LCDNokia_sendString(frec);

}

void buttonsInit(void){
	GPIO_pinControlRegisterType pinControlRegisterButtons = GPIO_MUX1 |GPIO_PE | GPIO_PS | INTR_FALLING_EDGE;
	GPIO_clockGating(GPIO_C);
	GPIO_pinControlRegister(GPIO_C, BIT0, &pinControlRegisterButtons);
	GPIO_pinControlRegister(GPIO_C, BIT1, &pinControlRegisterButtons);
	GPIO_pinControlRegister(GPIO_C, BIT8, &pinControlRegisterButtons);
	GPIO_pinControlRegister(GPIO_C, BIT9, &pinControlRegisterButtons);
	GPIO_pinControlRegister(GPIO_C, BIT16, &pinControlRegisterButtons);
	GPIO_pinControlRegister(GPIO_C, BIT17, &pinControlRegisterButtons);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT0);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT1);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT8);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT9);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT16);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT17);
	GPIO_clearPIN(GPIO_C, BIT0);
	GPIO_clearPIN(GPIO_C, BIT1);
	GPIO_clearPIN(GPIO_C, BIT8);
	GPIO_clearPIN(GPIO_C, BIT9);
	GPIO_clearPIN(GPIO_C, BIT16);
	GPIO_clearPIN(GPIO_C, BIT17);
	NVIC_enableInterruptAndPriotity(PORTC_IRQ, PRIORITY_10);

}

void PORTC_IRQHandler(void){
	printf("\nHandler");
	flagC = TRUE;
	GPIO_clearInterrupt(GPIO_C);
}

uint8 flagCStatus(void){
	return flagC;
}

void clearFlagC(void){
	flagC = FALSE;
}
