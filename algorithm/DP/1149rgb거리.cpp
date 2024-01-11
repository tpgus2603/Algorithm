#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	int n;
	int arr[1001][4];
	cin >> n;
	int n1, n2, n3;
	for (int i = 1; i <= n; i++)
	{
		cin >> n1 >> n2 >> n3;
		arr[i][1] = n1;
		arr[i][2] = n2;
		arr[i][3] = n3;
	}
	int dp[1001][4];  //i번째 집까지 마지막에 빨강(1) 초록(2) 파랑(3)을 택했을떄 최소비용
	dp[1][1] = arr[1][1];
	dp[1][2] = arr[1][2];
	dp[1][3] = arr[1][3];
	for (int i = 2; i <= n; i++)
	{
		dp[i][1] = min(dp[i - 1][2] + arr[i][1], dp[i - 1][3] + arr[i][1]);
		dp[i][2] = min(dp[i - 1][1] + arr[i][2], dp[i - 1][3] + arr[i][2]);
		dp[i][3] = min(dp[i - 1][1] + arr[i][3], dp[i - 1][2] + arr[i][3]);
	}
	cout << min({dp[n][1], dp[n][2], dp[n][2], dp[n][3]});


}