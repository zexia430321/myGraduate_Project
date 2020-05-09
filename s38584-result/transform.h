#ifndef TRANSFORM_H_
#define TRANSFORM_H_
#include"define.h"
//********************************************************************************************************	 	   
//列哈达玛变换
void wht(int **&init,int **&dest,int **&tran,int time,ofstream &fout1)//列和每一哈达玛行相乘 取结果最大 
int wht_three(int **&init,int **&dest,int **&init1,int **&tran,int time,ofstream &fout0,ofstream &fout1,ofstream & out_trans,float &daijia);
#endif
