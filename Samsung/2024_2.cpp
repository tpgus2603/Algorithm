#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};

struct gol{ //중앙 점의 좌표와 출구 위치 
  int x,y,d;
};
int R,C,K,ans;
int arr[72][72];//1-based
using namespace std;
vector<gol>glist;

bool over(int x,int y)
{
  if(x<=0||x>R||y<=0||y>C)return true;
  return false;
}

bool sover(int x,int y)
{
  if(x>R||y>C||y<=0)return true;
  else if(x>0&&arr[x][y]!=0)return true;
  return false;
}

//이동가능한지체크
bool gcheck(int n,int dir)
{
  auto cur=glist[n];
  int x=cur.x+dx[dir];
  int y=cur.y+dy[dir];
  for(int i=-1;i<=1;i++)
  {
    int d=dir+i;
    if(d<0)d=3;
    if(d>3)d=0;
    int nx=x+dx[d];
    int ny=y+dy[d];
    if(sover(nx,ny))return false;
  }
  return true;
}

//n번째 골렘 배치 
bool gmove(int n)
{
  //남쪽 한칸 이동 가능한지 확인
  bool flag2=false;
  if(gcheck(n,2))
  {
    glist[n].x+=dx[2];
    glist[n].y+=dy[2];
    flag2=true;
  }else if(gcheck(n,3)) //서쪽으로 
  {
    int x=glist[n].x+dx[3]+dx[2];
    int y=glist[n].y+dy[3]+dy[2];
    bool flag=true;
    int nx=x+dx[2];
    int ny=y+dy[2];
    if(sover(nx,ny))flag=false;
    nx=x+dx[3];
    ny=y+dy[3];
    if(sover(nx,ny))flag=false;

    if(flag) //이동가능  
    {
      glist[n].x=x;
      glist[n].y=y;
      glist[n].d-=1;
      if(glist[n].d<0)glist[n].d=3;
      flag2=true;
    }
  }
  if(!flag2)
  {
    if(gcheck(n,1)) //동쪽 
    {
      int x=glist[n].x+dx[1]+dx[2];
      int y=glist[n].y+dy[1]+dy[2];
      bool flag=true;
      int nx=x+dx[2];
      int ny=y+dy[2];
      if(sover(nx,ny))flag=false;
      nx=x+dx[1];
      ny=y+dy[1];
      if(sover(nx,ny))flag=false;
      if(flag) //이동가능  
      {
        glist[n].x=x;
        glist[n].y=y;
        glist[n].d+=1;
        if(glist[n].d>3)glist[n].d=0;
        flag2=true;
      }
    }
  }
  return flag2;
}
bool gupdate(int n)
{
  auto cur= glist[n];
  if(over(cur.x,cur.y))
  {
    memset(arr,0,sizeof(arr));
    return true; 
  }
  arr[cur.x][cur.y]=n;
  for(int dir=0;dir<4;dir++)
  {
    int nx=cur.x+dx[dir];
    int ny=cur.y+dy[dir];
    //골렘몸이 삐져나오는경우 :필드 리셋
    if(over(nx,ny))
    {
      memset(arr,0,sizeof(arr));
      return true;
    }
    arr[nx][ny]=n;
  }
  return false;
}
int cnt;
vector<bool> vis;
void func(int n) //현재 정령 위치에서 최대한 남쪽으로 이동시도 by dfs
{
  if(vis[n])return;
  vis[n]=true;
  auto cur=glist[n];
  cnt=max(cnt,cur.x+1);
  //출구 좌표 (x,y)
  int x=cur.x+dx[cur.d];
  int y=cur.y+dy[cur.d];
  for(int dir=0;dir<4;dir++)
  {
    int nx=x+dx[dir];
    int ny=y+dy[dir];
    if(over(nx,ny)||arr[nx][ny]==0)continue;
    func(arr[nx][ny]);
  }
}

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>R>>C>>K;
  glist.push_back({0,0,0});
  int c,d;
  for(int i=0;i<K;i++)
  {
    cin>>c>>d;
    glist.push_back({-1,c,d});
  }
  //K개의 골렘 배치
  int n=1;
  int k=K; 
  while(k--)
  {
    cnt=0;
    while(gmove(n));
    bool flag =gupdate(n);//격자에 반영
    vis.assign(K+1,0);
    if(!flag)func(n); //정령을 골렘끝까지 이동   
    n++;
    ans+=cnt;
  }
  cout<<ans;



}