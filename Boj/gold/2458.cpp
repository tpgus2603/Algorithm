#include <bits/stdc++.h>
using namespace std;

bool arr[501][501];

int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m;
    cin>>n>>m;
    int u,v;
    for(int i=0;i<m;i++)
    {
      cin>>u>>v;
      arr[u][v]=true;
    }
    //플로이드 워셜 사용
    for(int k=1;k<=n;k++)
    {
      for(int i=1;i<=n;i++)
      {
        if(!arr[i][k])continue;
        for(int j=1;j<=n;j++)
        {
          if(arr[k][j])arr[i][j]=true;
        }
      }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
      int s=0;
      int l=0;
      for(int j=1;j<=n;j++)
        if(arr[i][j]) l++;
      for(int j=1;j<=n;j++)
        if(arr[j][i])s++;
      if(s+l==n-1) ans++;
    }
    cout<<ans;
}
