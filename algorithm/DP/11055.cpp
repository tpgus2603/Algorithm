#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int dp[1001]; //부분 수열의 합 
int arr[1001];

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin>>n;
  int temp;
  for(int i=1;i<=n;i++)
  {
    cin>>temp;
    arr[i]=temp;
  }
  dp[1]=arr[1];
  for(int i=1;i<=n;i++)
  {
    vector<int>dptemp;
    for(int j=1;j<i;j++)
    {
      if(arr[i]>arr[j])
        dptemp.push_back(dp[j]);
    }
    if(dptemp.size())
    {
      auto k=max_element(dptemp.begin(),dptemp.end());
      dp[i]=*k+arr[i];
    }
    else
      dp[i]=arr[i];
  }
  auto k=max_element(dp,dp+n+1);
    cout<<*k;




}