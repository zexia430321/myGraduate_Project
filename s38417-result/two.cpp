/* ���ù����������½����������� �õ�n*n�п�ѡ������
/* Ȼ���ÿһ�� Ѱ������������  j*(n*n)
/*�任����Ϊint���ͣ��洢�ַ�����Ϊint 
*/
//20170304
/*
���·  
*/
#include<ctime> 
#include<cstring>
#include<iomanip>  
#include<fstream>
#include<iostream>
#define WAYS 3//�任��������
#define CODEWAYS 6// 6ѹ�����뷽������ 7
#include<vector> 
#include <direct.h>//�����ļ��� 
#include"two.h"
#include"matrix.h"
#include"code.h" 
#include"transform.cpp"
using namespace std;
string s0,sname,s2;char s1[20];
//�������������Ϣ����ӡ�������ݵ� 
void testinfo()
{	
	cout<<"�����������Ϣ��"<<endl;
	cout<<"���������������Сh,��ʾh*h����"<<endl;
	cin>>i;
	h=ceil(log2(i)); //����ȡ�� 
	h=pow(2,h);//����X 2^h  
    creath(a,h);  
    cout<<h<<"*"<<h<<"���������Ϊ��"<<endl;
  
  print(a,h,h);
  creatnewh2(a,h);//del(a,h); 	creatnewh(a,h);
  cout<<endl; 
  cout<<h<<"*"<<h<<"���ĺ�Ĺ��������Ϊ��"<<endl;
  print(a,h,h);
	del(a,h);	 
} 
//�����ļ�  ��ȡ�ļ��е����� 
int fileprocess(int argc,char **&argv)//argc--����������argv[]:���� 
{ 
//�жϲ����Ƿ�Ϊ2 
	if(argc!=2)
		{	cout<<"No file ��"<<endl; return 0;} 
// ������ĵڶ����������ļ�������filename
	const string& filename=argv[1]; 	
	if(filename=="-t")  
	{
	testinfo();
	return 0; }
// �������ļ��� 
	fin.open(filename.c_str());
//���ļ������ڣ����˳� 
	if(!fin) exit(0);
//��ȡ������������ļ���
	i=0; 
//���ļ�������s1 ,��ȡ��·����s2��name 
	strcpy(s1,filename.c_str()); 
	while(i<filename.size()&&s1[i]!='.')i++;
	s1[i]='\0';
	s2=s1;
	name=s2;
//���ļ��е����ݣ���¼��m��n)�������ݸ���data�� 
	data="";
	while(!fin.eof())
		{	fin>>s0;
			if(!fin.eof())
				{	data.append(s0); 
					m++; 
				}
		}
	n=s0.size() ; 
	if(m<4||n<4) return 0;  
//����data�ļ���	
	_mkdir("data"); 
//��snameΪ��·�� 
  sname=s2;
  s2="data\\"+s2;
//ios::app����������������ļ�ĩβ 
    fout.open("out.txt",ios::app);//0׷�� 
	fout11.open(s2+"_11.txt");  //1
	fout12.open(s2+"_12.txt");  //2
	fout21.open(s2+"_21.txt");//3
	fout22.open(s2+"_22.txt");//4
	fout31.open(s2+"_31.txt");//5	
	fout32.open(s2+"_32.txt"); //6
//Ԥ�������� 
//����0 1 X 
	for(i=0;i<8;i++)
		for(j=0;j<3;j++)
			{	result[i][j]=0;} 
//���ַ�ת�������� '0'->0   '1'->1  'x'->2
	c2i['0'] = ZERO;
	c2i['1'] = ONE;
	c2i['X'] = X;
//������ת�����ַ� 
	i2c[ZERO] = '0';
	i2c[ONE] = '1';
	i2c[X] = 'X';
//��Ҫ�Ĺ�������� 
	num=h=ceil(log2(m));
//��������������� 
    h=pow(2,h);    
//�б� log2(n-1)+1;
	num_row=h_row=ceil(log2(n));
//�б�
	h_row=pow(2,h_row);  
//������Լ����С����Լ� ������������ 
  cout<<"row number m="<<m<<endl; 
  cout<<"columnm    n="<<n<<endl; 
  cout<<"h="<<h<<endl;
// 
  str =new int * [m];
  str1=new int * [m];
  str2=new int * [m];
	for(i=0;i<m;i++)
		{	str[i]=new int [n+1]; 
			str1[i]=new int [n+1]; 
			str2[i]=new int [n+1]; 
		}
//����ÿһ��0-n��Ӧ���������к�	
//����ÿһ����������������С���� 
	max0=new int [h+h_row]; 
//�����Ӧ�� ����й����� ���	
//�����Ӧ������������ݵĽ�� 
	sum0=new int [h+h_row]; 
//������������ݡ��������ݣ�	
    g0=new int [h+h_row];
    
    char temp[n+1];	
	fin.clear();
// ��λ���ļ���ͷ��
    fin.seekg(0);    
    i=0;
    while(i<m) 
  	{
//����һ�� 	
	  fin>>temp;
	  temp[n]='\0'; 
	for(j=0;j<n;j++)
	{
//0 1 X  -> 0 1 2 
//���Լ�����str[m][n]�� 
		str[i][j]=c2i[temp[j]];}
      if(!fin.eof()) 
	    	{	i++;}
    }
	return 1;	
}

int outprocess()
{	int Golomb=0;
	if(CODEWAYS==7)
	Golomb=10;
	string codename[]={"FDR","EFDR","VIHC","Golomb","AFDR","RLHuff","FDR[R]","SHC","OSHC","VSHC","B=1","B=2","B=3","B=4","B=5","B=6","B=7","B=8","B=9","B=10"};
//�ļ������һ�� ˵����Ŀ	
	if(s2=="data\\s5378"||s2=="s5378")  
	fout<<"��·��	��С	X	0	1	ԭʼ1	����1	ԭʼ2	����2	����"<<endl; 
//ԭ���������һ�α任  ���Ĺ��������һ�α任  ԭʼ������+ԭʼB   ���Ĺ����ꡪ+����B 
//�ļ�ÿ�����Լ������ĵ�һ�� ���0 1 X����  1�ĸ��� 

//�����·�� �ܼƵĸ��� 
	fout<<s1<<"\t"<<result[0][0]+result[0][1]+result[0][2]<<"\t";
//���x  0  1�ĸ���	  
	fout<<result[0][2]<<"\t"<<result[0][1]<<"\t"<<result[0][0]<<"\t";
//�������4�ַ�����1�ĸ��� 
	for(i=1;i<WAYS;i++) 
	fout<<result[i][0]<<"\t";
	fout<<endl; 
//�ļ����ѹ���� 
	for(k=0;k<CODEWAYS;k++)	{	
	    fout<<s1<<"\t";
		fout<<codename[k+Golomb]<<"\t";
  		fout<<"\t";
		fout<<"\t";
		for(i=0;i<WAYS;i++) 
  		fout<<setiosflags(ios::fixed)<<setprecision(2)<<r[k][i]<<"\t";
  		fout<<setiosflags(ios::fixed)<<setprecision(2)<<r[k][WAYS-1]-r[k][1];  //r[k][6]-r[k][1]; 
  		fout<<endl;
		}
//�ļ����ѹ����  ./two s38417.vec
	for(k=0;k<CODEWAYS;k++)
		{	cout<<codename[k+Golomb]<<"\t"; 
  		if(k==0) cout<<"m"<<m<<"\t"<<"n"<<n<<"\t"; 
  		else cout<<"\t"<<"\t";
		for(i=0;i<WAYS;i++) 
  		cout<<setiosflags(ios::fixed)<<setprecision(2)<<r[k][i]<<"\t";
  		cout<<setiosflags(ios::fixed)<<setprecision(2)<<r[k][WAYS-1]-r[k][1]; 
  		cout<<endl;
		}
} 

#include<algorithm>
#include"testset.h"
#include"code.h"

#define FDR_CODE
#include"run_length.h"
#undef FDR_CODE

#define AFDR_CODE
#include"run_length.h"
#undef AFDR_CODE

#define EFDR_CODE
#include"run_length.h"
#undef EFDR_CODE

#define GOLOMB_CODE
#include"run_length.h"
#undef GOLOMB_CODE

#define MFDR_CODE
#include"run_length.h"
#undef MFDR_CODE

#define VTFPVL_CODE
#include"run_length.h"
#undef VTFPVL_CODE

#define VIHC_CODE
#include"run_length.h"
#undef VIHC_CODE

#define RL_HUFFMAN_CODE
#include"run_length.h"
#undef RL_HUFFMAN_CODE

#define TEST_RUN_LENGTH
#ifdef TEST_RUN_LENGTH
#include"testset.h"
#include<iostream>
int codemain(const string &data0,int time,int mm=m,int nn=n,float daijia=0.0)
{	
//���Լ����� 
    testset ts(data0,mm,nn,name);
	testset _t;	
	_t=ts; 
//����"Golomb"����ʱ���ŵ�Bȡֵ��
//#if CODEWAYS==7 
//	r[0][time]=Golomb(_t,2);
//	_t=ts;
//	r[1][time]=Golomb(_t,3);
//	_t=ts;
//	r[2][time]=Golomb(_t,4);
//	_t=ts;
//	r[3][time]=Golomb(_t,5);
//	_t=ts;
//	r[4][time]=Golomb(_t,6);
//	_t=ts;
//	r[5][time]=Golomb(_t,7);
//	_t=ts;
//	r[6][time]=Golomb(_t,8);
//#else 
	r[0][time]=FDR(_t);
	_t=ts;
	r[1][time]=EFDR(_t);
	_t=ts;
	r[2][time]=VIHC(_t);
	_t=ts;
	r[3][time]=Golomb(_t);	
	_t=ts;
	r[4][time]=AFDR(_t);	   
	_t=ts;
	r[5][time]=RL_Huffman(_t);
	_t=ts;
	FDR_reorder(_t);
	r[6][time]=FDR(_t);
//#endif 

	for(i=0;i<7;i++)
//ts.size
	r[i][time]=100.0-r[i][time]*100.0/(m*n)-daijia;
	return 0;
}
#endif
//----------------------------------main------------------------ 
int main(int argc,char *argv[])
{	
//�����ļ� �����Լ�����int str[m][n]��
  if(fileprocess(argc,argv)==0) 
		return 0;
//��ȡʱ��		
//���ʱ�� 
	time_t        tCurTime=time(NULL);
  struct tm*    ptmCurTime=localtime(&tCurTime);    
  cout<<ptmCurTime->tm_year+1900<<"-"<<ptmCurTime->tm_mon+1<<"-"<<ptmCurTime->tm_mday
	<<" "<<ptmCurTime->tm_hour<<":"<<ptmCurTime->tm_min<<":"<<ptmCurTime->tm_sec<<endl;
	time_t start,stop;
  start = time(NULL);
//�������������	
	creath(mat,h); 
#define  NEWH
#ifdef NEWH   
//��ʦ���ľ��� 
	creatnewh(b,h);
	dd(b,h);
#else 
	creath(b,h);
	creatnewh2(b,h);
#endif 
//д���ļ� 
	ofstream fout_trans("out_trans.txt",ios::app);
//���ۼ��� 
	int tempn=0;
	float daijia=0;
//һ�α任�Ĵ��� 
	float daijiaonce=(log2(h)+1.0)/m*100; 
//����ֱ��ѹ����ѹ���� 
	codemain(data,0);
//��ԭʼ���Լ��ù����������һ�α任  ѹ���ʣ�������  	
	wht(str,str1,mat,1,fout11);  
	codemain(data,1);
//�ҵķ���
xrx(str1,2);
codemain(data,2);
 //codemain(data,2);
////�޸ĺ�Ĺ��������任  ѹ����
//   wht(str,str1,b,2,fout12);	
//	codemain(data,2);
// ��Ԥ�������ù��������  ѹ����
//  tempn=wht_three(str,str2,str1,mat,3,fout21,fout22,fout_trans,daijia); 
//  codemain(data,3,m,tempn,daijia);                                     
////��Ԥ���������޸ĺ�Ĺ��������任 ѹ����
//   tempn=wht_three(str,str2,str1,b,4,fout31,fout32,fout_trans,daijia); 
//	codemain(data,4,m,tempn,daijia);                                   
//�����ֹʱ�� 
	stop = time(NULL);
    cout<<"Time : "<<(stop-start)<<" seconds "<<endl;
//������� 
    outprocess(); 
  //ɾ������ 
	del(mat,h);
	del(str,m);
	del(str1,m);
	del(str2,m);
	cout<<"_LINE_:"<<__LINE__<<endl; 
	if(s2=="data\\s38584")
		{	fout.close();
			system("out.txt"); 
		}
	exit(0);
	return 0;
} 
//-------------------ѹ�����벿��-------------------------- 


 

