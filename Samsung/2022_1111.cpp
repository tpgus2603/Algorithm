#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<cstring>
#include<algorithm>
#define X first 
#define Y second
using namespace std;
int N,M;
int arr[17][17]; //0빈공간 1베이스캠프 2 오염된 편의점,베이스캠프
int dx[4]={-1,0,0,1};
int dy[4]={0,-1,1,0};
struct player{
  pair<int,int> pt;
  pair<int,int> goal;
  bool ismove; //이번턴에 격자에서 움직일건지유무 ,초기값은 false 
};
vector<player> players; //0-based
int ans;

bool over(int x,int y)
{
  if(x<=0||x>N||y<=0||y>N)return true;
  return false;
}
pair<int,int> cbfs(int i)
{
  pair<int,int> goal=players[i].goal;
  pair<int,int>st=players[i].pt;
  bool vis[17][17]={0};
  pair<int,int> pre[17][17];
  for(int i=1;i<=N;i++)
  {
    for(int j=1;j<=N;j++)pre[i][j]={0,0};
  }
  queue<pair<int,int>> q;
  vis[st.X][st.Y]=true;
  q.push(st);
  while(!q.empty())
  {
    auto cur=q.front();
    q.pop();
    if(cur==goal)break;
    for(int dir=0;dir<4;dir++)
    {
      int nx=cur.X+dx[dir];
      int ny=cur.Y+dy[dir];
      if(over(nx,ny)||vis[nx][ny]||arr[nx][ny]==2)continue;
      vis[nx][ny]=true;
      q.push({nx,ny});
      pre[nx][ny]=cur;
    }
  }
  vector<pair<int,int>> path;
  path.push_back(goal);
  auto cur=goal;
  while(cur!=st)
  {
    path.push_back(pre[cur.X][cur.Y]);
    cur=pre[cur.X][cur.Y];
  }
  reverse(path.begin(),path.end());
  return path[1]; //다음행선지 return
} 

void cmove(int i)
{
  pair<int,int> next=cbfs(i);
  //cout<<"p1: "<<next.X<<' '<<next.Y<<'\n';
  players[i].pt=next;
  if(players[i].pt==players[i].goal)
  {
    players[i].ismove=false;
    ans++;
  }
}
//플레이어 위치와 편의점 위치가 같으면 dirty표시 
void checkdirty()
{
  for(auto cur:players)
  {
    if(cur.pt==cur.goal)arr[cur.pt.X][cur.pt.Y]=2;
  }
}
// i번째 플레이어 베이스캠프로 이동 
void bmove(int i)
{
  vector<pair<int,int>> candi;
  auto st=players[i].goal;
  queue<pair<int,int>> q;
  int dis[17][17]={0};
  dis[st.X][st.Y]=1; //시작위치 1로잡음 
  q.push(st);
  while(!q.empty())
  {
    auto cur=q.front();
    q.pop();
    for(int dir=0;dir<4;dir++)
    {
      int nx=cur.X+dx[dir];
      int ny=cur.Y+dy[dir];
      if(over(nx,ny)||dis[nx][ny]!=0||arr[nx][ny]==2)continue;
      dis[nx][ny]=dis[cur.X][cur.Y]+1;
      q.push({nx,ny});
    }
  }
  int minn=1e9;
  for(int x=1;x<=N;x++)
  {
    for(int y=1;y<=N;y++)
    {
      if(arr[x][y]!=1||dis[x][y]==0)continue;
      if(minn>=dis[x][y])
      {
        if(minn>dis[x][y])
        {
          minn=dis[x][y];
          candi.clear();
        }
        candi.push_back({x,y});
      }
    }
  }
  sort(candi.begin(),candi.end());
  //베이스캠프 이동 
  players[i].pt=candi[0];
  players[i].ismove=true;
  arr[candi[0].X][candi[0].Y]=2;

}


int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>N>>M;
  for(int i=1;i<=N;i++)
  {
    for(int j=1;j<=N;j++)cin>>arr[i][j];
  }
  int x,y;
  for(int i=0;i<M;i++)
  {
    cin>>x>>y;
    players.push_back({{0,0},{x,y},false});
  }
  int t=0; 
  while(1)
  {
    //플레이어 이동 
    for(int i=0;i<M;i++)
    {
      if(!players[i].ismove)continue;
      cmove(i); //i번째 플레이어 편의점향해 이동 
    }
    checkdirty(); 
    if(t<M)bmove(t); //t번째 플레이어 베이스캠프로 이동
    t++;
    if(ans==M)break;
  }
  cout<<t;
}


