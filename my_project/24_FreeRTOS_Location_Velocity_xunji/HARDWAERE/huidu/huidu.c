#include "huidu.h"

int sensor[8];//�Ҷ�ʶ������
int error=0;//Ѳ��ƫ��
int jiansu=0;//С�������ٶȵı�־������jiansuԽСʱ�������ٶ�Խ��


void read_sensor(void)
{
		  /*��λ�ô�����˳�����ҵĴ��������ص������ź����δ�������sensor[0��8]��*/
			sensor[0]=L4;//����Ĵ�����
			sensor[1]=L3;
			sensor[2]=L2;
			sensor[3]=L1;
			sensor[4]=R1;
			sensor[5]=R2;
			sensor[6]=R3;
			sensor[7]=R4;//���ҵĴ�����
	
			if((sensor[0]==1&&sensor[1]==1&&sensor[2]==1)&&(sensor[3]==0&&sensor[4]==0)&&(sensor[5]==1&&sensor[6]==1&&sensor[7]==1))
			{	/*ʶ�𵽺������м�*/	
				error=0;jiansu=0;
				Stop_flag=0;
 			}
//			else if((sensor[0]==0&&sensor[1]==0&&sensor[2]==0)&&(sensor[3]==0&&sensor[4]==0)&&(sensor[5]==0&&sensor[6]==0&&sensor[7]==0))
//			{	/*ʶ��ȫ��*/	
//				Stop_flag=1;
// 			}
			else if((sensor[0]==1&&sensor[1]==1&&sensor[2]==1)&&(sensor[3]==0&&sensor[4]==1)&&(sensor[5]==1&&sensor[6]==1&&sensor[7]==1))
			{/*С��λ���е�ƫ��*/
				error=-1;jiansu=1;
			}
			else if((sensor[0]==1&&sensor[1]==1&&sensor[2]==1)&&(sensor[3]==1&&sensor[4]==0)&&(sensor[5]==1&&sensor[6]==1&&sensor[7]==1))
			{/*С��λ���е�ƫ��*/
				error=1;jiansu=1;
			}

			else if((sensor[0]==1&&sensor[1]==1&&sensor[2]==0)&&(sensor[3]==1&&sensor[4]==1)&&(sensor[5]==1&&sensor[6]==1&&sensor[7]==1))
			{/*С��λ��ƫ��*/
				error=-3;jiansu=2;
			}
			
			else if((sensor[0]==1&&sensor[1]==1&&sensor[2]==1)&&(sensor[3]==1&&sensor[4]==1)&&(sensor[5]==0&&sensor[6]==1&&sensor[7]==1))
			{/*С��λ��ƫ��*/
				error=3;jiansu=2;
			}		
			else if((sensor[0]==1&&sensor[1]==0&&sensor[2]==1)&&(sensor[3]==1&&sensor[4]==1)&&(sensor[5]==1&&sensor[6]==1&&sensor[7]==1))
			{/*С��λ��ƫ����*/
				error=-5;jiansu=3;
			}
			
			else if((sensor[0]==1&&sensor[1]==1&&sensor[2]==1)&&(sensor[3]==1&&sensor[4]==1)&&(sensor[5]==1&&sensor[6]==0&&sensor[7]==1))
			{/*С��λ��ƫ����*/
				error=5;jiansu=3;
			}
						
			else if((sensor[0]==0&&sensor[1]==1&&sensor[2]==1)&&(sensor[3]==1&&sensor[4]==1)&&(sensor[5]==1&&sensor[6]==1&&sensor[7]==1))
			{/*С��λ��ƫ����*/
				error=-7;jiansu=5;
			}
			
			else if((sensor[0]==1&&sensor[1]==1&&sensor[2]==1)&&(sensor[3]==1&&sensor[4]==1)&&(sensor[5]==1&&sensor[6]==1 &&sensor[7]==0))
			{/*С��λ��ƫ����*/
				error=7;jiansu=5;
			}

}

