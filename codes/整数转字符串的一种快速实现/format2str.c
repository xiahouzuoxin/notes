/*
 * FileName : format2str.c
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : 2014/4/8 11:08:40
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include "format2str.h" 

/*
 * @brief   
 *   == Use Example
 *   str = (char *)malloc(k*sizeof(char));
 *   if (str) {
 *      int32_to_str(x, str, n);  // n <= k
 *   }
 *   == Be careful of choose the input n
 * @inputs  
 *   x - Interger numbers
 *   n - 
 *      x>0, n >= bit of x in decimal format + 1
 *      x<0, n >= bit of x in decimal format + 2
 * @outputs 
 *   str - Converted string
 * @retval  
 *   If success return 0, else others.
 */
int32_t int32_to_str(int32_t x, char *str, uint32_t n)
{
    uint32_t remain = 0;
    uint32_t div_x  = 0;
    uint32_t le_zero= 0;
    
    if (x<0) {
        x = -x;
        le_zero = 1;
    }

    str[--n] = '\0';
    while ((x > 0) && (n>0)) {
        div_x  = DIV10(x);
        remain = x - ((div_x<<3)+(div_x<<1));  // x - div_x * 10
        x      = div_x;

        str[--n] = remain + '0';
    }
    while (n > 1) {
        str[--n] = '0';
    } 
    if (le_zero > 0) {
        str[--n] = '-';
    } else {
        str[--n] = '0';
    }

    return (n);
}

