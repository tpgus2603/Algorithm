#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstring>
#include<utility>
#define X first 
#define Y second
int dx[8]={0,1,0,-1,1,1,-1,-1};
int dy[8]={1,0,-1,0,1,-1,1,-1};

using namespace std;
int turn=1;
struct tower{
  int power;//공격력 
  int t;//공격 턴
  int x,y; 
  bool isattack;
  bool operator<(const tower&other)const{
      if(power!=other.power)return power<other.power;
      if(t!=other.t)return t>other.t;
      if((x+y)!=(other.x+other.y))return (x+y)>(other.x+other.y);
      return y>other.y;
  }
};

vector<tower> tlist;
vector<pair<int,int>>path;
int arr[11][11];
int tarr[11][11];
int N,M,K;

void sel()
{
  sort(tlist.begin(),tlist.end());
  tlist[0].power+=(N+M);
  //cout<<"sel: "<<cur.x<<' '<<cur.y<<' '<<cur.power<<'\n';
  memset(tarr,-1,sizeof(tarr));
  for(int i=0;i<tlist.size();i++)
  {
    auto cur=tlist[i];
    tarr[cur.x][cur.y]=i;
  }
  // cout<<'\n';
}

pair<int,int> pchange(int x, int y)
{
  if(x<0||x>=N||y<0||y>=M)
  {
    if(x<0)x=N-1;
    if(x>=N)x=0;
    if(y<0)y=M-1;
    if(y>=M)y=0;
  }
  return {x,y};
}

bool bfs()
{
  int len=tlist.size()-1;
  pair<int,int>st={tlist[0].x,tlist[0].y};
  pair<int,int>goal={tlist[len].x,tlist[len].y};
  pair<int,int>pre[11][11];
  bool vis[11][11]={0};
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<M;j++)pre[i][j]={-1,-1};
  }
  bool flag=false;
  queue<pair<int,int>> q;
  vis[st.X][st.Y]=true;
  q.push(st);
  while(!q.empty())
  {
    auto cur=q.front();
    q.pop();
    if(cur==goal)
    {
      flag=true;
      break;
    }
    for(int dir=0;dir<4;dir++)
    {
      int nx=cur.X+dx[dir];
      int ny=cur.Y+dy[dir];
      pair<int,int> temp=pchange(nx,ny);
      nx=temp.X;
      ny=temp.Y;
      if(arr[nx][ny]<=0||vis[nx][ny])continue;
      vis[nx][ny]=true;
      pre[nx][ny]=cur;
      q.push({nx,ny});
    }
  }
  if(flag)
  {
    path.push_back(goal);
    auto cur=goal;
    while(cur!=st)
    {
      cur=pre[cur.X][cur.Y];
      path.push_back(cur);
    }
    reverse(path.begin(),path.end());
  }
  return flag;
}
void tattack()
{
  bool flag=bfs();
  int power=tlist[0].power;
  int target=tlist.size()-1;
  //레이저 공격 
  if(flag)
  {
    //path따라 공격 타겟이면 
    for(auto cur:path)
    {
      int idx=tarr[cur.X][cur.Y];
      if(idx==0)continue;
      if(idx==target)
      {
        tlist[idx].power-=power;
      }
      else
      {
        tlist[idx].power-=(power)/2;
      }
      tlist[idx].isattack=true;
    }
  } 
  else //포탄 공격 
  {
    //8방향으로 공격 
    int x=tlist[target].x;
    int y=tlist[target].y;
    tlist[target].power-=power;
    tlist[target].isattack=true;
    for(int dir=0;dir<8;dir++)
    {
      int nx=x+dx[dir];
      int ny=y+dy[dir];
      pair<int,int>temp=pchange(nx,ny);
      int idx=tarr[temp.X][temp.Y];
      if(idx<=0)continue;
      tlist[idx].power-=power/2;
      tlist[idx].isattack=true;
    }
  }
  tlist[0].isattack=true;
  tlist[0].t=turn;
}
void tupdate()
{
  vector<tower>backup;
  for(auto cur: tlist)
  {
    if(cur.power<=0)continue;
    backup.push_back(cur);
  }
  tlist=backup;
}
void trefair()
{
  for(int i=0;i<tlist.size();i++)
  {
    auto cur=tlist[i];
    if(cur.isattack)continue;
    tlist[i].power++;
  }
  memset(arr,0,sizeof(arr));
  for(int i=0;i<tlist.size();i++)
  {
    auto cur=tlist[i];
    arr[cur.x][cur.y]=cur.power;
    tlist[i].isattack=false;
  }
  path.clear();
}


int main(){
  
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>N>>M>>K;
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<M;j++)
    {
      cin>>arr[i][j];
      if(arr[i][j]!=0)
      {
        tlist.push_back({arr[i][j],0,i,j,false});
      }
    }
  }
  while(turn<=K)
  {
    sel();//공격자 선정 
    tattack(); //공격
    tupdate(); //공격력 0인포탑들 리스트에서 제거
    trefair();//정비
    turn++;
    if(tlist.size()==1)break;
  }
  sort(tlist.begin(),tlist.end());
  cout<<tlist[tlist.size()-1].power<<'\n';
}
