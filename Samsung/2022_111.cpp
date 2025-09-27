#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>

#define X first 
#define Y second
using namespace std;
struct player{
  //좌표,방향,스탯,총공격력
  int x,y,d,s,g;

  bool operator<(const player&other) const{
    if(x!=other.x)return x<other.x;
    if(y!=other.y)return y<other.y;
    if(s!=other.s)return s<other.s;
    if(g!=other.g)return g<other.g;
    return d<other.d;
  }
};
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
int N,M,K;
vector<player> players; //1-based
vector<int> scores;//1-based;
int parr[22][22]; //1-baesd 플레이어 배열(값이 0이면 없음 1부터는 플레이어번호)
map<int,int> garr[22][22]; //1-based 총공격력,개수가 담긴 map배열 


bool over(int x,int y)
{
  if(x<=0||x>N||y<=0||y>N)return true;
  return false;
}

//플레이어 배열 갱신 
void pupdate()
{
  memset(parr,0,sizeof(parr));
  for(int i=1;i<=M;i++)
  {
    auto cur=players[i];
    parr[cur.x][cur.y]=i;
  }
}

int dchange(int dir)
{
  switch(dir)
  {
    case 0:return 2;
    case 2:return 0;
    case 1:return 3;
    case 3:return 1;
  }
  return -1;
}
//플레이어 한명 이동하면서 플레이어 배열은 업데이트해주기 (직접 )
void pmove(int i,bool lose)
{
  auto cur=players[i];
  int nx=cur.x+dx[cur.d];
  int ny=cur.y+dy[cur.d];
  if(over(nx,ny)) //진 플레이어면 안일어남
  {
    players[i].d=dchange(players[i].d);
    nx=cur.x+dx[players[i].d];
    ny=cur.y+dy[players[i].d];
  }
  if(!lose)parr[cur.x][cur.y]=0;
  players[i].x=nx;
  players[i].y=ny;
  //cout<<"p1"<<' '<<cur.x<<' '<<cur.y<<' '<<nx<<' '<<ny<<'\n';
  //이동 칸에 플레이어 없는 경우 총 있는지확인  
  if(parr[nx][ny]==0)
  {
    parr[nx][ny]=i;
    int cgun=players[i].g;
    if(!garr[nx][ny].empty())
    {
      auto temp=*garr[nx][ny].rbegin();//가장 공격력 높은 총 
      int tgun=temp.X;
      if(tgun>cgun) //총 공격력이 더 강하면 주움
      {
        garr[nx][ny][tgun]--;
        if(garr[nx][ny][tgun]==0)garr[nx][ny].erase(tgun);
        players[i].g=tgun;
        if(cgun>0)garr[nx][ny][cgun]++;
      }
    }
  }
  else//플레이어 있는경우  싸움 
  {
    int idx=parr[nx][ny];
    int p1=players[i].g+players[i].s;
    int p2=players[idx].g+players[idx].s;
    int loser,winner;
    if(p1>p2)
    {
      winner=i;
      loser=idx;
    }
    else if(p2>p1)
    {
      winner=idx;
      loser=i;
    }
    else{
      if(players[i].s>players[idx].s)
      {
        winner=i;
        loser=idx;
      }
      else 
      {
        winner=idx;
        loser=i;
      }
    }
    parr[nx][ny]=winner;
    //진 플레이어 총 내려놓음
    int lgun=players[loser].g;
    players[loser].g=0;
    if(lgun>0)garr[nx][ny][lgun]++;
    for(int dir=0;dir<4;dir++)
    {
      int x=players[loser].x;
      int y=players[loser].y;
      int ndir=players[loser].d+dir;
      if(ndir>3)ndir-=4;
      int nnx=x+dx[ndir];
      int nny=y+dy[ndir];
      if(over(nnx,nny)||parr[nnx][nny]!=0)continue;
      players[loser].d=ndir;
      pmove(loser,true);//한칸 이동시킴 
      break;
    }
    //이긴 플레이어 가장 공격력 높은 총 획득
    scores[winner]+=abs(p1-p2);
    if(!garr[nx][ny].empty())
    {
      int wgun=players[winner].g;
      int temp=(*garr[nx][ny].rbegin()).X;
      if(temp>wgun)
      {
        garr[nx][ny][temp]--;
        if(garr[nx][ny][temp]==0)garr[nx][ny].erase(temp);
        players[winner].g=temp;
        if(wgun>0)garr[nx][ny][wgun]++;
      }
    }
  }

}


int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>N>>M>>K;
  for(int i=1;i<=N;i++)
  {
    for(int j=1;j<=N;j++)
    {
      int g;
      cin>>g;
      if(g!=0)garr[i][j][g]++;
    }
  }
  players.assign(M+1,{0,0,0,0,0});
  scores.assign(M+1,0);
  for(int i=1;i<=M;i++)
    cin>>players[i].x>>players[i].y>>players[i].d>>players[i].s;
  int k=K;
  pupdate();
  while(k--)
  {
    for(int i=1;i<=M;i++)
    {
      pmove(i,false);
    }
    // for(int i=1;i<=M;i++)
    //   cout<<"pt: "<<players[i].x<<' '<<players[i].y<<'\n';
    // cout<<'\n';
  }
  for(int i=1;i<=M;i++)
  {
    cout<<scores[i];
    if(i!=M)cout<<' ';
  }

}

