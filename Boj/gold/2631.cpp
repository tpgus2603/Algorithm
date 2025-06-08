#include<bits/stdc++.h>

using namespace std;
int dp[200]; //끝이 arr[i]인 수열중 가장 큰 값 
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  int n;
  vector<int> arr;
  cin>>n;
  int temp;
  for(int i=0;i<n;i++)
  {
    cin>>temp;
    arr.push_back(temp);
  }
  dp[0]=1;
  for(int i=1;i<n;i++)
  {
    dp[i]=1;
    for(int j=0;j<i;j++)
    {
      if(arr[j]>arr[i])continue;
      dp[i]=max(dp[j]+1,dp[i]);
    }
  }
  int ans=0;
  for(int i=0;i<n;i++)
  {
    ans=max(dp[i],ans);
  }
  cout<<n-ans;

}