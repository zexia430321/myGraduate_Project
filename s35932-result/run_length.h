/*
 * run_length.cpp
 *
 *  Created on: Mar 23, 2014
 *      Author: Liang Zhang
 */
//#include "function.h"
#include "testset.h"
#include "code.h"
#include<cmath>
#include<algorithm>
#include<cassert>

//#define GOLOMB_CODE
//#define FDR_CODE
//#define MFDR_CODE
//#define AFDR_CODE//alternating FDR
//#define VTFPVL_CODE//variable-to-fixed-plus-variable-length
//#define EFDR_CODE
//#define VIHC_CODE
//#define RL_HUFFMAN_CODE
#ifdef GOLOMB_CODE
int Golomb(matrix &ts,int B)
#elif defined(FDR_CODE)
int FDR(matrix &ts)
#elif defined(MFDR_CODE)
int MFDR(matrix &ts,int r)
#elif defined(AFDR_CODE)
int AFDR(matrix &ts)
#elif defined(VTFPVL_CODE)
int VTFPVL(matrix &ts,int k)
#elif defined(EFDR_CODE)
int EFDR(matrix &ts)
#elif defined(VIHC_CODE)
int VIHC(matrix &ts,int group_size)
#elif defined(RL_HUFFMAN_CODE)
int RL_Huffman(matrix &ts)
#endif
{
	intv Dic(40960,0);
	intv Run(40960,0);
	int size = 0;
	int RL=ZERO;
	int LIMIT=std::numeric_limits<int32_t>::max();//2147483647
	
#ifdef VTFPVL_CODE
	int MAX_RUN=(1<<((1<<k)+1))-3;
	int num[4]={0};
	for(int i=0;i<ts.size;++i)
		num[ts(i)]++;
	RL=num[ZERO]>=num[ONE]?ZERO:ONE;
#elif defined(EFDR_CODE)
	EFDR_fill_X(ts);
#elif defined(VIHC_CODE)
	LIMIT=group_size;
#elif defined(RL_HUFFMAN_CODE)
	int first_specify=0;
	while(ts(first_specify)==X)first_specify++;
	RL=ts(first_specify);
	assert(RL!=X);
#endif

	for (int i = 0; i < ts.size; i++)
	{
		int l = 0;
#ifdef EFDR_CODE
		RL=ts(i);
#endif
		while (i < ts.size&&(ts(i) == RL||ts(i)==X)&&l<LIMIT)
		{
			i++;
			l++;
		}
		Run[l]++;
		if (Dic[l] == 0)
		{
#ifdef GOLOMB_CODE
			int group = (l>>B)+1;
			Dic[l] = group + B;
#elif defined(FDR_CODE)||defined(AFDR_CODE)
			int group = int(ceil((log(l + 3.0) / log(2.0) - 1)));
			Dic[l] = group << 1;
			//int group = int(ceil((log(l + 4.0) / log(2.0) - 2)));
			//Dic[l] = group *2+1;

#elif defined(MFDR_CODE)
			if(l<(1<<(r+1)))
				Dic[l]=r+3;
			else
			{
				int k=int(log(1.0+l/(1<<(r+1)))/log(2.0));
				int half=((1<<k)-1)*(1<<(r+1))+(1<<r+k);
				if(l<half)
					Dic[l]=2*k+r+1;
				else
					Dic[l]=2*k+r+2;
			}
#elif defined(VTFPVL_CODE)
			if(l<MAX_RUN)
			{
				int group=int(log(l+2.0)/log(2.0));
				Dic[l]=group+k;
			}
			else
			{
				int group=int(log((l%MAX_RUN)+2.0)/log(2.0));
				Dic[l]=group+k+(l/MAX_RUN)*((1<<k)+k);
			}
#elif defined(EFDR_CODE)
			int group = int(ceil((log(l + 2.0) / log(2.0) - 1)));
			Dic[l] = (group << 1)+1;
#endif
		}
#ifdef AFDR_CODE
		RL^=1;
#elif defined(RL_HUFFMAN_CODE)
		RL^=1;
		i--;
#elif defined(VIHC_CODE)
		if(l==LIMIT)
			i--;
#endif
		size += Dic[l];
	}
#if defined(VIHC_CODE)||defined(RL_HUFFMAN_CODE)
	intv huffman(const intv& frequency);
	Run.erase(remove(Run.begin(),Run.end(),0),Run.end());
	Dic=huffman(Run);
	size=0;
	for(int i=0;i<Run.size();i++)
		size+=Run[i]*Dic[i];
	//cout<<"SIZE="<<size<<"   TS.SIZE="<<ts.size<<endl;
#endif
	return size;
}
