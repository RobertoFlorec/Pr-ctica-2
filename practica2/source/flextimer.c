/**
	\file
	\brief
		This is the starter file of FlexTimer.
		In this file the FlexTimer is configured in overflow mode.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Add configuration structures.
 */

#include "FlexTimer.h"
#include "MK64F12.h"
#include "GPIO.h"
#include "NVIC.h"

#include "FlexTimer.h"
#include "MK64F12.h"


static BooleanType FlexFlag0 = FALSE;
static BooleanType FlexFlag1 = FALSE;
static BooleanType FlexFlag2 = FALSE;

uint8 FTM_irqStatus(FTM_ChannelType channel){
	switch(channel)
				{
					case FTM_0: /** FTM 0 is selected*/
						return FlexFlag0;
						break;
					case FTM_1: /** FTM 1 is selected*/
						return FlexFlag1;
						break;
					case FTM_2: /** FTM 2 is selected*/
						return FlexFlag2;
						break;
					default: /**If doesn't exist the option*/
						return(FALSE);
				}
		/**Successful configuration*/
		return(TRUE);
	}// end function
void FTM0_IRQHandler(){				/** Se pone en 0 bit 7 (TIMER OVERFLOW) del registro FTM0_SC, limpia bandera*/
	FTM0->SC &= ~FLEX_TIMER_TOF;
	FlexFlag0=TRUE;

}

void FTM1_IRQHandler(){				/** Se pone en 0 bit 7 (TIMER OVERFLOW) del registro FTM0_SC, limpia bandera*/
	FTM1->SC &= ~FLEX_TIMER_TOF;
	FlexFlag1=TRUE;
}

void FTM2_IRQHandler(){				/** Se pone en 0 bit 7 (TIMER OVERFLOW) del registro FTM0_SC, limpia bandera*/
	FTM2->SC &= ~FLEX_TIMER_TOF;
	FlexFlag2=TRUE;
}

BooleanType FALSE_FTM_0(){
	return FlexFlag0 = FALSE;
}

BooleanType FALSE_FTM_1(){
	return FlexFlag1 = FALSE;
}

BooleanType FALSE_FTM_2(){
	return FlexFlag2 = FALSE;
}

//Funcion que activa el reloj del FTM, para poder utilizarlo
void FTM_ClockGatting(FTM_ChannelType channel)
{
	switch(channel)
	{
	case FTM_0:
		SIM->SCGC6 |= FTM0_CLOCK_GATTING;
		break;
	case FTM_1:
		SIM->SCGC6 |= FTM1_CLOCK_GATTING;
		break;
	case FTM_2:
		SIM->SCGC6 |= FTM2_CLOCK_GATTING;
		break;
	case FTM_3:
		SIM->SCGC6 |= FTM3_CLOCK_GATTING;
		break;
	default:
		break;
	}
}


//Funcion que habilita las interrupciones del FTM basandose en el OverFlow
void FTM_enableInterrupt(FTM_ChannelType channel, FTM_InterruptEnables interruptEnable){
	switch(channel)
	{
	case FTM_0:
		//comparamos el valor recibido con el valor que se tiene de la struct
		//si son iguales le ponemos el valor de uno de la mascara
		if(interruptEnable == FTM_INTERRUPT_DISABLE)
			FTM0->SC &= ~(FTM_SC_TOIE_MASK);
		// si no le ponemos el valor de 0 de la mascara
		else if(interruptEnable == FTM_INTERRUPT_ENABLE)
			FTM0->SC |= FTM_SC_TOIE_MASK;
		break;

	case FTM_1:
		if(interruptEnable == FTM_INTERRUPT_DISABLE)
			FTM1->SC &= ~(FTM_SC_TOIE_MASK);
		else if(interruptEnable == FTM_INTERRUPT_ENABLE)
			FTM1->SC |= FTM_SC_TOIE_MASK;
		break;

	case FTM_2:
		if(interruptEnable == FTM_INTERRUPT_DISABLE)
			FTM2->SC &= ~(FTM_SC_TOIE_MASK);
		else if(interruptEnable == FTM_INTERRUPT_ENABLE)
			FTM2->SC |= FTM_SC_TOIE_MASK;
		break;

	case FTM_3:
		if(interruptEnable == FTM_INTERRUPT_DISABLE)
			FTM3->SC &= ~(FTM_SC_TOIE_MASK);
		else if(interruptEnable == FTM_INTERRUPT_ENABLE)
			FTM3->SC |= FTM_SC_TOIE_MASK;
		break;

	default:
		break;
	}
}


//Funcion habilita WriteProtection de los registros de FTM
void FTM_enableWrite(FTM_ChannelType channel, FTM_WriteProtection writeEnable)
{
	switch(channel)
	{
	case FTM_0:
		if(writeEnable == WRITE_DISABLE)
			FTM0->MODE &= ~(FTM_MODE_WPDIS_MASK);
		else if(writeEnable == WRITE_ENABLE)
			FTM0->MODE |= FTM_MODE_WPDIS_MASK;
		break;

	case FTM_1:
		if(writeEnable == WRITE_DISABLE)
			FTM1->MODE &= ~(FTM_MODE_WPDIS_MASK);
		else if(writeEnable == WRITE_ENABLE)
			FTM1->MODE |= FTM_MODE_WPDIS_MASK;
		break;

	case FTM_2:
		if(writeEnable == WRITE_DISABLE)
			FTM2->MODE &= ~(FTM_MODE_WPDIS_MASK);
		else if(writeEnable == WRITE_ENABLE)
			FTM2->MODE |= FTM_MODE_WPDIS_MASK;
		break;

	case FTM_3:
		if(writeEnable == WRITE_DISABLE)
			FTM3->MODE &= ~(FTM_MODE_WPDIS_MASK);
		else if(writeEnable == WRITE_ENABLE)
			FTM3->MODE |= FTM_MODE_WPDIS_MASK;
		break;

	default:
		break;
	}
}

//Habilita el Flex Timer
void FTM_enableFTM(FTM_ChannelType channel, FTM_FTMEnable ftmEnable)
{
	switch(channel)
		{
		case FTM_0:
			if(ftmEnable == FTM_DISABLE)
				FTM0->MODE &= ~(FTM_MODE_FTMEN_MASK);
			else if(ftmEnable == FTM_ENABLE)
				FTM0->MODE |= FTM_MODE_FTMEN_MASK;
			break;

		case FTM_1:
			if(ftmEnable == FTM_DISABLE)
				FTM1->MODE &= ~(FTM_MODE_FTMEN_MASK);
			else if(ftmEnable == FTM_ENABLE)
				FTM1->MODE |= FTM_MODE_FTMEN_MASK;
			break;

		case FTM_2:
			if(ftmEnable == FTM_DISABLE)
				FTM2->MODE &= ~(FTM_MODE_FTMEN_MASK);
			else if(ftmEnable == FTM_ENABLE)
				FTM2->MODE |= FTM_MODE_FTMEN_MASK;
			break;

		case FTM_3:
			if(ftmEnable == FTM_DISABLE)
				FTM3->MODE &= ~(FTM_MODE_FTMEN_MASK);
			else if(ftmEnable == FTM_ENABLE)
				FTM3->MODE |= FTM_MODE_FTMEN_MASK;
			break;

		default:
			break;
		}
}


//Vuelve a comenzar el contador del FTM
void FTM_resetCount(FTM_ChannelType channel)
{
	switch(channel)
		{
		case FTM_0:
			FTM0->CNT = 0;
			break;

		case FTM_1:
			FTM1->CNT = 0;
			break;

		case FTM_2:
			FTM2->CNT = 0;
			break;

		case FTM_3:
			FTM3->CNT = 0;
			break;

		default:
			break;
		}
}


//Da el valor del conteo del OverFlow
void FTM_setCountOverflow(FTM_ChannelType channel, uint32 value)
{
	switch(channel)
		{
		case FTM_0:
			FTM0->MOD = value & FTM_MOD_MOD_MASK;
			break;

		case FTM_1:
			FTM1->MOD = value & FTM_MOD_MOD_MASK;
			break;

		case FTM_2:
			FTM2->MOD = value & FTM_MOD_MOD_MASK;
			break;

		case FTM_3:
			FTM3->MOD = value & FTM_MOD_MOD_MASK;
			break;

		default:
			break;
		}
}


//Le da el valor inicial al Contador
void FTM_setInitialCountValue(FTM_ChannelType channel, uint32 value)
{
	switch(channel)
		{
		case FTM_0:
			FTM0->CNTIN = value & FTM_CNTIN_INIT_MASK;
			break;

		case FTM_1:
			FTM1->CNTIN = value & FTM_CNTIN_INIT_MASK;
			break;

		case FTM_2:
			FTM2->CNTIN = value & FTM_CNTIN_INIT_MASK;
			break;

		case FTM_3:
			FTM3->CNTIN = value & FTM_CNTIN_INIT_MASK;
			break;

		default:
			break;
		}
}


//Selecciona la fuente de Reloj de cada FTM
void FTM_setClkSource(FTM_ChannelType channel, FTM_ClkSource clkSource)
{
	switch(channel)
		{
		case FTM_0:
			FTM0->SC |= ((clkSource << FTM_SC_CLKS_SHIFT) & (FTM_SC_CLKS_MASK));
			break;

		case FTM_1:
			FTM1->SC |= ((clkSource << FTM_SC_CLKS_SHIFT) & (FTM_SC_CLKS_MASK));
			break;

		case FTM_2:
			FTM2->SC |= ((clkSource << FTM_SC_CLKS_SHIFT) & (FTM_SC_CLKS_MASK));
			break;

		case FTM_3:
			FTM3->SC |= ((clkSource << FTM_SC_CLKS_SHIFT) & (FTM_SC_CLKS_MASK));
			break;

		default:
			break;
		}
}


//Selecciona el prescaler divider
void FTM_setPrDivider(FTM_ChannelType channel, FTM_PrescalerDivider divider)
{
	switch(channel)
		{
		case FTM_0:
			FTM0->SC |= ((divider) & (FTM_SC_PS_MASK));
			break;

		case FTM_1:
			FTM1->SC |= ((divider) & (FTM_SC_PS_MASK));
			break;

		case FTM_2:
			FTM2->SC |= ((divider) & (FTM_SC_PS_MASK));
			break;

		case FTM_3:
			FTM3->SC |= ((divider) & (FTM_SC_PS_MASK));
			break;

		default:
			break;
		}
}


//Selecciona el Cn del PWM
void FTM_setCnPWM(FTM_ChannelType channel, FTM_CnType cnChannel)
{
	switch(channel)
		{
		case FTM_0:
			FTM0->CONTROLS[cnChannel].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
			break;

		case FTM_1:
			FTM1->CONTROLS[cnChannel].CnSC  = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
			break;

		case FTM_2:
			FTM2->CONTROLS[cnChannel].CnSC  = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
			break;

		case FTM_3:
			FTM3->CONTROLS[cnChannel].CnSC  = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
			break;

		default:
			break;
		}
}


//Actualiza el valor del Cn
void FTM_updateCnValue(FTM_ChannelType channel, FTM_CnType cnChannel, uint32 cnValue)
{
	switch(channel)
		{
		case FTM_0:
			FTM0->CONTROLS[cnChannel].CnV  = cnValue & FTM_CnV_VAL_MASK;
			break;

		case FTM_1:
			FTM1->CONTROLS[cnChannel].CnV = cnValue & FTM_CnV_VAL_MASK;
			break;

		case FTM_2:
			FTM2->CONTROLS[cnChannel].CnV = cnValue & FTM_CnV_VAL_MASK;
			break;

		case FTM_3:
			FTM3->CONTROLS[cnChannel].CnV = cnValue & FTM_CnV_VAL_MASK;
			break;

		default:
			break;
		}
}


//Inicializa el FTM usando las funciones anteriores
void FTM_init(const FTM_ConfigType* FTMconfig)
{
	FTM_ClockGatting(FTMconfig->FTM_Channel);
	FTM_enableInterrupt(FTMconfig->FTM_Channel, FTMconfig->FTM_Interruption);
	FTM_enableWrite(FTMconfig->FTM_Channel, FTMconfig->FTM_WrProtection);
	FTM_enableFTM(FTMconfig->FTM_Channel, FTMconfig->FTM_Enable);
	FTM_setClkSource(FTMconfig->FTM_Channel, FTMconfig->FTM_Clock);
	FTM_setPrDivider(FTMconfig->FTM_Channel, FTMconfig->FTM_Divider);
	FTM_setInitialCountValue(FTMconfig->FTM_Channel, FTMconfig->FTM_InitialCnt);
	FTM_setCountOverflow(FTMconfig->FTM_Channel, FTMconfig->FTM_CountOVF);
	FTM_setCnPWM(FTMconfig->FTM_Channel, FTMconfig->FTM_Cn);
	FTM_resetCount(FTMconfig->FTM_Channel);
	FTM_updateCnValue(FTMconfig->FTM_Channel,FTMconfig->FTM_Cn,FTMconfig->FTM_CnValue);
}
