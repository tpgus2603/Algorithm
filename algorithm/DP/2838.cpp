#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>

#define X first
#define Y second
using namespace std;

int dp[5001];
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	dp[3]=1; dp[5]=1;
  for(int i=6;i<=n;i++)
  {
    if(dp[i-3]) dp[i]=dp[i-3]+1;
    if (dp[i]==0&&dp[i - 5])
     dp[i]=dp[i-5]+1;
    else if(dp[i]!=0&&dp[i-5])
     dp[i]=min(dp[i],dp[i-5]+1); 
  }
	if(dp[n]==0)
    cout<<-1;
  else
    cout<<dp[n];
}