/*k-means++算法实现
*@File:k_means++.cpp
*@Author:xiaze
*@Create:2019-4-4
*/
// s5378.vec s9234.vec  s13207.vec s15850.vec s38417.vec s38584.vec
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>
#define CHANGE 0.5
const int k = 6;
//const int k = 7;
//const int k = 8; 
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
 
//根据质心，决定当前元组属于哪个簇
int clusterOfTuple(vector<double> means[],vector<double> tuple){
	double dist=getDistXY(means[0],tuple);
	double tmp;
	int label = 0;//标示属于哪一个簇  
	for(int i=1;i<k;i++){
		tmp=getDistXY(means[i],tuple);
		if(tmp<dist) {dist=tmp;label=i;}
	}
	return label;	
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

//版本二 
//void getInitMeans(vector<vector<double>> myVector){
//	vector<double> sumCount;
//	//有多少列向量 
//	int size = myVector.size();
//	int temp = 0;
//	means[temp] = myVector[temp]; 
//	temp++;
//	while(temp < k){
//		sumCount.clear();
//		int sum = 0;
//		int diff = 0;
//		vector<double> tempVector;
//		//遍历所有的向量找到距离最大的 
//		for(int i = 0; i < myVector.size(); i++){
//			double dis = 255 ;
//			vector<double> disVector = myVector[i];
//			for(int j = 0; j < temp; j++){
//				double cur = getDistXY(means[j], disVector);
//				if(cur < dis){
//					dis = cur;
//				}
//			}
//		sum += dis;	 
//		sumCount.push_back(sum);		
//		}
//		
//		int targetSum = rand()%(int)(sumCount[size-1]-1)+1;
//		//找出那一个i与其他聚类中心的距离正好在这个里面直接赋值为新的聚类中心 
//		for(int i = 0; i < size; i++){
//			if(targetSum <= sumCount[i]){
//				means[temp++] = myVector[i];
//				break;
//			}
//		}
//	}
//}
/**************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
主要逻辑部分*/ 
 
void KMeans(vector<vector<double>> myVector){
	vector<vector<double>> clusters[k];
	int i=0;
	//默认一开始将前K个元组的值作为k个簇的质心（均值）
//	for(i=0;i<k;i++){
//		means[i] = myVector[i]; 
//	}

	getInitMeans(myVector);
	//输出一开始选出的聚类中心
	cout<<"-----------------------一开始的聚类中心----------------"<<endl<<endl<<endl; 
	 for(int p = 0; p < k; p++){
		vector<double> tmp = means[p];
		cout<<"第"<<p+1<<"个聚类中心为： ";
		for(int j = 0; j < tmp.size(); j++){
			cout<<tmp[j]<<" ";
		}
		cout<<endl<<endl<<endl;
	}
		
	int lable=0;
	//根据默认的质心给簇赋值
	for(i=0;i!=myVector.size();++i){
		lable=clusterOfTuple(means,myVector[i]);
		clusters[lable].push_back(myVector[i]);
	}
	double oldVar=-1;
	double newVar=getVar(clusters,means);
	
//	cout<<"xxxxxxxxxxxxx"<<newVar<<endl;
	
	while(fabs(newVar - oldVar) >= CHANGE) //当新旧函数值相差不到1即准则函数值不发生明显变化时，算法终止
	{
		for (i = 0; i < k; i++) //更新每个簇的中心点
		{
			means[i] = getMeans(clusters[i]);
			//cout<<"means["<<i<<"]:"<<means[i].attr1<<"  "<<means[i].attr2<<endl;
		}
		oldVar = newVar;
		newVar = getVar(clusters,means); //计算新的准则函数值
		
		for (i = 0; i < k; i++) //清空每个簇
		{
			clusters[i].clear();
		}
		
		// 
		for(i=0;i!=myVector.size();++i){
			lable=clusterOfTuple(means,myVector[i]);
			clusters[lable].push_back(myVector[i]);
		}
	}
	
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
	
	// 将X用0代替0和1直接使用 ，存入 myVector中 
//	for(int j = 0; j < vString.size(); j++){
//		string s = vString[j];
//		vector<double>  vint;
//	    for(int i = 0; i < s.length(); i++){
// 			if(s[i] == 'X'){
// 				vint.push_back(0);
//			 }else if(s[i] != ' '){
//			 	vint.push_back(s[i]-'0');
//			 }
//	    } 
//	    myVector.push_back(vint);
//	}
	
	
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
	
//      输出的文件内容如下所示 
//	for(int i = 0; i < myVector.size(); i++){
//		for(int j = 0; j < myVector[i].size(); j++){
//			cout<<myVector[i][j]<<" ";
//		}
//		cout<<endl;
//	} 
	cout<<"上述为文件内容-------------------------------------------------------------------"<<endl;
//	cout<<endl; 
	//	int k; 
	//	cout<<"请输入期望的簇的个数："
	//cin>>k;
	//cout<<endl;
	//输出文件中的元组信息
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

