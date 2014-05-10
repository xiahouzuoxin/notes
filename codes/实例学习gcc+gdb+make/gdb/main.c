/*
 * FileName : main.c
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : 2014/5/10 14:08:44
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#include <stdio.h>


int add(int a, int b)
{
    int c = a + b;

    return c;
}

int main(void)
{
    int i = 0;
    int j = 3;

    int k = add(i,j);

    printf("i=%d, j=%d, k=%d\n", i,j,k);

    return 0;
}

