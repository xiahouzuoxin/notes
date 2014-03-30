/*
 * FileName : FLASH.c
 * Author   : xiahouzuoxin
 * Date     : 2013.09.28
 * Version  : v1.0
 * Brief    :  
 */
#include "FLASH.h"
#include "stdio.h"

/* Global vaiables */
volatile uint16_t *FLASH_5555 = (volatile uint16_t *) (0x90000000+(0x5555<<1));
volatile uint16_t *FLASH_2AAA = (volatile uint16_t *) (0x90000000+(0x2AAA<<1));

/* 
 * @brief  Flash erase function.
 * @param  addr: 
 *         type:
 * @retval 
 */   
uint32_t Flash_Erase(uint32_t addr, uint16_t type)
{
	uint32_t i,j;

	*FLASH_5555 = FLASH_UL1;	//first
	*FLASH_2AAA = FLASH_UL2;	//second
	*FLASH_5555 = FLASH_UL3;	//third
	*FLASH_5555 = FLASH_UL4;
	*FLASH_2AAA = FLASH_UL5;

	switch(type)
	{
		case 0x50:		//block erase
			*(uint16_t *)addr = type;
			while((*(uint16_t *)addr & 0x80) != 0x80);
			for(i = 0; i < BLOCK_SIZE; i++)
			{
				if(*(uint16_t *)(addr + i) != 0xffff)
				{
					j = 0;
					break;
				}
			}
			j = 1;
			break;
		
		case 0x30:		//sector erase
			*(uint16_t *)addr = type;
			while((*(uint16_t *)addr & 0x80) != 0x80);
			break;
			
		case 0x10:		//chip erase
			*FLASH_5555 = type;
			while((*FLASH_5555 & 0x80) != 0x80);
			break;
		
		default:
			break;
	}
	return (j);
}

/* 
 * @brief  Write a single data.
 * @param  addr: 
 *         data:
 * @retval 
 */   
void Flash_Writes(uint32_t addr,uint16_t data)
{
	uint32_t j = 0;

	*FLASH_5555 = FLASH_UL1;
	*FLASH_2AAA = FLASH_UL2;
	*FLASH_5555 = FLASH_PROGRAM;

	*(uint16_t *)addr = data;

	j = 0;
	while (j<255) j++;  // with delay

	while(*(uint16_t *)addr != data);  // ะฃั้
}

/* 
 * @brief  Write the certain length data.
 * @param  addr: 
 *         ptr:
 *         length:
 * @retval 
 */ 
void Flash_Writem(uint32_t addr,uint16_t *ptr,uint32_t length)
{
	uint32_t i;

	for(i  = 0; i < length; i++)
	{
		Flash_Writes(addr+(i<<1),*(ptr+i));

		if (i % 0xFF == 0) {  
			printf("\nWrite %d bytes...", i<<1);
		}
	}
}

/* 
 * @brief  Read a single data.
 * @param  addr: 
 * @retval 
 */
uint32_t Flash_Reads(uint32_t addr)
{
	return (*(uint16_t *)addr);
}

/* 
 * @brief  Read the certain length data.
 * @param  addr: 
 *         ptr:
 *         length:
 * @retval 
 */
void Flash_Readm(uint32_t addr,uint16_t *ptr,uint32_t length)
{
	uint32_t i;
	for(i = 0; i < length; i++)
	{
		*(ptr + i) = Flash_Reads(addr+2*i);
	}
}

