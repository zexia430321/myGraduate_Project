#ifndef DEFINE_H_
#define DEFINE_H_
#include <string> 
using namespace std;

int n,m,h,i,j,k,num;//其他地方定义
int num_row,h_row;
int **mat; //列 
int **mat_row;//行 由于数组比较大，我们使用动态内存分配 
int **a;
int **b,**b_row;

int maxm0=0;//纪录n列每列的主分量对应的 哈达玛列 
int *max0;
int *sum0;//保存每列对应的 哈达码行 
int *g0;//标记正负（相容、反向相容）
string data;
string name;
double r[10][7];//20160822  7中情况 
int **str; //第n为'\0' 
int **str1; //存一次列变换 第n为'\0'
int **str2; //存二次变换结果 

int result[8][3];//保存0 1 X
int c2i[0xff];
char i2c[0xff];

extern int maxm0;//纪录n列每列的主分量对应的 哈达玛列 
extern int *max0;
extern int *sum0;//保存每列对应的 哈达码行 
extern int *g0;//标记正负（相容、反向相容）

extern string data;//存储数据以编码 
#endif
