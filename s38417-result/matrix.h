#ifndef MATRIX_H_
#define MATRIX_H_

#include<cmath> 
#include<cstring>
#include <time.h> 
#include"define.h"
using namespace std;
//�任���� 
//��������� ����int 
void creath(int **&a,int h)// 1��0 20160323 
{	
	a=new int * [h];
	for(i=0;i<h;i++)
		a[i]=new int [h]; 
  a[0][0]=1;//all 1  
  for(i=2;i<=h;i*=2)
  	for(j=0;j<i/2;j++)
      for(k=0;k<i/2;k++)
       {	a[j][k+i/2]=a[j][k];
        	a[j+i/2][k]=a[j][k]; 
	    		a[j+i/2][k+i/2]=a[j][k]^1;//160323
	   	 }; 
}
//���ɱ仯��Ĺ����� 
void creatnewh(int **&a,int h)// 1��0 201600526
{	int temp;
	a=new int * [h];
	for(i=0;i<h;i++)
		a[i]=new int [h]; 
  a[0][0]=1;//all 1  
  for(i=2;i<=h;i*=2)
  	{for(j=0;j<i/2;j++)
      for(k=0;k<i/2;k++)
       {	a[j][k+i/2]=a[j][k];
        	a[j+i/2][k]=a[j][k]; 
	    		a[j+i/2][k+i/2]=a[j][k]^1;//160323
	    	
	   	 }
			if(i>4)
				{	temp=ceil(log2(i));//�б� log2(n-1)+1;
					for(j=0;j<i/2;j++)
						a[j+i/2][i-temp-1]=a[j+i/2][i-temp-1]^1; 
				}
		} 
}
void creatnewh2(int **&a,int h)// ���ݹ�����������ɸ��ľ���
{	int temp;
	int tempnum=log2(h);
	cout<<" Hello "<<tempnum<<endl;
  for(i=0;i<h;i++)
  	{	temp=i;
			for(j=tempnum-1;j>=0;j--)
       {	a[h-1-i][j]=temp%2;//
       		temp=temp/2;
	   	 }
		} 
}
//���������ɾ��� 
void creatb(int **&a,int **tran,int h)
{	int g=0;
	a=new int * [h];
	for(i=0;i<h;i++)
		a[i]=new int [h];
	for(j=0;j<h;j++)
		a[0][j]=0;//all 0 //20160404 
	for(i=1;i<h;i++)
		for(j=0;j<h;j++)
			{	if(tran[i][j]==1)//����1ȡ��һ��1
					{	if(g==1)
							a[i][j]=1;
						else
							a[i][j]=0;
						g^=1;	
					}
				else a[i][j]=0; 
			}
}
void comb( int ** &init1,int **& init2,int **&dest,int hh)
{	int temp=ceil(log2(hh));
	for(i=0;i<hh;i++)
		for(j=0;j<hh;j++)
			{	if(j>hh-temp-1)//��tempλ ��init2��ͬ 
					dest[i][j]=init2[i][j];
				else
					dest[i][j]=init1[i][j];
			}	
}
//�Ե�0��n-1 1 n-2�� 
void dd(int **&a,int hh)
{	for(i=0;i<hh;i++)
		for(j=0;j<hh/2;j++)
			{	swap(a[i][j],a[i][hh-1-j]);
			}
}
//������� 
void print(int **&aa,int hh,int n) 
{	for(j=0;j<n;j++)
     {
      for(k=0;k<hh;k++)  
       {cout<<aa[j][k]<<" ";
       }
	   cout<<endl;
	 }
}
template<typename T>
void del(T **&aa,int hh)
	{	for(int i=0;i<hh;i++)
			{	delete [] aa[i];
				aa[i]=NULL;
			}
		delete aa;
		aa=NULL;
	} 
#endif
