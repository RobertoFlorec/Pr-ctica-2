/*
 * LCDFunctions.c
 *
 *  Created on: 23/10/2017
 *      Author: Roberto
 */

#include "LCDFunctions.h"
#include "LCDNokia5110.h"
#include "GlobalFunctions.h"
#include <stdio.h>

extern uint8 flagC;
extern BooleanType flagIncr;
extern BooleanType flagAl;
extern BooleanType flagTemp;
static BooleanType flagCelcius = FALSE;
static BooleanType flagFahrenheit = FALSE;
extern uint8 otraBandera;
extern BTNType Btn;
static uint8 decenaAlarma = 0x33;
static uint8 unidadAlarma = 0x30;
static uint8 decenaIncre = 0x31;
static uint8 unidadIncre = 0x35;
static BooleanType flagSave = FALSE;
static uint8 decenaTemperatura = 0x33;
static uint8 unidadTemperatura = 0x31;
static BooleanType flag100 = FALSE;
static BooleanType flagSaveIncr = FALSE;
static BooleanType controlManualON = FALSE;
static BooleanType controlManualFlag = FALSE;
static BooleanType incremento = FALSE;

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
	uint8 porcentaje[] = "'C";
	uint8 control[] = "(-)B1 (+)B2";
	uint8 control2[] = "(ok)B3";
	uint8 decenaTemp = decenaAlarma;
	uint8 unidadTemp = unidadAlarma;

	while(1){
		Btn.BTN0 = GPIO_readPIN(GPIO_C, BIT0);
		Btn.BTN1 = GPIO_readPIN(GPIO_C, BIT9);
		Btn.BTN2 = GPIO_readPIN(GPIO_C, BIT8);
		Btn.BTN3 = GPIO_readPIN(GPIO_C, BIT1);
		if(FALSE == Btn.BTN0){
			if(flagSave){
				flagSave = FALSE;
			}else{
				decenaAlarma = decenaTemp;
				unidadAlarma = unidadTemp;
			}
			break;
		}
		if((FALSE == Btn.BTN1 && !flagAl)){
			unidadAlarma -= 0x01;
			if(0x30 > unidadAlarma){
				decenaAlarma -= 0x01;
				unidadAlarma = 0x39;

			}
			if(0x30 >= decenaAlarma){
				decenaAlarma = 0x30;
				unidadAlarma = 0x30;
			}
			delay(65000);

		}
		if((FALSE == Btn.BTN2)){
			unidadAlarma += 0x01;
			if(0x39 < unidadAlarma){
				decenaAlarma += 0x01;
				unidadAlarma = 0x30;

			}
			if((0x34 <= decenaAlarma) && (0x35 <= unidadAlarma)){
				decenaAlarma = 0x34;
				unidadAlarma = 0x35;
				flag100 = TRUE;
			}
			delay(65000);
		}
		if(FALSE == Btn.BTN3){
			flagSave = TRUE;
			break;
		}
		if (Btn.BTN1 && flagAl){
			flagAl = FALSE;
		}

		LCDNokia_gotoXY(20,0);
		LCDNokia_sendString(alarma);
		LCDNokia_gotoXY(30,1);
		LCDNokia_sendChar(decenaAlarma);
		LCDNokia_gotoXY(36,1);
		LCDNokia_sendChar(unidadAlarma);
		LCDNokia_gotoXY(42,1);
		LCDNokia_sendString(porcentaje);
		LCDNokia_gotoXY(5,2);
		LCDNokia_sendString(control);
		LCDNokia_gotoXY(15,3);
		LCDNokia_sendString(control2);
		otraBandera = FALSE;
	}
}

void pantallaFormatoTemp(void){
	uint8 formato[] = "Formato temp";
	uint8 temp[] = "Temp= ";
	uint8 celcius[] = "'C";
//	uint8 decenaTemp = decenaTemperatura;
//	uint8 unidadTemp = unidadTemperatura;
//	uint8 punto = 0x2E;
	uint8 control[] = "(C)B1(F)B2";
	uint8 control2[] = "(ok)B3";

		while(1){
			Btn.BTN0 = GPIO_readPIN(GPIO_C, BIT0);
			Btn.BTN1 = GPIO_readPIN(GPIO_C, BIT9);
			Btn.BTN2 = GPIO_readPIN(GPIO_C, BIT8);
			Btn.BTN3 = GPIO_readPIN(GPIO_C, BIT1);
			if(FALSE == Btn.BTN0){
				break;
			}
			if((FALSE == Btn.BTN1)){
				convierteACelcius();
				delay(65000);
			}
			if((FALSE == Btn.BTN2 && !flagTemp)){
				convierteAFahrenheit(decenaTemperatura, unidadTemperatura);
				delay(65000);
			}
			if(FALSE == Btn.BTN3){

				break;
			}
			if(Btn.BTN2 && flagTemp){
				flagTemp = FALSE;
			}


			LCDNokia_gotoXY(0,0);
			LCDNokia_sendString(formato);
			LCDNokia_gotoXY(10,2);
			LCDNokia_sendString(temp);
			LCDNokia_gotoXY(50,2);
			LCDNokia_sendChar(decenaTemperatura);
			LCDNokia_gotoXY(56,2);
			LCDNokia_sendChar(unidadTemperatura);
			LCDNokia_gotoXY(62,2);
			LCDNokia_sendString(celcius);
			LCDNokia_gotoXY(5,4);
			LCDNokia_sendString(control);
			LCDNokia_gotoXY(20,5);
			LCDNokia_sendString(control2);
		}
}

void pantallaDecremento(void){
	uint8 porcentajeDecre[] = "% decre";
	uint8 porcentajeIncre[] = "% incre";
	uint8 signoPorc[] = "%";
	uint8 control[] = "(-)B1(+)B2";
	uint8 control2[] = "(ok)B3";
	uint8 decenaTemp = decenaIncre;
	uint8 unidadTemp = unidadIncre;

		while(1){
			Btn.BTN0 = GPIO_readPIN(GPIO_C, BIT0);
			Btn.BTN1 = GPIO_readPIN(GPIO_C, BIT9);
			Btn.BTN2 = GPIO_readPIN(GPIO_C, BIT8);
			Btn.BTN3 = GPIO_readPIN(GPIO_C, BIT1);
			if(FALSE == Btn.BTN0){
				if(flagSaveIncr){
					flagSaveIncr = FALSE;
				}else{
					decenaIncre = decenaTemp;
					unidadIncre = unidadTemp;
				}
				break;
			}
			if((FALSE == Btn.BTN1)){
				flagIncr = FALSE;
				incremento = FALSE;
				if(flag100){
					LCDNokia_gotoXY(23,2);
					LCDNokia_sendChar(0x20);
					decenaIncre = 0x3A;
					flag100 = FALSE;
				}
				unidadIncre -= 0x05;
				if(0x30 > unidadIncre){
					decenaIncre -= 0x01;
					unidadIncre = 0x35;

				}
				if((0x30 >= decenaIncre) && (0x35 >= unidadIncre)){
					decenaIncre = 0x30;
					unidadIncre = 0x35;
				}
				delay(65000);

			}
			if((FALSE == Btn.BTN2 && !flag100)){
				flagIncr = FALSE;
				incremento = TRUE;
				unidadIncre += 0x05;

				if(0x39 < unidadIncre){
					decenaIncre += 0x01;
					unidadIncre = 0x30;

				}
				if((0x39 < decenaIncre) && (0x30 == unidadIncre)){
					decenaIncre = 0x30;
					unidadIncre = 0x30;
					flag100 = TRUE;
				}
				delay(65000);
			}
			if(FALSE == Btn.BTN3 && !flagIncr){
				flagSaveIncr = TRUE;
				break;
			}else{

			}

			LCDNokia_gotoXY(10,0);
			if(incremento){
			LCDNokia_sendString(porcentajeIncre);
			}else {
				LCDNokia_sendString(porcentajeDecre);
			}
			if(flag100){
				LCDNokia_gotoXY(23,2);
				LCDNokia_sendChar(0x31);
			}
			LCDNokia_gotoXY(29,2);
			LCDNokia_sendChar(decenaIncre);
			LCDNokia_gotoXY(35,2);
			LCDNokia_sendChar(unidadIncre);
			LCDNokia_gotoXY(41,2);
			LCDNokia_sendString(signoPorc);
			LCDNokia_gotoXY(5,4);
			LCDNokia_sendString(control);
			LCDNokia_gotoXY(20,5);
			LCDNokia_sendString(control2);

		}


}

void pantallaCtrlManual(void){
	uint8 ctrlManual[] = "Ctrl Manual";
	uint8 porcentaje[] = " %";
	uint8 controlON[] = "(ON)B1";
	uint8 controlOFF[] = "(OFF)B2";
	uint8 controlOK[] = "(ok)B3";
	uint8 controlMenos[] = "(-)B4";
	uint8 controlMas[] = "(+)B5";
	uint8 decenaTemp = decenaIncre;
	uint8 unidadTemp = unidadIncre;

	while(1){
		Btn.BTN0 = GPIO_readPIN(GPIO_C, BIT0);
		Btn.BTN1 = GPIO_readPIN(GPIO_C, BIT9);
		Btn.BTN2 = GPIO_readPIN(GPIO_C, BIT8);
		Btn.BTN3 = GPIO_readPIN(GPIO_C, BIT1);
		Btn.BTN4 = GPIO_readPIN(GPIO_C, BIT17);
		Btn.BTN5 = GPIO_readPIN(GPIO_C, BIT16);

		if(FALSE == Btn.BTN0){
			if(flagSaveIncr){
				flagSaveIncr = FALSE;
			}else{
				decenaIncre = decenaTemp;
				unidadIncre = unidadTemp;
			}
			break;
		}
		if(FALSE == Btn.BTN1){
			controlManualON = TRUE;
		}
		if(FALSE == Btn.BTN2){
			controlManualON = FALSE;
		}
		if(FALSE == Btn.BTN3){
			flagSaveIncr = TRUE;
			if(controlManualON){
				controlManualFlag = TRUE;
			}else if (!controlManualON){
				controlManualFlag = FALSE;
			}
		}
		if((FALSE == Btn.BTN4 && controlManualFlag)){
			if(flag100){
				LCDNokia_gotoXY(23,1);
				LCDNokia_sendChar(0x20);
				decenaIncre = 0x3A;
				flag100 = FALSE;
			}
			unidadIncre -= 0x05;
			if(0x30 > unidadIncre){
				decenaIncre -= 0x01;
				unidadIncre = 0x35;

			}
			if((0x30 >= decenaIncre) && (0x35 >= unidadIncre)){
				decenaIncre = 0x30;
				unidadIncre = 0x35;
			}
			delay(65000);

		}
		if((FALSE == Btn.BTN5 && !flag100 && controlManualFlag)){
			unidadIncre += 0x05;

			if(0x39 < unidadIncre){
				decenaIncre += 0x01;
				unidadIncre = 0x30;

			}
			if((0x39 < decenaIncre) && (0x30 == unidadIncre)){
				decenaIncre = 0x30;
				unidadIncre = 0x30;
				flag100 = TRUE;
			}
			delay(65000);
		}

		LCDNokia_gotoXY(10,0);
		LCDNokia_sendString(porcentaje);
		if(flag100){
			LCDNokia_gotoXY(23,1);
			LCDNokia_sendChar(0x31);
		}

		LCDNokia_gotoXY(5,0);
		LCDNokia_sendString(ctrlManual);
		LCDNokia_gotoXY(29,1);
		LCDNokia_sendChar(decenaIncre);
		LCDNokia_gotoXY(35,1);
		LCDNokia_sendChar(unidadIncre);
		LCDNokia_gotoXY(41,1);
		LCDNokia_sendString(porcentaje);
		LCDNokia_gotoXY(0,2);
		LCDNokia_sendString(controlON);
		LCDNokia_gotoXY(0,3);
		LCDNokia_sendString(controlOFF);
		LCDNokia_gotoXY(0,4);
		LCDNokia_sendString(controlOK);
		LCDNokia_gotoXY(49,2);
		LCDNokia_sendString(controlMenos);
		LCDNokia_gotoXY(49,3);
		LCDNokia_sendString(controlMas);
	}
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
	flagC = TRUE;
	GPIO_clearInterrupt(GPIO_C);
}

uint8 flagCStatus(void){
	return flagC;
}

void clearFlagC(void){
	flagC = FALSE;
}

void convierteACelcius(void){
	flagCelcius = TRUE;
	flagFahrenheit = FALSE;
	uint8 frecuencia[]="Entramos";
	uint8 hz[] = "a";
	uint8 frec[] = "Celcius";

		LCDNokia_clear();
		LCDNokia_gotoXY(5,0);
		LCDNokia_sendString(frecuencia);
		LCDNokia_gotoXY(20,1);
		LCDNokia_sendString(hz);
		LCDNokia_gotoXY(15,2);
		LCDNokia_sendString(frec);
}

void convierteAFahrenheit(uint8 decenaTemperatura, uint8 unidadTemperatura){

	static float temperaturaFahrenheit = 0.0;
	float counter;

	switch(decenaTemperatura){
	case 0x30:
		temperaturaFahrenheit += 0.0;
		break;
	case 0x31:
		temperaturaFahrenheit += 10.0;
		break;
	case 0x32:
		temperaturaFahrenheit +=20.0;
		break;
	case 0x33:
		temperaturaFahrenheit +=30.0;
		break;
	case 0x34:
		temperaturaFahrenheit += 40.0;
		break;
	case 0x35:
		temperaturaFahrenheit += 50.0;
		break;
	case 0x36:
		temperaturaFahrenheit += 60.0;
		break;
	case 0x37:
		temperaturaFahrenheit += 70.0;
		break;
	case 0x38:
		temperaturaFahrenheit += 80.0;
		break;
	case 0x39:
		temperaturaFahrenheit += 90.0;
		break;
	default:
		break;
	}

	switch(unidadTemperatura){
	case 0x30:
			temperaturaFahrenheit += 0.0;
			break;
		case 0x31:
			temperaturaFahrenheit += 1.0;
			break;
		case 0x32:
			temperaturaFahrenheit += 2.0;
			break;
		case 0x33:
			temperaturaFahrenheit += 3.0;
			break;
		case 0x34:
			temperaturaFahrenheit += 4.0;
			break;
		case 0x35:
			temperaturaFahrenheit += 5.0;
			break;
		case 0x36:
			temperaturaFahrenheit += 6.0;
			break;
		case 0x37:
			temperaturaFahrenheit += 7.0;
			break;
		case 0x38:
			temperaturaFahrenheit += 8.0;
			break;
		case 0x39:
			temperaturaFahrenheit += 9.0;
			break;
		default:
			break;
		}

	temperaturaFahrenheit = ((temperaturaFahrenheit) * 1.8) + 32;

//	for(counter = 0 ; counter < sizeof(temperaturaFahrenheit); counter++){
//		temperaturaFahrenheit >> counter;
//		if(TRUE == (temperaturaFahrenheit && 0x01)){
//			printf("%d", 1);
//		}else if(FALSE == (temperaturaFahrenheit && 0x01)){
//			printf("%d", 0);
//		}
//
//	}

//	float tempFahr= temperaturaFahrenheit;


	flagFahrenheit = TRUE;
	flagCelcius = FALSE;

//	     float tempFahr[]
		uint8 formato[] = "Formato temp";
		uint8 temp[] = "Temp= ";
		uint8 fahrenheit[] = "'F";
		uint8 punto = 0x2E;
		uint8 control[] = "(C)B1(F)B2";
		uint8 control2[] = "(ok)B3";

		LCDNokia_gotoXY(0,0);
		LCDNokia_sendString(formato);
		LCDNokia_gotoXY(10,2);
		LCDNokia_sendString(temp);
//		LCDNokia_gotoXY(50,2);
//		LCDNokia_sendString(tempFahr);
//		LCDNokia_gotoXY(56,2);
//		LCDNokia_sendChar(unidadTemperatura);
//		LCDNokia_gotoXY(62,2);
//		LCDNokia_sendString(fahrenheit);
		LCDNokia_gotoXY(5,4);
		LCDNokia_sendString(control);
		LCDNokia_gotoXY(20,5);
		LCDNokia_sendString(control2);

}
