#include<iostream>
#include<vector>
using namespace std;

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> arr;
	int temp;
	arr.push_back(0);
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		arr.push_back(temp);
	}
	int dp[100001];//sn
	dp[0] = 0;
	dp[1] = arr[1];
	for (int i = 2; i <= n; i++)
	{
		dp[i] = dp[i - 1] + arr[i];
	}
	int k, j; // k~j번째수 까지 합 구하기 
	for (int i = 0; i < m; i++)
	{
		cin >> k >> j;
		cout << dp[j] - dp[k - 1]<<'\n';
	}


}