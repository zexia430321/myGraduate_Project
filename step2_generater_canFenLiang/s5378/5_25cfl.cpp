#include<iostream>
#include <fstream>
#include <cstring>
#include<cmath>
#include<vector>
#include<sstream>//�����ַ�������
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

int zfl[1000][2000];//������ 
int cfl[1000][2000];//�з���
int jxlzh[300][4100];//�������7�н�������õ���127�� 
int jxlzh2[300][4100];//������Ż�������Ϻ���ȡ����
int jxlzh3[300][4100];


int main(){
//һ��ʼ��ȷ����·��	
string fname;
cout<<"���������ɵĻ������ļ����� ";
cin>>fname;
cout<<endl;

ifstream input;
input.open(fname+".vec");
string str;
input>>str;
int m=0;
//nΪ���ݼ������� 
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
    
    //һ���ж�ȡ���ҽ�ÿһ�е�ֵ��Ϊһ�з���test�����в����޹�λ����Ϊ5 
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

//test1��testy��testy1����Ŀǰ��testһëһ�� 
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

cout<<"��·�Ĵ�С����m="<<m<<"    "<<"��n="<<n<<endl;//�����·�Ĵ�С 

void getSubset(int list[],bool v[],int a,int b);

//int N;    //��ʾ��������Ҫ������ 
//N=ceil(log(m)/log(2));
//N=10; 
cout<<"���������еĻ�������Ҫ"<<N<<"��"<<endl; 
int jxl[m][N];//������Ż����� 
int p,q;  //��i,jһ�� 
int column=0;
int max;
int N1=0;

//Ҫ�����kmeans���ļ� (Ϊ�˼��ݾ��ǲ���Ҫÿ�θı��ȡ��ͬ���ļ���)
	ifstream infile;
	infile.open(fname,ios::in);
	if(!infile){
		cout<<"���ܴ�������ļ�"<<fname<<endl;
		return 0;
	}
	int count=0;
	//���ļ���ÿһ�е���һ��string����vString�� 
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
    getSubset(li,v,0,N);  //�õ���������127�������ʽ
	//����127�������ʽһһ������� 
	
cout<<"HANG="<<HANG<<endl;

//int jxlzh[m][HANG-1];//�������7�н�������õ���127�� 
//int jxlzh2[m][2*(HANG-1)];//������Ż�������Ϻ���ȡ����
//int jxlzh3[m][2*(HANG-1)];

 
int count0,count1;//������¼ÿһ����0,1�ĸ��� 
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

//���������������һ���ٽ�ȥȡ�� 
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

//�ѻ������������ʽ2��ԭ���Լ��Ƚϣ��õ��������� 

//���������Ͳз��������ں������� 

//int xrlie[n];//������¼ԭ���Լ�����Щ������������2�е�������
//int xrcolumn=0;//��¼���ݵ��ж����� 
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

//���½�testy1����ԭ���Լ� ����Ԥ����0����-1 5����0 1����1 
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
	//û�����ݵ� 
	
	int sum[2*(HANG-1)];
	for(p=0;p<2*(HANG-1);p++){//lie
	   sum[p]=0;
		for(q=0;q<m;q++){
			sum[p]=sum[p]+testy1[q][j]*jxlzh3[q][p];
		}
	}
	max=0;
	int c;//��¼���ֵ���Ӧ���������3�е��� 
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
