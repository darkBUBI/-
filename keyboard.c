/*
 * keyboard.c
 *
 *  Created on: 2022年1月27日
 *      Author: Shinelon
 */

#include "lcd.h"
#include "GUI.h"
#include "touch.h"


//在指定宽度的中间显示字符串
//如果字符长度超过了len,则用Show_Str显示
//len:指定要显示的宽度
void Show_Str_Mid(unsigned short int x,unsigned short int y,unsigned char*str,unsigned char size,unsigned char len)
{
	unsigned short int strlenth=0;
  strlenth=sizeof((const char*)str)-1; //字符串长度
	strlenth*=size/2;
	if(strlenth>len)
		LCD_ShowString(x,y,size,str,1);
	else
	{
		strlenth=(len-strlenth)/2; //剩余空间的一半
	  LCD_ShowString(strlenth+x,y,size,str,1);
	}
}


unsigned char** keycontent;
//加载按键界面（尺寸x,y为240*150）
//x,y:界面起始坐标（240*320分辨率的时候，x必须为0）
void Load_keyboard(unsigned short int x,unsigned short int y,unsigned char **key_content)
{
	unsigned short int i;
	POINT_COLOR=RED; //字体颜色为红色
	keycontent=key_content;
	LCD_Fill(x,y,x+240,y+150,WHITE);
	LCD_DrawRectangle(x,y,x+240,y+150);
	LCD_DrawRectangle(x+80,y,x+160,y+150);
	LCD_DrawRectangle(x,y+30,x+240,y+60);
	LCD_DrawRectangle(x,y+90,x+240,y+120);
	POINT_COLOR=BLUE;
	for(i=0;i<15;i++)
	{
		if(i==1) //"："不需要中间显示
			LCD_ShowString(x+(i%3)*80+2,y+7+30*(i/3),16,(unsigned char*)keycontent[i],1);
		else
			Show_Str_Mid(x+(i%3)*80,y+7+30*(i/3),(unsigned char*)keycontent[i],16,80);//让字符串在所要求位置的中间显示
	}
}


void Key_staset(unsigned short int x,unsigned short int y,unsigned char keyx,unsigned char sta)
{
	unsigned short int i=keyx/3,j=keyx%3;
	if(keyx>16)return;
	if(sta &&keyx!=1)  //"："区域不捕获
		LCD_Fill(x+j*80+1,y+i*30+1,x+j*80+78,y+i*30+28,GREEN);  //当该区域被按下 区域被绿色填充
	else if(keyx!=1)  //松手后区域恢复白色
		LCD_Fill(x+j*80+1,y+i*30+1,x+j*80+78,y+i*30+28,WHITE);
	if(keyx!=1)  //区域被填色后重新显示
		Show_Str_Mid(x+j*80,y+7+30*i,(unsigned char*)keycontent[keyx],16,80);
}


//得到触摸屏的输入
//x,y:键盘坐标
//返回值:（1~15,对应按键表）
unsigned char Get_keynum(unsigned short int x,unsigned short int y)
{
	unsigned short int i,j;
	static unsigned char key_x=0;
	unsigned char key=0;
	tp_dev.scan(0);
	if(tp_dev.sta&TP_PRES_DOWN)  //触摸屏被按下
	{
		for(i=0;i<5;i++)
		{
			for(j=0;j<3;j++)
			{
			 	if(tp_dev.x<(x+j*80+80)&&tp_dev.x>(x+j*80)&&tp_dev.y<(y+i*30+30)&&tp_dev.y>(y+i*30))  //决定每一块区域所代表的值
				{
					key=i*3+j+1;	//i代表行 每一行的变化需要变化三个值 j代表列 每一列变化仅需要变化一个值
					break;
				}
			}
			if(key) //key!=0
			{
				if(key_x==key)key=0;
				else
				{
					Key_staset(x,y,key_x-1,0);
					key_x=key;
					Key_staset(x,y,key_x-1,1);  //决定哪一块区域发生按键捕获
				}
				break;
			}
	  }
	}
	else if(key_x)  //每次从0开始 不记录上次的状态
	{
		Key_staset(x,y,key_x-1,0);
		key_x=0;
	}
	return key;
}



//获取键盘数值
unsigned short int GET_NUM(void)
{
	unsigned char  key_num=0;
	unsigned short int num=0;
	while(1)
	{
		key_num=Get_keynum(0,170);
		if(key_num)
		{
			if(key_num==1)return 0xFFFF;//‘返回’键
			if(key_num==3)return 0xFF00;//	NONE
			if(key_num>3&&key_num<13&&num<99)//‘1-9’键(限制输入3位数)
				num =num*10+key_num-3;
			if(key_num==13)num =num/10;//‘Del’键
			if(key_num==14&&num<99)num =num*10;//‘0’键
			if(key_num==15)return num;  //‘Enter’键
		}
		LCD_ShowNum(80+15,170+7,num,6,16);
	}
}
