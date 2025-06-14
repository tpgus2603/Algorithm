#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
#define X first 
#define Y second 

int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};
int n;
int arr[29][29];
int idx; //그룹 인덱스
int group[29][29];
vector<vector<pair<int,int>>> garr; //그룹별 좌표모음집 
long long ans;

bool over(int x,int y)
{
  if(x<0||x>=n||y<0||y>=n)return true;
  return false;
}
void init()
{
  idx=0;
  for(int i=0;i<n;i++)
  {
    fill(group[i],group[i]+n,0);
  }
  garr.clear();

}
void makegroup() //bfs돌면서 그룹 형성 (group벡터 및 배열 생성)
{
  vector<vector<bool>>vis(n,vector<bool>(n,false));
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      if(vis[i][j])continue;
      vis[i][j]=true;
      queue<pair<int,int>> q;
      vector<pair<int,int>> g;
      g.push_back({i,j});
      q.push({i,j});
      group[i][j]=idx;
      int temp=arr[i][j];
      while(!q.empty())
      {
        auto cur=q.front();
        q.pop();
        for(int dir=0;dir<4;dir++)
        {
          int nx=cur.X+dx[dir];
          int ny=cur.Y+dy[dir];
          if(over(nx,ny)||arr[nx][ny]!=temp||vis[nx][ny])continue;
          group[nx][ny]=idx;
          g.push_back({nx,ny});
          vis[nx][ny]=true;
          q.push({nx,ny});
        }
      }
      idx++;
      garr.push_back(g);
    }
  }
}
void getscore()
{
  vector<vector<int>> narr(idx,vector<int>(idx,0)); //이웃 그룹의수 [i][j]-> i그릅과 j그룹 변숫자   
  for(int i=0;i<idx;i++)
  {
    for(auto cur:garr[i]) //i그룹 
    {
      //cout<<i<<' '<<cur.X<<'\n';
      for(int dir=0;dir<4;dir++)
      {
        int nx=cur.X+dx[dir];
        int ny=cur.Y+dy[dir];
        if(over(nx,ny))continue;
        int temp=group[nx][ny]; //temp그룹인덱스 
        // cout<<i<<' '<<temp<<'\n';
        //cout<<nx<<' '<<ny<<'\n';
        narr[i][temp]++;
      }
    }
  }
  long long score;
  for(int i=0;i<idx;i++) //i그룹 
  {
    score=0;
    for(int j=i+1;j<idx;j++) //j그룹 
    {
      if(!narr[i][j])continue;
      int a=arr[garr[i][0].X][garr[i][0].Y];
      int b=arr[garr[j][0].X][garr[j][0].Y];
      score=(a*b)*(garr[i].size()+garr[j].size())*(narr[i][j]);
      //cout<<i<<' '<<j<<' '<<score<<'\n';
      ans+=score;
    }
  }
}
void cross()
{
  for(int layer=0;layer<n/2;layer++)
  {
    int temp=arr[n/2][layer];
    arr[n/2][layer]=arr[layer][n/2];
    arr[layer][n/2]=arr[n/2][n-1-layer];
    arr[n/2][n-1-layer]=arr[n-1-layer][n/2];
    arr[n-1-layer][n/2]=temp;
  }
}

void rota(pair<int,int>st) //십자가 영역제외 90도 시계방향 회전
{
  int len=n/2; // 가로세로길이 
  pair<int,int> ed={st.X+len-1,st.Y+len-1};
  for(int layer=0;layer<len/2;layer++)
  {
    pair<int,int> s={st.X+layer,st.Y+layer};
    pair<int,int> e={ed.X-layer,ed.Y-layer};
    vector<int> temp;
    //끝칸 비워두고 하기 
    for(int i=s.Y;i<e.Y;i++)
      temp.push_back(arr[s.X][i]);
    for(int i=s.X;i<e.X;i++)
      temp.push_back(arr[i][e.Y]);
    for(int i=e.Y;i>s.Y;i--)
      temp.push_back(arr[e.X][i]);
    for(int i=e.X;i>s.X;i--)
      temp.push_back(arr[i][s.Y]);
    //시계방향 len-1-2*layer칸 회전 
    rotate(temp.begin(),temp.end()-len+1+2*layer,temp.end());
      //끝칸 비워두고 채우기
    int cnt=0;
    for(int i=s.Y;i<e.Y;i++)
      arr[s.X][i]=temp[cnt++];
    for(int i=s.X;i<e.X;i++)
      arr[i][e.Y]=temp[cnt++];
    for(int i=e.Y;i>s.Y;i--)
      arr[e.X][i]=temp[cnt++];
    for(int i=e.X;i>s.X;i--)
      arr[i][s.Y]=temp[cnt++];
  }
}

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
      cin>>arr[i][j];
  }
  int t=4;
  while(t--)
  {
    init();
    makegroup();
    //cout<<idx<<'\n';
    getscore();
    int len=n/2;
    rota({0,0});
    rota({0,len+1});
    rota({len+1,0});
    rota({len+1,len+1});
    
    cross();
  }

  cout<<ans;
}