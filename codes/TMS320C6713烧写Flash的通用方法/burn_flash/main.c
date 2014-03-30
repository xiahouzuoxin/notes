	
#include <c6x.h>
#include <csl.h>
#include <stdio.h>
#include <stdlib.h>
#include "Flash.h"
#include "BSP.h"
#include "boot.h"
#include "text.h"

main()
{
	BSP_init();

	/* Fetch data from file */

    /* Erase flash memory. */
    Flash_Erase(0x90000000,0x10);
	printf("\nErase Flash ok.");
	
    /* Write flash memory. */
	Flash_Writem(0x90000000, (uint16_t *)boot, sizeof(boot)<<1);   
    printf("\nWrite .boot ok.");

   	Flash_Writem(0x90000000+(0x200<<1), (uint16_t *)text, sizeof(text)<<1);
    printf("\nWrite .text ok.");

	printf("\nBurn to flash ok.");
}






