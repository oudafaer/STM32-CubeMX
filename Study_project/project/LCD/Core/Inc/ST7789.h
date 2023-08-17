#ifndef __ST7789_H__
#define __ST7789_H__

#include "main.h"


#define USE_HORIZONTAL 0  //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 240
#define LCD_H 240
#else
#define LCD_W 240
#define LCD_H 240
#endif


// SW_SPI or HW_SPI or HW_SPI_DMA  ��HW_SPI_DMA��ʱ���ò��ˣ���ش��뻹ûд��
#define HW_SPI

//==========================================
//����spi 
//==========================================
#if (defined HW_SPI) || (defined HW_SPI_DMA)
#define ST7789_LCD_SPI hspi1
extern SPI_HandleTypeDef hspi1;
#endif // HW_SPI

//==========================================
//GPIO-��д
//==========================================
#define LCD_RES_GPIO        GPIOB
#define LCD_RES_GPIO_PIN    GPIO_PIN_0
#define LCD_DC_GPIO         GPIOB
#define LCD_DC_GPIO_PIN     GPIO_PIN_1
#define LCD_CS_GPIO         GPIOB
#define LCD_CS_GPIO_PIN     GPIO_PIN_10
#define LCD_BLK_GPIO        GPIOB
#define LCD_BLK_GPIO_PIN    GPIO_PIN_11

#ifdef SW_SPI
#define LCD_SCLK_GPIO       GPIOA
#define LCD_SCLK_GPIO_PIN   GPIO_PIN_5
#define LCD_MOSI_GPIO       GPIOA
#define LCD_MOSI_GPIO_PIN   GPIO_PIN_7
#endif // SW_SPI

//==========================================
//GPIO��ƽ���� �궨�� ����Ҫ�޸�
//==========================================
#define LCD_RES_Clr()  HAL_GPIO_WritePin(LCD_RES_GPIO,LCD_RES_GPIO_PIN,GPIO_PIN_RESET)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(LCD_RES_GPIO,LCD_RES_GPIO_PIN,GPIO_PIN_SET)
                                 
#define LCD_DC_Clr()   HAL_GPIO_WritePin(LCD_DC_GPIO,LCD_DC_GPIO_PIN,GPIO_PIN_RESET)//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(LCD_DC_GPIO,LCD_DC_GPIO_PIN,GPIO_PIN_SET)
 		     
#define LCD_CS_Clr()   HAL_GPIO_WritePin(LCD_CS_GPIO,LCD_CS_GPIO_PIN,GPIO_PIN_RESET)//CS
#define LCD_CS_Set()   HAL_GPIO_WritePin(LCD_CS_GPIO,LCD_CS_GPIO_PIN,GPIO_PIN_SET)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin(LCD_BLK_GPIO,LCD_BLK_GPIO_PIN,GPIO_PIN_RESET)//BLK
#define LCD_BLK_Set()  HAL_GPIO_WritePin(LCD_BLK_GPIO,LCD_BLK_GPIO_PIN,GPIO_PIN_SET)

#ifdef SW_SPI
#define LCD_SCLK_Clr() HAL_GPIO_WritePin(LCD_SCLK_GPIO,LCD_SCLK_GPIO_PIN,GPIO_PIN_RESET)//SCL=SCLK
#define LCD_SCLK_Set() HAL_GPIO_WritePin(LCD_SCLK_GPIO,LCD_SCLK_GPIO_PIN,GPIO_PIN_SET)
#define LCD_MOSI_Clr() HAL_GPIO_WritePin(LCD_MOSI_GPIO,LCD_MOSI_GPIO_PIN,GPIO_PIN_RESET)//SDA=MOSI
#define LCD_MOSI_Set() HAL_GPIO_WritePin(LCD_MOSI_GPIO,LCD_MOSI_GPIO_PIN,GPIO_PIN_SET)
#endif // SW_SPI

void LCD_Writ_Bus(uint8_t dat);//ʵ�ʷ���
void LCD_WR_DATA8(uint8_t dat);//д��һ���ֽ�
void LCD_WR_DATA(uint16_t dat);//д�������ֽ�
void LCD_WR_REG(uint8_t dat);//д��һ��ָ��
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//�������꺯��
void LCD_Init(void);//LCD��ʼ��


void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color);//ָ�����������ɫ
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color);//��ָ��λ�û�һ����
void LCD_DrawLine(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t color);//��ָ��λ�û�һ����
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);//��ָ��λ�û�һ������
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);//��ָ��λ�û�һ��Բ

//���ں��ֱȽ��鷳����ֱ��ȫ��ע���ˣ����ԶԱȹٷ����̣��������Ҫ���ϣ��ܼ򵥡�
// void LCD_ShowChinese(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ���ִ�
// void LCD_ShowChinese12x12(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����12x12����
// void LCD_ShowChinese16x16(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����16x16����
// void LCD_ShowChinese24x24(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����24x24����
// void LCD_ShowChinese32x32(uint16_t x,uint16_t y,uint8_t *s,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ����32x32����

void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾһ���ַ�
void LCD_ShowString(uint16_t x,uint16_t y,const uint8_t *p,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);//��ʾ�ַ���
uint32_t mypow(uint8_t m,uint8_t n);//����
void LCD_ShowIntNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//��ʾ��������
void LCD_ShowFloatNum1(uint16_t x,uint16_t y,float num,uint8_t len,uint16_t fc,uint16_t bc,uint8_t sizey);//��ʾ��λС������
void LCD_ShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t width,const uint8_t pic[]);//��ʾͼƬ

//������ɫ
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
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)




#endif
