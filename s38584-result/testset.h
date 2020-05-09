/*
 * testset.h
 *
 *  Created on: Mar 22, 2014
 *      Author: Liang Zhang
 */

#ifndef TESTSET_H_
#define TESTSET_H_
#include<string>
#include<memory>
#include<cassert>
#include <algorithm>
#include <tuple>
#include"function.h"
using namespace std;

struct view
{
	int *ptr;
	int size;
	view(int *p,int _size):ptr(p),size(_size){}
	int &operator()(int i)
	{
	assert(i<size);return ptr[i];
	}
	const int &operator()(int i)const
	{
	assert(i<size);return ptr[i];
	}
	void operator=(const view& other)
	{
	copy(other.ptr,other.ptr+size,ptr);
	}
	void operator=(const intv& other)
	{
	copy(other.begin(),other.end(),ptr);
	}
	intv get(){
	return intv(ptr,ptr+size);
	}
};

struct matrix//�洢���Լ� 
{
	unique_ptr<int[]> data;//����data����  
	int shape[2];//���Լ������������������� 
	int size;//���Լ���С 
	void operator=(const matrix& other);
	matrix(const intvv& vecs);
	matrix(const matrix& other){*this=other;}
	matrix()=default;
	int &operator()(int i)
	{
	return data[i];
	}
	int &operator()(int x,int y){
	return data[x*shape[1]+y];}
	view operator[](int x){
	return view(data.get()+shape[1]*x,shape[1]);
	}
	const view operator[](int x)const
	{
	return view(data.get()+shape[1]*x,shape[1]);
	}
	void printm();
	void output(const string &filename);
};

class testset:public matrix
{
public:	
	string name;
	testset()=default;
	testset(const string& filename);
	testset(const string& data0,int m,int n,string name0);//���Լ�����
	void set(const matrix& m){matrix::operator=(m);};
	/*Average Power,Peak Power,Total Power(Energy)*/
	tuple<double,double> power();
};
#include <fstream>

matrix::matrix(const intvv& vecs)
{
	shape[0]=vecs.size();
	shape[1]=vecs.back().size();
	size=shape[0]*shape[1];
	data=unique_ptr<int[]>(new int[size]);
	for(int i=0;i<shape[0];i++)
		for(int j=0;j<shape[1];j++)
			operator()(i,j)=vecs[i][j];
}
void matrix::printm()
{
	char m[0xff];
	m[ZERO] = '0';
	m[ONE] = '1';
	m[X] = 'X';
	m[C] = 'C';
	for (int i=0;i<shape[0];i++)
	{
		for(int j=0;j<shape[1];j++)
			cout <<m[operator()(i,j)];
		cout << endl;
	}
}
void matrix::output(const string &filename)
{
	ofstream out(filename.c_str());
	CHECK(out);
	char m[0xff];
	m[ZERO] = '0';
	m[ONE] = '1';
	m[X] = 'X';
	m[C] = 'C';
	for (int i=0;i<shape[0];i++)
	{
		for(int j=0;j<shape[1];j++)
			out <<m[operator()(i,j)];
		out << endl;
	}
}

void matrix::operator=(const matrix& other)
{
	shape[0]=other.shape[0];
	shape[1]=other.shape[1];
	size=other.size;
	data.reset(new int[size]);
	copy(other.data.get(),other.data.get()+size,data.get());
}

testset::testset(const string& filename)//���Լ����� 
{
	intvv vecs;
	ifstream in(filename.c_str());
	CHECK(in.is_open());
	string line;
	int m[0xff];
	m['0'] = ZERO;
	m['1'] = ONE;
	m['X'] = X;
	m['C'] = C;
	while (in >> line)
	{
		intv vec(line.length());//���������ַ�ת��Ϊint 
		for (size_t i = 0; i < line.length(); ++i)
			vec[i] = m[(int) line[i]];
		vecs.push_back(move(vec));//�浽vecs�� 
	}
	shape[0] = vecs.size();//���Լ����������� 
	shape[1] = vecs.back().size();//�������� 
	size=shape[0]*shape[1];
	data.reset(new int[size]);//�������ݵ�data��ȥ 
	for (int i=0;i<shape[0];i++)
		for(int j=0;j<shape[1];j++)
			operator()(i,j)=vecs[i][j];
	//test set name
	auto r = filename.rfind('.');
	auto l = filename.rfind('/');// ���ַ������滹�ǲ��ҵ�. /ֹͣ 
	if(l == string::npos)//������ 
		l = filename.rfind('\\');
	if (l == string::npos)
		l = 0;
	else l++;
	if (l > r)
		r = filename.length();
	name = filename.substr(l, r - l);//��ȡ�ļ�����������׺�� 
}
//****A 
testset::testset(const string& data0,int mm,int nn,string name0)
{	intv vecs(data0.length());	
	int m[0xff];
	m['0'] = ZERO;
	m['1'] = ONE;
	m['X'] = X;
	m['C'] = C;
	for(size_t i=0;i<data0.length();i++)//���������ַ�ת��Ϊint
		{	vecs[i] = m[(int) data0[i]];}
	shape[0] = mm;//���Լ����������� 
	shape[1] = nn;//�������� 
	size=shape[0]*shape[1];
	data.reset(new int[size]);//�������ݵ�data��ȥ 
	for (int i=0;i<size;i++)
		data[i]=vecs[i];
	
	name = name0;//��ȡ�ļ�����������׺�� 
}
//****B
tuple<double,double> testset::power()
{
	intv WT;
	for(int i=0;i<shape[0];i++)
	{
		int k=shape[1]-1;
		while(operator()(i,k)==X)k++;
		assert(k<shape[1]);
		int RL=operator()(i,k);
		assert(RL!=X);
		int C=0;
		for(int j=1;j<shape[1];j++)
		{
			if(operator()(i,shape[1]-1-j)==(RL^1))
			{
				C+=shape[1]-j;
				RL^=1;
			}
		}
		WT.push_back(C);
	}
	double AveragePower=accumulate(WT.begin(),WT.end(),0)/(double)WT.size();
	double PeakPower=*max_element(WT.begin(),WT.end());
	return make_tuple(AveragePower,PeakPower);
}


#endif /* TESTSET_H_ */
