/*
 * flextimer.h
 *
 *  Created on: Oct 25, 2017
 *      Author: Santos
 */

#ifndef FLEXTIMER_H_
#define FLEXTIMER_H_

#include "DataTypeDefinitions.h"


#define FTM0_CLOCK_GATTING 0x01000000
#define FTM1_CLOCK_GATTING 0x02000000
#define FTM2_CLOCK_GATTING 0x03000000
#define FTM3_CLOCK_GATTING 0x04000000

#define FTM_TOF 0x80

#define FLEX_TIMER_FAULTIE  0x80
#define FLEX_TIMER_FAULTM_0   0x00
#define FLEX_TIMER_FAULTM_1   0x20
#define FLEX_TIMER_FAULTM_2   0x40
#define FLEX_TIMER_FAULTM_3   0x60
#define FLEX_TIMER_CAPTEST  0x10
#define FLEX_TIMER_PWMSYNC  0x08
#define FLEX_TIMER_WPDIS    0x04
#define FLEX_TIMER_INIT     0x02
#define FLEX_TIMER_FTMEN    0x01

#define FLEX_TIMER_TOF     0x80
#define FLEX_TIMER_TOIE    0x40
#define FLEX_TIMER_CPWMS   0x20
#define FLEX_TIMER_CLKS_0  0x00
#define FLEX_TIMER_CLKS_1  0x08
#define FLEX_TIMER_CLKS_2  0x10
#define FLEX_TIMER_CLKS_3  0x18
#define FLEX_TIMER_PS_1    0x00
#define FLEX_TIMER_PS_2    0x01
#define FLEX_TIMER_PS_4    0x02
#define FLEX_TIMER_PS_8    0x03
#define FLEX_TIMER_PS_16    0x04
#define FLEX_TIMER_PS_32    0x05
#define FLEX_TIMER_PS_64    0x06
#define FLEX_TIMER_PS_128    0x07

#define FLEX_TIMER_PWMLOAD_CH0 0x01
#define FLEX_TIMER_PWMLOAD_CH1 0x02
#define FLEX_TIMER_PWMLOAD_CH2 0x04
#define FLEX_TIMER_PWMLOAD_CH3 0x08
#define FLEX_TIMER_PWMLOAD_CH4 0x10
#define FLEX_TIMER_PWMLOAD_CH5 0x20
#define FLEX_TIMER_PWMLOAD_CH6 0x40
#define FLEX_TIMER_PWMLOAD_CH7 0x80
#define FLEX_TIMER_LDOK        0x200


#define  FLEX_TIMER_DMA   0x01
#define  FLEX_TIMER_ELSA  0x04
#define  FLEX_TIMER_ELSB  0x08
#define  FLEX_TIMER_MSA   0x10
#define  FLEX_TIMER_MSB   0x20
#define  FLEX_TIMER_CHIE  0x40
#define  FLEX_TIMER_CHF   0x80


typedef enum {
	FTM_0,
	FTM_1,
	FTM_2,
	FTM_3
}FTM_ChannelType;


typedef enum {
	DIVIDER_1,
	DIVIDER_2,
	DIVIDER_4,
	DIVIDER_8,
	DIVIDER_16,
	DIVIDER_32,
	DIVIDER_64,
	DIVIDER_128
}FTM_PrescalerDivider;


typedef enum {
	FTM_INTERRUPT_DISABLE,
	FTM_INTERRUPT_ENABLE
}FTM_InterruptEnables;


typedef enum {
	WRITE_DISABLE,
	WRITE_ENABLE
}FTM_WriteProtection;


typedef enum {
	FTM_ENABLE,
	FTM_DISABLE
}FTM_FTMEnable;


typedef enum {
	FTM_CLKDISABLE,
	SYS_CLK,
	FFREQ_CLK,
	EXT_CLK
}FTM_ClkSource;


typedef enum {
	CHANNEL_0,
	CHANNEL_1,
	CHANNEL_2,
	CHANNEL_3,
	CHANNEL_4,
	CHANNEL_5,
	CHANNEL_6,
	CHANNEL_7
}FTM_CnType;


typedef struct {
	FTM_ChannelType FTM_Channel;
	FTM_PrescalerDivider FTM_Divider;
	FTM_InterruptEnables FTM_Interruption;
	FTM_WriteProtection FTM_WrProtection;
	FTM_FTMEnable FTM_Enable;
	FTM_ClkSource FTM_Clock;
	FTM_CnType FTM_Cn;
	uint32 FTM_CountOVF;
	uint32 FTM_InitialCnt;
	uint16 FTM_CnValue;
}FTM_ConfigType;

typedef struct {
	FTM_ChannelType FTM_Channel;
	FTM_PrescalerDivider FTM_Divider;
	FTM_InterruptEnables FTM_Interruption;
	FTM_WriteProtection FTM_WrProtection;
	FTM_FTMEnable FTM_Enable;
	FTM_ClkSource FTM_Clock;
	FTM_CnType FTM_Cn;
	uint32 FTM_CountOVF;
	uint32 FTM_InitialCnt;
	uint16 FTM_CnValue;
}PWM_ConfigType;

//Funcion que activa los reloj del FTM
void FTM_ClockGatting(FTM_ChannelType channel);
//Funcion que habilita las interrupciones del FTM basandose en el OverFlow
void FTM_enableInterrupt(FTM_ChannelType channel, FTM_InterruptEnables interruptEnable);
//Funcion habilita WriteProtection de los registros de FTM
void FTM_enableWrite(FTM_ChannelType channel, FTM_WriteProtection writeEnable);
//Habilita el Flex Timer
void FTM_enableFTM(FTM_ChannelType channel, FTM_FTMEnable ftmEnable);
//Vuelve a comenzar el contador del FTM
void FTM_resetCount(FTM_ChannelType channel);
//Da el valor del conteo del OverFlow
void FTM_setCountOverflow(FTM_ChannelType channel, uint32 value);
//Le da el valor inicial al Contador
void FTM_setInitialCountValue(FTM_ChannelType channel, uint32 value);
//Selecciona la fuente de Reloj
void FTM_setClkSource(FTM_ChannelType channel, FTM_ClkSource clkSource);
//Selecciona el prescaler divider
void FTM_setPrDivider(FTM_ChannelType channel, FTM_PrescalerDivider divider);
//Selecciona el Cn del PWM
void FTM_setCnPWM(FTM_ChannelType channel, FTM_CnType cnChannel);
//Actualiza el valor del Cn
void FTM_updateCnValue(FTM_ChannelType channel, FTM_CnType cnChannel, uint32 cnValue);
//Inicializa el FTM
void FTM_init(const FTM_ConfigType* FTMconfig);

void PWM_init(const PWM_ConfigType* FTMconfig);
uint8 FTM_irqStatus(FTM_ChannelType channel);

BooleanType FALSE_FTM_0();
BooleanType FALSE_FTM_1();
BooleanType FALSE_FTM_2();



#endif /* FLEXTIMER_H_ */
