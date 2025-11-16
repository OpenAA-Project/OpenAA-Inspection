/**
  * SPI2 Generated Driver File
  *
  * @file spi2.c
  *
  * @ingroup spi2
  *
  * @brief This file contains the driver code for the SPI2 module.
  *
  * @version SPI2 Driver Version v3.2.0.
  * 
  * @version SPI2 Package Version v5.2.0.
*/

/*
? [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include <xc.h>
#include "../spi_interface.h"
#include "../spi2.h"
#include "../spi_polling_types.h"

/**
 * @ingroup spi2
 * @struct SPI_INTERFACE SPI2
 * @brief Defines an object for SPI_INTERFACE functions.
 */ 
 
const struct SPI_INTERFACE SPI2 = {
    .Initialize = SPI2_Initialize,
    .Deinitialize = SPI2_Deinitialize,
    .Open = SPI2_Open,
    .Close = SPI2_Close,
	.Transfer = SPI2_Transfer,
    .BufferExchange = SPI2_BufferExchange,
    .BufferWrite = SPI2_BufferWrite,
    .BufferRead = SPI2_BufferRead,	
    .ByteExchange = SPI2_ByteExchange,
    .ByteWrite = SPI2_ByteWrite,
    .ByteRead = SPI2_ByteRead,
    .IsTxReady = SPI2_IsTxReady,
    .IsRxReady = SPI2_IsRxReady,
    .RxCompleteCallbackRegister = NULL,
    .TxCompleteCallbackRegister = NULL
};

// con0 == SPI2CON0, con1 == SPI2CON1, con2 == SPI2CON2, baud == SPI2BAUD, clksel == SPI2CLKSEL
static const spi_configuration_t spi2_configuration[] = {   
    { 0x2, 0x40, 0x0, 0x0, 0x0 }
};

void SPI2_Initialize(void)
{
    SPI2CON0bits.EN = 0U;

	// Disable the interrupts
    PIE5bits.SPI2IE 		= 0U;
    PIE5bits.SPI2TXIE 	= 0U;
    PIE5bits.SPI2RXIE 	= 0U;
	
    SPI2CON1 = (0 << _SPI2CON1_SDOP_POSITION)	/* SDOP active high(0) */
			|(0 << _SPI2CON1_SDIP_POSITION)	/* SDIP active high(0) */
			|(0 << _SPI2CON1_SSP_POSITION)	/* SSP active high(0) */
			|(0 << _SPI2CON1_FST_POSITION)	/* FST disabled(0) */
			|(0 << _SPI2CON1_CKP_POSITION)	/* CKP Idle:Low, Active:High(0) */
			|(1 << _SPI2CON1_CKE_POSITION)	/* CKE Active to idle(1) */
			|(0 << _SPI2CON1_SMP_POSITION);	/* SMP Middle(0) */
    SPI2CON2 = (0 << _SPI2CON2_RXR_POSITION)	/* RXR data is not stored in the FIFO(0) */
			|(0 << _SPI2CON2_TXR_POSITION)	/* TXR not required for a transfer(0) */
			|(0 << _SPI2CON2_SSET_POSITION);	/* SSET disabled(0) */
    SPI2BAUD = (0 << _SPI2BAUD_BAUD_POSITION);	/* BAUD 0x0(0) */
    SPI2CLK = (0 << _SPI2CLK_CLKSEL_POSITION);	/* CLKSEL FOSC(0) */
	SPI2TCNTL = (0 << _SPI2TCNTL_TCNTL_POSITION);	/* TCNTL 0x0(0) */
	SPI2TCNTH = (0 << _SPI2TCNTH_TCNTH_POSITION);	/* TCNTH 0x0(0) */
	SPI2STATUS = (0 << _SPI2STATUS_CLRBF_POSITION)	/* CLRBF no action(0) */
			|(0 << _SPI2STATUS_RXRE_POSITION)	/* RXRE no error(0) */
			|(0 << _SPI2STATUS_TXWE_POSITION);	/* TXWE no error(0) */
	SPI2TWIDTH = (0 << _SPI2TWIDTH_TWIDTH_POSITION);	/* TWIDTH 0x0(0) */
	SPI2INTE = (0 << _SPI2INTE_TXUIE_POSITION)	/* TXUIE disabled(0) */
			|(0 << _SPI2INTE_RXOIE_POSITION)	/* RXOIE disabled(0) */
			|(0 << _SPI2INTE_EOSIE_POSITION)	/* EOSIE disabled(0) */
			|(0 << _SPI2INTE_SOSIE_POSITION)	/* SOSIE disabled(0) */
			|(0 << _SPI2INTE_TCZIE_POSITION)	/* TCZIE disabled(0) */
			|(0 << _SPI2INTE_SRMTIE_POSITION);	/* SRMTIE disabled(0) */
	SPI2INTF = (0 << _SPI2INTF_TXUIF_POSITION)	/* TXUIF disabled(0) */
			|(0 << _SPI2INTF_RXOIF_POSITION)	/* RXOIF disabled(0) */
			|(0 << _SPI2INTF_EOSIF_POSITION)	/* EOSIF disabled(0) */
			|(0 << _SPI2INTF_SOSIF_POSITION)	/* SOSIF disabled(0) */
			|(0 << _SPI2INTF_TCZIF_POSITION)	/* TCZIF disabled(0) */
			|(0 << _SPI2INTF_SRMTIF_POSITION);	/* SRMTIF disabled(0) */
    
	SPI2STATUSbits.CLRBF = 1U;
	
	SPI2CON0 = (0 << _SPI2CON0_BMODE_POSITION)	/* BMODE last byte(0) */
			|(1 << _SPI2CON0_MST_POSITION)	/* MST bus host(1) */
			|(0 << _SPI2CON0_LSBF_POSITION)	/* LSBF MSb first(0) */
			|(0 << _SPI2CON0_EN_POSITION);	/* EN disabled(0) */
}

void SPI2_Deinitialize(void)
{
    SPI2CON0 = 0x0;
    SPI2CON1 = 0x4;
    SPI2CON2 = 0x0;
    SPI2BAUD = 0x0;
    SPI2CLK = 0x0; 
	SPI2TCNTL = 0x0;
	SPI2TCNTH = 0x0;
	SPI2STATUS = 0x20;
	SPI2TWIDTH = 0x0;
	SPI2INTE = 0x0;
	SPI2INTF = 0x0 ;
}

bool SPI2_Open(uint8_t spiConfigIndex)
{
	bool returnValue = false; 
	if(false == SPI2CON0bits.EN)
	{
        SPI2CON0 = spi2_configuration[spiConfigIndex].con0;
        SPI2CON1 = spi2_configuration[spiConfigIndex].con1;
        SPI2CON2 = spi2_configuration[spiConfigIndex].con2 & ~(_SPI2CON2_SPI2RXR_MASK) & ~(_SPI2CON2_SPI2TXR_MASK);
        SPI2BAUD = spi2_configuration[spiConfigIndex].baud;        
        SPI2CLK = spi2_configuration[spiConfigIndex].clksel;        
		TRISCbits.TRISC3 = 0;
        SPI2CON0bits.EN = 1U;
		returnValue = true;
	}
	else
	{
		returnValue = false;
	}
	return returnValue;
}

void SPI2_Close(void)
{
	SPI2CON0bits.EN = 0U;
	PIE5bits.SPI2IE 		= 0U;
    PIE5bits.SPI2TXIE 	= 0U;
    PIE5bits.SPI2RXIE 	= 0U;
}

void SPI2_Transfer(const void * txBuffer, void * rxBuffer, size_t bufferSize)
{
	uint8_t* bufferReceive = rxBuffer;
	const uint8_t* bufferTransmit = (const uint8_t *)txBuffer;

    SPI2STATUSbits.CLRBF = 1U;

	// Clear the TCZIF interrupt flag
	SPI2INTFbits.TCZIF = 0U;

	// Set as full duplex mode for buffer exchange operation
    SPI2CON2 = (SPI2CON2 | _SPI2CON2_SPI2RXR_MASK) | _SPI2CON2_SPI2TXR_MASK;
	
	// Load the transfer count registers
	SPI2TCNTH = (uint8_t)(bufferSize>>8);
	SPI2TCNTL = (uint8_t)(bufferSize);	
	
	while(0U == SPI2INTFbits.TCZIF)
	{
		// Write input data to SPI transmit buffer register
		SPI2TXB = *bufferTransmit;
		while(!PIR5bits.SPI2RXIF)
		{
			// Wait on receive interrupt flag to be set
        };
		
		// Store received data  from receive buffer register 
		*bufferReceive = SPI2RXB;		
		bufferReceive++;
		bufferTransmit++;
	}
}
void SPI2_BufferExchange(void *bufferData, size_t bufferSize)
{
	uint8_t* bufferInput = bufferData;

    SPI2STATUSbits.CLRBF = 1U;

	// Clear the TCZIF interrupt flag
	SPI2INTFbits.TCZIF = 0U;

	// Set as full duplex mode for buffer exchange operation
    SPI2CON2 = (SPI2CON2 | _SPI2CON2_SPI2RXR_MASK) | _SPI2CON2_SPI2TXR_MASK;
	
	// Load the transfer count registers
	SPI2TCNTH = (uint8_t)(bufferSize>>8);
	SPI2TCNTL = (uint8_t)(bufferSize);	
	
	while(0U == SPI2INTFbits.TCZIF)
	{
		// Write input data to SPI transmit buffer register
		SPI2TXB = *bufferInput;
		while(!PIR5bits.SPI2RXIF)
		{
			// Wait on receive interrupt flag to be set
        };
		
		// Store received data  from receive buffer register 
		*bufferInput = SPI2RXB;		
		bufferInput++;
	}
}

void SPI2_BufferWrite(void *bufferData, size_t bufferSize)
{
	uint8_t* bufferInput = bufferData;

	SPI2STATUSbits.CLRBF = 1U;

	// Clear the TCZIF interrupt flag
	SPI2INTFbits.TCZIF = 0U;

	// Set as transmit only mode for buffer write operation
    SPI2CON2 = (SPI2CON2 & ~_SPI2CON2_SPI2RXR_MASK) | _SPI2CON2_SPI2TXR_MASK;
   
	// Load the transfer count registers
	SPI2TCNTH = (uint8_t)(bufferSize>>8);
	SPI2TCNTL = (uint8_t)(bufferSize);

	
	while(0U == SPI2INTFbits.TCZIF)
	{
		// Write input data to SPI transmit buffer register
		SPI2TXB = *bufferInput;
		while(!PIR5bits.SPI2TXIF)
		{
			// Wait on transmit interrupt flag to be set
        };
		bufferInput++;
	}
}

void SPI2_BufferRead(void *bufferData, size_t bufferSize)
{
	uint8_t* bufferInput = bufferData;

	SPI2STATUSbits.CLRBF = 1U;

	// Clear the TCZIF interrupt flag
	SPI2INTFbits.TCZIF = 0U;

	// Set as receive only mode for buffer read operation
    SPI2CON2 = (SPI2CON2 & ~_SPI2CON2_SPI2TXR_MASK) | _SPI2CON2_SPI2RXR_MASK;
	
	// Load the transfer count registers
	SPI2TCNTH = (uint8_t)(bufferSize>>8);
	SPI2TCNTL = (uint8_t)(bufferSize);

	while(0U == SPI2INTFbits.TCZIF)
	{
		while(!PIR5bits.SPI2RXIF)
		{
            // Wait on receive interrupt flag to be set
        };

		// Store received data  from receive buffer register 
		*bufferInput = SPI2RXB;
		bufferInput++;
	}
}

uint8_t SPI2_ByteExchange(uint8_t byteData)
{
	uint8_t returnValue = 0U;
    
	SPI2STATUSbits.CLRBF = 1U;

	// Set as full duplex mode
	SPI2CON2 = SPI2CON2 | _SPI2CON2_SPI2RXR_MASK | _SPI2CON2_SPI2TXR_MASK;
	
	// Load the transfer count registers
	SPI2TCNTH = 0U;
	SPI2TCNTL = 1U;

	SPI2TXB = byteData;

	while(!PIR5bits.SPI2RXIF)
	{
		// Wait on receive interrupt flag to be set
    };
	returnValue = SPI2RXB;
	return returnValue;
}

void SPI2_ByteWrite(uint8_t byteData)
{	
	// Set as full duplex mode
	SPI2CON2 = SPI2CON2 | _SPI2CON2_SPI2RXR_MASK | _SPI2CON2_SPI2TXR_MASK;
	
	// Load the transfer count registers
	SPI2TCNTH = 0;
	SPI2TCNTL = 1;
	
	SPI2TXB = byteData;
}

uint8_t SPI2_ByteRead(void)
{
	uint8_t returnValue = 0x00U;
	
	// Set as full duplex mode
    SPI2CON2 = SPI2CON2 | _SPI2CON2_SPI2RXR_MASK | _SPI2CON2_SPI2TXR_MASK;
	
	// Store received data from receive buffer register 
	returnValue = SPI2RXB;	
	return returnValue;
}

bool SPI2_IsTxReady(void)
{
	bool returnValue = false;
	if(true == SPI2CON0bits.EN)
	{
		returnValue = PIR5bits.SPI2TXIF;
	}
	else 
	{
		returnValue = false;
	}
	return returnValue;
}

bool SPI2_IsRxReady(void)
{
	bool returnValue = false;
	
	if(true == SPI2CON0bits.EN)
    {
		returnValue = PIR5bits.SPI2RXIF;
    }
    else 
    {
        returnValue = false;
    }
    return returnValue;
}