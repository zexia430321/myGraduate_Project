/*k-means++算法实现
*@File:k_means++.cpp
*@Author:xiaze
*@Create:2019-4-4
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>
#include <cstdlib>
#define CHANGE 0.5
//const int k = 6;
//const int k = 7;
const int k = 8;
//const int k = 9;
//const int k = 10;
//const int k = 11;
using namespace std;
vector<double> initVector;
//存放元组的属性信息

vector<double> means[k];
//计算两个元组间的欧几里距离（不需要开根号） 
double getDistXY(vector<double> t1, vector<double> t2) {
	double sum = 0;
	for(int i = 0; i < t1.size(); i++){
		sum += (t1[i]-t2[i])*(t1[i]-t2[i]);
	}
	return sum;
}
//获得给定簇集的平方误差
double getVar(vector<vector<double>> clusters[],vector<double> means[]){
	double var = 0;
	for (int i = 0; i < k; i++)
	{
		vector<vector<double>> t = clusters[i];
		for (int j = 0; j< t.size(); j++)
		{
			var += getDistXY(means[i],t[j]);
		}
	}
	//cout<<"sum:"<<sum<<endl;
	return var;
 
}
//获得当前簇的均值（质心） 获取的方式为当前族的每一个vector和当前质心进行求欧几里得距离 
vector<double> getMeans(vector<vector<double>> cluster){
	
	//当前族所拥有的向量数 
	double num  = cluster.size();
	//定义一个向量t用于最后更新当前族的means中心 
	vector<double> t;
	
	//当前族没有一个向量那么就将一个全为0的向量返回当做新的聚类中心 
	//	cout<<"num = "<<num<<endl;
	if(num == 0){
		t = initVector;
		return t;
	}
	
	//需要进行赋值操作，因为vector类型不匹配 
	t = cluster[0];
	
	//将其余k-1个族的距离进行 
	for (int i = 1; i < num; i++){
		vector<double> tmp = cluster[i];
		for(int j = 0; j < tmp.size(); j++){
			t[j] += tmp[j];
		}
	}
	
	//将向量中的每一个位置均除上num得到平均值，当做我们的质心 
	for(int i = 0; i < t.size(); i++){
		t[i] = int(t[i]/num+0.5);
	}
	return t;
}

//改进之后的k-means++算法 传入的参数为处理之后的数据集也就是只包含0和1的一个二维数组           
//means[k]为一个定义的全局变量，也就是用于存放聚类中心的数据结构 
void getInitMeans(vector<vector<double>> myVector){
	
//	for(int i = 0; i < k; i++){
//		int temp = rand()%myVector.size();
//		means[i] = myVector[temp]; 
//	}
	
	

	int temp = 0;
	means[temp] = myVector[temp]; 
	temp++;
	
//	cout<<"myVector.size = "<<myVector.size()<<endl;
	while(temp < k){
		int diff = 0;
		vector<double> tempVector = means[0];
		//遍历所有的向量找到距离最大的 
		for(int i = 0; i < myVector.size(); i++){
			double dis = 255;
			vector<double> disVector = myVector[i];
			for(int j = 0; j < temp; j++){
				double cur = getDistXY(means[j], disVector);
				//这里不需要考虑两个向量一样的情况，因为两个向量一样那么差距定为0 
				if(cur < dis){
					dis = cur;
				}
			} 
			//如果差距为0那么下面的if语句便不会进去 
			if(dis > diff){
				diff = dis;
				tempVector = disVector;
			}
		}
		
		
		//输出当前向量与各个聚类中心之间的距离
		for(int i = 0; i < temp; i++){
			cout<<getDistXY(means[i], tempVector)<<endl;
		} 
		cout<<"-------------------分割线-------------------"<<endl; 

		means[temp] = tempVector;
		temp++;
	}
}
 
void KMeans(vector<vector<double>> myVector){

	getInitMeans(myVector);
	
}   
int main(){
	//定义一个二维数组来存储我们需要的比特位 
 	vector<vector<double>> myVector;
	char fname[256];
	cout<<"请输入存放数据的文件名： ";
	cin>>fname;
	cout<<endl;
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
	
	
	 
//将一行行读取转化成为一列列读取
	string s   = vString[0];
	int length = s.length();
	
//赋初值为0 
	for(int i = 0; i < vString.size(); i++){
		initVector.push_back(0);
	}
	
	for(int j = 0; j < length; j++){
		vector<double>  vint;
	    for(int i = 0; i < vString.size(); i++){
	    	string s = vString[i];
 			if(s[j] == 'X'){
 				vint.push_back(0);
			 }else if(s[j] != ' '){
			 	vint.push_back(s[j]-'0');
			 }
	    } 
	    myVector.push_back(vint);
	}
	
	cout<<"上述为文件内容-------------------------------------------------------------------"<<endl;
	KMeans(myVector);
	vector<double> myRes[k];
	
	cout<<"-------------------------------------"<<"运算之后的向量---------------------------------"<<endl<<endl<<endl<<endl<<endl;
	for(int p = 0; p < k; p++){
		vector<double> tmp = means[p];
		cout<<"第"<<p+1<<"个聚类中心为： ";
		for(int j = 0; j < tmp.size(); j++){
			cout<<tmp[j]<<" ";
		}
		cout<<endl<<endl<<endl;
	}
		
		
		
	cout<<"-----------------------------------------------------------------------------------------"<<endl<<endl<<endl<<endl<<endl;
	int total = means[0].size();
	
	cout<<"total = "<<total<<endl;
	for(int i = 0; i < total; i++){
		for(int j = 0; j < k; j++){
			cout<<means[j][i];
		}
		cout<<endl;
	}	
	return 0;
}

/*
具体实现思路：
1、读文件，将文件读入一个string数组中
2、将文件转置，就是每一列变成我们myVector的一行向量
3、将第一个向量设置为初始的聚类中心，然后根据第一个聚类中心产生初始的聚类个数，根据距离的最大值产生
4、产生了初试的聚类中心之后将整个myVector进行分组，标记每一个向量属于哪一个聚类中心组 
5、求出每一个组的向量与所求的中心向量的欧氏距离，当这个距离不再变动的时候停止迭代
6、odlVal和neaVal之间的差值在某个范围内就可以停止了， 根据所产生的聚簇生成新的中心，继续分组，求newVal 
*/ 

