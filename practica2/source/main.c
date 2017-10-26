/**
	\file 
	\brief 
		This is a starter file to use the Nokia 5510 LCD. 
		The LCD is connected as follows:
		reset-PDT0
		CE-GND
		DC-PTD3
		DIN-PTD2
		CLK-PTD1
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	1/08/2015
	\todo
	    The SPI device driver needs to be completed.
 */

 
#include "SPI.h"
#include "GPIO.h"
#include "DatatypeDefinitions.h"
#include "LCDNokia5110.h"
#include "LCDNokia5110Images.h"
#include "GlobalFunctions.h"
#include "SPI.h"
#include "LCDFunctions.h"
#include <stdio.h>
/** \brief This is the configuration structure to configure the LCD.
 * Note that is constants and it is because is only a variable used for configuration*/
const SPI_ConfigType SPI_Config={SPI_DISABLE_FIFO,
							SPI_LOW_POLARITY,
							SPI_LOW_PHASE,
							SPI_MSB,
							SPI_0,
							SPI_MASTER,
							GPIO_MUX2,
							SPI_BAUD_RATE_2,
							SPI_FSIZE_8,
							{GPIO_D,BIT1,BIT2}};
/*! This array hold the initial picture that is shown in the LCD*/
extern const uint8 Finger[504];
uint8 string1[] = "Btn 0";
uint8 string2[] = "Btn 1";
uint8 string3[] = "Btn 2";
uint8 string4[] = "Btn 3";
uint8 string5[] = "Btn 4";
uint32 pressedBtn = 0;
uint8 flagC = FALSE;
uint8 Btn0_flag = FALSE;

typedef struct{
	uint8 BTN0: 1;
	uint8 BTN1: 1;
	uint8 BTN2: 1;
	uint8 BTN3: 1;
	uint8 BTN4: 1;
	uint8 BTN5: 1;
}BTNType;

typedef struct{
	uint8 BTN0_flag:1;
	uint8 BTN1_flag:1;
	uint8 BTN2_flag:1;
	uint8 BTN3_flag:1;
	uint8 BTN4_flag:1;
	uint8 BTN5_flag:1;
}BtnFlagType;

BTNType Btn;
BtnFlagType BtnFlag;

int main(void)
{
	buttonsInit();
	SPI_init(&SPI_Config); /*! Configuration function for the LCD port*/
	LCDNokia_init(); /*! Configuration function for the LCD */
	LCDNokia_clear();
	EnableInterrupts;

	pantallaInicial();

		while(1) {
			Btn.BTN0 = GPIO_readPIN(GPIO_C, BIT0);
			Btn.BTN1 = GPIO_readPIN(GPIO_C, BIT9);
			Btn.BTN2 = GPIO_readPIN(GPIO_C, BIT8);
			Btn.BTN3 = GPIO_readPIN(GPIO_C, BIT1);
			Btn.BTN4 = GPIO_readPIN(GPIO_C, BIT17);
			Btn.BTN5 = GPIO_readPIN(GPIO_C, BIT16);
			if()
			if(TRUE == flagCStatus()){
//				printf("\nInterrupcion correcta");

				 if(FALSE == Btn.BTN0){
					 clearFlagC();
					 BtnFlag.BTN0_flag = TRUE;
					 BtnFlag.BTN1_flag = FALSE;
					 BtnFlag.BTN2_flag = FALSE;
					 BtnFlag.BTN3_flag = FALSE;
					 BtnFlag.BTN4_flag = FALSE;
					 BtnFlag.BTN5_flag = FALSE;
					 LCDNokia_clear();
					 menu();
				 }
				 else if(FALSE == Btn.BTN1 && !BtnFlag.BTN2_flag && !BtnFlag.BTN3_flag && !BtnFlag.BTN4_flag && !BtnFlag.BTN5_flag){
					 clearFlagC();
					 BtnFlag.BTN1_flag = TRUE;
					 LCDNokia_clear();
					 pantallaAlarma();
				 }
				 else if(FALSE == Btn.BTN2 && !BtnFlag.BTN1_flag && !BtnFlag.BTN3_flag && !BtnFlag.BTN4_flag && !BtnFlag.BTN5_flag){
					 clearFlagC();
					 BtnFlag.BTN2_flag = TRUE;
					 LCDNokia_clear();
					 pantallaFormatoTemp();
				  }
				 else if(FALSE == Btn.BTN3  && !BtnFlag.BTN1_flag && !BtnFlag.BTN2_flag && !BtnFlag.BTN4_flag && !BtnFlag.BTN5_flag){
					 clearFlagC();
					 BtnFlag.BTN3_flag = TRUE;
					 LCDNokia_clear();
				 	 pantallaDecremento();
				 }
				 else if(FALSE == Btn.BTN4 && !BtnFlag.BTN1_flag && !BtnFlag.BTN2_flag && !BtnFlag.BTN3_flag && !BtnFlag.BTN5_flag){
					 clearFlagC();
					 BtnFlag.BTN4_flag = TRUE;
					 LCDNokia_clear();
					 pantallaCtrlManual();
				 }
				 else if(FALSE == Btn.BTN5 && !BtnFlag.BTN1_flag && !BtnFlag.BTN2_flag && !BtnFlag.BTN3_flag && !BtnFlag.BTN4_flag){
					 clearFlagC();
					 BtnFlag.BTN5_flag = TRUE;
					 LCDNokia_clear();
				 	 pantallaFrecuancia();
				 }
			 }
		}
	
	return 0;
}