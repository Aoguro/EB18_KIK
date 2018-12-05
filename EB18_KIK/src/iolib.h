/***********************************************************************/
/*                                                                     */
/*  FILE        :iolib.h                                               */
/*  DATE        :Sept 7, 2012    2                                     */
/*  DESCRIPTION :RX62T iolibrary                                       */
/*  CPU TYPE    :RX62T                                                 */
/*                                                                     */
/***********************************************************************/
/*********************************************************************
* Copyright (C) 2012 Renesas Electronics Corporation.
* and Renesas Solutions Corporation. All rights reserved.
*********************************************************************/

void  inverter_init(int fs, int dt);
void  inverter_set_uvw(float u, float v, float w, unsigned short YT_cnt,unsigned short MN);
void  inverter_start_int(void);
void  inverter_stop_int(void);
