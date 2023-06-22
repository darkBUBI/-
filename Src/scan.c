/*
 * scan.c
 *
 *  Created on: Oct 18, 2021
 *      Author: Shinelon
 */

/*
 频点数组[]=[100,200,300...省略...,0]最后一个数以0结尾，【扫函数】里用0判断结尾。
 */
#include "scan.h"
#include "ad9833.h"
#include "i2c.h"
#include "usart.h"
#include "ads1115i2c.h"
void scan(unsigned long int a[], long int b[], long int c[])//扫函数
{//这么多个参数干嘛？参数只需要传入【频点数组】【幅度记录数组】【相位记录数组】三个数组。这三个数组又有几组，每次传入不同的一组。
	int i=0,j=0;

	unsigned  char showbuff[20]={"0"};
	while(a[i]!=0)//从 频率数组[0]开始，到 频率数组[i]==0 结束。
	  {
		//把频率输出到DDS
		//记录ADC值到【幅度】【相位】数组
		AD9833_WaveSeting(a[i], 0, 1, 0);
		LL_mDelay(100);
		for(j=0;j<5;j++)//采样五次取平均
		{
			ads1115_config_register(hi2c1,0x01,CONFIG_REG_H,CONFIG_REG_L);
			LL_mDelay(10);
			b[i]=b[i]+ads1115_read_data(hi2c1);
		}
		b[i]=b[i]*0.2;
//		sprintf(showbuff,"%d = %d\n",i,b[i]);
//		HAL_UART_Transmit(&huart1,showbuff, 20, 1000);
//		LL_mDelay(100);
//		b[i]=ads1115_get_voltage_val(hi2c1,0x01,CONFIG_REG_H,CONFIG_REG_L);
		i++;
//		while(i>=2 && (FuDu[i] > FuDu[i-1] || FuDu[i] > FuDu[i-2]) )	//最低点,当前点比前两个点或者前一点的采样值高，则三点之中存在最低点
//		{
//			PinDianShengCheng_1(a1, b1)
//			scan_2(PinDian[40],FuDu[40],XiangWei[40]);
//		}
	  }
}
void PinDianShengCheng_1(unsigned long int d[])//粗扫
{
	int i=0;
	d[0]=1000;
	for(i=1;i<10;i++)
		d[i]=d[i-1]+1000;
	for(i=10;i<29;i++)
		d[i]=d[i-1]+10000;
	i++;
	d[i]=0;
}
void PinDianShengCheng_S(unsigned long int aL1,unsigned long int bL1, int n, long int L[])
{
	int i=0,j=0;
	for(j=aL1;j<=bL1;j=j+n)
		{
			L[i]=j;
			i++;
		}
	i++;
	L[i]=0;
}

//void PinDianShengCheng_1(unsigned long int a2,unsigned long int b2)
//{
//	int i=0;
//	unsigned long int PinDian[40]={0};
//	for(i=0;i<10;i++)
//		PinDian[i] +=1000;
//	for(i=10;i<30;i++)
//		PinDian[i] +=10000;
//	i++;
//	PinDian[i]=0;
//}
