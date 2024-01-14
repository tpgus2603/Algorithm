#include <iostream>
#include <algorithm>

using namespace std;

#define MAX 100000000
int dp[101][101];

int main()
{

  ios::sync_with_stdio(0);
  cin.tie(0);
  for (int i = 0; i <= 100; i++)
  {
    for (int j = 0; j <= 100; j++)
    {
      if (i == j)
        dp[i][j] = 0;
      else
        dp[i][j] = MAX;
    }
  }
  int n, m;
  cin >> n >> m;
  int a, b, c;
  for (int i = 0; i < m; i++)
  {
    cin >> a >> b >> c;
    if (dp[a][b] > c)
      dp[a][b] = c;
  }
  for (int k = 1; k <= n; k++)
  {
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
      }
    }
  }
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      if(dp[i][j]==MAX)
        cout<<'0'<<' ';
      else
       cout << dp[i][j] << ' ';
    }
    cout << '\n';
  }
}