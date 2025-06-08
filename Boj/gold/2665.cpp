#include<bits/stdc++.h>
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
int dis[50][50];
#define X first 
#define Y second 
using namespace std;
string arr[50];
int n;
bool over(pair<int,int> cur)
{
  int x=cur.X;
  int y=cur.Y;
  if(x<0||x>=n||y<0||y>=n)return true;
  return false;
}
//0-1 bfs
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n;
  for(int i=0;i<n;i++) //'0'이 검은색 '1'이 흰색 
  {
    cin>>arr[i];
  }
  //(0,0)이 시작점 (n-1,n-1)이 끝점 
  int ans=1e9;
  for(int i=0;i<n;i++)
    fill(dis[i],dis[i]+n,1e9);
  //거리 좌표 
  priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>> pq;
  pq.push({0,0,0});
  dis[0][0]=0;
  while(!pq.empty())
  {
    auto [d,x,y]=pq.top();
    pq.pop();
    if(d!=dis[x][y])continue;
    //if(x==n-1&&y==n-1)break;
    for(int dir=0;dir<4;dir++)
    {
      int nx=x+dx[dir];
      int ny=y+dy[dir];
      if(over({nx,ny}))continue;
      int c=(arr[nx][ny]=='0')?1:0;
      if(d+c<dis[nx][ny])
      {
        dis[nx][ny]=d+c;
        pq.push({d+c,nx,ny});
      }
    }
  }
  cout<<dis[n-1][n-1];

}