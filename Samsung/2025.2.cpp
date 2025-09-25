#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<cstring>
#include<algorithm>
#include<map>
#include<set>
#define X first 
#define Y second 
using namespace std;
int N,Q;
vector<set<pair<int,int>>> group;
int arr[16][16]; //0-based
int gidx=0;
int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};

bool over(int x,int y)
{
  if(x<0||x>=N||y<0||y>=N)return true;
  return false;

}

void place(pair<int,int>st,pair<int,int>ed)
{
  set<pair<int,int>> cells;
  set<int> idxs; //침범당한 그룹인덱스모음
  //새로 들어온 미생물 배치
  for(int x=st.X;x<ed.X;x++)
  {
    for(int y=st.Y;y<ed.Y;y++)
    {
      if(arr[x][y]!=gidx&&arr[x][y]!=-1)
      {
        int t=arr[x][y];
        group[t].erase({x,y}); //그룹세포제거
        idxs.insert(t);
      }
      arr[x][y]=gidx;
      cells.insert({x,y});
    }
  }
  group.push_back(cells);
  //비울지말지 결정
  bool vis[16][16]={0}; 
  for(auto idx:idxs)
  {
      int len=group[idx].size();
      //bfs시작
      auto st=*group[idx].begin();
      queue<pair<int,int>>q;
      vis[st.X][st.Y]=true;
      q.push(st);
      int cnt=0;
      while(!q.empty())
      {
        auto cur=q.front();
        q.pop();
        cnt++;
        for(int dir=0;dir<4;dir++)
        {
          int nx=cur.X+dx[dir];
          int ny=cur.Y+dy[dir];
          if(over(nx,ny)||arr[nx][ny]!=idx||vis[nx][ny])continue;
          vis[nx][ny]=true;
          q.push({nx,ny});
        }
      }
      //두종류로 분리된것
      if(len!=cnt)group[idx].clear();
      //cout<<"cnt,len: "<<cnt<<' '<<len<<'\n';
  }
}

bool cmp(pair<int,int>a,pair<int,int> b)
{
  if(a.X==b.X)
  {
    return a.Y<b.Y;
  }
  else return a.X>b.X;
}

//해당
bool match(int x,int y,int idx)
{

  bool flag=true;
  pair<int,int>cur=*group[idx].begin();
  int xgap=cur.X-x;
  int ygap=cur.Y-y;
  for(auto pt:group[idx])
  {
    int nx=pt.X-xgap;
    int ny=pt.Y-ygap;
    if(over(nx,ny)||arr[nx][ny]!=-1)
    {
      flag=false;
      break;
    }
  }
  set<pair<int,int>>s;
  //새롭게배치
  if(flag)
  {
    for(auto pt:group[idx])
    {
      int nx=pt.X-xgap;
      int ny=pt.Y-ygap;
      arr[nx][ny]=idx;
      s.insert({nx,ny});
    }
    group[idx]=s;
  }
  return flag;
}
int calc()
{
  int len=group.size();
  vector<vector<bool>>vis(len,vector<bool>(len,0));
  int sum=0;
  for(int x=0;x<N;x++)
  {
    for(int y=0;y<N;y++)
    {
      int cur=arr[x][y];
      if(cur==-1)continue;
      for(int dir=0;dir<4;dir++)
      {
        int nx=x+dx[dir];
        int ny=y+dy[dir];
        if(over(nx,ny)||arr[nx][ny]==-1)continue;
        vis[cur][arr[nx][ny]]=true;
      }
    }
  }
  for(int i=0;i<len;i++)
  {
    for(int j=i+1;j<len;j++)
    { 
      if(!vis[i][j])continue;
      sum+=(group[i].size()*group[j].size());
    }
  }
  return sum;
}
void cmove()
{

  memset(arr,-1,sizeof(arr));
  vector<pair<int,int>> order; //사이즈,그룹인덱스
  int idx=0;
  for(auto cur:group)
  {
    order.push_back({cur.size(),idx++});
  }
  sort(order.begin(),order.end(),cmp);
  //용기이동
  for(auto t:order)
  {
    int idx=t.Y;
    if(group[idx].empty())continue;
    bool flag=false;
    for(int i=0;i<N&&!flag;i++)
    {
      for(int j=0;j<N;j++)
      {
        if(match(i,j,idx))
        {
          flag=true;
          break;
        }
      }
    }
    if(!flag)
    {
      group[idx].clear();
    }
  }
}
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>N>>Q;
  int q=Q;
  memset(arr,-1,sizeof(arr));
  while(q--)
  {
    pair<int,int>st;
    pair<int,int>ed;
    cin>>st.X>>st.Y>>ed.X>>ed.Y;
    place(st,ed);
    cmove();
    gidx++;
    int ans=calc();
    cout<<ans<<'\n';
  }
}