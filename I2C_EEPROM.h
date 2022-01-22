/**
  ******************************************************************************
  * @file           : I2C_EEPROM.h
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



#ifndef INC_I2C_EEPROM_H_
#define INC_I2C_EEPROM_H_

/*BEGIN--------------------------includes-------------------------------------*/
#include "stdint.h"
#include "stddef.h"
#include "stm32f3xx_hal.h"
#include "main.h"
#include "math.h"
/*END----------------------------includes-------------------------------------*/
/*
 *
 */
/*BEGIN--------------------------typedef--------------------------------------*/
extern I2C_HandleTypeDef hi2c1;
#define I2C_EEPROM &hi2c1

/*END----------------------------typedef--------------------------------------*/
/*
 *
 */
/*BEGIN--------------------------define---------------------------------------*/
/*COSTANTS*/

/*Communication Status*/

#define COMM_OK				0
#define COMM_ERROR			1
#define EEPROM_MEM_SIZE_ERR	2
/*---------------------------*/

/*Memory configuration*/

/*I2C_EEPROM address*/

#define A0PIN_BIT			1
#define A1PIN_BIT			2
#define A2PIN_BIT			3

/*Guide:
 * Set  EEPROM_A0_PIN value to 0 or to 1 according hardware configuration*/

#define EEPROM_A0_PIN 		0		// Address Pin A0
#define EEPROM_A1_PIN 		0		// Address Pin A1
#define EEPROM_A2_PIN 		0		// Address Pin A2
#define EEPROM_WP_PORT		GPIOB	// Peripheral Port
#define	EEPROM_WP_PIN		6		// Write Protection Pin

#define DEV_ADDRESS			(0XA0 | (EEPROM_A2_PIN << A2PIN_BIT) | (EEPROM_A1_PIN << A1PIN_BIT) | (EEPROM_A0_PIN << A0PIN_BIT))		// IC memory address
/*-----------------------------------------------------------------------------------------------------------------------------*/

/*Memory configuration*/

#define EEPROM_ADD_SIZE		2U		//EEPROM address size
#define	EEPROM_PAGE_SIZE	128U	//EEPROM page size
#define EEPROM_NUM_OF_PAGE	512U	//EEPROM number of pages
#define EEPROM_STWC			5U		//EEPROM Self time write cycle
#define EEPROM_SIZE_ERROR	2		// EEPROM error value
#define TRAILS				5		//Number of test used for connection test
#define TIMEOUT				1000	// Time out

#define EEPROM_pPAGE_ADD	log(EEPROM_PAGE_SIZE)/log(2) // Pointer for page address

#define	EEPROM_MAX_SIZE		((EEPROM_PAGE_SIZE)*(EEPROM_NUM_OF_PAGE)) //EEPROM maximum memory size
/*----------------------------------------------------------------------------*/

/*Functions*/

#define _GPIO_PIN_RESET										GPIO_PIN_RESET
#define _GPIO_PIN_SET										GPIO_PIN_SET
#define _DELAY_STWC(void)									HAL_Delay(EEPROM_STWC)

#define I2C_EEPROM_READY(void)            					HAL_I2C_IsDeviceReady(I2C_EEPROM,DEV_ADDRESS,TRAILS,TIMEOUT)
#define	I2C_EEPROM_WRITE(da, ma, mas, md, qu, tim)			HAL_I2C_Mem_Write(I2C_EEPROM, (da), (ma), (mas), (md), (qu), (tim))
#define I2C_EEPROM_READ(da, ma, mas, md, qu, tim)			HAL_I2C_Mem_Read(I2C_EEPROM, (da), (ma), (mas), (md), (qu), (tim))
#define I2C_EEPROM_WP(sp)									HAL_GPIO_WritePin(EEPROM_WP_PORT,(1 << EEPROM_WP_PIN), (sp))

/*------------------------------------------------------------------------------------------------------------------------------*/

/*END----------------------------define---------------------------------------*/
/*
 *
 */

/*BEGIN-----------------------functions prototypes----------------------------*/

/*BEGIN**************************MEMORY READY *********************************/
/*
 * Description: Function for test if memory is ready for communication
 *
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
uint8_t I2C_EEPROM_IsReady(void);

/*END****************************MEMORY READY *********************************/
/*
 *
 */
/*BEGIN**************************MEMORY READ **********************************/
/*
 * Description: Function for read data from EEPROM
 *
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
uint8_t I2C_EEPROM_Read(uint32_t address, uint8_t *udata, uint32_t size);

/*END****************************MEMORY READ **********************************/
/*
 *
 */
/*BEGIN**************************MEMORY WRITE *********************************/

/* Description: Function for write data to EEPROM
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
uint8_t I2C_EEPROM_Write(uint32_t address, uint8_t *wData, uint16_t size);

/*END****************************MEMORY WRITE *********************************/
/*
 *
 */
/*BEGIN**************************MEMORY ERASE *********************************/

/* Description: Function for write data to EEPROM
 * Parameters:
 * 		address : Internal memory address
 * 		size	: Size of the date to be send
 *
 * Return:
 * 		EEPROM_MEM_SIZE_ERR
 * 		HAL_OK
 * 		HAL_ERR
 */
uint8_t I2C_EEPROM_Erase(uint32_t address, uint16_t size);

/*END****************************MEMORY WRITE *********************************/
/*
 *
 */
/*END-------------------------functions prototypes----------------------------*/

#endif /* INC_I2C_EEPROM_H_ */
