/******************************************************************************
 * GRID2HOME SMART ENERGY 2
 *****************************************************************************/
/**
 * Copyright (C) 2010 Grid2Home, Inc. All rights reserved.
 * This source code and any compilation or derivative thereof is the proprietary
 * information of Grid2Home, Inc and is confidential in nature.
 *
 * \file          psal_types.h
 *
 * \version       $Revision: $
 *
 * \date          $Date: $
 *
 * \brief         Interface for Platform Services Abstraction Layer
 *
 * \section info  Change Information
 *
 * \verbatim
   $History: $
 */

#ifndef PSAL_TYPES_H
#define PSAL_TYPES_H


/* --------------------------------------------------------------------------------------------------
 *                                           Typedefs
 * --------------------------------------------------------------------------------------------------
 */
typedef  unsigned       char   u8_t;
typedef    signed       char   i8_t;
typedef  unsigned      short  u16_t;
typedef    signed      short  i16_t;
//typedef  unsigned       long  u32_t;    HT: this is compiler-specific, but 32-bit values should be
//typedef    signed       long  i32_t;    HT:   "int" for gcc and IAR
typedef  unsigned        int  u32_t;
typedef    signed        int  i32_t;
typedef  unsigned  long long  u64_t;
typedef    signed  long long  i64_t;


/* --------------------------------------------------------------------------------------------------
 *                                           Defines
 * --------------------------------------------------------------------------------------------------
 */
#define NULLP   0

#include <stdio.h>

#ifndef BSS_PLACE
  #define BSS_PLACE
#endif

/* --------------------------------------------------------------------------------------------------
 *                                           Macros
 * --------------------------------------------------------------------------------------------------
 */
#define LS_BYTE(x)  ((u8_t)((x)&0xFF))
#define MS_BYTE(x)  ((u8_t)(((x)>>8)&0xFF))
#define LS0_BYTE(x) ((u8_t)((x)&0xFF))
#define LS1_BYTE(x) ((u8_t)(((x)>>8)&0xFF))
#define LS2_BYTE(x) ((u8_t)(((x)>>16)&0xFF))
#define LS3_BYTE(x) ((u8_t)(((x)>>24)&0xFF))


/* --------------------------------------------------------------------------------------------------
 */
#endif  /* PSAL_TYPES_H */
