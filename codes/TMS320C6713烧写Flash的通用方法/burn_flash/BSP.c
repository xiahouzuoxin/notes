/*
 * FileName : BSP.c
 * Author   : xiahouzuoxin
 * Date     : 2013.09.28
 * Version  : v1.0
 * Brief    :  
 */
#include "BSP.h"
#include "csl.h"
#include "csl_emif.h"
#include "csl_pll.h"

/* EMIF Registers */
#define EMIF_GCTL       0x01800000
#define EMIF_CE1        0x01800004
#define EMIF_CE0        0x01800008
#define EMIF_CE2        0x01800010
#define EMIF_CE3        0x01800014
#define EMIF_SDRAMCTL   0x01800018
#define EMIF_SDRAMTIM   0x0180001C
#define EMIF_SDRAMEXT   0x01800020
#define EMIF_CCFG       0x01840000
#define SDRAM_BASE_ADDRESS_CE0    0x80000000	
#define SDRAM_SIZE_BYTE           0x01000000	//256Mb SDRAM

extern far void vectors();   /* _init_c00 */

/*Local software delay function*/
static void PLLDelay(int Count)
{
    volatile int i = Count;
    while(i--);
}

/*
 * @brief
 * @param  None
 * @retval None
 */
void InitEmif( void )
{
	*(int *)EMIF_GCTL     = 0x00000078;
	*(int *)EMIF_CE0      = 0xffffff93;  // CE0:SDRAM 16-bit 
	*(int *)EMIF_CE1      = 0xffffff13;  // CE1:Flash 16-bit 
	 		
	*(int *)EMIF_SDRAMCTL = 0x53115000;  // SDRAM control                
	*(int *)EMIF_SDRAMTIM = 0x00000578;  // SDRAM timing (refresh)        
	*(int *)EMIF_SDRAMEXT = 0x000a8529;  // SDRAM Extension register     
}

/*
 * @brief  Init Board, BSP means Board Support Package.
 *         Place configuration for SDRAM and PLL here.
 * @param  
 * @retval 
 */
void BSP_init(void)
{
	/* Initealize the board APIs */
	/*
	EMIF_Config MyEMIFcfg0={
		0x30								|
		EMIF_FMKS(GBLCTL,NOHOLD,DISABLE)	|
		EMIF_FMKS(GBLCTL,EKEN,DEFAULT)		|
		EMIF_FMKS(GBLCTL,CLK1EN,DISABLE)	|
		EMIF_FMKS(GBLCTL,CLK2EN,DISABLE),
		
		EMIF_FMKS(CECTL,WRSETUP,DEFAULT)	|
		EMIF_FMKS(CECTL,WRSTRB,DEFAULT)		|
		EMIF_FMKS(CECTL,WRHLD,DEFAULT)		|
		EMIF_FMKS(CECTL,RDSETUP,DEFAULT)	|
		EMIF_FMKS(CECTL,TA,OF(2))			|
		EMIF_FMKS(CECTL,RDSTRB,DEFAULT)		|
		EMIF_FMKS(CECTL,MTYPE,SDRAM32)		|
		EMIF_FMKS(CECTL,RDHLD,DEFAULT),
		
		EMIF_FMKS(CECTL, WRSETUP, OF(0))    |
        EMIF_FMKS(CECTL, WRSTRB, OF(8))     |
        EMIF_FMKS(CECTL, WRHLD, OF(2))      |
        EMIF_FMKS(CECTL, RDSETUP, OF(0))    |
        EMIF_FMKS(CECTL, TA, OF(2))         |
        EMIF_FMKS(CECTL, RDSTRB, OF(8))     |
        EMIF_FMKS(CECTL, MTYPE, ASYNC16)    |
        EMIF_FMKS(CECTL, RDHLD, OF(2)),
        
        EMIF_FMKS(CECTL, WRSETUP, OF(0))    |
        EMIF_FMKS(CECTL, WRSTRB, OF(8))     |
        EMIF_FMKS(CECTL, WRHLD, OF(2))      |
        EMIF_FMKS(CECTL, RDSETUP, OF(0))    |
        EMIF_FMKS(CECTL, TA, OF(2))         |
        EMIF_FMKS(CECTL, RDSTRB, OF(8))     |
        EMIF_FMKS(CECTL, MTYPE, ASYNC8)    |
        EMIF_FMKS(CECTL, RDHLD, OF(2)),
		
		EMIF_FMKS(CECTL, WRSETUP, OF(2))    |
        EMIF_FMKS(CECTL, WRSTRB, OF(10))    |
        EMIF_FMKS(CECTL, WRHLD, OF(2))      |
        EMIF_FMKS(CECTL, RDSETUP, OF(2))    |
        EMIF_FMKS(CECTL, TA, OF(2))         |
        EMIF_FMKS(CECTL, RDSTRB, OF(10))    |
        EMIF_FMKS(CECTL, MTYPE, ASYNC32)    |
        EMIF_FMKS(CECTL, RDHLD, OF(2)),
        
        EMIF_FMKS(SDCTL,SDBSZ,4BANKS)		|
        EMIF_FMKS(SDCTL,SDRSZ,12ROW)		|
        EMIF_FMKS(SDCTL,SDCSZ,8COL)			|
        EMIF_FMKS(SDCTL,RFEN,ENABLE)		|
        EMIF_FMKS(SDCTL,INIT,YES)			|
        EMIF_FMKS(SDCTL,TRCD,OF(2))			|
        EMIF_FMKS(SDCTL,TRP,OF(2))			|
        EMIF_FMKS(SDCTL,TRC,OF(7)),
        
        //EMIF_FMKS(SDTIM,XRFR,OF(1))			|
        EMIF_FMKS(SDTIM, CNTR, OF(0))       |
        EMIF_FMKS(SDTIM, PERIOD, OF(1400)),
        
		EMIF_FMKS(SDEXT, WR2RD, OF(0))      |
        EMIF_FMKS(SDEXT, WR2DEAC, OF(2))    |
        EMIF_FMKS(SDEXT, WR2WR, OF(0))      |
        EMIF_FMKS(SDEXT, R2WDQM, OF(1))     |
        EMIF_FMKS(SDEXT, RD2WR, OF(0))      |
        EMIF_FMKS(SDEXT, RD2DEAC, OF(1))    |
        EMIF_FMKS(SDEXT, RD2RD, OF(0))      |
        EMIF_FMKS(SDEXT, THZP, OF(2))       |
        EMIF_FMKS(SDEXT, TWR, OF(2))        |
        EMIF_FMKS(SDEXT, TRRD, OF(0))       |
        EMIF_FMKS(SDEXT, TRAS, OF(5))       |
        EMIF_FMKS(SDEXT, TCL, OF(1))
        };
    */    
	/* Initialize PLL Registers */         
	/* Put PLL in bypass */
	PLL_bypass();
	PLLDelay(20);
	
	/* Reset PLL */
	PLL_reset();
	PLLDelay(20);
	
	/* Crystal 50MHz */
	/* Set main multiplier/divisor */
    PLL_RSET(PLLDIV0, (1<<15 | 0<<0));          // 50MHz / 1 = 50MHz
    PLL_RSET(OSCDIV1, (1<<15 | 0<<0));          // 50MHz / 1 = 50Mhz

	PLL_RSET(PLLM, 8);                          // 50MHz  x 9 = 400MHz

    /* Set DSP clock */
    PLL_RSET(PLLDIV1, (1<<15 | 1<<0));          // 400MHz / 2 = 200MHz
    PLLDelay(20);
    
    /* Set peripheral clock */
    PLL_RSET(PLLDIV2, (1<<15 | 3<<0));         // 400MHz / 4 = 100MHz
    PLLDelay(20);
    
    /* Set EMIF clock (ECLKOUT) */
    PLL_RSET(PLLDIV3, (1<<15 | 3<<0));         // 400MHz / 4 = 100MHz
    PLLDelay(20);
    
    /* Take PLL out of reset */
    PLL_deassert();
    PLLDelay(1500);
    
    /* Enalbe PLL */
    PLL_enable();
    PLLDelay(20);
   
   	/* Initialize EMIF */
    //EMIF_config(&MyEMIFcfg0);
    InitEmif();   

    /* Init chip support library */
    CSL_init();
        
    /**************************** 
     * Set vector table pointor 
     ***************************/
	IRQ_setVecs(vectors);
    IRQ_nmiEnable();
    IRQ_globalEnable();     
}

