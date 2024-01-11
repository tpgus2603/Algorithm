#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
int dp[1001]; // dp[i] 부분수열의 마지막 항이 arr[i]인 수열중 최대 길이 
int arr[1001];

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		int temp;
		cin >> temp;
		arr[i] = temp;
	}
	dp[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		vector<int>dptemp; //현재 커서의 인덱스보다 작은 인덱스의 부분수열중 가장긴 것을 찾기위해
		for (int j = 1; j < i; j++)
		{
			if (arr[i] > arr[j]) //최종항이 arr[i]보다 작은 dp값 찾기
				dptemp.push_back(dp[j]);
		}
		if (dptemp.size() != 0) //최종값이 arr[i]보다 작은게 있으면
		{
			auto k = max_element(dptemp.begin(), dptemp.end());
			dp[i] = *k + 1;
		}
		else //없으면-> 1
			dp[i] = 1;
	}
	auto k = max_element(dp+1, dp + n+1);
	cout << *k;

}