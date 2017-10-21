/*
 * SPI.c
 *
 *  Created on: 21/10/2017
 *      Author: Roberto
 */
#include "SPI.h"

/*it enable the clock module of the SPI by modifying the MDIS bits*/
static void SPI_enable(SPI_ChannelType){

}

/*It activate the clock gating*/
static void SPI_clk(SPI_ChannelType){

}

/*It configure the SPI as a master or slave depending on the value of masterOrslave*/
static void SPI_setMaster(SPI_ChannelType channel, SPI_MasterType masterOrSlave){

}

/*It activate the TX and RX FIFOs of the SPI depending on the value of enableOrdisable*/
static void SPI_fIFO(SPI_ChannelType channel, SPI_EnableFIFOType enableOrDisable){

}

/*It selects the clock polarity depending on the value of cpol*/
static void SPI_clockPolarity(SPI_ChannelType channel, SPI_PolarityType cpol){

}

/*It selects the frame size depending on the value of frameSize and the macros that are defined above*/
static void SPI_frameSize(SPI_ChannelType channel, uint32 frameSize){

}

/*It selects the clock phase depending on the value of cpha*/
static void SPI_clockPhase(SPI_ChannelType channel, SPI_PhaseType cpha){

}

/*It selects the baud rate depending on the value of baudRate and the macros that are defined above*/
static void SPI_baudRate(SPI_ChannelType channel, uint32 baudRate){

}

/*It selects if MSB or LSM bits is first transmitted*/
static void SPI_mSBFirst(SPI_ChannelType channel, SPI_LSMorMSBType msb){

}

/*It stars the SPI transmission by modifying the value of HALT bit*/
void SPI_startTranference(SPI_ChannelType channel){

}

/*It stops the SPI transmission by modifying the value of HALT bit*/
void SPI_stopTranference(SPI_ChannelType channel){

}

/*It transmits the information contained in data*/
void SPI_sendOneByte(uint8 Data){

}

/*It configures the SPI for transmission, this function as arguments receives a pointer to a constant structure where are all
 * the configuration parameters*/
void SPI_init(const SPI_ConfigType*){

}
