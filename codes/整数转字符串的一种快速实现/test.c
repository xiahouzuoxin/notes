/*
 * FileName : test.c
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : 2014/4/9 10:17:44
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include "format2str.h" 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int32_t x = -65544;
    char *str  = NULL;
    int32_t i  = 0;

    printf("%d\n", DIV10(x)); 

    str = (char *)malloc(10*sizeof(char));
    if (str) {
        i = int32_to_str(x, str, 8+2);
        
        if (!i) {
            printf("Converted success.\n");
        } else {
            printf("Converted failure.\n");
        }
        printf("str=%s\n", str);
    }
}

