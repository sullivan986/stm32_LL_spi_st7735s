#ifndef __LCD_H_
#define __LCD_H_

#include <stdlib.h>
#include <string.h>

#include "main.h"

#define USE_HORIZONTAL 1  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

// offset of the display
#define DISPLAY_X_OFFSET        0
#define DISPLAY_Y_OFFSET        0

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif


#define SET(x) LL_GPIO_SetOutputPin(x##_GPIO_Port, x##_Pin)
#define CLR(x) LL_GPIO_ResetOutputPin(x##_GPIO_Port, x##_Pin)

#define LCD_RES_Clr()  CLR(RST)
#define LCD_RES_Set()  SET(RST)

#define LCD_DC_Clr()   CLR(DC)
#define LCD_DC_Set()   SET(DC)
 		     
#define LCD_CS_Clr()   CLR(CS)
#define LCD_CS_Set()   SET(CS)

#define LCD_BLK_Clr()  CLR(BL)
#define LCD_BLK_Set()  SET(BL)

void LCD_Init(void);

void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);//指定区域填充颜色

__STATIC_INLINE uint16_t RGB565(uint8_t R, uint8_t G, uint8_t B)
{
	return ((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3);
}

void Disp0_DrawBitmap(uint32_t x, uint32_t y, uint32_t width, uint32_t height, const void *bitmap);

// color
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40
#define BRRED 			 0XFC07
#define GRAY  			 0X8430
#define DARKBLUE      	 0X01CF
#define LIGHTBLUE      	 0X7D7C
#define GRAYBLUE       	 0X5458
#define LIGHTGREEN     	 0X841F
#define LGRAY 			 0XC618
#define LGRAYBLUE        0XA651
#define LBBLUE           0X2B12

#endif