#ifndef FUNCTION_H_
#define FUNCTION_H_
#include <limits>

//0,1,X,C
const int ZERO = 0;
const int ONE = 1;
const int X = 2;
const int C = 3;

/* typedef */
#include<vector>
#include<memory>
#include<tuple>
typedef unsigned int uint;
typedef std::vector<int> intv;
typedef std::vector<uint> uintv;
typedef std::unique_ptr<std::vector<int>> intvp;
typedef std::unique_ptr<std::vector<uint>> uintvp;
typedef std::vector<std::vector<int>> intvv;
typedef std::vector<std::vector<uint>> uintvv;
typedef std::tuple<int,int> ii;
typedef std::vector<ii> iiv;


/*error handle*/
#include<iostream>
#include<cstdlib>
#include<cassert>
#define CHECK(success) {\
	if(!(success)){\
		std::cerr<<__FILE__<<':'<<__LINE__\
<<"\terror:In function "<<__FUNCTION__<<std::endl;\
		exit(-1);}}

template<typename T>
void print(const std::vector<T>& v)
{
	std::cout<<"["<<v.size()<<"]";
	for(auto &e:v)
		std::cout<<" "<<e;
	std::cout<<std::endl;
}
template<typename T>
void print(const std::vector<std::vector<T>>& vs)
{
	std::cout<<"("<<vs.size()<<")"<<std::endl;
	for(auto &e:vs)
		print(e);
	std::cout<<std::endl;
}

template<typename T>
std::vector<T> operator+(const std::vector<T> &l,const std::vector<T> &r)
{
	std::vector<T> all(l);
	all.insert(all.end(),r.begin(),r.end());
	return all;
}


#endif //FUNCTION_H_
