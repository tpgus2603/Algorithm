#include<iostream>
#include<algorithm>

using namespace std;

int dp[1000001] = { 0 };
int back[1000001] = { 0 };

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	dp[0] = 0;
	dp[1] = 0;
	int n;
	cin >> n;
	for (int i = 2; i <= n; i++)
	{
		dp[i] = dp[i - 1] + 1;
		back[i] = i - 1;
		if (i % 2 == 0)
		{
			if (dp[i] >= (dp[i / 2] + 1))
				back[i] = i / 2;
			dp[i] = min(dp[i], dp[i / 2] + 1);
		}
		if (i % 3 == 0)
		{
			if (dp[i] >= (dp[i / 3] + 1))
				back[i] = i / 3;
			dp[i] = min(dp[i], dp[i / 3] + 1);
		}

	}
	cout << dp[n] << '\n';
	for (int cur = n; cur != 0; cur = back[cur])
	{
		cout << cur << ' ';
	}


}