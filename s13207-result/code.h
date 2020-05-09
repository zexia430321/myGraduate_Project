#ifndef CODE_H_
#define CODE_H_
#include<vector>
//using namespace std;
int FDR0(const string& data)
{
	vector<int> Dic(4096, -1);
	int fdr = 0;
	for (int i = 0; i < data.size(); i++)
	{
		int l = 0;
		while (i < data.size()&&data.at(i) != '1')
		{
			i++;
			l++;
		}
		if (Dic[l] == -1) //储存编码前长度为 l 编码后的长度 
		{
			int group = int(ceil((log(l + 3.0) / log(2.0) - 1)));
			Dic[l] = group << 1;
		}
		fdr += Dic[l];
	}
	return fdr;
}

int EFDR0(const string& data)
{ vector<int> Dic(4096, -1);//存取对应的长度 
  int n=data.size();
  int codesum=0,x=0,l=0;//记录编码和原码的大小 
  char a=data.at(0),b;//上一个字符 和当前字符 
  //if(a=='X') l=x=1; 
   codesum=0;
  for(int i=1;i<data.size();i++)
   { l=1+x;x=0; //长度最少为1 	  
	 if(a=='1')
	  {while(i<data.size()&&data.at(i)!='0') //直到b=='0' 
	    { if(data.at(i)!='X') x=0; //b=='1' 
	      else       x++; //记录‘X’的个数 
		  l++;i++;
		}
		if(i<data.size()) l=l-x;//1XXX0
		//else cout<<"W ";
	  }
	 else//a=='0'  
	  { while(i<data.size()&&data.at(i)!='1')//直到b=='1' 
	     { if(data.at(i)!='X') x=0; //b=='0' 
	       else       x++; //记录‘X’的个数 
		   l++;i++;
		 } 
        x=0;//0XXX1 
	  }
	  
	  if(i<data.size()&&data.at(i)!=a) //a只能为0,1 
	    { a=data.at(i);//更新前一个 
	    }
	  else//i=data.size() 
	    {cout<<"H ";
	    }
	  if (Dic[l] == -1) //储存编码前长度为 l 编码后的长度 
	   { int group = int(ceil((log(l+2.0) / log(2.0)-1)));//log2(l+3) ceil返回大于或者等于指定表达式的最小整数
		 Dic[l] = (group<<1);
		 
	   }//cout<<l<<" "<<Dic[l]<<"; ";
	   codesum+=Dic[l];	
   } cout<<"WWWWWWWWWWWWWWWWWWWWWWWWWW"<<endl;
   return codesum;
}



#include"testset.h"

int Golomb(matrix &ts,int B=2);
int FDR(matrix &ts);
int MFDR(matrix &ts,int r=1);
int AFDR(matrix &ts);
int VTFPVL(matrix &ts,int k=2);
int EFDR(matrix &ts);
int VIHC(matrix &ts,int group_size=std::numeric_limits<int32_t>::max());
int RL_Huffman(matrix &ts);

void FDR_fill_X(matrix& ts);
void EFDR_fill_X(matrix& ts);
void FDR_reorder(matrix &ts);

intv huffman(const intv& frequency);

int SHC(const matrix &ts,int block=12,int encode=16);
int OSHC(const matrix &ts,int block=12,int encode=32);
int VSHC(const matrix &ts,int block=24,int encode=20,int div=3);

void FDR_fill_X(matrix& ts)
{
	replace(ts.data.get(),ts.data.get()+ts.size,X,ZERO);
}

void EFDR_fill_X(matrix& ts)
{
	for(int i=0;i<ts.size;i++)
	{
		int specify=i;
		while(specify<ts.size&&ts(specify)==X)specify++;
		int RL=ZERO;
		if(specify!=ts.size)
			RL=ts(specify);
		while(i<ts.size&&(ts(i)==X||ts(i)==RL))
			ts(i++)=RL;
	}
}

void FDR_reorder(matrix &ts)
{
	auto weight=[](const view& a,const view& b){
		int c=0;
		for(int i=0;i<a.size;i++)
			if(a(i)==b(i))
				c+=1;
			else if((a(i)^b(i))==1)
				c-=1;
		return c;};
	for(int i=1;i<ts.shape[0];i++)
	{
		int max_vec=i;
		int max_w=0;
		for(int j=i;j<ts.shape[0];j++)
		{
			int w=weight(ts[i-1],ts[j]);
			if(w>max_w)
			{
				max_vec=j;
				max_w=w;
			}
		}
		view vw=ts[i];
		swap_ranges(vw.ptr,vw.ptr+vw.size,ts[max_vec].ptr);
		for(int k=0;k<ts.shape[1];k++)
			if(ts(i,k)==X)
				ts(i,k)=ts(i-1,k);
	}
	for(int i=ts.shape[0]-1;i>0;i--)
		for(int j=0;j<ts.shape[1];j++)
			ts(i,j)^=ts(i-1,j);
}

/****************************************************
EFDR_Fill_X_Dynamic
*/
#define N 2000 //vectors
#define M 300  //length
int s[N*M];//
int mm[N*M],m_posix[N*M];
int code_num;
inline void code_set(matrix& v,int len)
{
	int i,j,k=1;
	//11111xxxx0000xxxx11
	//11111xxxx0000xxxx10
	//last
	int last;
	if(v(len-1)==v(len-2))
	{
		for(last=len-1;v(last)==v(len-1)&&last>0;last--){}
	}
	else
	{
		for(last=len-2;v(last)==v(len-2)&&last>0;last--){}
	}

	for(i=0;i<=last;)
	{
		for(j=i;v(j)==v(i);j++){}
		s[k]=j-i-1;
		if(i==0)s[k]++;//first
		int u;
		for(u=j;v(u)==X;u++){}
		mm[k]=u-j;
		m_posix[k]=j;
		k++;
		i=u;
	}
	if(v(len-1)==v(len-2))s[k]=len-2-last;
	else s[k]=len-3-last;
	mm[k]=0;
	m_posix[k]=0;
	code_num=k;
	for(int i=0;i<code_num;i++)
	cout<<m_posix[i]<<' ';
	cout<<endl;
	for(int i=0;i<code_num;i++)
	cout<<mm[i]<<' ';
	cout<<endl;
	for(int i=0;i<code_num;i++)
	cout<<s[i]<<' ';
	cout<<endl;

}
int efdr_lenth(int length)
{
	if(length==0)
		return 0;
	//int x=int(1+2*int(ceil((log(length+2.0)/log(2.0)-1))));
	int group = int(ceil((log(length + 4.0) / log(2.0) - 2)));
	int x = group *2+1;
	return x;
}
//dynamic program
int y[N*M/10][N],p[N*M/10][N];int aa[N*M];
int marginAssignAlgorithm(matrix& v,int len)
{
	int i,j,k;
	for(i=0;i<=mm[1];i++)
		y[1][i]=efdr_lenth(s[1]+i);
	for(i=2;i<=code_num;i++)
		for(j=0;j<=mm[i];j++)
		{
			int miny=y[i-1][0]+efdr_lenth(s[i]+j+mm[i-1]);//k=0
			int mink=0;
			for(k=1;k<=mm[i-1];k++)
			{
				int t=y[i-1][k]+efdr_lenth(s[i]+j+mm[i-1]-k);
				if(miny>t)
				{
					miny=t;
					mink=k;
				}
			}
			y[i][j]=miny;
			p[i][j]=mink;
		}
		aa[code_num]=0;
		for(i=code_num;i>=2;i--)
		{
			aa[i-1]=p[i][aa[i]];
		}
		//fill
		for(i=1;i<code_num;i++)
			if(mm[i]>0)
			{
				for(j=0;j<aa[i];j++)
				{
					CHECK(v(m_posix[i]+j)==X);
					v(m_posix[i]+j)=v(m_posix[i]-1);
				}

				for(;v(m_posix[i]+j)==X;j++)v(m_posix[i]+j)=v(m_posix[i]-1)^1;
			}
			return y[code_num][0];
}

//char pp[N*M];
void EFDR_Fill_X_Dynamic(matrix& ts)
{
	/*Casa@130414c
xxx0,1xxxx1.
xxx1->11111,xxxx0->00000.
0xx->001,00x->001

0x1x000xxx111xxx0x1

	*/
	uint32_t j,k,ppl=ts.size;
	//xxx1->11111,xxxx0->00000
	if(ts(0)==X)
	{
		for(k=0;k<ts.size&&ts(k)==X;k++){}
		for(j=0;j<k;j++)
		{
			CHECK(ts(j)==X);
			ts(j)=ts(k);
		}
	}
	//0xx->001,00x->001
	if(ts(ppl-1)==X)
	{
		for(k=ppl-1;k>0&&ts(k)==X;k--){}
		for(j=k+1;j<ppl-1;j++)ts(j)=ts(k);
		ts(ppl-1)=ts(k)^0x1;
	}
	if(ts(ppl-2)==X)
		for(j=ppl-2;ts(j)==X;j--)ts(j)=ts(ppl-1)^0x1;
	//xxx0,1xxxx1.
	for(j=1;j<ppl-1;j++)
		if(ts(j)==X)
		{
			char x0=ts(j-1);
			for(k=j;k<ppl&&ts(k)==X;k++){}
			if(x0==ts(k))
			{
				for(;j<k;j++)
				{
					CHECK(ts(j)==X);
					ts(j)=x0;
				}
				j--;
			}
			else j=k-1;
			//cout<<j<<endl;
		}
		//0x1x000xxx111xxx0x1
		code_set(ts,ppl);
		marginAssignAlgorithm(ts,ppl);
}
/*************************************************/
#include<set>
#include<tuple>
using namespace std;

intv huffman(const intv& frequency)
{
	vector<tuple<int,int>> node;//vaule,parent
	auto compare=[&node](const int& a,const int& b){
		return (get<0>(node[a]))<(get<0>(node[b]));};
	multiset<int,decltype(compare)> _set(compare);
	for(int i=0;i<frequency.size();i++)
	{
		node.emplace_back(frequency[i],-1);
		_set.insert(i);
	}
	while(_set.size()>=2)
	{
		int x=*_set.begin();_set.erase(_set.begin());
		int y=*_set.begin();_set.erase(_set.begin());
		node.emplace_back(get<0>(node[x])+get<0>(node[y]),-1);
		_set.insert(node.size()-1);
		get<1>(node[x])=get<1>(node[y])=node.size()-1;		
	}
	intv code;
	for(int i=0;i<frequency.size();i++)
	{
		int size=0;
		int p=i;
		while(get<1>(node[p])!=-1)
		{
			size++;
			p=get<1>(node[p]);
		}
		code.push_back(size);
	}
	return code;
}
//#define TEST_HUFFMAN
#ifdef TEST_HUFFMAN
int main()
{
	intv f{3,4,7,9,2};
	intv c=huffman(f);
	for(auto &e:c)
		cout<<e<<' ';
	cout<<endl;
	return 0;
}

#endif
//***********************************************************
#endif
