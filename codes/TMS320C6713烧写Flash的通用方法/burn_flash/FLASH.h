/*
 * FileName : FLASH.h
 * Author   : xiahouzuoxin
 * Date     : 2013.09.28
 * Version  : v1.0
 * Brief    :  
 */
#ifndef _FLASH_H
#define _FLASH_H

#include "Config.h"

#define		FLASH_UL1           0xAA
#define		FLASH_UL2           0x55
#define		FLASH_UL3           0x80
#define		FLASH_UL4           0xAA
#define		FLASH_UL5           0x55
#define		FLASH_SECTOR_UL6    0x30
#define		FLASH_CHIP_UL6	    0x10
#define		FLASH_PROGRAM       0xA0
#define		SECTOR_SIZE         0x0800
#define		BLOCK_SIZE          0x8000
#define		CHIP_SIZE           0x40000

#define     FLASH_FIRST_ADDR    0x90000000
#define     FLASH_OFFSET(addr)  (FLASH_FIRST_ADDR+(addr)<<1)  // 16 bit boot mode
			

/* External functions propotype */
extern uint32_t Flash_Erase(uint32_t addr,uint16_t type);
extern void Flash_Readm(uint32_t addr,uint16_t *ptr,uint32_t length);
extern uint32_t Flash_Reads(uint32_t addr);
extern void Flash_Writem(uint32_t addr,uint16_t *ptr,uint32_t length);
extern void Flash_Writes(uint32_t addr,uint16_t data);

#ifdef __TEST
extern void FLASH_test(void);
#endif

#endif
