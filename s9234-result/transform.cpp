#include<map>
#include<set>
#include<algorithm>
#include<fstream>
#include<iostream>
#include <cstring>
#include<cmath>
#include<sstream>
//********************************************************************************************************	 	   
//�й�����任
void wht(int **&init,int **&dest,int **&tran,int time,ofstream &fout1)//�к�ÿһ����������� ȡ������ 
{
//init��ԭ���Լ� ��dest:�з����� ;tran: �������� 
	for(j=0;j<n;j++)//��ÿһ���Ž��о������ �ҳ������ƵĹ������� 
   	{	
	   max0[j]=0; g0[j]=0;maxm0=0;
	   for(i=0;i<h;i++)//������i��
      {	
	   sum0[i]=0; 
	   for(k=0;k<m;k++)// ������ÿһ��i [i][0-m-1] k<m 
	{	
	   if(init[k][j]!=2)
       sum0[i]+=((init[k][j]^tran[i][k]^1)-(init[k][j]^tran[i][k]));//the same 0 +1,not 1, -1
	    			}
//��ӦX ������ 
	   if(abs(sum0[i])>maxm0) 
	{ 
		maxm0=abs(sum0[i]);max0[j]=i; 
		sum0[i]<0?g0[j]=1:g0[j]=0;//��Ǹ����0 ȡ�� 
		 				}//��¼���ֵ���ڹ�������� ���У� 
		 		}
   	} 
//ԭλ�����������������
	for(j=0;j<n;j++)
	{	 
		for(i=0;i<m;i++)
    	{	if(init[i][j]!=2)
	   			{	dest[i][j]=(tran[max0[j]][i]^init[i][j]^g0[j]); 
			 			if(dest[i][j]==1) 
			 				result[time][0]++;
			 			else
							result[time][1]++;
						if(time==1) 
						if(init[i][j]==1) 
						result[0][0]++;
						else 
						result[0][1]++;
    			}
				else
	    		{ 
				dest[i][j]=2;result[time][2]++;
	    			if(time==1) result[0][2]++;
	   			}
     } 
		 }
    data=""; 
		char tempt[n+1]; tempt[n]='\0';
    for(j=0;j<m;j++)
    	{ for(i=0;i<n;i++)
					{	tempt[i]=i2c[dest[j][i]];
					}
//#define OUTEN 
#ifdef OUTEN		
        ofstream fout1("dest.txt");		
         for(j=0;j<m;j++){
         	for(i=0;i<n;i++){
         		fout1<<dest[j][i];	
         	}
         	fout1<<endl;
         }
				
#endif				
				data.append(tempt);
			}
}
void xrx(int **&dest,int time){
ifstream input;
input.open("s9234cfl.txt");
string s;
input>>s;
m=0;
n=s.size();
input.close();
input.open("s9234cfl.txt");
string s1;
//int **dest;
int ch;
ch=4*n;
dest=new int*[ch+1];

for(int i=0;i<ch+1;i++)  
    {dest[i] = new int[ch+1]; 
    }
while(getline(input,s1,'\n'))
{  
   char a1[n];
   strcpy(a1,s1.c_str());
   int b1[n]; 
   for(int j=0;j<n;j++)
     {if(a1[j]=='1') b1[j]=1;
      else if (a1[j]=='0') b1[j]=0;
      else b1[j]=2;
	  dest[m][j]=b1[j];
     }
  if (s1.size()>0 )  
  m++;
} 
input.close();

	
	 data=""; 
	char tempt[n+1]; tempt[n]='\0';
    for(j=0;j<m;j++)
    	{ for(i=0;i<n;i++)
					{	tempt[i]=i2c[dest[j][i]];
					}
						data.append(tempt);
			}
}
int wht_three(int **&init,int **&dest,int **&init1,int **&tran,int time,ofstream &fout0,ofstream &fout1,ofstream & out_trans,float &daijia)//�к�ÿһ����������� ȡ������ 
/*                                    �м����     �任����    ����     �м����        ������    
wht_three(str,str2,str1,mat,6,fout31,fout32,fout_trans);
һ�α任 ��¼�������ݣ��з���=ĳЩ���ܱ任�õ����������� 
��ÿһ�� ԭλ�� ���й�����任�õ��Ĳз������������ ��������  ��ô ��λ�������ɻ�����������õ� 
+��ÿһ�� ԭλ�� ���й�����任�õ��Ĳз������������ ����ֻ��һ��λ��ͬ ��ô ��λ�������ɻ����������+����һλ�õ� 
���»���
�����л�����й�����任 Ȼ�������б���ѹ��
 ���� ���ÿһԭλ�� 0Ϊ ����=ԭλ��  1Ϊԭλ������ͨ��������������� �õ�  
 
 ���أ�����������������ܾ���������任�õ����У� 
*/
{	
//#define TEST
#ifdef TEST
		ofstream ywl("ԭλ��.txt");
		ofstream zfl("������.txt");
		ofstream cfl("�з���.txt");
			int **flz=new int* [m];
			int **flc=new int* [m];
			for(i=0;i<m;i++)
				{	flz[i]=new int [n];
					flc[i]=new int [n];
				} 
#endif
	int *pre=new int [m];//sum11[h],sum10[h];//�洢ǰһ�� \��¼EFDR 
	int *g=new int [n]; //0��ʾ�������  �任������ 
	int sumall0n=0,tempi=0,sumall1n=0;
	int wei=0,wei1=0,wei0=0; //��¼����ֻ��һ��1��λ�� 
	int *sum0n=new int [n];
	int *sum1=new int [h];
	for(i=0;i<m;i++)
		pre[i]=init[i][0];//��һ�У�λ��������������  ����з��� 
	g[0]=0;
	//vector <pair<int,int>> onetwo; //��¼������key��vaule֮��Ĺ�ϵ20160530 
	
	//----------------------------------------------j=0------------������任����--------
	for(j=1;j<n;j++)//��ÿһ���Ž��о������ �ҳ������ƵĹ������� 
   	{	g[j]=0;	
		  max0[j]=0;
		  g0[j]=0;//ȡ�� 
			maxm0=h;  
	  	for(i=0;i<h;i++)//������i�� ��ԭλ������������������  �ж�����Ľ���Ƿ��뻺����ͬ 
      	{	sum0[i]=0; sum1[i]=0; //sum11[i]=0;sum10[i]=0;
	    		for(k=0;k<m;k++)// ������ÿһ��i [i][0-m-1] k<m   
	    			{		   
							if(init[k][j]!=2&&pre[k]!=2)//��ͬΪ 0^0^1=1  0^0=0  1-0=1�� ��ͬ 0^1^1=0  0^1=1   0-1=-1   
								{	sum0[i]+=init[k][j]^tran[i][k]^pre[k];//��ͬ�ĸ��� 
								 	sum1[i]+=init[k][j]^tran[i][k]^pre[k]^1;//��ͬ�ĸ��� 
								 	if(init[k][j]^tran[i][k]^pre[k])//��¼1��λ�� 
								 		wei0=k;
									if(init[k][j]^tran[i][k]^pre[k]^1)
								 		wei1=k;
							  }	
	    			}
          //��ӦX ������  
	      	if(sum0[i]<maxm0||sum1[i]<maxm0) 
			 			{ if(sum0[i]<=sum1[i])
			 					{	maxm0=sum0[i];
								 	g0[j]=0;
								 	wei=wei0; //��¼�仯��λλ�� 
								}
							else
								{	maxm0=sum1[i]; 
									g0[j]=1;
									wei=wei1; //��¼�仯��λλ�� 
								}
						 max0[j]=i;
		 				}//��¼���ֵ���ڹ�������� ���У� 
		   	}
#ifdef TEST	
					cout<<"ԭλ����  ";for(k=0;k<m;k++)cout<<init[k][j]<<" ";cout<<endl;
#endif	
			sum0n[j]=maxm0;//����ÿһ�е������С�� 
			if(maxm0==0)//���� ��������max0[j]  ȡ��g0[j]
				{	g[j]=1;
#ifdef TEST	
					cout<<"������:   ";
						for(k=0;k<m;k++)
							{	cout<<(tran[max0[j]][k]^g0[j])<<" ";
								flz[k][j]=(tran[max0[j]][k]^g0[j]);
								//cout<<flz[k][j]<<"V";
							}cout<<endl;
					cout<<"�з���:   ";
						for(k=0;k<m;k++)
							{	if(init[k][j]==2)flc[k][j]=init[k][j],cout<<init[k][j]<<" ";
								else flc[k][j]=(init[k][j]^tran[max0[j]][k]^g0[j]),cout<<(init[k][j]^tran[max0[j]][k]^g0[j])<<" ";
							}cout<<endl;
					cout<<"����ǰper=";for(k=0;k<m;k++)cout<<pre[k]<<" "; cout<<endl;					
#endif
					for(k=0;k<m;k++)//���� �������»��� 
						{	
							if(init[k][j]!=2) //���� �з��������޹�λ 
								pre[k]=init[k][j]^tran[max0[j]][k]^g0[j];//ԭλ�����������������  �õ��з��� 
						} 
#ifdef TEST
					cout<<"���º�per=";for(k=0;k<m;k++)cout<<pre[k]<<" "; cout<<endl;
					cout<<"λ����"<<j<<" 0����"<<" H="<<max0[j]<<" g="<<g0[j]<<endl;//getchar(); getchar(); 
#endif
					sumall0n++;//
				} 

//#define CODE1 
#ifdef CODE1				 
			else if(maxm0==1)//ֻ��һ��1 
				{	g[j]=1; 
#ifdef TEST
					cout<<"������:   ";
						for(k=0;k<m;k++)
							{	cout<<(tran[max0[j]][k]^g0[j])<<" ";
								flz[k][j]=(tran[max0[j]][k]^g0[j]);
							}cout<<endl;
					cout<<"�з���:   ";
						for(k=0;k<m;k++)
							{	if(init[k][j]==2)flc[k][j]=init[k][j],cout<<init[k][j]<<" ";
								else flc[k][j]=(init[k][j]^tran[max0[j]][k]^g0[j]),cout<<(init[k][j]^tran[max0[j]][k]^g0[j])<<" ";
							}cout<<endl;
					cout<<"����ǰper=";for(k=0;k<m;k++)cout<<pre[k]<<" "; cout<<endl;
					
#endif						
						for(k=0;k<m;k++)//���� �������»��� 
						{	if(init[k][j]!=2&&wei!=k) //���� �з��������޹�λ 
								pre[k]=init[k][j]^tran[max0[j]][k]^g0[j];//ԭλ�����������������  �õ��з��� 
						} 
#ifdef TEST
					cout<<"���º�per=";for(k=0;k<m;k++)cout<<pre[k]<<" "; cout<<endl;
					cout<<"λ����"<<j<<" 1����"<<" H="<<max0[j]<<" g="<<g0[j]<<" wei="<<wei<<endl; //getchar(); getchar();
#endif
					sumall1n++;////��¼ֻ��һ����ͬ�ĸ��� ����λ�� 
				}//*/ 
#endif
			else //������Ƭ 
				{  	//pre[i];//������Ƭ 
#ifdef TEST
					cout<<"λ����"<<j<<" ������"<<endl; //getchar(); getchar(); 	
#endif				
					for(i=0;i<m;i++)
						{	init1[i][tempi]=pre[i];
							pre[i]=init[i][j];//��j�У�λ��������������  ����з��� 
						}
					tempi++;//�������Ƶ�� 
				} 		
#ifdef OUTEN	
				out_trans<<maxm0<<" ";
#endif
		}//j end 
		
#ifdef TEST
	for(j=0;j<m;j++)
		{
			for(i=0;i<n;i++)
				{	if(init[j][i]==2)
						ywl<<'X'<<" ";
					else
						ywl<<init[j][i]<<" ";
						
					zfl<<flz[j][i]<<" "; 
					if(flc[j][i]==2)
						cfl<<'X'<<" ";
					else
						cfl<<flc[j][i]<<" "; 
				} 
				ywl<<endl;
				zfl<<endl;
				cfl<<endl;
		}
#endif
#ifdef OUTEN	
		out_trans<<endl;
#endif
		for(i=0;i<m;i++)
			{	init1[i][tempi]=pre[i];	}//���һ��pre  [0-m-1][0-tempi] m,tempi+1                      
			//һλ��ʾ�Ƿ�����n  ���ݺ�һλ��ʾ��0,1 sumall0n+sumall1n	
#ifdef CODE1	
		daijia=(sumall1n*log2(h)+n+sumall0n+sumall1n)*100.0/(m*n); 	
		cout<<"����1����="<<daijia<<endl; 
#else 
		daijia=(n)*100.0/(m*n); //������1 
		cout<<"����0����="<<daijia<<endl; 	
#endif
#ifdef OUTEN	
		out_trans<<"n="<<n<<"="<<sumall0n<<"+"<<sumall1n<<"+"<<tempi+1<<"="<<sumall0n+sumall1n+tempi+1<<" ����="<<daijia<<endl;//����з������Ϊ0X00 ���� 
#endif		
		//�м���Ϊ n-sumall0n ;��Ϊ m 
	//ԭλ�����������������
	//init1[i][tempi]=pre[i];	}//���һ��pre  [0-m-1][0-tempi] m,tempi+1
	//----------------------------------------------j=0------------������任--------
	// ԭλ�� init1[m][tempi+1]  ���������H  �з���dest[m][tempi+1]; ��������max0[j] ȡ��g0[j] 
	//�Բ����ݵ� ������Ƭ ������任 
	for(j=0;j<tempi+1;j++)
	{	max0[j]=0;
		g0[j]=0;//ȡ�� 
		maxm0=0;
		//������任 
	  for(i=0;i<h;i++)//������i��
     	{	sum0[i]=0; 
	   		for(k=0;k<m;k++)// ������ÿһ��i [i][0-m-1] k<m 
	   			{	if(init1[k][j]!=2)
         		sum0[i]+=((init1[k][j]^tran[i][k]^1)-(init1[k][j]^tran[i][k]));//the same 0 +1,not 1, -1
	   			}
          //��ӦX ������ 
	      if(abs(sum0[i])>maxm0) 
			 		{ maxm0=abs(sum0[i]);max0[j]=i; 
			 			sum0[i]<0?g0[j]=1:g0[j]=0;//��Ǹ����0 ȡ�� 
		 			}//��¼���ֵ���ڹ�������� ���У� 
		 	}
		//�õ��з��� 
		for(i=0;i<m;i++)//i<m
    	{	if(init1[i][j]!=2)
	   			{	dest[i][j]=(tran[max0[j]][i]^init1[i][j]^g0[j]); 
			 			if(dest[i][j]==1) 
			 				result[time][0]++;
			 			else
							result[time][1]++;
				  		if(time==1) 
						if(init1[i][j]==1) result[0][0]++;
						else result[0][1]++;
    			}
				else//str[i][j]=='X' 
	    		{ dest[i][j]=2;result[time][2]++;
	    			if(time==1) result[0][2]++;
	   			}
     } 
	}
	
#ifdef OUTEN	
	out_trans<<endl;
#endif
  data=""; //n=tempi+1;
	char tempt[tempi+1+1]; tempt[tempi+1]='\0';
  for(j=0;j<m;j++)
  	{ for(i=0;i<tempi+1;i++)
				{	tempt[i]=i2c[dest[j][i]];//���  
				}
#ifdef OUTEN	
			fout1<<tempt<<endl;
#endif	
			data.append(tempt);
		}
		
  for(j=0;j<m;j++)
  	{ for(i=0;i<tempi+1;i++)
				{	tempt[i]=i2c[init1[j][i]];
				}
#ifdef OUTEN	
			fout0<<tempt<<endl;
#endif
		}
		return tempi+1;//������Ŀ 
}

