/*
 * FileName : format2str.h
 * Author   : xiahouzuoxin @163.com
 * Version  : v1.0
 * Date     : 2014/4/9 10:15:09
 * Brief    : 
 * 
 * Copyright (C) MICL,USTB
 */
#ifndef _FORMAT2STR_H
#define _FORMAT2STR_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>

/* 
 * Magic Number 0x66666667 
 * Refrence to <<Hacker's Delight>> By Henry S. Warren
 */
#define DIV5(x)        (((int64_t)x*0x66666667L) >> 33)
#define DIV10(x)       (((int64_t)x*0x66666667L) >> 34)

extern int32_t int32_to_str(int32_t x, char *str, uint32_t n);

#ifdef __cplusplus
}
#endif
#endif

