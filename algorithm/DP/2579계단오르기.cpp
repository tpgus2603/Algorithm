#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	vector<int> stair;
	stair.push_back(0);
	int temp;
	for (int i = 0; i < n; i++)
	{
		cin >> temp;
		stair.push_back(temp);
	}
	int dp[301][3];  //dp[i][1]=i번째 계단을 밟는데 1계단째 밟은경우 dp[i][2]= 2계단째 밟는경우
	dp[1][1] = stair[1]; dp[1][2] = 0; //dp[i][1]은 2번째 전 계단에서 한칸 점프한것임 
	dp[2][1] = stair[2];
	dp[2][2] = stair[1] + stair[2];
	for (int i = 3; i <= n; i++)
	{
		dp[i][1] = max(dp[i - 2][1], dp[i - 2][2]) + stair[i];
		dp[i][2] = dp[i - 1][1] + stair[i];
	}
	cout << max(dp[n][1], dp[n][2]);

}



//#include <bits/stdc++.h>
//using namespace std;
//
//int step[305];
//int dp[305];
//
//int main(void) {
//	ios::sync_with_stdio(0);
//	cin.tie(0);
//	int n;
//	cin >> n;
//	for (int i = 1; i <= n; i++)
//		cin >> step[i];
//	dp[1] = step[1];
//	dp[2] = step[2] + step[1];
//	dp[3] = step[3] + max(step[2], step[1]);
//	for (int i = 4; i <= n; i++)
//		dp[i] = step[i] + max(step[i - 1] + dp[i - 3], dp[i - 2]);
//	cout << dp[n];
//	return 0;
//}
//
