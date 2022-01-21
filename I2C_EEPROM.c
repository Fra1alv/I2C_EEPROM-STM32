/**
  ******************************************************************************
  * @file           : I2C_EEPROM.C
  * @Author			: A. Freire
  *	@Created		: 01.21.2022
  * @brief          : Header for I2C_EEPROM.c file.
  *                   This file contains the common defines of the application.
  * @Support		:
  *						E-mail : alonsofra1alv@gmail.com
  ******************************************************************************
  * @Changes:
  *
  *
  *
  *
  *
  ******************************************************************************
  */

/*BEGIN**************************INCLUDES************************************/
#include "I2C_EEPROM.h"
#include "string.h"

/*END****************************INCLUDES************************************/
/*
 *
 */
/*BEGIN**************************MEMORY READY *********************************/

/*
 * Parameters:
 *
 *
 *
 * Return:
 *
 * 		HAL_OK
 * 		HAL_ERR
 *
 */

uint8_t I2C_EEPROM_IsReady(void)
{

	return	I2C_EEPROM_READY();

}

/*END****************************MEMORY READY *********************************/

/*
 *
 */

/*BEGIN**************************MEMORY WRITE *********************************/

/*
 * Parameters:
 * 		address : Internal memory address
 * 		wData	: Data to be send
 * 		size	: Size of the date to be send
 *
 * Return:
 * 		EEPROM_MEM_SIZE_ERR
 * 		HAL_OK
 * 		HAL_ERR
 */
uint8_t I2C_EEPROM_Write(uint32_t address, uint8_t *wData, uint16_t size)
{

	/*---------Variables----------*/

	uint8_t wStatus		=	COMM_ERROR; 				//Take the Status of the communication
	int pPage			=	EEPROM_pPAGE_ADD;			//Pointer to identify page bit address
	uint16_t startPage	=	address >> pPage;			//Start page
	uint16_t endPage	=	(address+size) >> pPage;	//End Page
	uint16_t numPages 	=	(endPage-startPage)+1;		// Number of pages
	uint16_t pData		=	0;							// Pointer for data array

	uint16_t PageDataLength = ((startPage + 1) * EEPROM_PAGE_SIZE) - address; // Amount of date to be send

	/*-END-----Variables----------*/

	if ((address + size) <= EEPROM_MAX_SIZE) // Check data length
	{
		/*---------Reset WP----------*/

		I2C_EEPROM_WP(_GPIO_PIN_RESET); // reset write protection

		/*-END-----Reset WP----------*/

		if (size <= PageDataLength) // Check data length
		{

			wStatus = I2C_EEPROM_WRITE(DEV_ADDRESS, address, EEPROM_ADD_SIZE, wData, size, TIMEOUT); // Write data
			_DELAY_STWC(); // Delay Self Timed Write Cycle
		}

		else
		{

			for (int i=0; i < numPages ; i++) // Loop write data

			{
				/*---------Variables----------*/
				uint16_t bytesToWrite;

				/*-END-----Variables----------*/

				if (size + address > (startPage + 1) * EEPROM_PAGE_SIZE) // Check page capacity
				{
					bytesToWrite	=	((startPage + 1)* EEPROM_PAGE_SIZE) - address; // Calculate amount of bytes to write at the page
				}
				else
				{
					bytesToWrite	=	size;
				}

				wStatus = I2C_EEPROM_WRITE(DEV_ADDRESS, address, EEPROM_ADD_SIZE, &wData[pData], bytesToWrite, TIMEOUT); // Write data
				_DELAY_STWC(); // Delay Self Timed Write Cycle

				startPage++; // Increase the page

				address	+= bytesToWrite; // Set new address
				size	-= bytesToWrite; // Set the size of date for the page
				pData	+= bytesToWrite; // Pointer for data array
			}
		}
		I2C_EEPROM_WP(_GPIO_PIN_SET); // Set write protection

	}
	else
	{
		wStatus	= EEPROM_MEM_SIZE_ERR; // Set Status
	}

	return wStatus;
}

/*END****************************MEMORY WRITE *********************************/

/*
 *
 *
 */

/*BEGIN**************************MEMORY READ **********************************/
/*
 * Parameters:
 * 		address : Internal memory address
 * 		rData	: Data to be send
 * 		size	: Size of the date to be send
 *
 * Return:
 * 		EEPROM_MEM_SIZE_ERR
 * 		HAL_OK
 * 		HAL_ERR
 */

uint8_t I2C_EEPROM_Read(uint32_t address, uint8_t *rData, uint32_t size)
{
	/*---------Variables----------*/

	uint8_t rStatus		=	COMM_ERROR; // Take the Status of the communication

	/*-END-----Variables----------*/

	if ((address + size) <= EEPROM_MAX_SIZE) // Amount of date to be send
	{

		rStatus	= I2C_EEPROM_READ(DEV_ADDRESS, address, EEPROM_ADD_SIZE, rData, size, TIMEOUT); //Read data
	}

	else
	{
		rStatus			=	EEPROM_MEM_SIZE_ERR; // Set Status
	}

	return rStatus;

}
/*END****************************MEMORY READ **********************************/
/*
 *
 */
/*BEGIN**************************MEMORY ERASE *********************************/

/* Description: Function for Erase EEPROM
 * Parameters:
 * 		address : Internal memory address
 * 		size	: Size of the date to be send
 *
 * Return:
 * 		EEPROM_MEM_SIZE_ERR
 * 		HAL_OK
 * 		HAL_ERR
 */
uint8_t I2C_EEPROM_Erase(uint32_t address, uint16_t size)
{

	/*---------Variables----------*/

	uint8_t eStatus		=	COMM_ERROR; // Take the Status of the communication
	uint8_t eData[size];
	memset(eData,0xff,size);			// Create a data value for reset

	/*-END-----Variables----------*/

	if ((address + size) < EEPROM_MAX_SIZE) // Amount of date to be send
	{

		eStatus			=	I2C_EEPROM_Write(address, eData, size); // Send reset value to EEPROM

	}
	else
	{
		eStatus			=	 EEPROM_MEM_SIZE_ERR; // Set Status
	}

	return eStatus;
}

/*END****************************MEMORY ERASE**********************************/
