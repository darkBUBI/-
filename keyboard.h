/*
 * keyboard.h
 *
 *  Created on: 2022年1月27日
 *      Author: Shinelon
 */

#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_


const  unsigned char* key_menu[15]={"Rst"," : ","wuhu","1","2","3","4","5","6","7","8","9","DEL","0","Enter",};  //按键界面菜单
void Load_keyboard(unsigned short int x,unsigned short int y,unsigned char **key_content);  //加载按键界面
void Key_staset(unsigned short int x,unsigned short int y,unsigned char keyx,unsigned char sta);  //设置按键捕获状态
unsigned char Get_keynum(unsigned short int x,unsigned short int y);  //得到按键的输入
unsigned short int GET_NUM(void);
void Show_Str_Mid(unsigned short int x,unsigned short int y,unsigned char*str,unsigned char size,unsigned char len);
#endif /* INC_KEYBOARD_H_ */
