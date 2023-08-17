#include "huidu.h"

int sensor[8];//灰度识别数组
int error=0;//巡线偏差
int jiansu=0;//小车基础速度的标志变量，jiansu越小时，基础速度越大


void read_sensor(void)
{
		  /*将位置从最左按顺序到最右的传感器返回的数字信号依次存入数组sensor[0至8]里*/
			sensor[0]=L4;//最左的传感器
			sensor[1]=L3;
			sensor[2]=L2;
			sensor[3]=L1;
			sensor[4]=R1;
			sensor[5]=R2;
			sensor[6]=R3;
			sensor[7]=R4;//最右的传感器
	
			if((sensor[0]==1&&sensor[1]==1&&sensor[2]==1)&&(sensor[3]==0&&sensor[4]==0)&&(sensor[5]==1&&sensor[6]==1&&sensor[7]==1))
			{	/*识别到黑线在中间*/	
				error=0;jiansu=0;
				Stop_flag=0;
 			}
//			else if((sensor[0]==0&&sensor[1]==0&&sensor[2]==0)&&(sensor[3]==0&&sensor[4]==0)&&(sensor[5]==0&&sensor[6]==0&&sensor[7]==0))
//			{	/*识别到全白*/	
//				Stop_flag=1;
// 			}
			else if((sensor[0]==1&&sensor[1]==1&&sensor[2]==1)&&(sensor[3]==0&&sensor[4]==1)&&(sensor[5]==1&&sensor[6]==1&&sensor[7]==1))
			{/*小车位置有点偏右*/
				error=-1;jiansu=1;
			}
			else if((sensor[0]==1&&sensor[1]==1&&sensor[2]==1)&&(sensor[3]==1&&sensor[4]==0)&&(sensor[5]==1&&sensor[6]==1&&sensor[7]==1))
			{/*小车位置有点偏左*/
				error=1;jiansu=1;
			}

			else if((sensor[0]==1&&sensor[1]==1&&sensor[2]==0)&&(sensor[3]==1&&sensor[4]==1)&&(sensor[5]==1&&sensor[6]==1&&sensor[7]==1))
			{/*小车位置偏右*/
				error=-3;jiansu=2;
			}
			
			else if((sensor[0]==1&&sensor[1]==1&&sensor[2]==1)&&(sensor[3]==1&&sensor[4]==1)&&(sensor[5]==0&&sensor[6]==1&&sensor[7]==1))
			{/*小车位置偏左*/
				error=3;jiansu=2;
			}		
			else if((sensor[0]==1&&sensor[1]==0&&sensor[2]==1)&&(sensor[3]==1&&sensor[4]==1)&&(sensor[5]==1&&sensor[6]==1&&sensor[7]==1))
			{/*小车位置偏更右*/
				error=-5;jiansu=3;
			}
			
			else if((sensor[0]==1&&sensor[1]==1&&sensor[2]==1)&&(sensor[3]==1&&sensor[4]==1)&&(sensor[5]==1&&sensor[6]==0&&sensor[7]==1))
			{/*小车位置偏更左*/
				error=5;jiansu=3;
			}
						
			else if((sensor[0]==0&&sensor[1]==1&&sensor[2]==1)&&(sensor[3]==1&&sensor[4]==1)&&(sensor[5]==1&&sensor[6]==1&&sensor[7]==1))
			{/*小车位置偏最右*/
				error=-7;jiansu=5;
			}
			
			else if((sensor[0]==1&&sensor[1]==1&&sensor[2]==1)&&(sensor[3]==1&&sensor[4]==1)&&(sensor[5]==1&&sensor[6]==1 &&sensor[7]==0))
			{/*小车位置偏最左*/
				error=7;jiansu=5;
			}

}

