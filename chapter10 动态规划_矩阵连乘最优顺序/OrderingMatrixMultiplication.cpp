#include <iostream>
#include <vector>
using namespace std;/*�����������ռ䣬vectorҲ����ʶ��*/
const int INF=100000;
int min(const int &a, const int &b)
{
	int min = a;
	if (b < min)
	{
		min = b;
	}
	return min;
}
int OrderingMatrixMutiplication(const vector<int> &dimension)
{
	int n = dimension.size() - 1;
	vector<vector<int>> dp;
	dp.resize(n, vector<int>(n, INF));
	for (int i = 0; i < n; ++i)
	{
		dp[i][i] = 0;
	}
	int left, right;
	for (int k = 1; k < n; ++k)
	{
		for (left = 0; left + k < n; ++left)
		{
			right = left + k;
			for (int i = left; i < right; ++i)
			{
				/*
				�ؼ��㷨
				dp[left][i] + dp[i + 1][right]+ dimension[left] * dimension[i + 1] * dimension[right + 1]����
				�α�p291ҳ�Ĺ�ʽ
				ֻ����left�Ǵ�0��ʼ�ģ�����ȡ��ά�ȵ������Ŷ�Ҫ��1
				*/
				dp[left][right] = min(dp[left][right], dp[left][i] + dp[i + 1][right]+ dimension[left] * dimension[i + 1] * dimension[right + 1]);
			}
		}
	}
	int result = dp[0][n - 1];
	dp.clear();
	return result;
}

void main()
{
	vector<int> Matrix;
	int n;
	cin >> n;
	Matrix.resize(n);
	for (int i = 0; i < n; i++)
	{
		cin >> Matrix[i];
	}
	cout << OrderingMatrixMutiplication(Matrix) << endl;



	cin.get();
	cin.get();
}
