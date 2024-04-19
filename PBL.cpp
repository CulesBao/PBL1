#include <bits/stdc++.h>
using namespace std;

const long MAX_ARRAY = 1e3;

//Ma tran chuyen vi
vector <vector<float>> transpose(vector <vector<float>> T)
{
	vector <vector<float>> Tt;
	
	Tt.resize(T[0].size(), vector<float>(T.size()));
	
	for (int i = 0; i < T.size(); i++)
		for (int j = 0; j < T[0].size(); j++)
			Tt[j][i] = T[i][j];
			
	return Tt;
}
//Nhan 2 ma tran
//Tim cac tri rieng vecto

//Buoc 3: Tinh su chenh lech giua bien ban dau va gia tri trung binh tim duoc o buoc 2
vector <vector<float>> step3(int N, int M, vector <vector<float>> T, vector <float> a)
{	
	vector <vector<float>> data;
	
	data.resize(N, vector<float>(M));	//N dong M cot
	
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			data[i][j] = T[i][j] - a[i];
			
	return data;
}

//Buoc 2: Tinh vector trung binh
vector <float> step2(int N, int M, vector <vector<float>> T)
{
	vector <float> average;
	
	for (int i = 0; i < N; i++)
	{
		float sum = 0;
		for (int j = 0; j < M; j++)
			sum += T[i][j];
		average.push_back(sum / (float) M);	
	}	
	
	return average;
}

// Buoc 1: Doc du lieu
int main()
{
	//Khai bao
	int N, M;
	vector <vector<float>> T, tempData;
	vector <float> a;
	
	//Doc du lieu tu file data.inp vao, xuat ra file data.out
	freopen("data.inp", "r", stdin);
	freopen("data.out", "w", stdout);
	
	//Doc du lieu dau vao
	cin >> M >> N;
	
	//Cap phat bo nho
	T.resize(N, vector<float>(M));	//N dong M cot
	tempData.resize(N, vector<float>(M));	//N dong M cot
	
	//Doc gia tri cho mang T
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> T[i][j];
			
	a = step2(N, M, T);
	tempData = step3(N, M, T, a);
			
	//In thu du lieu		
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < M; j++)
//			cout << tempData[i][j] << "		";
//		cout << endl;
//	}
}