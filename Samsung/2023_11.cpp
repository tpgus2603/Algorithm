#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<utility>
#include<set>
using namespace std;
#define X first 
#define Y second 
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
struct knight{
  int r,c,h,w,k;  //k가 목숨 
};
int L,N,Q; 
int arr[45][45]; //격자판  0:빈 1:함정 2:벽  1-based
int karr[45][45]; //기사 번호 
vector<knight> klist; //기사 정보가 담긴 배열  //1-based
vector<int>damage; //기사들이 받은 데미지 누적 
vector<bool>alpush; //밀린경우 또 밀리지않게 체크  
int ans;
bool over(int x,int y) //범위를 넘어가면 그것도 벽에 막힌것 
{
  if(x<=0||x>L||y<=0||y>L)return true;
  return false;
}

void kupdate() //위치 갱신 
{
  for(int i=1;i<=N;i++)
  {
    auto cur= klist[i];
    if(cur.k<=0)continue;
    //이동하면 바뀔 좌상단 좌표
    for(int x=cur.r;x<cur.r+cur.h;x++)
    {
      for(int y=cur.c;y<cur.c+cur.w;y++)
      { 
        karr[x][y]=i;
      }
    }
  }
}

set<int> check(int n,int d)
{
  set<int> temp;
  auto cur=klist[n];
  int nx=cur.r+dx[d];
  int ny=cur.c+dy[d];
  for(int x=nx;x<nx+cur.h;x++)
  {
    for(int y=ny;y<ny+cur.w;y++)
    {
      //이동 구역에 기사가 존재하는 경우
      if(over(x,y)||arr[x][y]==2)continue;
      int t=karr[x][y];
      if(t!=n&&t>0)temp.insert(t);
    }
  }  
  return temp;
}

bool block(int n,int d) //벽에 막힌 경우  
{
  auto cur=klist[n];
  int nx=cur.r+dx[d];
  int ny=cur.c+dy[d];
  for(int x=nx;x<nx+cur.h;x++)
  {
    for(int y=ny;y<ny+cur.w;y++)
    {
      if(over(x,y)||arr[x][y]==2) return true;
    }
  }  
  return false;
}
void calc(int n,int d) //함정 카운트하고 체력 깎음 
{
  int cnt=0;
  auto cur=klist[n];
  int nx=cur.r;
  int ny=cur.c;
  for(int x=nx;x<nx+cur.h;x++)
  {
    for(int y=ny;y<ny+cur.w;y++)
    {
      if(arr[x][y]==1)cnt++;
    }
  }
  klist[n].k-=cnt; 
  damage[n]+=cnt; 
}


//top=true인 경우 이동명령 받은기사 -> 모든 노드들이 이동가능한지 체크
bool kmove(int n,int d,bool top,bool apply) //현재칸이 벽에 막히면 true 아니면 false  
{
  if(alpush[n])return false; //이미 밀린적있는경우 안밀음 
  auto cu=klist[n];
  if(cu.k<=0)return false;
  alpush[n]=true; //민 기사의 증표 
  bool flag=false; //연쇄 이동할 기사들이 벽에 막힌경우 true 
  
  //이동할 구역에 기사가 있는경우
  set<int> temp=check(n,d); 
  if (block(n, d)) return true;
  if(!temp.empty())
  {
    for(auto cur:temp)
    {
      flag=kmove(cur,d,false,apply);
      if(flag) return true;
    }
  }
  if(apply) // 실제이동 
  {
    klist[n].r+=dx[d];
    klist[n].c+=dy[d];
    //데미지 계산 (이동명령 받은 기사 제외) 
    if(!top)calc(n,d);
  }

  return false;

}


int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>L>>N>>Q;
  for(int i=1;i<=L;i++)
  {
    for(int j=1;j<=L;j++)
      cin>>arr[i][j];
  }
  klist.push_back({0,0,0,0,0});
  for(int i=1;i<=N;i++)
  {
    int r,c,h,w,k;
    cin>>r>>c>>h>>w>>k;
    klist.push_back({r,c,h,w,k});
  }
  int n,d;
  damage.assign(N+1,0);
  memset(karr,0,sizeof(karr));
  kupdate();
  while(Q--)
  {
    cin>>n>>d;
    alpush.assign(N+1,0);
    //1.기사 이동
    bool flag=kmove(n,d,true,false); //벽에막히면 flag=true;
    alpush.assign(N+1,0);
    kmove(n,d,true,!flag);
    //2.기사 업데이트
    memset(karr,0,sizeof(karr));
    kupdate();
  }
  for(int i=1;i<=N;i++)
  {
    if(klist[i].k<=0)continue;
    ans+=damage[i];
  }
  cout<<ans;



}