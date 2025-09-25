#include<iostream>
#include<utility>
#include<tuple>
#include<vector>
#include<algorithm>
#define X first
#define Y second

using namespace std;
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int sdir=0; //술래 방향 
bool cdir=true ;// 술래이동이 시계방향인지 아닌지 
pair<int,int> cur ;// 술래 위치
vector<tuple<int,int,int>> earr ;//도망자 위치,방향 배열
int n,m,h,k,turn;
bool tree[102][102]; //1-based

int scnt; //방향 전환전 술래가 이동한 횟수 
int dcnt; //방향 전환전 해당 방향으로 일직선으로 몇번 갔는지 2번부터 1증가 2가되면 dgoal 증가 
int dgoal=1;//scnt값이 dgoal이 되면 방향전환   
int ans=0;

bool calc(int x,int y) //술래와 거리가 3초과면 true
{
  int dis= abs(cur.X-x)+abs(cur.Y-y);
  if(dis>3) return true;
  return false;
}
bool over(int x,int y) //술래가 있거나 격자넘어감
{
  if(x<=0||x>n||y<=0||y>n)return true;
  return false;
}
bool isSeek(int x,int y)
{
  if(cur ==pair<int,int>{x,y})return true;
  return false;
}

int echange(int dir)
{
  switch(dir)
  {
    case 1:return 3;
    case 3:return 1;
    case 0:return 2;
    case 2:return 0;
    default: return -1;
  }
}
void emove()
{
  vector<tuple<int,int,int>>tarr;
  for(auto t:earr)
  {
    int x,y,dir;
    tie(x,y,dir)=t;
    if(calc(x,y))
    {
      tarr.push_back(t);
      continue; //거리3초과면
    }
    int nx=x+dx[dir];
    int ny=y+dy[dir];
    if(isSeek(nx,ny))
    {
      tarr.push_back(t);
      continue;
    }
    if(over(nx,ny))
    {
      dir=echange(dir);
      nx=x+dx[dir];
      ny=y+dy[dir];
    }
    if(isSeek(nx,ny))tarr.push_back(t);
    else tarr.push_back({nx,ny,dir});
  }
  earr=tarr;
}



//술래  회전  
void sswitch() 
{
  if(cdir)
  {
    sdir++;
    if(sdir>3)sdir=0;
  }
  else
  {
    sdir--;
    if(sdir<0)sdir=3;
  }
}
void smove()
{
  int nx=cur.X+dx[sdir];
  int ny=cur.Y+dy[sdir];
  cur={nx,ny};
  scnt++;
  if(nx==1&&ny==1) // 끝지점 도달한경우
  {
    scnt=0;
    dcnt=0;
    dgoal=n-1;
    cdir=false;
    sdir=2;
  }
  if(nx==n/2+1&&ny==n/2+1)
  {
    scnt=0;
    dcnt=0;
    dgoal=1;
    cdir=true;
    sdir=0;
  }
}
void schange()
{
  if(scnt==dgoal) //이동횟수 채운경우 
  {
    sswitch();
    scnt=0;
    dcnt++;
    if(cdir)
    {
      if(dgoal!=n-1&&dcnt==2) //2번 이동시 1증가
      {
        dgoal++;
        dcnt=0;
      }
      else if(dgoal==n-1&&dcnt==3) //3번 이동시 1증가
      {
        dgoal++;
        dcnt=0;
      }
    }
    else
    {
      if(dgoal!=n-1&&dcnt==2) //2번 이동시 1감소
      {
        dgoal--;
        dcnt=0;
      }
      else if(dgoal==n-1&&dcnt==3) 
      {
        dgoal--;
        dcnt=0;
      }
    }
  }
}
//3칸 잡기 
void scatch()
{
  pair<int,int> sight=cur;
  int prev=earr.size(); 
  for(int i=0;i<3;i++)
  {
    vector<tuple<int,int,int>>tarr;
    if(i!=0)
    {
      int nx=sight.X+dx[sdir];
      int ny=sight.Y+dy[sdir];
      sight={nx,ny};
    }
    //나무에 가린경우
    if(tree[sight.X][sight.Y])continue;
    for(auto t: earr)
    {
      int x,y,d;
      tie(x,y,d)=t;
      if(sight==pair<int,int>{x,y})continue;
      tarr.push_back(t);
    }
    earr=tarr;
  }
  int next=earr.size();
  ans+=turn*(prev-next);
}


int main()
{ 
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n>>m>>h>>k;
  for(int i=0;i<m;i++)
  {
    int x,y,d;
    cin>>x>>y>>d;
    earr.push_back({x,y,d});
  }
  for(int i=0;i<h;i++)
  {
    int x,y;
    cin>>x>>y;
    tree[x][y]=true;
  }
  cur={n/2+1,n/2+1};
  while(turn++<k)
  {

    //cout<<cur.X<<' '<<cur.Y<<'\n';

    //1. 도망자 이동
    emove();
    // for(auto t: earr)
    // {
    //   int x,y,d;
    //   tie(x,y,d)=t;
    //   cout<<x<<' '<<y<<' '<<d<<'\n';
    // }
    //2. 술래 이동
    smove();
    //cout<<cur.X<<' '<<cur.Y<<'\n';
    
    //3..술래 방향 결정
    schange();
    

    // //4..도망자잡기
     scatch();

  }
  cout<<ans;


}