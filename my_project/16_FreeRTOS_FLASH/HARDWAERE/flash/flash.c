#include "flash.h"
#include <stdio.h>
#include <string.h>

DataToSave data_to_save ;//这个是要保存的数据
DataToSave data_read ;// 将读取到的数据转换回原始结构体


/*FLASH写入程序*/
void WriteFlash(uint32_t addr,uint32_t *Data,uint32_t L)
{
	uint32_t i=0;
	/* 1/4解锁FLASH*/
	HAL_FLASH_Unlock();
	/* 2/4擦除FLASH*/
	/*初始化FLASH_EraseInitTypeDef*/
	/*擦除方式页擦除FLASH_TYPEERASE_PAGES，块擦除FLASH_TYPEERASE_MASSERASE*/
	/*擦除页数*/
	/*擦除地址*/
	FLASH_EraseInitTypeDef FlashSet;
	FlashSet.TypeErase = FLASH_TYPEERASE_PAGES;
	FlashSet.PageAddress = addr;
	FlashSet.NbPages = 1;
	/*设置PageError，调用擦除函数*/
	uint32_t PageError = 0;
	HAL_FLASHEx_Erase(&FlashSet, &PageError);
	/* 3/4对FLASH烧写*/
	for(i=0;i<L;i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr+4*i, Data[i]);
	}
	/* 4/4锁住FLASH*/
	HAL_FLASH_Lock();
}

void Flash_Read(uint32_t address, uint32_t *data, uint16_t length)
{
    uint16_t i;
    for (i = 0; i < length; i++) {
        data[i] = *(__IO uint32_t *)(address + (i * 4)); // 以字为单位读取Flash
    }
}

/**
  ******************************************************************************
	* @文件名  :   flash写入函数
	* @函数介绍: 将结构体中的数据写入flash中 
 	 * @输入参数: 无
	* @输出参数:   无   
	* @备注:在调用这个函数之前，记得先把要写入的数据放入data_to_save这个结构体中，结构体具体详情见.h中
  *
  *
  ******************************************************************************
  */
void my_flash_write(void)
{
	// 将数据转换为uint32_t数组以便写入Flash
	uint32_t flash_data[sizeof(DataToSave) / sizeof(uint32_t)];
	memcpy(flash_data, &data_to_save, sizeof(DataToSave));

	// 将数据写入Flash
	WriteFlash(FLASH_SAVE_ADDR, flash_data, sizeof(DataToSave) / sizeof(uint32_t));
}


/**
  ******************************************************************************
	* @文件名  : flash读取函数
	* @函数介绍: 将flash中的数据读取后结构体中
 	* @输入参数: 无
	* @输出参数: 无   
	* @备注:在调用这个函数之后，从flash读取的数据放入data_read这个结构体中，结构体具体详情见.h中
  *
  *
  ******************************************************************************
  */
void my_flash_read(void)
{
	
	// 从Flash中读取数据
	uint32_t flash_data_read[sizeof(DataToSave) / sizeof(uint32_t)];
	Flash_Read(FLASH_SAVE_ADDR, flash_data_read, sizeof(DataToSave) / sizeof(uint32_t));
	memcpy(&data_read, flash_data_read, sizeof(DataToSave));
	// 现在，data_read.float_data 和 data_read.int_data 中分别包含从Flash中读取的float和int数据

}
