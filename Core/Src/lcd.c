#include "lcd.h"

static void ST7735_write(uint8_t data)
{
    // int count = 0;
    while(!LL_SPI_IsActiveFlag_TXE(SPI1))
    {
        // if(count++ > 1000) break;
    }
    
    LL_SPI_TransmitData8(SPI1, data);
    // count = 0;
    while(LL_SPI_IsActiveFlag_BSY(SPI1))
    {
        // if(count++ > 1000) break;
    }
}

static void LCD_WR_REG(uint8_t cmd)
{
	CLR(DC);
	ST7735_write(cmd);
}

static void LCD_WR_REG_FOL(uint8_t cmd)
{
	ST7735_write(cmd);
}


static void LCD_WR_DATA8(uint8_t data)
{
	SET(DC);
	ST7735_write(data);
}

static void LCD_WR_DATA8_FOL(uint8_t data)
{
	ST7735_write(data);
}

static void LCD_WR_DATA(uint16_t dat)
{
    SET(DC);
	ST7735_write(dat>>8);
	ST7735_write(dat);
}

static void LCD_WR_DATA_FOL(uint16_t dat)
{
	ST7735_write(dat>>8);
	ST7735_write(dat);
}

static void st7735r_set_mem_area(const uint16_t x, const uint16_t y,
                                const uint16_t w, const uint16_t h)
{
    LCD_WR_REG(0x2a);
    LCD_WR_DATA(x + DISPLAY_X_OFFSET);
    LCD_WR_DATA_FOL(x + w - 1 + DISPLAY_X_OFFSET);
    LCD_WR_REG(0x2b);
    LCD_WR_DATA(y + DISPLAY_Y_OFFSET);
    LCD_WR_DATA_FOL(y + h - 1 + DISPLAY_Y_OFFSET);
    LCD_WR_REG(0x2c);
}

void LCD_Init(void)
{
    LCD_CS_Clr();
    LL_mDelay(100);
	LL_SPI_Enable(SPI1);
    LL_mDelay(100);
	LCD_RES_Clr();//复位
	LL_mDelay(100);
	LCD_RES_Set();
	LL_mDelay(100);
	LCD_BLK_Set();//打开背光
    LL_mDelay(100);
	//************* Start Initial Sequence **********//
	LCD_WR_REG(0x11); //Sleep out 
	LL_mDelay(120);              //Delay 120ms 
	//------------------------------------ST7735S Frame Rate-----------------------------------------// 
	LCD_WR_REG_FOL(0xB1); 
    
	LCD_WR_DATA8(0x05); 
	LCD_WR_DATA8_FOL(0x3C); 
	LCD_WR_DATA8_FOL(0x3C); 
    
	LCD_WR_REG(0xB2); 
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8_FOL(0x3C); 
	LCD_WR_DATA8_FOL(0x3C); 
    
	LCD_WR_REG(0xB3); 
	LCD_WR_DATA8(0x05); 
	LCD_WR_DATA8_FOL(0x3C); 
	LCD_WR_DATA8_FOL(0x3C); 
	LCD_WR_DATA8_FOL(0x05); 
	LCD_WR_DATA8_FOL(0x3C); 
	LCD_WR_DATA8_FOL(0x3C); 
	//------------------------------------End ST7735S Frame Rate---------------------------------// 
	LCD_WR_REG(0xB4); //Dot inversion 
	LCD_WR_DATA8(0x03); 
	//------------------------------------ST7735S Power Sequence---------------------------------// 
	LCD_WR_REG(0xC0); 
	LCD_WR_DATA8(0x28); 
	LCD_WR_DATA8_FOL(0x08); 
	LCD_WR_DATA8_FOL(0x04); 
    
	LCD_WR_REG(0xC1); 
	LCD_WR_DATA8(0XC0); 
    
	LCD_WR_REG(0xC2); 
	LCD_WR_DATA8(0x0D); 
	LCD_WR_DATA8_FOL(0x00); 
    
	LCD_WR_REG(0xC3); 
	LCD_WR_DATA8(0x8D); 
	LCD_WR_DATA8_FOL(0x2A); 
    
	LCD_WR_REG(0xC4); 
	LCD_WR_DATA8(0x8D); 
	LCD_WR_DATA8_FOL(0xEE); 
	//---------------------------------End ST7735S Power Sequence-------------------------------------// 
	LCD_WR_REG(0xC5); //VCOM 
	LCD_WR_DATA8(0x1A); 
	LCD_WR_REG(0x36); //MX, MY, RGB mode 
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
	else LCD_WR_DATA8(0xA0); 
	//------------------------------------ST7735S Gamma Sequence---------------------------------// 
	LCD_WR_REG(0xE0); 
	LCD_WR_DATA8(0x04); 
	LCD_WR_DATA8_FOL(0x22); 
	LCD_WR_DATA8_FOL(0x07); 
	LCD_WR_DATA8_FOL(0x0A); 
	LCD_WR_DATA8_FOL(0x2E); 
	LCD_WR_DATA8_FOL(0x30); 
	LCD_WR_DATA8_FOL(0x25); 
	LCD_WR_DATA8_FOL(0x2A); 
	LCD_WR_DATA8_FOL(0x28); 
	LCD_WR_DATA8_FOL(0x26); 
	LCD_WR_DATA8_FOL(0x2E); 
	LCD_WR_DATA8_FOL(0x3A); 
	LCD_WR_DATA8_FOL(0x00); 
	LCD_WR_DATA8_FOL(0x01); 
	LCD_WR_DATA8_FOL(0x03); 
	LCD_WR_DATA8_FOL(0x13); 
    
	LCD_WR_REG(0xE1); 
	LCD_WR_DATA8(0x04); 
	LCD_WR_DATA8_FOL(0x16); 
	LCD_WR_DATA8_FOL(0x06); 
	LCD_WR_DATA8_FOL(0x0D); 
	LCD_WR_DATA8_FOL(0x2D); 
	LCD_WR_DATA8_FOL(0x26); 
	LCD_WR_DATA8_FOL(0x23); 
	LCD_WR_DATA8_FOL(0x27); 
	LCD_WR_DATA8_FOL(0x27); 
	LCD_WR_DATA8_FOL(0x25); 
	LCD_WR_DATA8_FOL(0x2D); 
	LCD_WR_DATA8_FOL(0x3B); 
	LCD_WR_DATA8_FOL(0x00); 
	LCD_WR_DATA8_FOL(0x01); 
	LCD_WR_DATA8_FOL(0x04); 
	LCD_WR_DATA8_FOL(0x13); 
	//------------------------------------End ST7735S Gamma Sequence-----------------------------// 
	LCD_WR_REG(0x3A); //65k mode 
	LCD_WR_DATA8(0x05); 
	LCD_WR_REG(0x29); //Display on 
} 

void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{          
	uint16_t i,j; 
	st7735r_set_mem_area(0, 0, LCD_W, LCD_H);
    SET(DC);
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{
			LCD_WR_DATA_FOL(color);
		}
	} 					  	    
}

void Disp0_DrawBitmap (uint32_t x, 
                       uint32_t y, 
                       uint32_t width, 
                       uint32_t height, 
                       const void *bitmap)
                           
{
    const uint8_t* buf = (uint8_t*)bitmap;
    st7735r_set_mem_area(x, y, width, height);
    SET(DC);
    for(int i = 0; i < height*width*2; i++)
    {
        LCD_WR_DATA8_FOL(*(buf++));
    }
}
