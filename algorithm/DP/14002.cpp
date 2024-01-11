#include<iostream>
#include<algorithm>
#include<vector>
#include<utility>

using namespace std;
vector<int> dp[1001]; // dp[i] 부분수열의 마지막 항이 arr[i]인 부분수열 중 길이가 최대인 부분수열 리스트
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
	//dp[1].push_back(arr[1]);
	for (int i = 1; i <= n; i++)
	{
		vector<pair<int,int>> dpsize; //현재 커서의 인덱스보다 작은 인덱스의 부분수열중 가장긴 것을 찾기위해
		for (int j = 1; j < i; j++)
		{
			if (arr[i] > arr[j]) //최종항이 arr[i]보다 작은 
				dpsize.push_back({dp[j].size(),j});
		}
		if (dpsize.size() != 0) //최종값이 arr[i]보다 작은게 있으면
		{
			auto k = max_element(dpsize.begin(), dpsize.end());
      auto p=*k;
			dp[i] = dp[p.second];
      dp[i].push_back(arr[i]);
		}
		else //없으면
			dp[i].push_back(arr[i]);
	}
  int maxsize=0;
  int maxidx=1;
	for(int i=1;i<=n;i++)
  {
    int temp=dp[i].size();
    if(maxsize<temp)
    {
      maxsize=temp;
      maxidx=i;
    }
  }
  cout<<maxsize<<'\n';
  for(auto k:dp[maxidx])
    cout<<k<<' ';  
}