#include "mpu6050.h"
#include "main.h"
#include "i2c.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

float pitch, roll, yaw;                                  //欧拉角


//初始化MPU6050
//串口提示不需要可以注释了
void mpu6050_init(void)
{
//  printf("-- Mpu6050 Project Start -- \r\n");
  uint8_t recv = 0x00;
  HAL_I2C_Mem_Read(&hi2c1, (0x68 << 1), 0x75, I2C_MEMADD_SIZE_8BIT, &recv, 1, 0xfff);
  if (recv == 0x68)
  {
//    printf("mpu6050 ID Read: OK at 0x68\r\n");
  }
  else
  {
//    printf("Err mpu id:0x%x\r\n", recv);
  }
  /*
   *DMP初始化
   */
  while (mpu_dmp_init())
  {
    HAL_Delay(200);
  }	
}


//初始化MPU
//返回值:0,成功
//    其他,错误代码
uint8_t MPU_Init(void)
{
	uint8_t res;
	MPU_Write_Byte(MPU_ADDR, MPU_PWR_MGMT1_REG, 0X80); //复位MPU6050
	HAL_Delay(100);									   //延时100ms
	MPU_Write_Byte(MPU_ADDR, MPU_PWR_MGMT1_REG, 0X00); //唤醒MPU6050
	MPU_Set_Gyro_Fsr(3);							   //陀螺仪传感器,±2000dps
	MPU_Set_Accel_Fsr(0);							   //加速度传感器,±2g
	MPU_Set_Rate(50);								   //设置采样率50Hz
	MPU_Write_Byte(MPU_ADDR, MPU_INT_EN_REG, 0X00);	   //关闭所有中断
	MPU_Write_Byte(MPU_ADDR, MPU_USER_CTRL_REG, 0X00); //I2C主模式关闭
	MPU_Write_Byte(MPU_ADDR, MPU_FIFO_EN_REG, 0X00);   //关闭FIFO
	MPU_Write_Byte(MPU_ADDR, MPU_INTBP_CFG_REG, 0X80); //INT引脚低电平有效
	res = MPU_Read_Byte(MPU_ADDR, MPU_DEVICE_ID_REG);
	if (res == MPU_ADDR) //器件ID正确
	{
		MPU_Write_Byte(MPU_ADDR, MPU_PWR_MGMT1_REG, 0X01); //设置CLKSEL,PLL X轴为参考
		MPU_Write_Byte(MPU_ADDR, MPU_PWR_MGMT2_REG, 0X00); //加速度与陀螺仪都工作
		MPU_Set_Rate(50);								   //设置采样率为50Hz
	}
	else
		return 1;
	return 0;
}
//设置MPU6050陀螺仪传感器满量程范围
//fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
//返回值:0,设置成功
//    其他,设置失败
uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU_ADDR, MPU_GYRO_CFG_REG, fsr << 3); //设置陀螺仪满量程范围
}
//设置MPU6050加速度传感器满量程范围
//fsr:0,±2g;1,±4g;2,±8g;3,±16g
//返回值:0,设置成功
//    其他,设置失败
uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
	return MPU_Write_Byte(MPU_ADDR, MPU_ACCEL_CFG_REG, fsr << 3); //设置加速度传感器满量程范围
}
//设置MPU6050的数字低通滤波器
//lpf:数字低通滤波频率(Hz)
//返回值:0,设置成功
//    其他,设置失败
uint8_t MPU_Set_LPF(u16 lpf)
{
	uint8_t data = 0;
	if (lpf >= 188)
		data = 1;
	else if (lpf >= 98)
		data = 2;
	else if (lpf >= 42)
		data = 3;
	else if (lpf >= 20)
		data = 4;
	else if (lpf >= 10)
		data = 5;
	else
		data = 6;
	return MPU_Write_Byte(MPU_ADDR, MPU_CFG_REG, data); //设置数字低通滤波器
}
//设置MPU6050的采样率(假定Fs=1KHz)
//rate:4~1000(Hz)
//返回值:0,设置成功
//    其他,设置失败
uint8_t MPU_Set_Rate(u16 rate)
{
	uint8_t data;
	if (rate > 1000)
		rate = 1000;
	if (rate < 4)
		rate = 4;
	data = 1000 / rate - 1;
	data = MPU_Write_Byte(MPU_ADDR, MPU_SAMPLE_RATE_REG, data); //设置数字低通滤波器
	return MPU_Set_LPF(rate / 2);								//自动设置LPF为采样率的一半
}

//得到温度值
//返回值:温度值(扩大了100倍)
short MPU_Get_Temperature(void)
{
	uint8_t buf[2];
	short raw;
	float temp;
	MPU_Read_Len(MPU_ADDR, MPU_TEMP_OUTH_REG, 2, buf);
	raw = ((u16)buf[0] << 8) | buf[1];
	temp = 36.53 + ((double)raw) / 340;
	return temp * 100;
	;
}
//得到陀螺仪值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
uint8_t MPU_Get_Gyroscope(short *gx, short *gy, short *gz)
{
	uint8_t buf[6], res;
	res = MPU_Read_Len(MPU_ADDR, MPU_GYRO_XOUTH_REG, 6, buf);
	if (res == 0)
	{
		*gx = ((u16)buf[0] << 8) | buf[1];
		*gy = ((u16)buf[2] << 8) | buf[3];
		*gz = ((u16)buf[4] << 8) | buf[5];
	}
	return res;
	;
}
//得到加速度值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
uint8_t MPU_Get_Accelerometer(short *ax, short *ay, short *az)
{
	uint8_t buf[6], res;
	res = MPU_Read_Len(MPU_ADDR, MPU_ACCEL_XOUTH_REG, 6, buf);
	if (res == 0)
	{
		*ax = ((u16)buf[0] << 8) | buf[1];
		*ay = ((u16)buf[2] << 8) | buf[3];
		*az = ((u16)buf[4] << 8) | buf[5];
	}
	return res;
	;
}
//IIC连续写
//addr:器件地址
//reg:寄存器地址
//len:写入长度
//buf:数据区
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Write_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
	uint8_t res;
	res = HAL_I2C_Mem_Write(&hi2c1, (addr << 1), reg, I2C_MEMADD_SIZE_8BIT, buf, len, 0xfff);
	return res;
}

//IIC连续读
//addr:器件地址
//reg:要读取的寄存器地址
//len:要读取的长度
//buf:读取到的数据存储区
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Read_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
	uint8_t res;
	res = HAL_I2C_Mem_Read(&hi2c1, (addr << 1), reg, I2C_MEMADD_SIZE_8BIT, buf, len, 0xfff);
	return res;
}

//IIC写一个字节
//devaddr:器件IIC地址
//reg:寄存器地址
//data:数据
//返回值:0,正常
//    其他,错误代码
uint8_t MPU_Write_Byte(uint8_t addr, uint8_t reg, uint8_t data)
{
	uint8_t res;
	res = HAL_I2C_Mem_Write(&hi2c1, (addr << 1), reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 0xfff);
	return res;
}

//IIC读一个字节
//reg:寄存器地址
//返回值:读到的数据
uint8_t MPU_Read_Byte(uint8_t addr, uint8_t reg)
{
	uint8_t res;
	HAL_I2C_Mem_Read(&hi2c1, (addr << 1), reg, I2C_MEMADD_SIZE_8BIT, &res, 1, 0xfff);
	return res;
}





