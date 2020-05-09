/* 先让哈达玛矩阵和新建矩阵进行异或 得到n*n行可选主分量
/* 然后对每一列 寻找最优主分量  j*(n*n)
/*变换矩阵为int类型，存储字符串的为int 
*/
//20170304
/*
大电路  
*/
#include<ctime> 
#include<cstring>
#include<iomanip>  
#include<fstream>
#include<iostream>
#define WAYS 3//变换方法数量
#define CODEWAYS 6// 6压缩编码方法数量 7
#include<vector> 
#include <direct.h>//创建文件夹 
#include"two.h"
#include"matrix.h"
#include"code.h" 
#include"transform.cpp"
using namespace std;
string s0,sname,s2;char s1[20];
//处理测试数据信息、打印数据内容等 
void testinfo()
{	
	cout<<"请输入测试信息："<<endl;
	cout<<"请输入哈达码矩阵大小h,表示h*h矩阵："<<endl;
	cin>>i;
	h=ceil(log2(i)); //向上取整 
	h=pow(2,h);//补成X 2^h  
    creath(a,h);  
    cout<<h<<"*"<<h<<"哈达码矩阵为："<<endl;
  
  print(a,h,h);
  creatnewh2(a,h);//del(a,h); 	creatnewh(a,h);
  cout<<endl; 
  cout<<h<<"*"<<h<<"更改后的哈达码矩阵为："<<endl;
  print(a,h,h);
	del(a,h);	 
} 
//处理文件  读取文件中的数据 
int fileprocess(int argc,char **&argv)//argc--参数个数；argv[]:参数 
{ 
//判断参数是否为2 
	if(argc!=2)
		{	cout<<"No file ！"<<endl; return 0;} 
// 把输入的第二个参数（文件名）给filename
	const string& filename=argv[1]; 	
	if(filename=="-t")  
	{
	testinfo();
	return 0; }
// 打开输入文件； 
	fin.open(filename.c_str());
//若文件不存在，则退出 
	if(!fin) exit(0);
//提取命令中输入的文件名
	i=0; 
//将文件名赋给s1 ,提取电路名给s2和name 
	strcpy(s1,filename.c_str()); 
	while(i<filename.size()&&s1[i]!='.')i++;
	s1[i]='\0';
	s2=s1;
	name=s2;
//读文件中的数据（记录行m列n)；把数据给到data中 
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
//创建data文件夹	
	_mkdir("data"); 
//给sname为电路名 
  sname=s2;
  s2="data\\"+s2;
//ios::app：所有输出附加在文件末尾 
    fout.open("out.txt",ios::app);//0追加 
	fout11.open(s2+"_11.txt");  //1
	fout12.open(s2+"_12.txt");  //2
	fout21.open(s2+"_21.txt");//3
	fout22.open(s2+"_22.txt");//4
	fout31.open(s2+"_31.txt");//5	
	fout32.open(s2+"_32.txt"); //6
//预处理数据 
//保存0 1 X 
	for(i=0;i<8;i++)
		for(j=0;j<3;j++)
			{	result[i][j]=0;} 
//将字符转换成数字 '0'->0   '1'->1  'x'->2
	c2i['0'] = ZERO;
	c2i['1'] = ONE;
	c2i['X'] = X;
//将数字转换成字符 
	i2c[ZERO] = '0';
	i2c[ONE] = '1';
	i2c[X] = 'X';
//需要的哈达码阶数 
	num=h=ceil(log2(m));
//哈达码的行与列数 
    h=pow(2,h);    
//列变 log2(n-1)+1;
	num_row=h_row=ceil(log2(n));
//列变
	h_row=pow(2,h_row);  
//输出测试集的行、列以及 哈达吗矩阵的行 
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
//保存每一列0-n对应最大哈达玛行号	
//保存每一列与其他列相容最小的列 
	max0=new int [h+h_row]; 
//保存对应列 与各行哈达码 结果	
//保存对应的列与各列相容的结果 
	sum0=new int [h+h_row]; 
//标记正负（相容、反向相容）	
    g0=new int [h+h_row];
    
    char temp[n+1];	
	fin.clear();
// 定位到文件开头处
    fin.seekg(0);    
    i=0;
    while(i<m) 
  	{
//输入一行 	
	  fin>>temp;
	  temp[n]='\0'; 
	for(j=0;j<n;j++)
	{
//0 1 X  -> 0 1 2 
//测试集给到str[m][n]中 
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
//文件输出第一排 说明项目	
	if(s2=="data\\s5378"||s2=="s5378")  
	fout<<"电路名	大小	X	0	1	原始1	更改1	原始2	更改2	提升"<<endl; 
//原哈达玛矩阵一次变换  更改哈达玛矩阵一次变换  原始哈达玛+原始B   更改哈达玛—+更改B 
//文件每个测试集操作的第一排 输出0 1 X个数  1的个数 

//输出电路名 总计的个数 
	fout<<s1<<"\t"<<result[0][0]+result[0][1]+result[0][2]<<"\t";
//输出x  0  1的个数	  
	fout<<result[0][2]<<"\t"<<result[0][1]<<"\t"<<result[0][0]<<"\t";
//输出后面4种方法中1的个数 
	for(i=1;i<WAYS;i++) 
	fout<<result[i][0]<<"\t";
	fout<<endl; 
//文件输出压缩率 
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
//文件输出压缩率  ./two s38417.vec
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
//测试集输入 
    testset ts(data0,mm,nn,name);
	testset _t;	
	_t=ts; 
//测试"Golomb"编码时最优的B取值。
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
//处理文件 将测试集存在int str[m][n]中
  if(fileprocess(argc,argv)==0) 
		return 0;
//获取时间		
//输出时间 
	time_t        tCurTime=time(NULL);
  struct tm*    ptmCurTime=localtime(&tCurTime);    
  cout<<ptmCurTime->tm_year+1900<<"-"<<ptmCurTime->tm_mon+1<<"-"<<ptmCurTime->tm_mday
	<<" "<<ptmCurTime->tm_hour<<":"<<ptmCurTime->tm_min<<":"<<ptmCurTime->tm_sec<<endl;
	time_t start,stop;
  start = time(NULL);
//创建哈达玛矩阵	
	creath(mat,h); 
#define  NEWH
#ifdef NEWH   
//老师更改矩阵 
	creatnewh(b,h);
	dd(b,h);
#else 
	creath(b,h);
	creatnewh2(b,h);
#endif 
//写入文件 
	ofstream fout_trans("out_trans.txt",ios::app);
//代价计算 
	int tempn=0;
	float daijia=0;
//一次变换的代价 
	float daijiaonce=(log2(h)+1.0)/m*100; 
//计算直接压缩的压缩率 
	codemain(data,0);
//对原始测试集用哈达玛矩阵做一次变换  压缩率（张亮）  	
	wht(str,str1,mat,1,fout11);  
	codemain(data,1);
//我的方法
xrx(str1,2);
codemain(data,2);
 //codemain(data,2);
////修改后的哈达码矩阵变换  压缩率
//   wht(str,str1,b,2,fout12);	
//	codemain(data,2);
// 先预处理再用哈达玛矩阵  压缩率
//  tempn=wht_three(str,str2,str1,mat,3,fout21,fout22,fout_trans,daijia); 
//  codemain(data,3,m,tempn,daijia);                                     
////先预处理再用修改后的哈达码矩阵变换 压缩率
//   tempn=wht_three(str,str2,str1,b,4,fout31,fout32,fout_trans,daijia); 
//	codemain(data,4,m,tempn,daijia);                                   
//输出截止时间 
	stop = time(NULL);
    cout<<"Time : "<<(stop-start)<<" seconds "<<endl;
//处理输出 
    outprocess(); 
  //删除矩阵 
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
//-------------------压缩编码部分-------------------------- 


 

