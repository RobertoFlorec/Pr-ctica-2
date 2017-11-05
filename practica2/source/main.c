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

uint32 pressedBtn = 0;
uint8 flagC = FALSE;
BooleanType flagIncr = FALSE;
BooleanType flagAl = FALSE;
BooleanType flagTemp = FALSE;



BTNType Btn;
BtnFlagType BtnFlag;
uint8 otraBandera = FALSE;

int main(void)
{
 	BtnFlag.BTN0_flag = FALSE;
	BtnFlag.BTN1_flag = FALSE;
	BtnFlag.BTN2_flag = FALSE;
	BtnFlag.BTN3_flag = FALSE;
	BtnFlag.BTN4_flag = FALSE;
	BtnFlag.BTN5_flag = FALSE;
	BtnFlag.BTN_flag = FALSE;

	buttonsInit();
	SPI_init(&SPI_Config); /*! Configuration function for the LCD port*/
	LCDNokia_init(); /*! Configuration function for the LCD */
	LCDNokia_clear();
	EnableInterrupts;

	pantallaInicial();

		while(1) {
			/**This variables get the push buttons values*/
			Btn.BTN0 = GPIO_readPIN(GPIO_C, BIT0);
			Btn.BTN1 = GPIO_readPIN(GPIO_C, BIT9);
			Btn.BTN2 = GPIO_readPIN(GPIO_C, BIT8);
			Btn.BTN3 = GPIO_readPIN(GPIO_C, BIT1);
			Btn.BTN4 = GPIO_readPIN(GPIO_C, BIT17);
			Btn.BTN5 = GPIO_readPIN(GPIO_C, BIT16);

			/**If push button 0 is pressed*/
				 if(FALSE == Btn.BTN0){
					 clearFlagC(); /**Clears the interruption flag, to use it again later*/
					 BtnFlag.BTN0_flag = TRUE;/**Turns on the button 0 flag, to indicate */
					 BtnFlag.BTN_flag = TRUE;
					 otraBandera = TRUE;
					 BtnFlag.BTN1_flag = FALSE;
					 BtnFlag.BTN2_flag = FALSE;
					 BtnFlag.BTN3_flag = FALSE;
					 BtnFlag.BTN4_flag = FALSE;
					 BtnFlag.BTN5_flag = FALSE;
					 LCDNokia_clear();
					 menu();
				 }
				 else if(FALSE == Btn.BTN1 && BtnFlag.BTN_flag && !BtnFlag.BTN2_flag && !BtnFlag.BTN3_flag && !BtnFlag.BTN4_flag && !BtnFlag.BTN5_flag){
					 clearFlagC();
					 BtnFlag.BTN1_flag = TRUE;
					 flagAl = TRUE;
					 LCDNokia_clear();
					 pantallaAlarma();
				 }
				 else if(FALSE == Btn.BTN2 && BtnFlag.BTN_flag && !BtnFlag.BTN1_flag && !BtnFlag.BTN3_flag && !BtnFlag.BTN4_flag && !BtnFlag.BTN5_flag){
					 clearFlagC();
					 BtnFlag.BTN2_flag = TRUE;
					 flagTemp = TRUE;
					 LCDNokia_clear();
					 pantallaFormatoTemp();
				  }
				 else if(FALSE == Btn.BTN3 && BtnFlag.BTN_flag  && !BtnFlag.BTN1_flag && !BtnFlag.BTN2_flag && !BtnFlag.BTN4_flag && !BtnFlag.BTN5_flag){
					 clearFlagC();
					 flagIncr = TRUE;
					 BtnFlag.BTN3_flag = TRUE;
					 LCDNokia_clear();
				 	 pantallaDecremento();
				 }
				 else if(FALSE == Btn.BTN4 && BtnFlag.BTN_flag && !BtnFlag.BTN1_flag && !BtnFlag.BTN2_flag && !BtnFlag.BTN3_flag && !BtnFlag.BTN5_flag){
					 clearFlagC();
					 BtnFlag.BTN4_flag = TRUE;
					 LCDNokia_clear();
					 pantallaCtrlManual();
				 }
				 else if(FALSE == Btn.BTN5 && BtnFlag.BTN_flag && !BtnFlag.BTN1_flag && !BtnFlag.BTN2_flag && !BtnFlag.BTN3_flag && !BtnFlag.BTN4_flag){
					 clearFlagC();
					 BtnFlag.BTN5_flag = TRUE;
					 LCDNokia_clear();
				 	 pantallaFrecuancia();
				 }

		}
	
	return 0;
}
