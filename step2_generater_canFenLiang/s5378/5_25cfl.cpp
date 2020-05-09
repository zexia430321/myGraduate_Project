#include<iostream>
#include <fstream>
#include <cstring>
#include<cmath>
#include<vector>
#include<sstream>//基于字符串的流
#include <stdlib.h> 
//#include"globalVal_127.h"
//#include"globalVal-511.h"
//#include"globalVal-1023.h"
#include"globalVal-2047.h"
#include <time.h>
#include<windows.h>
using namespace std;

//const int N = 9;
//const int N = 10;
const int N = 6;

int zfl[1000][2000];//主分量 
int cfl[1000][2000];//残分量
int jxlzh[300][4100];//用来存放7列进行异或后得到的127列 
int jxlzh2[300][4100];//用来存放基向量组合后再取反的
int jxlzh3[300][4100];


int main(){
//一开始就确定电路名	
string fname;
cout<<"请输入生成的基向量文件名： ";
cin>>fname;
cout<<endl;

ifstream input;
input.open(fname+".vec");
string str;
input>>str;
int m=0;
//n为数据集的列数 
int n=str.size();
input.close();
input.open(fname+".vec");
string str1;
int **test,**test1,**testy,**testy1;
int ch;
int k,i,j;
ch=4*n;
cout<<"n = "<<n<<endl;

test=new int*[ch+1];
test1=new int*[ch+1];
testy=new int*[ch+1];
testy1=new int*[ch+1];
for(i=0;i<ch+1;i++)  
    {test[i] = new int[ch+1]; 
    test1[i] = new int[ch+1];
    testy[i] = new int[ch+1];
    testy1[i] = new int[ch+1];
    }
    
    //一行行读取并且将每一行的值读为一列放在test数组中并将无关位设置为5 
while(getline(input,str1,'\n'))
{  
   char a[n];
   strcpy(a,str1.c_str());
   int b[n]; 
   for(int j=0;j<n;j++)
     {if(a[j]=='1') b[j]=1;
      else if (a[j]=='0') b[j]=0;
      else b[j]=5;
	  test[m][j]=b[j];
     }
 //for(int j=0;j<n;j++)
   //cout<<test[m][j];
 if (str1.size()>0 )  
  m++;
} 
input.close();

//test1、testy、testy1内容目前与test一毛一样 
for(int i=0;i<m;i++){
	for(int j=0;j<n;j++){
		test1[i][j]=test[i][j];
		testy[i][j]=test[i][j];
		testy1[i][j]=test[i][j];
	}
}
//for(int i = 0;i < 10; i++){
//	for(int j = 0; j < n; j++){
//		cout<<test[i][j];
//	}
//	cout<<endl;
//} 

cout<<"电路的大小：行m="<<m<<"    "<<"列n="<<n<<endl;//输出电路的大小 

void getSubset(int list[],bool v[],int a,int b);

//int N;    //表示基向量需要的列数 
//N=ceil(log(m)/log(2));
//N=10; 
cout<<"主分量集中的基向量需要"<<N<<"列"<<endl; 
int jxl[m][N];//用来存放基向量 
int p,q;  //和i,j一样 
int column=0;
int max;
int N1=0;

//要加入读kmeans的文件 (为了兼容就是不需要每次改变读取不同的文件名)
	ifstream infile;
	infile.open(fname,ios::in);
	if(!infile){
		cout<<"不能打开输入的文件"<<fname<<endl;
		return 0;
	}
	int count=0;
	//将文件的每一行当做一个string放入vString中 
	vector<string> vString;
	string line;
	while(getline(infile, line)){
		vString.push_back(line);
	}
	
	for(int i = 0; i < vString.size(); i++){
		string curStr = vString[i];
		for(int j = 0; j < curStr.length(); j++){
			jxl[i][j] = curStr[j]-'0';
		}
	} 
	
//	for(int i = 0; i < vString.size(); i++){
//		
//		for(int j = 0; j < N; j++){
//			cout<<jxl[i][j];
//		}
//		cout<<endl;
//	}

cout<<"N="<<N<<endl;
int li[N];
bool v[N];
for(int i=0;i<N;i++){
	 v[i]=false;
     li[i]=i;
	
} 
HANG=0;
LIE=0;
   lieColumn[HANG]=0;
    getSubset(li,v,0,N);  //得到基向量的127种组合形式
	//将这127种组合形式一一进行异或 
	
cout<<"HANG="<<HANG<<endl;

//int jxlzh[m][HANG-1];//用来存放7列进行异或后得到的127列 
//int jxlzh2[m][2*(HANG-1)];//用来存放基向量组合后再取反的
//int jxlzh3[m][2*(HANG-1)];

 
int count0,count1;//用来记录每一行中0,1的个数 
for(i=0;i<HANG-1;i++){
	if(lieColumn[i]==1){
		for(j=0;j<m;j++){
			jxlzh[j][i]=jxl[j][zh[i][0]];
		}	
	}
	else{
		for(q=0;q<m;q++){
			count0=count1=0;
			for(p=0;p<lieColumn[i];p++){
				if(jxl[q][zh[i][p]]==1)
				count1++;
				else 
				count0++;
			}
			if(count1%2==0)
			jxlzh[q][i]=0;
			else 
			jxlzh[q][i]=1;
		}
	}
}

//将基向量组合扩大一倍再进去取反 
for(i=0;i<m;i++){
	for(j=0;j<HANG-1;j++){
		jxlzh2[i][j]=jxlzh[i][j];
		 if(jxlzh[i][j]==1)
		jxlzh2[i][j+(HANG-1)]=0;
		else
		jxlzh2[i][j+(HANG-1)]=1;
	}
}

for(i=0;i<m;i++){
	for(j=0;j<2*(HANG-1);j++){
		if(jxlzh2[i][j]==0)
		jxlzh3[i][j]=-1;
		else 
		jxlzh3[i][j]=1;
	}
}

//把基向量的组合形式2与原测试集比较，得到主分量集 

//将主分量和残分量定义在函数外面 

//int xrlie[n];//用来记录原测试集中哪些列与基向量组合2中的列相容
//int xrcolumn=0;//记录相容的有多少列 
//p=0;
for(i=0;i<m;i++){
	for(j=0;j<n;j++){
			if(testy1[i][j]==0)
		testy1[i][j]=-1;
		else if(testy1[i][j]==5)
		testy1[i][j]=0;
		else
		testy1[i][j]=1;
	}
}

//如下将testy1当做原测试集 做了预处理0当做-1 5当做0 1还是1 
j=-1;
l1:j++;
for(;j<n;){
	for(k=0;k<2*(HANG-1);k++){
		for(i=0;i<m;i++){
			if(testy[i][j]==5 || testy[i][j]==jxlzh2[i][k]){
					if(i==(m-1)){
							for(int t=0;t<m;t++)
						zfl[t][j]=jxlzh2[t][k];							
					cout<<k<<" ";
					goto l1;
				}
			}
			else
			break;
		}
		
	}
	//没有相容的 
	
	int sum[2*(HANG-1)];
	for(p=0;p<2*(HANG-1);p++){//lie
	   sum[p]=0;
		for(q=0;q<m;q++){
			sum[p]=sum[p]+testy1[q][j]*jxlzh3[q][p];
		}
	}
	max=0;
	int c;//记录最大值多对应基向量组合3中的列 
	for(i=0;i<2*(HANG-1);i++){
		if(sum[i]>max){
			max=sum[i];
			c=i;
		}
	}
	for(i=0;i<m;i++){
			zfl[i][j]=jxlzh2[i][c];
	}
	//cout<<c<<"-";
//cout<<max<<" ";
	j++;	
}


for(i=0;i<m;i++){
	for(j=0;j<n;j++){
	 if(testy[i][j]==zfl[i][j]){
			cfl[i][j]=0;
			//cout<<cfl[i][j]<<" ";
		}
		else if(testy[i][j]==5)
		cfl[i][j]=0;
		else 
		cfl[i][j]=1;
	//	cout<<cfl[i][j]<<" ";
	}
//	cout<<endl;
}
ofstream fout(fname+".txt");

for(int i=0;i<m;i++)
 {for(int j=0;j<n;j++)
 { 
   fout<<test[i][j];
 }
  fout<<endl;
}
fout << flush;
fout.close();
ofstream fout3(fname+"-jxl.txt");
for(i=0;i<m;i++){
 for(j=0;j<N;j++){
 		fout3<<jxl[i][j];
 }
 	fout3<<endl;
 }
 fout3<<endl;
fout3<< flush;
 fout3.close();
 ofstream fout4(fname+"zh.txt");
 for(i=0;i<HANG-1;i++){
 	fout4<<lieColumn[i]<<" ";
 	if((i+1)%40==0)
 	fout4<<endl;
 }
 
 fout4<<endl<<endl;
for(int i=0;i<HANG-1;i++)
 {for(int j=0;j<lieColumn[i];j++)
 { 
   fout4<<zh[i][j]<<" ";
 }
  fout4<<endl;
}
fout4 << flush;
fout4.close(); 
 ofstream fout5(fname+"jxlzh.txt");
 for(i=0;i<m;i++){
 	for(j=0;j<HANG-1;j++){
 		fout5<<jxlzh[i][j];
 	}
 	fout5<<endl;
 }
fout5 << flush;
fout5.close(); 

ofstream fout6(fname+"jxlzh3.txt");
 for(i=0;i<m;i++){
 	for(j=0;j<2*(HANG-1);j++){
 		fout6<<jxlzh3[i][j];
 	}
 	fout6<<endl;
 }
fout6<< flush;
fout6.close();
ofstream fout8(fname+"cfl.txt");
for(int i=0;i<m;i++)
 {
 for(int j=0;j<n;j++)
 { 
   fout8<<cfl[i][j];
 }
  fout8<<endl;
}
fout8 << flush;
fout8.close();
ofstream fout9(fname+"jxlzh2.txt");
 for(i=0;i<m;i++){
 	for(j=0;j<2*(HANG-1);j++){
 		fout9<<jxlzh2[i][j];
 	}
 	fout9<<endl;
 }
fout9<< flush;
fout9.close(); 

return 0;
}

void getSubset(int list[],bool v[],int a,int b){  
  
    if(a == b){  
        for(int i = 0; i < b; i++){  
            if(v[i])  {
            	//cout<<list[i]<<"  "; 
			zh[HANG][LIE]=list[i];
			lieColumn[HANG]++;
			LIE++;
            } 
            
        }  
        HANG++;
        lieColumn[HANG]=0;
        LIE=0;
        //cout<<endl; 
        return;  
    }  
    v[a] = true;  
    getSubset(list,v,a+1,b);  
    v[a] = false;  
    getSubset(list,v,a+1,b);  
 
} 
