#ifndef __FLASH_H
#define __FLASH_H


#include "main.h"



void WriteFlash(uint32_t addr,uint32_t *Data,uint32_t L);
void Flash_Read(uint32_t address, uint32_t *data, uint16_t length);
#define FLASH_SAVE_ADDR  (0x08060000) // 这地方不用改直接用这个地址



typedef struct {
    float float_data[6];
    int int_data[6];
} DataToSave;								//这个是要保存数据的结构体


extern DataToSave data_to_save ;//这个是写入数据后的缓冲结构体
extern DataToSave data_read ;		//这个是读取数据后保存的缓冲结构体


void my_flash_write(void);
void my_flash_read(void);



#endif
