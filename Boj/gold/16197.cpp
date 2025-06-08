#include<bits/stdc++.h>

#define X first 
#define Y second

int dx[4] ={-1,0,1,0};
int dy[4]={0,-1,0,1};
using namespace std;
string arr[20];
int dis[20][20][20][20];
int n,m;
bool check(pair<int,int> cur) //범위넘어가면 true
{
  int x=cur.X;
  int y=cur.Y;
  if(x<0||x>=n||y<0||y>=m)return true;
  return false; 
}
int main()
{ 
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n>>m;
  pair<int,int> co1;
  pair<int,int> co2;
  vector<pair<int,int>> coin;
  for(int i=0;i<n;i++)
  {
    cin>>arr[i];
    for(int j=0;j<m;j++)
    {
      if(arr[i][j]=='o')coin.push_back({i,j});
    }
  }
  co1=coin[0];
  co2=coin[1];
  queue<pair<pair<int,int>,pair<int,int>>> q;
  q.push({co1,co2});
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
    {
      for(int z=0;z<n;z++)
      {
        for(int k=0;k<m;k++)
          dis[i][j][z][k]=-1;
      }
    }
  }
  dis[co1.X][co1.Y][co2.X][co2.Y]=0;
  while(!q.empty())
  { 
    auto cur=q.front();
    pair<int,int> c1=cur.X;
    pair<int,int> c2=cur.Y;
    q.pop();
    int t=dis[c1.X][c1.Y][c2.X][c2.Y];
    if(t>=10)
    {
      cout<<-1;
      return 0;
    }
    for(int dir=0;dir<4;dir++)
    {
      int nx1=c1.X+dx[dir];
      int nx2=c2.X+dx[dir];
      int ny1=c1.Y+dy[dir];
      int ny2=c2.Y+dy[dir];
      //두 둥전 모두 방문 했던 위치는 방문x
      if(check({nx1,ny1})&&check({nx2,ny2}))continue;
      if(check({nx1,ny1})^check({nx2,ny2})) //둘중 하나만 out인경우
      {
        cout<<t+1;
        return 0;
      }
      if(arr[nx1][ny1]=='#'&&arr[nx2][ny2]=='#')continue; //두 동전 모두다음이 벽인경우
      if(arr[nx1][ny1]=='#') //1번 동전만 벽인경우 
      {
        nx1=c1.X;
        ny1=c1.Y;
      } 
      else if(arr[nx2][ny2]=='#')
      {
        nx2=c2.X;
        ny2=c2.Y;
      }
      if(dis[nx1][ny1][nx2][ny2]!=-1)continue;
      dis[nx1][ny1][nx2][ny2]=t+1;
      q.push({{nx1,ny1},{nx2,ny2}});
    }
  }
  cout<<-1;

}