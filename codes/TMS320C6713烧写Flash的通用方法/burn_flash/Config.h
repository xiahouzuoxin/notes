/*
 * FileName : Config.h
 * Author   : xiahouzuoxin
 * Date     : 2013.08.31
 * Version  : v1.0
 * Brief    : place global typedefs and macros here 
 */

#ifndef _CONFIG_H
#define _CONFIG_H

/* type redefinition */
/*
typedef enum
{
   FALSE = 0,
   TRUE  = !FALSE
} BOOL;
*/

typedef unsigned int                      UINT16;
typedef unsigned long                     UINT32;
typedef unsigned char                     UINT8;
typedef int                               INT16;
typedef long                              INT32;
typedef char                              INT8;

typedef float                             FP32;
typedef double                            FP64;

#ifndef __stdint_h
typedef unsigned long                     uint40_t;
typedef unsigned int                      uint32_t;
typedef unsigned short                    uint16_t;
typedef unsigned char                     uint8_t;
typedef long                              int40_t;
typedef int                               int32_t;
typedef short                             int16_t;
typedef char                              int8_t;

typedef float                             fp32_t;
typedef double                            fp64_t;

#endif  // #ifndef __stdint_h

/* Get a byte or word in specified address */
#define MEM_B(x)                          ( *( (UINT8 *)(x) ) )
#define MEM_W(x)                          ( *( (UINT32 *)(x) ) )

#define UPCASE( c )                       ( ((c) >= ''a'' && (c) <= ''z'') ?  \
                                          ( (c) - 0x20) : (c) )

/* Check wether a case is a decimal */
#define DECCHK( c )                       ((c) >= ''0'' && (c) <= ''9'')

/* Check wether a case is a hex */
#define HEXCHK( c )                       ( ((c) >= ''0'' && (c) <= ''9'') ||  \
                                          ( (c) >= ''A'' && (c) <= ''F'') ||  \
                                          ( (c) >= ''a'' && (c) <= ''f'') )

/* ABS/MAX/MIN */
#define ABS(x)                            ( ((x) > 0) ? (x) : (-x) ) 
#define MIN(a, b)                         ( ((a) < (b))?(a):(b) )
#define MAX(a, b)                         ( ((a) > (b))?(a):(b) ) 

/* Constants */
#define PI                                3.14159265359f

/* Function Define */
#ifndef ClrBit
#define ClrBit(reg, bit)                  reg &= ~(1 << bit)
#endif

#ifndef SetBit
#define SetBit(reg, bit)                  reg |= (1 << bit)
#endif 

/* Constants */
#define ZX_SUCCESS                        (1)
#define ZX_FAILURE                        (0)  

#endif
