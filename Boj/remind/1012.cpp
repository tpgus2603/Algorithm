#include<bits/stdc++.h>

using namespace std;
#define X first 
#define Y second 

int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};

int n,m;

bool over(int x,int y)
{
  if(x<0||x>=n||y<0||y>=m) return true;
  return false;
}

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  int t,k;
  cin>>t;
  while(t--)
  {
    cin>>m>>n>>k;
    int cnt=0;
    queue<pair<int,int>> q;
    vector<vector<int>>arr(n,vector<int>(m,0));
    vector<vector<bool>>vis(n,vector<bool>(m,false));
    int x,y;
    for(int i=0;i<k;i++) //배추 심기 
    {
      cin>>y>>x;
      arr[x][y]=1;
    }
    for(int i=0;i<n;i++)
    {
      for(int j=0;j<m;j++)
      {
        if(vis[i][j]||arr[i][j]==0)continue;
        cnt++;
        q.push({i,j});
        vis[i][j]=true;
        while(!q.empty())
        {
          auto cur=q.front();
          q.pop();
          for(int dir=0;dir<4;dir++)
          {
            int nx=cur.X+dx[dir];
            int ny=cur.Y+dy[dir];
            if(over(nx,ny)||vis[nx][ny])continue;
            if(arr[nx][ny]==0)continue;
            q.push({nx,ny});
            vis[nx][ny]=true;
          }
        }
      }
    }
    cout<<cnt<<'\n';
  }


}