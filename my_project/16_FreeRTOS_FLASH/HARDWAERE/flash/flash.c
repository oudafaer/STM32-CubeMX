#include "flash.h"
#include <stdio.h>
#include <string.h>

DataToSave data_to_save ;//�����Ҫ���������
DataToSave data_read ;// ����ȡ��������ת����ԭʼ�ṹ��


/*FLASHд�����*/
void WriteFlash(uint32_t addr,uint32_t *Data,uint32_t L)
{
	uint32_t i=0;
	/* 1/4����FLASH*/
	HAL_FLASH_Unlock();
	/* 2/4����FLASH*/
	/*��ʼ��FLASH_EraseInitTypeDef*/
	/*������ʽҳ����FLASH_TYPEERASE_PAGES�������FLASH_TYPEERASE_MASSERASE*/
	/*����ҳ��*/
	/*������ַ*/
	FLASH_EraseInitTypeDef FlashSet;
	FlashSet.TypeErase = FLASH_TYPEERASE_PAGES;
	FlashSet.PageAddress = addr;
	FlashSet.NbPages = 1;
	/*����PageError�����ò�������*/
	uint32_t PageError = 0;
	HAL_FLASHEx_Erase(&FlashSet, &PageError);
	/* 3/4��FLASH��д*/
	for(i=0;i<L;i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr+4*i, Data[i]);
	}
	/* 4/4��סFLASH*/
	HAL_FLASH_Lock();
}

void Flash_Read(uint32_t address, uint32_t *data, uint16_t length)
{
    uint16_t i;
    for (i = 0; i < length; i++) {
        data[i] = *(__IO uint32_t *)(address + (i * 4)); // ����Ϊ��λ��ȡFlash
    }
}

/**
  ******************************************************************************
	* @�ļ���  :   flashд�뺯��
	* @��������: ���ṹ���е�����д��flash�� 
 	 * @�������: ��
	* @�������:   ��   
	* @��ע:�ڵ����������֮ǰ���ǵ��Ȱ�Ҫд������ݷ���data_to_save����ṹ���У��ṹ����������.h��
  *
  *
  ******************************************************************************
  */
void my_flash_write(void)
{
	// ������ת��Ϊuint32_t�����Ա�д��Flash
	uint32_t flash_data[sizeof(DataToSave) / sizeof(uint32_t)];
	memcpy(flash_data, &data_to_save, sizeof(DataToSave));

	// ������д��Flash
	WriteFlash(FLASH_SAVE_ADDR, flash_data, sizeof(DataToSave) / sizeof(uint32_t));
}


/**
  ******************************************************************************
	* @�ļ���  : flash��ȡ����
	* @��������: ��flash�е����ݶ�ȡ��ṹ����
 	* @�������: ��
	* @�������: ��   
	* @��ע:�ڵ����������֮�󣬴�flash��ȡ�����ݷ���data_read����ṹ���У��ṹ����������.h��
  *
  *
  ******************************************************************************
  */
void my_flash_read(void)
{
	
	// ��Flash�ж�ȡ����
	uint32_t flash_data_read[sizeof(DataToSave) / sizeof(uint32_t)];
	Flash_Read(FLASH_SAVE_ADDR, flash_data_read, sizeof(DataToSave) / sizeof(uint32_t));
	memcpy(&data_read, flash_data_read, sizeof(DataToSave));
	// ���ڣ�data_read.float_data �� data_read.int_data �зֱ������Flash�ж�ȡ��float��int����

}
