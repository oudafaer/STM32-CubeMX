#include "key.h"

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
uint8_t KEY_Scan(void)
{
	static uint8_t key_up=1; //�������ɿ���־
	if(key_up && (K0==0 || K1==0 ))
	{
		HAL_Delay(10);//(10); //ȥ����
		key_up=0;
		if(K0==0)  return 1;
		else if(K1==0) return 2;
	}
	else if(K0==1 &&  K1==1 ) key_up=1; 
	return 0; // �ް�������
	
}
