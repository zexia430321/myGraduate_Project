#include<map>
#include<set>
#include<algorithm>
#include<fstream>
#include<iostream>
#include <cstring>
#include<cmath>
#include<sstream>
//********************************************************************************************************	 	   
//列哈达玛变换
void wht(int **&init,int **&dest,int **&tran,int time,ofstream &fout1)//列和每一哈达玛行相乘 取结果最大 
{
//init：原测试集 ；dest:残分量集 ;tran: 主分量集 
	for(j=0;j<n;j++)//对每一竖排进行矩阵操作 找出最相似的哈达玛行 
   	{	
	   max0[j]=0; g0[j]=0;maxm0=0;
	   for(i=0;i<h;i++)//哈达码i行
      {	
	   sum0[i]=0; 
	   for(k=0;k<m;k++)// 哈达码每一行i [i][0-m-1] k<m 
	{	
	   if(init[k][j]!=2)
       sum0[i]+=((init[k][j]^tran[i][k]^1)-(init[k][j]^tran[i][k]));//the same 0 +1,not 1, -1
	    			}
//对应X 不操作 
	   if(abs(sum0[i])>maxm0) 
	{ 
		maxm0=abs(sum0[i]);max0[j]=i; 
		sum0[i]<0?g0[j]=1:g0[j]=0;//标记负最大0 取反 
		 				}//记录最大值所在哈达码的行 （列） 
		 		}
   	} 
//原位流与主分量进行异或
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
int wht_three(int **&init,int **&dest,int **&init1,int **&tran,int time,ofstream &fout0,ofstream &fout1,ofstream & out_trans,float &daijia)//列和每一哈达玛行相乘 取结果最大 
/*                                    中间变量     变换矩阵    次数     中间输出        结果输出    
wht_three(str,str2,str1,mat,6,fout31,fout32,fout_trans);
一次变换 记录缓存数据（残分量=某些不能变换得到的主分量） 
将每一列 原位流 进行哈达码变换得到的残分量如果可以与 缓存相容  那么 该位流可以由缓存和主分量得到 
+将每一列 原位流 进行哈达码变换得到的残分量如果可以与 缓存只有一个位不同 那么 该位流可以由缓存和主分量+编码一位得到 
更新缓存
对所有缓存进行哈达码变换 然后对其进行编码压缩
 其中 标记每一原位流 0为 缓存=原位流  1为原位流可以通过缓存异或主分量 得到  
 
 返回：缓存更新行数（不能经过哈达码变换得到的行） 
*/
{	
//#define TEST
#ifdef TEST
		ofstream ywl("原位流.txt");
		ofstream zfl("主分量.txt");
		ofstream cfl("残分量.txt");
			int **flz=new int* [m];
			int **flc=new int* [m];
			for(i=0;i<m;i++)
				{	flz[i]=new int [n];
					flc[i]=new int [n];
				} 
#endif
	int *pre=new int [m];//sum11[h],sum10[h];//存储前一列 \记录EFDR 
	int *g=new int [n]; //0表示缓存更换  变换不相容 
	int sumall0n=0,tempi=0,sumall1n=0;
	int wei=0,wei1=0,wei0=0; //记录异或后只有一个1的位置 
	int *sum0n=new int [n];
	int *sum1=new int [h];
	for(i=0;i<m;i++)
		pre[i]=init[i][0];//第一列（位流）保存在里面  保存残分量 
	g[0]=0;
	//vector <pair<int,int>> onetwo; //记录主分量key与vaule之间的关系20160530 
	
	//----------------------------------------------j=0------------哈达码变换相容--------
	for(j=1;j<n;j++)//对每一竖排进行矩阵操作 找出最相似的哈达玛行 
   	{	g[j]=0;	
		  max0[j]=0;
		  g0[j]=0;//取反 
			maxm0=h;  
	  	for(i=0;i<h;i++)//哈达码i行 将原位流与哈达码矩阵进行异或  判断异或后的结果是否与缓存相同 
      	{	sum0[i]=0; sum1[i]=0; //sum11[i]=0;sum10[i]=0;
	    		for(k=0;k<m;k++)// 哈达码每一行i [i][0-m-1] k<m   
	    			{		   
							if(init[k][j]!=2&&pre[k]!=2)//相同为 0^0^1=1  0^0=0  1-0=1； 不同 0^1^1=0  0^1=1   0-1=-1   
								{	sum0[i]+=init[k][j]^tran[i][k]^pre[k];//不同的个数 
								 	sum1[i]+=init[k][j]^tran[i][k]^pre[k]^1;//不同的个数 
								 	if(init[k][j]^tran[i][k]^pre[k])//记录1的位置 
								 		wei0=k;
									if(init[k][j]^tran[i][k]^pre[k]^1)
								 		wei1=k;
							  }	
	    			}
          //对应X 不操作  
	      	if(sum0[i]<maxm0||sum1[i]<maxm0) 
			 			{ if(sum0[i]<=sum1[i])
			 					{	maxm0=sum0[i];
								 	g0[j]=0;
								 	wei=wei0; //记录变化的位位置 
								}
							else
								{	maxm0=sum1[i]; 
									g0[j]=1;
									wei=wei1; //记录变化的位位置 
								}
						 max0[j]=i;
		 				}//记录最大值所在哈达码的行 （列） 
		   	}
#ifdef TEST	
					cout<<"原位流：  ";for(k=0;k<m;k++)cout<<init[k][j]<<" ";cout<<endl;
#endif	
			sum0n[j]=maxm0;//保存每一列的异或最小和 
			if(maxm0==0)//相容 哈达码行max0[j]  取反g0[j]
				{	g[j]=1;
#ifdef TEST	
					cout<<"主分量:   ";
						for(k=0;k<m;k++)
							{	cout<<(tran[max0[j]][k]^g0[j])<<" ";
								flz[k][j]=(tran[max0[j]][k]^g0[j]);
								//cout<<flz[k][j]<<"V";
							}cout<<endl;
					cout<<"残分量:   ";
						for(k=0;k<m;k++)
							{	if(init[k][j]==2)flc[k][j]=init[k][j],cout<<init[k][j]<<" ";
								else flc[k][j]=(init[k][j]^tran[max0[j]][k]^g0[j]),cout<<(init[k][j]^tran[max0[j]][k]^g0[j])<<" ";
							}cout<<endl;
					cout<<"更新前per=";for(k=0;k<m;k++)cout<<pre[k]<<" "; cout<<endl;					
#endif
					for(k=0;k<m;k++)//相容 紧缩更新缓存 
						{	
							if(init[k][j]!=2) //相容 残分量不是无关位 
								pre[k]=init[k][j]^tran[max0[j]][k]^g0[j];//原位流与主分量进行异或  得到残分量 
						} 
#ifdef TEST
					cout<<"更新后per=";for(k=0;k<m;k++)cout<<pre[k]<<" "; cout<<endl;
					cout<<"位流："<<j<<" 0相容"<<" H="<<max0[j]<<" g="<<g0[j]<<endl;//getchar(); getchar(); 
#endif
					sumall0n++;//
				} 

//#define CODE1 
#ifdef CODE1				 
			else if(maxm0==1)//只有一个1 
				{	g[j]=1; 
#ifdef TEST
					cout<<"主分量:   ";
						for(k=0;k<m;k++)
							{	cout<<(tran[max0[j]][k]^g0[j])<<" ";
								flz[k][j]=(tran[max0[j]][k]^g0[j]);
							}cout<<endl;
					cout<<"残分量:   ";
						for(k=0;k<m;k++)
							{	if(init[k][j]==2)flc[k][j]=init[k][j],cout<<init[k][j]<<" ";
								else flc[k][j]=(init[k][j]^tran[max0[j]][k]^g0[j]),cout<<(init[k][j]^tran[max0[j]][k]^g0[j])<<" ";
							}cout<<endl;
					cout<<"更新前per=";for(k=0;k<m;k++)cout<<pre[k]<<" "; cout<<endl;
					
#endif						
						for(k=0;k<m;k++)//相容 紧缩更新缓存 
						{	if(init[k][j]!=2&&wei!=k) //相容 残分量不是无关位 
								pre[k]=init[k][j]^tran[max0[j]][k]^g0[j];//原位流与主分量进行异或  得到残分量 
						} 
#ifdef TEST
					cout<<"更新后per=";for(k=0;k<m;k++)cout<<pre[k]<<" "; cout<<endl;
					cout<<"位流："<<j<<" 1相容"<<" H="<<max0[j]<<" g="<<g0[j]<<" wei="<<wei<<endl; //getchar(); getchar();
#endif
					sumall1n++;////记录只有一个不同的个数 并记位置 
				}//*/ 
#endif
			else //更新切片 
				{  	//pre[i];//保存切片 
#ifdef TEST
					cout<<"位流："<<j<<" 不相容"<<endl; //getchar(); getchar(); 	
#endif				
					for(i=0;i<m;i++)
						{	init1[i][tempi]=pre[i];
							pre[i]=init[i][j];//第j列（位流）保存在里面  保存残分量 
						}
					tempi++;//缓存更换频率 
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
			{	init1[i][tempi]=pre[i];	}//最后一个pre  [0-m-1][0-tempi] m,tempi+1                      
			//一位表示是否相容n  相容后一位表示是0,1 sumall0n+sumall1n	
#ifdef CODE1	
		daijia=(sumall1n*log2(h)+n+sumall0n+sumall1n)*100.0/(m*n); 	
		cout<<"编码1代价="<<daijia<<endl; 
#else 
		daijia=(n)*100.0/(m*n); //不编码1 
		cout<<"编码0代价="<<daijia<<endl; 	
#endif
#ifdef OUTEN	
		out_trans<<"n="<<n<<"="<<sumall0n<<"+"<<sumall1n<<"+"<<tempi+1<<"="<<sumall0n+sumall1n+tempi+1<<" 代价="<<daijia<<endl;//异或后残分量结果为0X00 的行 
#endif		
		//列减少为 n-sumall0n ;行为 m 
	//原位流与主分量进行异或
	//init1[i][tempi]=pre[i];	}//最后一个pre  [0-m-1][0-tempi] m,tempi+1
	//----------------------------------------------j=0------------哈达码变换--------
	// 原位流 init1[m][tempi+1]  哈达码矩阵H  残分量dest[m][tempi+1]; 哈达码行max0[j] 取反g0[j] 
	//对不相容的 缓存切片 哈达码变换 
	for(j=0;j<tempi+1;j++)
	{	max0[j]=0;
		g0[j]=0;//取反 
		maxm0=0;
		//哈达码变换 
	  for(i=0;i<h;i++)//哈达码i行
     	{	sum0[i]=0; 
	   		for(k=0;k<m;k++)// 哈达码每一行i [i][0-m-1] k<m 
	   			{	if(init1[k][j]!=2)
         		sum0[i]+=((init1[k][j]^tran[i][k]^1)-(init1[k][j]^tran[i][k]));//the same 0 +1,not 1, -1
	   			}
          //对应X 不操作 
	      if(abs(sum0[i])>maxm0) 
			 		{ maxm0=abs(sum0[i]);max0[j]=i; 
			 			sum0[i]<0?g0[j]=1:g0[j]=0;//标记负最大0 取反 
		 			}//记录最大值所在哈达码的行 （列） 
		 	}
		//得到残分量 
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
				{	tempt[i]=i2c[dest[j][i]];//结果  
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
		return tempi+1;//缓存数目 
}

