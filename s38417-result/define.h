#ifndef DEFINE_H_
#define DEFINE_H_
#include <string> 
using namespace std;

int n,m,h,i,j,k,num;//�����ط�����
int num_row,h_row;
int **mat; //�� 
int **mat_row;//�� ��������Ƚϴ�����ʹ�ö�̬�ڴ���� 
int **a;
int **b,**b_row;

int maxm0=0;//��¼n��ÿ�е���������Ӧ�� �������� 
int *max0;
int *sum0;//����ÿ�ж�Ӧ�� �������� 
int *g0;//������������ݡ��������ݣ�
string data;
string name;
double r[10][7];//20160822  7����� 
int **str; //��nΪ'\0' 
int **str1; //��һ���б任 ��nΪ'\0'
int **str2; //����α任��� 

int result[8][3];//����0 1 X
int c2i[0xff];
char i2c[0xff];

extern int maxm0;//��¼n��ÿ�е���������Ӧ�� �������� 
extern int *max0;
extern int *sum0;//����ÿ�ж�Ӧ�� �������� 
extern int *g0;//������������ݡ��������ݣ�

extern string data;//�洢�����Ա��� 
#endif
