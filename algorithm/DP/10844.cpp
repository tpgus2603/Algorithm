#include<iostream>
#define K 1000000000
#define ll long long
using namespace std;

ll dp[101][10]; //dp[n][k]  n자리수 까지 끝(오른쪽 혹은 왼쪽끝)이 k인 경우의수 .


int main()
{
  int n;
  cin>>n;
  dp[1][0]=0;
  for(int i=1;i<=9;i++)
    dp[1][i]=1;
  for(int i=2;i<=n;i++)
  {
    for(int j=0;j<=9;j++)
    {
      if(j>0&&j<9)
        dp[i][j]=(dp[i-1][j+1]+dp[i-1][j-1])%K;
      else if(j==0)
        dp[i][j]=dp[i-1][j+1];
      else if(j==9)
        dp[i][j]=dp[i-1][j-1];
    }
  }
  ll sum=0;
  for(int i=0;i<=9;i++)
  {
    sum+=dp[n][i];
  }
  cout<<sum%K;

}

