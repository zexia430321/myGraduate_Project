#ifndef TWO_H_
#define TWO_H_
#include<fstream>
#include<iostream>
#include"define.h"
ifstream fin;
ofstream fout;//("out.txt",ios::app);//0×·¼Ó 
ofstream fout11;//(s2+"_11.txt");  //1
ofstream fout12;//(s2+"_12.txt");  //2
ofstream fout21;//(s2+"_21.txt");//3
ofstream fout22;//(s2+"_22.txt");//4
ofstream fout31;//(s2+"_31.txt");//5	
ofstream fout32;//(s2+"_32.txt"); //6
//ofstream fout33(s2+"_re.txt"); //7
//ofstream fout34(s2+"_r2.txt"); //8	
int outprocess();
int fileprocess(int argc,char **&argv); 
//int codemain(const string &data0,int time,int mm=m,int nn=n,float daijia=0.0);
#endif
