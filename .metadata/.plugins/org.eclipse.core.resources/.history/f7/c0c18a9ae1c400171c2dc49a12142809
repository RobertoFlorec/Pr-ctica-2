/*
 * SPI.c
 *
 *  Created on: 21/10/2017
 *      Author: Roberto
 */
#include "SPI.h"

/*it enable the clock module of the SPI by modifying the MDIS bits*/
static void SPI_enable(SPI_ChannelType channel){

	/**This switch case, selects the required SPI channel*/
	switch(channel){
		case SPI_0:
			SPI0->MCR &= ~(SPI_MCR_MDIS_MASK);/**Enables SPI0 by placing a 0 in the MDIS bit*/
			break;
		case SPI_1:
			SPI1->MCR &= ~(SPI_MCR_MDIS_MASK);/**Enables SPI0 by placing a 1 in the MDIS bit*/
			break;
		case SPI_2:
			SPI2->MCR &= ~(SPI_MCR_MDIS_MASK);/**Enables SPI0 by placing a 2 in the MDIS bit*/
			break;
		default:
			break;
	}
}

/*It activate the clock gating*/
static void SPI_clk(SPI_ChannelType channel){

	/**This switch case, selects the required SPI channel*/
		switch(channel){
			case SPI_0:
				SIM->SCGC6 = SPI0_CLOCK_GATING;/**Enables SPI0 Clock Gating*/
				break;
			case SPI_1:
				SIM->SCGC6 = SPI1_CLOCK_GATING;/**Enables SPI1 Clock Gating*/
				break;
			case SPI_2:
				SIM->SCGC6 = SPI2_CLOCK_GATING;/**Enables SPI2 Clock Gating*/
				break;
			default:
				break;
		}
}

/*It configure the SPI as a master or slave depending on the value of masterOrslave*/
static void SPI_setMaster(SPI_ChannelType channel, SPI_MasterType masterOrSlave){

	/**This switch case, selects the required SPI channel*/
	switch(channel){
	case SPI_0:
		if(SPI_MASTER == masterOrSlave){
			SPI0->MCR |= SPI_MCR_MSTR_MASK; /**When SPI0 Master in selected, this sentence places 1 in the MSTR bit configuring it as master*/
		}else if(SPI_SLAVE == masterOrSlave){
			SPI0->MCR &= ~(SPI_MCR_MSTR_MASK);/**When SPI0 Slave in selected, this sentence places 0 in the MSTR bit configuring it as slave*/
		}
		break;
	case SPI_1:
		if(SPI_MASTER == masterOrSlave){
			SPI1->MCR |= SPI_MCR_MSTR_MASK;/**When SPI1 Master in selected, this sentence places 1 in the MSTR bit configuring it as master*/
		}else if(SPI_SLAVE == masterOrSlave){
			SPI1->MCR &= ~(SPI_MCR_MSTR_MASK);/**When SPI1 Slave in selected, this sentence places 0 in the MSTR bit configuring it as slave*/
		}
		break;
	case SPI_2:
		if(SPI_MASTER == masterOrSlave){
			SPI2->MCR |= SPI_MCR_MSTR_MASK;/**When SPI2 Master in selected, this sentence places 1 in the MSTR bit configuring it as master*/
		}else if(SPI_SLAVE == masterOrSlave){
			SPI2->MCR &= ~(SPI_MCR_MSTR_MASK);/**When SPI2 Slave in selected, this sentence places 0 in the MSTR bit configuring it as slave*/
		}
		break;
	default:
		break;


	}

}

/*It activate the TX and RX FIFOs of the SPI depending on the value of enableOrdisable*/
static void SPI_fIFO(SPI_ChannelType channel, SPI_EnableFIFOType enableOrDisable){

	/**This switch case, selects the required SPI channel*/
		switch(channel){
			case SPI_0:
				if(SPI_ENABLE_FIFO == enableOrDisable){
					SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK);/**If Enable FIFO is selected, this sentence places a 0 in the RXF bit enabling it*/
					SPI0->MCR &= ~(SPI_MCR_DIS_TXF_MASK);/**If Enable FIFO is selected, this sentence places a 0 in the TXF bit enabling it*/
				}else if(SPI_DISABLE_FIFO == enableOrDisable){
					SPI0->MCR |= SPI_MCR_DIS_RXF_MASK;/**If Disable FIFO is selected, this sentence places a 1 in the RXF bit disabling it*/
					SPI0->MCR |= SPI_MCR_DIS_TXF_MASK;/**If Disable FIFO is selected, this sentence places a 1 in the TXF bit disabling it*/
				}
				break;
			case SPI_1:
				if(SPI_ENABLE_FIFO == enableOrDisable){
					SPI1->MCR &= ~(SPI_MCR_DIS_RXF_MASK);/**If Enable FIFO is selected, this sentence places a 0 in the RXF bit enabling it*/
					SPI1->MCR &= ~(SPI_MCR_DIS_TXF_MASK);/**If Enable FIFO is selected, this sentence places a 0 in the TXF bit enabling it*/
				}else if(SPI_DISABLE_FIFO == enableOrDisable){
					SPI1->MCR |= SPI_MCR_DIS_RXF_MASK;/**If Disable FIFO is selected, this sentence places a 1 in the RXF bit disabling it*/
					SPI1->MCR |= SPI_MCR_DIS_TXF_MASK;/**If Disable FIFO is selected, this sentence places a 1 in the RXF bit disabling it*/
				}
				break;
			case SPI_2:
				if(SPI_ENABLE_FIFO == enableOrDisable){
					SPI2->MCR &= ~(SPI_MCR_DIS_RXF_MASK);/**If Enable FIFO is selected, this sentence places a 0 in the RXF bit enabling it*/
					SPI2->MCR &= ~(SPI_MCR_DIS_TXF_MASK);/**If Enable FIFO is selected, this sentence places a 0 in the TXF bit enabling it*/
				}else if(SPI_DISABLE_FIFO == enableOrDisable){
					SPI2->MCR |= SPI_MCR_DIS_RXF_MASK;/**If Disable FIFO is selected, this sentence places a 1 in the RXF bit disabling it*/
					SPI2->MCR |= SPI_MCR_DIS_TXF_MASK;/**If Disable FIFO is selected, this sentence places a 1 in the TXF bit disabling it*/
				}
				break;
			default:
				break;
		}

}

/*It selects the clock polarity depending on the value of cpol*/
static void SPI_clockPolarity(SPI_ChannelType channel, SPI_PolarityType cpol){

	/**This switch case, selects the required SPI channel*/
	switch(channel){
	case SPI_0:
		if(SPI_LOW_POLARITY == cpol){
			SPI0->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);/**If Low Polarity is selected, this sentence places a 0 in the CPOL bit enabling the inactive state value of the Serial Communications Clock as low */
		}else if(SPI_HIGH_POLARITY == cpol){
			SPI0->CTAR[0] |= SPI_CTAR_CPOL_MASK;/**If High Polarity is selected, this sentence places a 1 in the CPOL bit enabling the inactive state value of the Serial Communications Clock as high */
		}
		break;
	case SPI_1:
		if(SPI_LOW_POLARITY == cpol){
			SPI1->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);/**If Low Polarity is selected, this sentence places a 0 in the CPOL bit enabling the inactive state value of the Serial Communications Clock as low */
		}else if(SPI_HIGH_POLARITY == cpol){
			SPI1->CTAR[0] |= SPI_CTAR_CPOL_MASK;/**If High Polarity is selected, this sentence places a 1 in the CPOL bit enabling the inactive state value of the Serial Communications Clock as high*/
		}
		break;
	case SPI_2:
		if(SPI_LOW_POLARITY == cpol){
			SPI2->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);/**If Low Polarity is selected, this sentence places a 0 in the CPOL bit enabling the inactive state value of the Serial Communications Clock as low */
		}else if(SPI_HIGH_POLARITY == cpol){
			SPI2->CTAR[0] |= SPI_CTAR_CPOL_MASK;/**If High Polarity is selected, this sentence places a 1 in the CPOL bit enabling the inactive state value of the Serial Communications Clock as high*/
		}
		break;
	default:
		break;
	}
}

/*It selects the frame size depending on the value of frameSize and the macros that are defined above*/
static void SPI_frameSize(SPI_ChannelType channel, uint32 frameSize){

	/**This switch case, selects the required SPI channel*/
	switch(channel){
	case SPI_0:
		SPI0->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);/**This sentences clear the last 4 bits of the CTAR register, letting a new value to be written*/
		SPI0->CTAR[0] |= frameSize;/**This sentence writes a new frame size value to the CTAR register*/
		break;
	case SPI_1:
		SPI1->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);/**This sentences clear the last 4 bits of the CTAR register, letting a new value to be written*/
		SPI1->CTAR[0] |= frameSize;/**This sentence writes a new frame size value to the CTAR register*/
		break;
	case SPI_2:
		SPI2->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);/**This sentences clear the last 4 bits of the CTAR register, letting a new value to be written*/
		SPI2->CTAR[0] |= frameSize;/**This sentence writes a new frame size value to the CTAR register*/
		break;
	default:
		break;
	}
}

/*It selects the clock phase depending on the value of cpha*/
static void SPI_clockPhase(SPI_ChannelType channel, SPI_PhaseType cpha){

	/**This switch case, selects the required SPI channel*/
	switch(channel){
	case SPI_0:
		if(SPI_LOW_PHASE == cpha){
			SPI0->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);/**If Low Phase is selected, this sentence puts a 0 in the CPHA bit capturing data on the leading edge of the Serial Communications Clock and changing on the next following edge*/
		}else if(SPI_HIGH_PHASE == cpha){
			SPI0->CTAR[0] |= SPI_CTAR_CPHA_MASK;/**If High Phase is selected, this sentence puts 1 in the CPHA bit changing on the leading edge of the Serial Communications Clock and capturing data on the next following edge*/
		}
		break;
	case SPI_1:
		if(SPI_LOW_PHASE == cpha){
			SPI1->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);/**If Low Phase is selected, this sentence puts a 0 in the CPHA bit capturing data on the leading edge of the Serial Communications Clock and changing on the next following edge*/
		}else if(SPI_HIGH_PHASE == cpha){
			SPI1->CTAR[0] |= SPI_CTAR_CPHA_MASK;/**If High Phase is selected, this sentence puts 1 in the CPHA bit changing on the leading edge of the Serial Communications Clock and capturing data on the next following edge*/
		}
		break;
	case SPI_2:
		if(SPI_LOW_PHASE == cpha){
			SPI2->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);/**If Low Phase is selected, this sentence puts a 0 in the CPHA bit capturing data on the leading edge of the Serial Communications Clock and changing on the next following edge*/
		}else if(SPI_HIGH_PHASE == cpha){
			SPI2->CTAR[0] |= SPI_CTAR_CPHA_MASK;/**If High Phase is selected, this sentence puts 1 in the CPHA bit changing on the leading edge of the Serial Communications Clock and capturing data on the next following edge*/
		}
		break;
	default:
		break;
	}
}

/*It selects the baud rate depending on the value of baudRate and the macros that are defined above*/
static void SPI_baudRate(SPI_ChannelType channel, uint32 baudRate){

	/**This switch case, selects the required SPI channel*/
	switch(channel){
		case SPI_0:
			SPI0->CTAR[0] &= ~(SPI_CTAR_BR_MASK);/**This sentence clears the four bits of the Baud Rate Scaler */
			SPI0->CTAR[0] |= baudRate;/**This sentence places baudRate value in the Baud Rate Scaler bits*/
			break;
		case SPI_1:
			SPI1->CTAR[0] &= ~(SPI_CTAR_BR_MASK);/**This sentence clears the four bits of the Baud Rate Scaler */
			SPI1->CTAR[0] |= baudRate;/**This sentence places baudRate value in the Baud Rate Scaler bits*/
			break;
		case SPI_2:
			SPI2->CTAR[0] &= ~(SPI_CTAR_BR_MASK);/**This sentence clears the four bits of the Baud Rate Scaler */
			SPI2->CTAR[0] |= baudRate;/**This sentence places baudRate value in the Baud Rate Scaler bits*/
			break;
		default:
			break;
	}
}

/*It selects if MSB or LSM bits is first transmitted*/
static void SPI_mSBFirst(SPI_ChannelType channel, SPI_LSMorMSBType msb){

	/**This switch case, selects the required SPI channel*/
	switch(channel){
	case SPI_0:
		if(SPI_MSB == msb){
			SPI0->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);/**If Most Significant Bit is selected, this sentence places a 0 in the LSBFE bit enabling data to be transferred MSB first.*/
		}else if(SPI_LSM == msb){
			SPI0->CTAR[0] |= SPI_CTAR_LSBFE_MASK;/**If Less Significant Bit is selected, this sentence places a 1 in the LSBFE bit enabling data to be transferred LSB first.*/
		}
		break;
	case SPI_1:
		if(SPI_MSB == msb){
			SPI1->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);/**If Most Significant Bit is selected, this sentence places a 0 in the LSBFE bit enabling data to be transferred MSB first.*/
		}else if(SPI_LSM == msb){
			SPI1->CTAR[0] |= SPI_CTAR_LSBFE_MASK;/**If Less Significant Bit is selected, this sentence places a 1 in the LSBFE bit enabling data to be transferred LSB first.*/
		}
		break;
	case SPI_2:
		if(SPI_MSB == msb){
			SPI2->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);/**If Most Significant Bit is selected, this sentence places a 0 in the LSBFE bit enabling data to be transferred MSB first.*/
		}else if(SPI_LSM == msb){
			SPI2->CTAR[0] |= SPI_CTAR_LSBFE_MASK;/**If Less Significant Bit is selected, this sentence places a 1 in the LSBFE bit enabling data to be transferred LSB first.*/
		}
		break;
	default:
		break;
	}
}

/*It stars the SPI transmission by modifying the value of HALT bit*/
void SPI_startTranference(SPI_ChannelType channel){

	/**This switch case, selects the required SPI channel*/
	switch(channel){
	case SPI_0:
		SPI0->MCR &= ~(SPI_MCR_HALT_MASK);/**Starts transfers by placing 0 in the HALT bit*/
		break;
	case SPI_1:
		SPI1->MCR &= ~(SPI_MCR_HALT_MASK);/**Starts transfers by placing 0 in the HALT bit*/
		break;
	case SPI_2:
		SPI2->MCR &= ~(SPI_MCR_HALT_MASK);/**Starts transfers by placing 0 in the HALT bit*/
		break;
	default:
		break;
	}
}

/*It stops the SPI transmission by modifying the value of HALT bit*/
void SPI_stopTranference(SPI_ChannelType channel){

	/**This switch case, selects the required SPI channel*/
	switch(channel){
	case SPI_0:
		SPI0->MCR |= SPI_MCR_HALT_MASK;/**Stops transfers by placing 1 in the HALT bit*/
		break;
	case SPI_1:
		SPI1->MCR |= SPI_MCR_HALT_MASK;/**Stops transfers by placing 1 in the HALT bit*/
		break;
	case SPI_2:
		SPI2->MCR |= SPI_MCR_HALT_MASK;/**Stops transfers by placing 1 in the HALT bit*/
		break;
	default:
		break;
	}
}

/*It transmits the information contained in data*/
void SPI_sendOneByte(uint8 data){
	/****************FALTAN COMENTARIOS******************************************************/
	/**This switch case, selects the required SPI channel*/
//	switch(channel){
//		case SPI_0:
			SPI0->PUSHR = data;
			while(FALSE == (SPI0->SR & SPI_SR_TCF_MASK));
			SPI0->SR |= SPI_SR_TCF_MASK;
//			break;
//		case SPI_1:
//			SPI1->PUSHR = data;
//			while(FALSE == (SPI1->SR & SPI_SR_TCF_MASK));
//			SPI1->SR |= SPI_SR_TCF_MASK;
//			break;
//		case SPI_2:
//			SPI2->PUSHR = data;
//			while(FALSE == (SPI2->SR & SPI_SR_TCF_MASK));
//			SPI2->SR |= SPI_SR_TCF_MASK;
//			break;
//		default:
//			break;
//	}
}

/*It configures the SPI for transmission, this function as arguments receives a pointer to a constant structure where are all
 * the configuration parameters*/
void SPI_init(const SPI_ConfigType* spiConfig){
	SPI_clk(spiConfig->SPI_Channel);  /**turns the clockgating on for the channel*/
			GPIO_clockGating(spiConfig->GPIOForSPI.GPIO_portName);/**Turns on the clockgating for the PORT_D, needed for the next step*/
					/**configures the pin control register depending on the data on the struct*/
			GPIO_pinControlRegister(spiConfig->GPIOForSPI.GPIO_portName,spiConfig->GPIOForSPI.SPI_clk,&spiConfig->pinConttrolRegisterPORTD);
			GPIO_pinControlRegister(spiConfig->GPIOForSPI.GPIO_portName,spiConfig->GPIOForSPI.SPI_Sout,&spiConfig->pinConttrolRegisterPORTD);
					/**configures the pin control register depending on the data on the struct*/
			SPI_setMaster(spiConfig->SPI_Channel,spiConfig->SPI_Master);/**sets the channel for master or slave*/
			SPI_fIFO(spiConfig->SPI_Channel, spiConfig->SPI_EnableFIFO);/**turns on or off the FIFOs*/
			SPI_enable(spiConfig->SPI_Channel);/**Turns on or off the SPI*/
			SPI_clockPolarity(spiConfig->SPI_Channel,spiConfig->SPI_Polarity);/**Chooses from high or lo polarity*/
			SPI_frameSize(spiConfig->SPI_Channel,spiConfig->frameSize);/**Gives the framesize depending on the value given*/
			SPI_clockPhase(spiConfig->SPI_Channel, spiConfig->SPI_Phase);/**Gives the phase depending on the value given*/
			SPI_baudRate(spiConfig->SPI_Channel, spiConfig->baudrate);/**Gives the baud rate depending on the value given*/
			SPI_mSBFirst(spiConfig->SPI_Channel, spiConfig->SPI_LSMorMSB);/**Chooses from MSB or LSB*/

}
