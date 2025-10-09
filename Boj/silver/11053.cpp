#include<bits/stdc++.h>

using namespace std;
int arr[1001];
int dp[1001]; //i번째로 끝나는 값중 수열의 길이가 가장 긴
int N;
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>N;
  for(int i=1;i<=N;i++)
  {
    cin>>arr[i];
  }
  fill(dp,dp+N+1,1);
  for(int i=2;i<=N;i++)
  {
    for(int j=1;j<i;j++)
    {
      if(arr[i]>arr[j])
      {
        dp[i]=max(dp[i],dp[j]+1);
      }
    }
  }
  auto it=max_element(dp+1,dp+N+1);  
  cout<<*it;

}