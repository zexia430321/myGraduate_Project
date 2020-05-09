/*k-means++�㷨ʵ��
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
//���Ԫ���������Ϣ

vector<double> means[k];
//��������Ԫ����ŷ������루����Ҫ�����ţ� 
double getDistXY(vector<double> t1, vector<double> t2) {
	double sum = 0;
	for(int i = 0; i < t1.size(); i++){
		sum += (t1[i]-t2[i])*(t1[i]-t2[i]);
	}
	return sum;
}
 
//�������ģ�������ǰԪ�������ĸ���
int clusterOfTuple(vector<double> means[],vector<double> tuple){
	double dist=getDistXY(means[0],tuple);
	double tmp;
	int label = 0;//��ʾ������һ����  
	for(int i=1;i<k;i++){
		tmp=getDistXY(means[i],tuple);
		if(tmp<dist) {dist=tmp;label=i;}
	}
	return label;	
}
//��ø����ؼ���ƽ�����
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
//��õ�ǰ�صľ�ֵ�����ģ� ��ȡ�ķ�ʽΪ��ǰ���ÿһ��vector�͵�ǰ���Ľ�����ŷ����þ��� 
vector<double> getMeans(vector<vector<double>> cluster){
	
	//��ǰ����ӵ�е������� 
	double num  = cluster.size();
	//����һ������t���������µ�ǰ���means���� 
	vector<double> t;
	
	//��ǰ��û��һ��������ô�ͽ�һ��ȫΪ0���������ص����µľ������� 
	//	cout<<"num = "<<num<<endl;
	if(num == 0){
		t = initVector;
		return t;
	}
	
	//��Ҫ���и�ֵ��������Ϊvector���Ͳ�ƥ�� 
	t = cluster[0];
	
	//������k-1����ľ������ 
	for (int i = 1; i < num; i++){
		vector<double> tmp = cluster[i];
		for(int j = 0; j < tmp.size(); j++){
			t[j] += tmp[j];
		}
	}
	
	//�������е�ÿһ��λ�þ�����num�õ�ƽ��ֵ���������ǵ����� 
	for(int i = 0; i < t.size(); i++){
		t[i] = int(t[i]/num+0.5);
	}
	return t;
}

//�Ľ�֮���k-means++�㷨 ����Ĳ���Ϊ����֮������ݼ�Ҳ����ֻ����0��1��һ����ά����           
//means[k]Ϊһ�������ȫ�ֱ�����Ҳ�������ڴ�ž������ĵ����ݽṹ 
void getInitMeans(vector<vector<double>> myVector){
	int temp = 0;
	means[temp] = myVector[temp]; 
	temp++;
	
//	cout<<"myVector.size = "<<myVector.size()<<endl;
	while(temp < k){
		int diff = 0;
		vector<double> tempVector = means[0];
		//�������е������ҵ��������� 
		for(int i = 0; i < myVector.size(); i++){
			double dis = 255;
			vector<double> disVector = myVector[i];
			for(int j = 0; j < temp; j++){
				double cur = getDistXY(means[j], disVector);
				//���ﲻ��Ҫ������������һ�����������Ϊ��������һ����ô��ඨΪ0 
				if(cur < dis){
					dis = cur;
				}
			} 
			//������Ϊ0��ô�����if���㲻���ȥ 
			if(dis > diff){
				diff = dis;
				tempVector = disVector;
			}
		}
		
		
		//�����ǰ�����������������֮��ľ���
		for(int i = 0; i < temp; i++){
			cout<<getDistXY(means[i], tempVector)<<endl;
		} 
		cout<<"-------------------�ָ���-------------------"<<endl; 

		means[temp] = tempVector;
		temp++;
	}
}

//�汾�� 
//void getInitMeans(vector<vector<double>> myVector){
//	vector<double> sumCount;
//	//�ж��������� 
//	int size = myVector.size();
//	int temp = 0;
//	means[temp] = myVector[temp]; 
//	temp++;
//	while(temp < k){
//		sumCount.clear();
//		int sum = 0;
//		int diff = 0;
//		vector<double> tempVector;
//		//�������е������ҵ��������� 
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
//		//�ҳ���һ��i�������������ĵľ����������������ֱ�Ӹ�ֵΪ�µľ������� 
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
��Ҫ�߼�����*/ 
 
void KMeans(vector<vector<double>> myVector){
	vector<vector<double>> clusters[k];
	int i=0;
	//Ĭ��һ��ʼ��ǰK��Ԫ���ֵ��Ϊk���ص����ģ���ֵ��
//	for(i=0;i<k;i++){
//		means[i] = myVector[i]; 
//	}

	getInitMeans(myVector);
	//���һ��ʼѡ���ľ�������
	cout<<"-----------------------һ��ʼ�ľ�������----------------"<<endl<<endl<<endl; 
	 for(int p = 0; p < k; p++){
		vector<double> tmp = means[p];
		cout<<"��"<<p+1<<"����������Ϊ�� ";
		for(int j = 0; j < tmp.size(); j++){
			cout<<tmp[j]<<" ";
		}
		cout<<endl<<endl<<endl;
	}
		
	int lable=0;
	//����Ĭ�ϵ����ĸ��ظ�ֵ
	for(i=0;i!=myVector.size();++i){
		lable=clusterOfTuple(means,myVector[i]);
		clusters[lable].push_back(myVector[i]);
	}
	double oldVar=-1;
	double newVar=getVar(clusters,means);
	
//	cout<<"xxxxxxxxxxxxx"<<newVar<<endl;
	
	while(fabs(newVar - oldVar) >= CHANGE) //���¾ɺ���ֵ����1��׼����ֵ���������Ա仯ʱ���㷨��ֹ
	{
		for (i = 0; i < k; i++) //����ÿ���ص����ĵ�
		{
			means[i] = getMeans(clusters[i]);
			//cout<<"means["<<i<<"]:"<<means[i].attr1<<"  "<<means[i].attr2<<endl;
		}
		oldVar = newVar;
		newVar = getVar(clusters,means); //�����µ�׼����ֵ
		
		for (i = 0; i < k; i++) //���ÿ����
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
	//����һ����ά�������洢������Ҫ�ı���λ 
 	vector<vector<double>> myVector;
	char fname[256];
	cout<<"�����������ݵ��ļ����� ";
	cin>>fname;
	cout<<endl;
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
	
	// ��X��0����0��1ֱ��ʹ�� ������ myVector�� 
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
	
	
//��һ���ж�ȡת����Ϊһ���ж�ȡ
	string s   = vString[0];
	int length = s.length();
	
//����ֵΪ0 
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
	
//      ������ļ�����������ʾ 
//	for(int i = 0; i < myVector.size(); i++){
//		for(int j = 0; j < myVector[i].size(); j++){
//			cout<<myVector[i][j]<<" ";
//		}
//		cout<<endl;
//	} 
	cout<<"����Ϊ�ļ�����-------------------------------------------------------------------"<<endl;
//	cout<<endl; 
	//	int k; 
	//	cout<<"�����������Ĵصĸ�����"
	//cin>>k;
	//cout<<endl;
	//����ļ��е�Ԫ����Ϣ
	KMeans(myVector);
	vector<double> myRes[k];
	
	cout<<"-------------------------------------"<<"����֮�������---------------------------------"<<endl<<endl<<endl<<endl<<endl;
	for(int p = 0; p < k; p++){
		vector<double> tmp = means[p];
		cout<<"��"<<p+1<<"����������Ϊ�� ";
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
����ʵ��˼·��
1�����ļ������ļ�����һ��string������
2�����ļ�ת�ã�����ÿһ�б������myVector��һ������
3������һ����������Ϊ��ʼ�ľ������ģ�Ȼ����ݵ�һ���������Ĳ�����ʼ�ľ�����������ݾ�������ֵ����
4�������˳��Եľ�������֮������myVector���з��飬���ÿһ������������һ������������ 
5�����ÿһ��������������������������ŷ�Ͼ��룬��������벻�ٱ䶯��ʱ��ֹͣ����
6��odlVal��neaVal֮��Ĳ�ֵ��ĳ����Χ�ھͿ���ֹͣ�ˣ� �����������ľ۴������µ����ģ��������飬��newVal 
*/ 

