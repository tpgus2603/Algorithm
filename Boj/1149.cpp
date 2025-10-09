#include<bits/stdc++.h>

using namespace std;
int dp[1001][3]; //dp[i][1]은 1번색을 칠할때 누적 최소비용 
int N;
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>N;
  int temp;
  for(int i=1;i<=N;i++)
  {
    for(int j=0;j<3;j++)dp[i][j]=1e9;
  }

  for(int i=0;i<3;i++)
  {
    cin>>temp;
    dp[1][i]=temp;
  }
  for(int i=2;i<=N;i++)
  {
    for(int j=0;j<3;j++)
    {
      cin>>temp;
      for(int k=0;k<3;k++)
      {
        if(k==j)continue;
        dp[i][j]=min(dp[i][j],dp[i-1][k]+temp);
      }
    }
  }
  int ans=1e9;
  for(int i=0;i<3;i++)
  {
    if(ans>dp[N][i])ans=dp[N][i];
  }
  cout<<ans;
}