#ifndef __FLASH_H
#define __FLASH_H


#include "main.h"



void WriteFlash(uint32_t addr,uint32_t *Data,uint32_t L);
void Flash_Read(uint32_t address, uint32_t *data, uint16_t length);
#define FLASH_SAVE_ADDR  (0x08060000) // ��ط����ø�ֱ���������ַ



typedef struct {
    float float_data[6];
    int int_data[6];
} DataToSave;								//�����Ҫ�������ݵĽṹ��


extern DataToSave data_to_save ;//�����д�����ݺ�Ļ���ṹ��
extern DataToSave data_read ;		//����Ƕ�ȡ���ݺ󱣴�Ļ���ṹ��


void my_flash_write(void);
void my_flash_read(void);



#endif
