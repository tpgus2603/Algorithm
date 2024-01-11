#include<iostream>

using namespace std;
int main()
{
	int dp[1001];//dp[n] 2xn크기 타일을 채우는 방법의 수 
	dp[1] = 1;
	dp[2] = 2;
	int n;
	cin >> n;
	for (int i = 3; i <= n; i++)
	{
		dp[i] = (dp[i - 1] + dp[i - 2]) % 10007;

	}
	cout << dp[n];



}

