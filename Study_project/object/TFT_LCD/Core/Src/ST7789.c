#include "st7789.h"
#include "font.h"


/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(uint8_t dat) 
{	
	LCD_CS_Clr();
	
	#if defined HW_SPI
		//   HAL_SPI_Transmit(&hspi1,&data,1,0xff);
		HAL_SPI_Transmit(&ST7789_LCD_SPI, &dat, 1, 0xffff);
	#elif defined SW_SPI
		uint8_t i;
		for(i=0;i<8;i++)
		{			  
			LCD_SCLK_Clr();
			if(dat&0x80)
			{
			LCD_MOSI_Set();
			}
			else
			{
			LCD_MOSI_Clr();
			}
			LCD_SCLK_Set();
			dat<<=1;
		}	
	#elif defined HW_SPI_DMA
	//TODO: spi+dma 在这感觉没必要，因为是发送一个字节。
	//期望整体优化，改成一个w*h的数组整体使用dma发送
	#endif

  	LCD_CS_Set();
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(uint8_t dat)
{
    LCD_DC_Set();//写数据
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA16(uint16_t dat)
{
    LCD_DC_Set();//写数据
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_CMD(uint8_t dat)
{
	LCD_DC_Clr();//写命令
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//写数据
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
if(USE_HORIZONTAL==0)
	{
		LCD_WR_CMD(0x2a);//列地址设置
		LCD_WR_DATA16(x1);
		LCD_WR_DATA16(x2);
		LCD_WR_CMD(0x2b);//行地址设置
		LCD_WR_DATA16(y1);
		LCD_WR_DATA16(y2);
		LCD_WR_CMD(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_CMD(0x2a);//列地址设置
		LCD_WR_DATA16(x1);
		LCD_WR_DATA16(x2);
		LCD_WR_CMD(0x2b);//行地址设置
		LCD_WR_DATA16(y1+80);
		LCD_WR_DATA16(y2+80);
		LCD_WR_CMD(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_CMD(0x2a);//列地址设置
		LCD_WR_DATA16(x1);
		LCD_WR_DATA16(x2);
		LCD_WR_CMD(0x2b);//行地址设置
		LCD_WR_DATA16(y1);
		LCD_WR_DATA16(y2);
		LCD_WR_CMD(0x2c);//储存器写
	}
	else
	{
		LCD_WR_CMD(0x2a);//列地址设置
		LCD_WR_DATA16(x1+80);
		LCD_WR_DATA16(x2+80);
		LCD_WR_CMD(0x2b);//行地址设置
		LCD_WR_DATA16(y1);
		LCD_WR_DATA16(y2);
		LCD_WR_CMD(0x2c);//储存器写
	}
}


/******************************************************************************
      函数说明：液晶初始化
      入口数据：无
      返回值：  无
******************************************************************************/
 
void LCD_Init(void)
{
//	LCD_GPIO_Init();//初始化GPIO
	
	LCD_BLK_Clr();//关闭背光
 
	LCD_RES_Clr();//复位
	HAL_Delay(50);
	LCD_RES_Set();
	HAL_Delay(50);
	
   	LCD_BLK_Set();//打开背光

  HAL_Delay(100);
	
	LCD_WR_CMD(0x11);                                             //无此指令，不能正常初始化芯片，无显示
	HAL_Delay(120); 
	LCD_WR_CMD(0x36);                                             //设置内存扫描方向，0X00正常扫描，从上往下，从左往右，RGB方式
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
	else LCD_WR_DATA8(0xA0);

	LCD_WR_CMD(0x3A);                                             //数据格式，65K色,565
	LCD_WR_DATA8(0x05);

	LCD_WR_CMD(0xB2);                                             //帧频设置
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x33); 

  LCD_WR_CMD(0xC6);                                               //正常模式下的帧速率控制
//  LCD_WR_DATA8(0x01);                                            //正常模式下：屏幕刷新率 111Hz
  LCD_WR_DATA8(0x1F);                                            //正常模式下：屏幕刷新率 39Hz
  
	LCD_WR_CMD(0xB7);                                             //GATE 设置
	LCD_WR_DATA8(0x35);  

	LCD_WR_CMD(0xBB);                                             //VCOM设置 
	LCD_WR_DATA8(0x19);

	LCD_WR_CMD(0xC0);                                             //LCM设置,默认0x2c
	LCD_WR_DATA8(0x2C);

	LCD_WR_CMD(0xC2);                                             //VDV&VRH SET ,默认0x01
	LCD_WR_DATA8(0x01);

	LCD_WR_CMD(0xC3);                                             //VRHS SET，默认0x0b
	LCD_WR_DATA8(0x12);                                           //此处根据实际情况修正

	LCD_WR_CMD(0xC4);                                             //VDV SET，默认0x20
	LCD_WR_DATA8(0x20);  

	LCD_WR_CMD(0xC6);                                             // FR SET, 默认0x0F
	LCD_WR_DATA8(0x0F);    

	LCD_WR_CMD(0xD0);                                             //电源控制1
	LCD_WR_DATA8(0xA4);                                           //该参数不变  
	LCD_WR_DATA8(0xA1);                                           //此处根据实际情况修改

	LCD_WR_CMD(0xE0);                                             //正极性GAMMA调整 
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2B);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0x4C);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x0B);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x23);

	LCD_WR_CMD(0xE1);                                              //负极性GAMMA调整
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2C);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x44);
	LCD_WR_DATA8(0x51);
	LCD_WR_DATA8(0x2F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x20);
	LCD_WR_DATA8(0x23);

	LCD_WR_CMD(0x21);                                             //反显开，默认是0X20，正常模式
  
	LCD_WR_CMD(0x29);                                             //显示开，等待MCU数传送
}


/******************************************************************************
      函数说明：LCD清屏函数
      入口数据：无
      返回值：  无
******************************************************************************/
void LCD_Clear(uint16_t Color)
{
	uint16_t i,j;  	
	LCD_Address_Set(0,0,LCD_W-1,LCD_H-1);
    for(i=0;i<LCD_W;i++)
	 {
	  for (j=0;j<LCD_H;j++)
	   	{
        	LCD_WR_DATA16(Color);	 			 
	    }

	  }
}


/******************************************************************************
      函数说明：在指定区域填充颜色
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
								color       要填充的颜色
      返回值：  无
******************************************************************************/
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{          
	uint16_t i,j; 
	LCD_Address_Set(xsta,ysta,xend-1,yend-1);//设置显示范围
	for(i=ysta;i<yend;i++)
	{													   	 	
		for(j=xsta;j<xend;j++)
		{
			LCD_WR_DATA16(color);
		}
	} 					  	    
}

/******************************************************************************
      函数说明：在指定位置画点
      入口数据：x,y 画点坐标
                color 点的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
	LCD_Address_Set(x,y,x,y);//设置光标位置 
	LCD_WR_DATA16(color);
} 


/******************************************************************************
      函数说明：画线
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   线的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1;
	uRow=x1;//画线起点坐标
	uCol=y1;
	if(delta_x>0)incx=1; //设置单步方向 
	else if (delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//水平线 
	else {incy=-1;delta_y=-delta_y;}
	if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		LCD_DrawPoint(uRow,uCol,color);//画点
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}


/******************************************************************************
      函数说明：画矩形
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
                color   矩形的颜色
      返回值：  无
******************************************************************************/
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
      函数说明：画圆
      入口数据：x0,y0   圆心坐标
                r       半径
                color   圆的颜色
      返回值：  无
******************************************************************************/
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
	int a,b;
	a=0;b=r;	  
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a,color);             //3           
		LCD_DrawPoint(x0+b,y0-a,color);             //0           
		LCD_DrawPoint(x0-a,y0+b,color);             //1                
		LCD_DrawPoint(x0-a,y0-b,color);             //2             
		LCD_DrawPoint(x0+b,y0+a,color);             //4               
		LCD_DrawPoint(x0+a,y0-b,color);             //5
		LCD_DrawPoint(x0+a,y0+b,color);             //6 
		LCD_DrawPoint(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//判断要画的点是否过远
		{
			b--;
		}
	}
}

/******************************************************************************
      函数说明：显示汉字串
      入口数据：x,y显示坐标
                *s 要显示的汉字串
                fc 字的颜色
                bc 字的背景色
                sizey 字号 可选 16 24 32
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	while(*s!=0)
	{
		if(sizey==12) LCD_ShowChinese12x12(x,y,s,fc,bc,sizey,mode);
		else if(sizey==16) LCD_ShowChinese16x16(x,y,s,fc,bc,sizey,mode);
		else if(sizey==24) LCD_ShowChinese24x24(x,y,s,fc,bc,sizey,mode);
		else if(sizey==32) LCD_ShowChinese32x32(x,y,s,fc,bc,sizey,mode);
		else return;
		s+=2;
		x+=sizey;
	}
}

/******************************************************************************
      函数说明：显示单个12x12汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
//	uint8_t i,j,m=0;
//	uint16_t k;
//	uint16_t HZnum;//汉字数目
//	uint16_t TypefaceNum;//一个字符所占字节大小
//	uint16_t x0=x;
//	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	                         
//	HZnum=sizeof(tfont12)/sizeof(typFNT_GB12);	//统计汉字数目
//	for(k=0;k<HZnum;k++) 
//	{
//		if((tfont12[k].Index[0]==*(s))&&(tfont12[k].Index[1]==*(s+1)))
//		{ 	
//			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//非叠加方式
//					{
//						if(tfont12[k].Msk[i]&(0x01<<j))LCD_WR_DATA16(fc);
//						else LCD_WR_DATA16(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//叠加方式
//					{
//						if(tfont12[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//	}
} 

/******************************************************************************
      函数说明：显示单个16x16汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
//	uint8_t i,j,m=0;
//	uint16_t k;
//	uint16_t HZnum;//汉字数目
//	uint16_t TypefaceNum;//一个字符所占字节大小
//	uint16_t x0=x;
//  TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	HZnum=sizeof(tfont16)/sizeof(typFNT_GB16);	//统计汉字数目
//	for(k=0;k<HZnum;k++) 
//	{
//		if ((tfont16[k].Index[0]==*(s))&&(tfont16[k].Index[1]==*(s+1)))
//		{ 	
//			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//非叠加方式
//					{
//						if(tfont16[k].Msk[i]&(0x01<<j))LCD_WR_DATA16(fc);
//						else LCD_WR_DATA16(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//叠加方式
//					{
//						if(tfont16[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//	}
} 


/******************************************************************************
      函数说明：显示单个24x24汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
//	uint8_t i,j,m=0;
//	uint16_t k;
//	uint16_t HZnum;//汉字数目
//	uint16_t TypefaceNum;//一个字符所占字节大小
//	uint16_t x0=x;
//	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
//	HZnum=sizeof(tfont24)/sizeof(typFNT_GB24);	//统计汉字数目
//	for(k=0;k<HZnum;k++) 
//	{
//		if ((tfont24[k].Index[0]==*(s))&&(tfont24[k].Index[1]==*(s+1)))
//		{ 	
//			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
//			for(i=0;i<TypefaceNum;i++)
//			{
//				for(j=0;j<8;j++)
//				{	
//					if(!mode)//非叠加方式
//					{
//						if(tfont24[k].Msk[i]&(0x01<<j))LCD_WR_DATA16(fc);
//						else LCD_WR_DATA16(bc);
//						m++;
//						if(m%sizey==0)
//						{
//							m=0;
//							break;
//						}
//					}
//					else//叠加方式
//					{
//						if(tfont24[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
//						x++;
//						if((x-x0)==sizey)
//						{
//							x=x0;
//							y++;
//							break;
//						}
//					}
//				}
//			}
//		}				  	
//		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
//	}
} 

/******************************************************************************
      函数说明：显示单个32x32汉字
      入口数据：x,y显示坐标
                *s 要显示的汉字
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
/*void LCD_ShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t i,j,m=0;
	uint16_t k;
	uint16_t HZnum;//汉字数目
	uint16_t TypefaceNum;//一个字符所占字节大小
	uint16_t x0=x;
	TypefaceNum=(sizey/8+((sizey%8)?1:0))*sizey;
	HZnum=sizeof(tfont32)/sizeof(typFNT_GB32);	//统计汉字数目
	for(k=0;k<HZnum;k++) 
	{
		if ((tfont32[k].Index[0]==*(s))&&(tfont32[k].Index[1]==*(s+1)))
		{ 	
			LCD_Address_Set(x,y,x+sizey-1,y+sizey-1);
			for(i=0;i<TypefaceNum;i++)
			{
				for(j=0;j<8;j++)
				{	
					if(!mode)//非叠加方式
					{
						if(tfont32[k].Msk[i]&(0x01<<j))LCD_WR_DATA16(fc);
						else LCD_WR_DATA16(bc);
						m++;
						if(m%sizey==0)
						{
							m=0;
							break;
						}
					}
					else//叠加方式
					{
						if(tfont32[k].Msk[i]&(0x01<<j))	LCD_DrawPoint(x,y,fc);//画一个点
						x++;
						if((x-x0)==sizey)
						{
							x=x0;
							y++;
							break;
						}
					}
				}
			}
		}				  	
		continue;  //查找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
	}
}
*/

/******************************************************************************
      函数说明：显示单个字符
      入口数据：x,y显示坐标
                num 要显示的字符
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t temp,sizex,t,m=0;
	uint16_t i,TypefaceNum;//一个字符所占字节大小
	uint16_t x0=x;
	sizex=sizey/2;
	TypefaceNum=(sizex/8+((sizex%8)?1:0))*sizey;
	num=num-' ';    //得到偏移后的值
	LCD_Address_Set(x,y,x+sizex-1,y+sizey-1);  //设置光标位置 
	for(i=0;i<TypefaceNum;i++)
	{ 
//		if(sizey==12)temp=ascii_1206[num][i];		       //调用6x12字体
//		else if(sizey==16)temp=ascii_1608[num][i];		 //调用8x16字体
//		else      if(sizey==24)temp=ascii_2412[num][i];		 //调用12x24字体
//		else 
      if(sizey==32)temp=ascii_3216[num][i];		 //调用16x32字体
		else return;
		for(t=0;t<8;t++)
		{
			if(!mode)//非叠加模式
			{
				if(temp&(0x01<<t))LCD_WR_DATA16(fc);
				else LCD_WR_DATA16(bc);
				m++;
				if(m%sizex==0)
				{
					m=0;
					break;
				}
			}
			else//叠加模式
			{
				if(temp&(0x01<<t))LCD_DrawPoint(x,y,fc);//画一个点
				x++;
				if((x-x0)==sizex)
				{
					x=x0;
					y++;
					break;
				}
			}
		}
	}   	 	  
}


/******************************************************************************
      函数说明：显示字符串
      入口数据：x,y显示坐标
                *p 要显示的字符串
                fc 字的颜色
                bc 字的背景色
                sizey 字号
                mode:  0非叠加模式  1叠加模式
      返回值：  无
******************************************************************************/
void LCD_ShowString(uint16_t x,uint16_t y,const char *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{         
	while(*p!='\0')
	{       
		LCD_ShowChar(x,y,*p,fc,bc,sizey,mode);
		x+=sizey/2;
		p++;
	}  
}


/******************************************************************************
      函数说明：显示数字
      入口数据：m底数，n指数 m^n函数
      返回值：  无
******************************************************************************/
uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;
	return result;
}


/******************************************************************************
      函数说明：显示整数变量
      入口数据：x,y显示坐标
                num 要显示整数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint16_t fc,uint16_t bc,uint8_t sizey)
{ 
  uint16_t numTemp;
  uint8_t len=0;
	uint8_t t,temp;
	uint8_t enshow=0;
	uint8_t sizex=sizey/2;
  
  numTemp=num;
  while(numTemp>0)    //得出整型值的长度
  {
    len++;
    numTemp/=10;
  }
  
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+t*sizex,y,' ',fc,bc,sizey,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+t*sizex,y,temp+48,fc,bc,sizey,0);
	}
} 

/******************************************************************************
      函数说明：显示两位小数变量
      入口数据：x,y显示坐标
                num 要显示小数变量
                len 要显示的位数
                fc 字的颜色
                bc 字的背景色
                sizey 字号
      返回值：  无
******************************************************************************/
void LCD_ShowFloat(uint16_t x,uint16_t y,float num,uint16_t fc,uint16_t bc,uint8_t sizey)
{
//-----------------方式1--------------------
//  float numTemp;      //浮点数临时备份
//  uint8_t IntNum;     //整数部分
//  uint8_t FloatNum;   //小数部分
//  
//  numTemp=num;        //将浮点数保存
//  IntNum=num;         //提取整数部分
//  
//  
//  while(numTemp-1>0)  //提取浮点数，将整数部分去掉
//  {
//    numTemp--;
//  }
  //FloatNum=numTemp*100;   //去掉整数部分后，提取两位浮点数
//  
//    LCD_ShowIntNum(x,y,IntNum,fc,bc,sizey);
//    LCD_ShowFloatNum(x+sizey,y,numTemp,2,fc,bc,sizey);
//  printf("输入数值%0.2f  整数部分：%d  小数部分:%d\r\n",num,IntNum,FloatNum);
 
//-----------------方式2--------------------  
    char temp[20];      //缓存
    sprintf((char *)temp,"%0.2f",num);        //需要"string.h",取小数两位
    LCD_ShowString(x,y,temp,fc,bc,sizey,0);   //调用字符串显示
}
/******************************************************************************
      函数说明：显示图片
      入口数据：x,y起点坐标
                length 图片宽度
                width  图片高度
                pic[]  图片数组    
      返回值：  无
      说明：Image2LCD 3.2版本软件生成代码 4.0版本不行
       设置：  扫描模式：水平扫描
               输出灰度：16位真彩色
               最大宽度和高度： 图片分辨率       
               高位在前 √ 打勾 其它的均不要√
******************************************************************************/
void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[])
{
	uint16_t i,j;
	uint32_t k=0;
	LCD_Address_Set(x,y,x+length-1,y+width-1);
	for(i=0;i<length;i++)
	{
		for(j=0;j<width;j++)
		{
			LCD_WR_DATA8(pic[k*2]);
			LCD_WR_DATA8(pic[k*2+1]);
			k++;
		}
	}		         
}


/*
      函数说明：垂直滚动区域定义指令
      入口数据：TFA：顶部固定显示区域
                VSA：滚动区域，这部分指定后会滚动显示；
                BFA：底部固定显示区域
      返回值：  无
      说明：1、先设置滚动区域，TFA、VSA、BFA三个区域的值设置都是16位，并且三个值加起来要等于320，否则滚动区域定义失败。
            2、LCD初始化函数的最后设置滚动区域
            3、 LCD_Set_Scroll_Area(20,120,180);  
*/
int LCD_Set_Scroll_Area(uint16_t TFA, uint16_t VSA, uint16_t BFA)
{
    uint8_t data;    
    if (TFA + VSA + BFA != 320) {
        return -1;
    }    
    LCD_WR_CMD(0x33);    
    data = TFA >> 8;    
    LCD_WR_DATA8(data);   //TFA高8位
    data = TFA;
    LCD_WR_DATA8(data);   //TFA低8位
    data = VSA >> 8;
    LCD_WR_DATA8(data);   //VSA高8位
    data = VSA;
    LCD_WR_DATA8(data);   //VSA低8位
    data = BFA >> 8;
    LCD_WR_DATA8(data);   //BFA高8位
    data = BFA;
    LCD_WR_DATA8(data);   //BFA低8位
    return 0;
}

/*
      函数说明：设置滚动显示起始地址
      入口数据：TFA：顶部固定显示区域
                VSA：滚动区域，这部分指定后会滚动显示；
                BFA：底部固定显示区域
      返回值：  无
      说明：在LCD初始化代码的最后添加设置滚动显示起始地址的代码
                正滚
                for(uint8_t i=120;i>0;i--)
                {
                  LCD_Set_Scroll_Start_Address(i);
                  HAL_Delay(5); 
                }
                 反滚
                for(uint8_t i=0;i<120;i++)
                {
                  LCD_Set_Scroll_Start_Address(i);
                  HAL_Delay(5); 
                }

*/
void LCD_Set_Scroll_Start_Address(uint16_t vsp)
{
    uint8_t data;
    LCD_WR_CMD(0x37);   //设置滚动显示起始地址的指令为0x37
    data=vsp>>8;
    LCD_WR_DATA8(data);  //VSP高8位
    data=vsp;
    LCD_WR_DATA8(data);  //VSP低8位
}

/*
函数说明：曲线绘制
入口数据：输入值，线颜色，背景色                
                
返回值：  无
说明：

*/

uint16_t lastX,lastY;
uint8_t firstPoint = 1;
void DrawCurve(uint16_t RawValue,uint16_t fc,uint16_t bc)  
{
	uint16_t x,y;
  y=240-RawValue*2;     //2为放大倍数
//  y=100-RawValue*10;//曲线幅度
//	y = 120 - rawValue/280;  	//data processing code
	//这里之所以是120-rawValue/280，与屏幕的扫描方向有关，如果出现上下颠倒的情况，可以改成120 + 
	if(firstPoint)//如果是第一次画点，则无需连线，直接描点即可
	{
		LCD_DrawPoint(0,y,fc);
		lastX=0;
		lastY=y;
		firstPoint=0;
	}
	else
	{
		x=lastX+1;
		if(x<240)  //不超过屏幕宽度
		{
			LCD_DrawLine(lastX,lastY,x,y,fc);   //超始坐标：lastX lastY 终止坐标：x,y
			lastX=x;
			lastY=y;
		}
		else  //超出屏幕宽度，清屏，从第一个点开始绘制，实现动态更新效果
		{
			LCD_Clear(bc);//清屏，
			LCD_DrawPoint(0,y,fc);
			lastX=0;
			lastY=y;
		}
  }
}