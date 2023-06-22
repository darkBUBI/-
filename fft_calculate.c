/*
 * fft_calculate.c
 *
 *  Created on: Aug 3, 2021
 *      Author: Shinelon
 */


#include "fft_calculate.h"
#include "math.h"

long InBufArray[NPT]={0};
long OutBufArray[NPT/2];
long MagBufArray[NPT/2];
//#define N 512;

void GetPowerMag()
{
    signed short lX,lY;
    float X,Y,Mag;
    unsigned short i;
//    cr4_fft_256_stm32(OutBufArray, InBufArray, N);
    for(i=0; i<NPT/2; i++)
    {
        lX  = (OutBufArray[i] << 16) >> 16;
        lY  = (OutBufArray[i] >> 16);

        //除以32768再乘65536是为了符合浮点数计算规律
        X = NPT * ((float)lX) / 32768;
        Y = NPT * ((float)lY) / 32768;
        Mag = sqrt(X * X + Y * Y) / NPT;
        if(i == 0)
            MagBufArray[i] = (unsigned long)(Mag * 32768);
        else
            MagBufArray[i] = (unsigned long)(Mag * 65536);
    }
}
