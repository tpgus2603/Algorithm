#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<utility>
#include<cstring>

#define X first 
#define Y second
using namespace std;
int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};

int arr[30][30]; //격자판
int garr[30][30]; //그룹 인덱스가담긴 격자판
vector<vector<int>> earr; //그룹끼리 맞닿는 변의수가 계산될 배열 
vector<int>gcnt;
vector<int>varr; //그룹인덱스별 값 저장 배열 
int n,ans;
bool vis[30][30];
int gidx;
bool over(int x,int y)
{
  if(x<0||x>=n||y<0||y>=n)return true;
  return false;
}
void makeGroup(int x,int y) //x,y를 시작점으로 하는 그룹 만듬 
{
  queue<pair<int,int>> q;
  garr[x][y]=gidx;
  int value=arr[x][y];
  int cnt=1;
  vis[x][y]=true;
  q.push({x,y});
  while(!q.empty())
  {
    auto cur= q.front();
    q.pop();
    for(int dir=0;dir<4;dir++)
    {
      int nx=cur.X+dx[dir];
      int ny=cur.Y+dy[dir];
      if(over(nx,ny)||arr[nx][ny]!=value||vis[nx][ny])continue;
      vis[nx][ny]=true;
      garr[nx][ny]=gidx;
      cnt++;
      q.push({nx,ny});
    }
  }
  gcnt.push_back(cnt);
  varr.push_back(value);
}

void gcount()
{
  for(int x=0;x<n;x++)
  {
    for(int y=0;y<n;y++)
    {
      int u=garr[x][y];
      for(int dir=0;dir<4;dir++)
      {
        int nx=x+dx[dir];
        int ny=y+dy[dir];
        if(over(nx,ny))continue;
        int v=garr[nx][ny];
        earr[u][v]++;
      }
    }
  }
}

void crotate() //십자가모양 회전 
{
  for(int layer=0;layer<n/2;layer++)
  {
    int top=0+layer;
    int bot=n-1-layer;
    int left=0+layer;
    int right=n-1-layer;
    int temp=arr[n/2][left];
    arr[n/2][left]=arr[top][n/2];
    arr[top][n/2]=arr[n/2][right];
    arr[n/2][right]=arr[bot][n/2];
    arr[bot][n/2]=temp;
  }
}
void srotate(int x,int y) //정사각형 시계방향 len-1-layer칸 회전 
{
  int len=n/2;
  for(int layer=0;layer<len/2;layer++)
  {
    int top=x+layer;
    int bot=x+len-1-layer;
    int left=y+layer;
    int right=y+len-1-layer;
    int rotation=len-1-layer*2;
    vector<int> temp;
    for(int i=left;i<right;i++)temp.push_back(arr[top][i]);
    for(int i=top;i<bot;i++)temp.push_back(arr[i][right]);
    for(int i=right;i>left;i--)temp.push_back(arr[bot][i]);
    for(int i=bot;i>top;i--)temp.push_back(arr[i][left]);
    rotate(temp.begin(),temp.end()-rotation,temp.end());
    int idx=0;
    for(int i=left;i<right;i++)arr[top][i]=temp[idx++];
    for(int i=top;i<bot;i++)arr[i][right]=temp[idx++];
    for(int i=right;i>left;i--)arr[bot][i]=temp[idx++];
    for(int i=bot;i>top;i--)arr[i][left]=temp[idx++];
  }
}


int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n;
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)cin>>arr[i][j];
  
  int t=4; //4번 시행 
  while(t--)
  {
    memset(vis,0,sizeof(vis));
    gidx=0;
    gcnt.clear();
    gcnt.push_back(0);
    varr.clear();
    varr.push_back(0);
    memset(garr,0,sizeof(garr));
    earr.clear();
    //그룹화 수행
    for(int x=0;x<n;x++)
    {
      for(int y=0;y<n;y++)
      {
        if(vis[x][y])continue;
        gidx++;
        makeGroup(x,y);
      }
    }
    int s=gcnt.size();
    earr.assign(s+1,vector<int>(s+1,0));
    //맞닿은 변의 수 세기
    gcount();
    //점수 계산 
    for(int i=1;i<=s;i++)
    {
      for(int j=i+1;j<=s;j++)
      {
        int u=varr[i];
        int v=varr[j];
        int temp=(gcnt[i]+gcnt[j])*u*v*earr[i][j];
        ans+=temp;
      }
    }
    //+회전 
    crotate();
    //나머지 회전
    srotate(0,0);
    srotate(0,n/2+1);
    srotate(n/2+1,0);
    srotate(n/2+1,n/2+1);
    // for(int i=0;i<n;i++)
    // {
    //   for(int j=0;j<n;j++)
    //     cout<<arr[i][j];
    //   cout<<'\n';
    // } 
  }
  cout<<ans;
}