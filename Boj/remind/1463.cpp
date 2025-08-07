#include<bits/stdc++.h>

using namespace std;

int dp[1000001];
int main()
{
  ios::sync_with_stdio();cin.tie(0);
  int n;
  cin>>n;
  fill(dp,dp+n+1,1e9);
  dp[1]=0;
  for(int cur=1;cur<=n;cur++)
  {
    int n1=cur+1;
    int n2=cur*2;
    int n3=cur*3;
    if(n1>n)continue;
    dp[n1]=min(dp[n1],dp[cur]+1);
    if(n2>n)continue;
    dp[n2]=min(dp[n2],dp[cur]+1);
    if(n3>n)continue;
    dp[n3]=min(dp[n3],dp[cur]+1);
  }
  cout<<dp[n];




}