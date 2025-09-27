#include<iostream>
#include<vector>
#include<cstring>
#include<utility>
#include<algorithm>
#include<cmath>
#include<set>
#include<map>
#define X first 
#define Y second
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
int N,M,K;
using namespace std;
int arr[12][12]; //빈칸0 벽1 출구 -1
vector<pair<int,int>> earr; //참가자배열
bool vis[12][12]; //참가자 유뮤확인
pair<int,int> ept; //탈출구위치
int ans=0;
bool over(int x,int y)
{
  if(x<=0||x>N||y<=0||y>N)return true;
  return false;
}

int dis(int x,int y)
{
  return abs(ept.X-x)+abs(ept.Y-y);
}

void eupdate()
{
  memset(vis,0,sizeof(vis));
  for(auto cur:earr)
  {
    vis[cur.X][cur.Y]=true;
  }
}

void emove()
{
  //cout<<ept.X<<' '<<ept.Y<<'\n';
  for(int i=0;i<earr.size();i++)
  {
    auto cur=earr[i];
    for(int dir=0;dir<4;dir++)
    {
      int nx=cur.X+dx[dir];
      int ny=cur.Y+dy[dir];
      if(over(nx,ny)||dis(nx,ny)>=dis(cur.X,cur.Y)||arr[nx][ny]>=1)continue;
      earr[i]={nx,ny};
      ans++;
      break;
    }
  }
}



bool scheck(int len,pair<int,int>st)
{
  bool eflag=false;
  bool sflag=false;
  for(int x=st.X;x<st.X+len;x++)
  {
    for(int y=st.Y;y<st.Y+len;y++)
    {
      if(vis[x][y]==true)sflag=true;
      if(ept==pair<int,int>{x,y})eflag=true;
      if(eflag&&sflag)return true;
    }
  }
  return false;
}


pair<int,pair<int,int>> sfind()
{
  int slen=0;
  pair<int,int>st; 
  for(int len=2;len<=N;len++)
  {
    for(int x=1;x<=N-len+1;x++)
    {
      for(int y=1;y<=N-len+1;y++)
      {
        if(scheck(len,{x,y}))
        {
          return {len,{x,y}};        
        }
      }
    }
  }
  return {0,{0,0}};
}

//실제회전수행
void func(pair<int,int>st,int len)
{
    int tarr[16][16];
    memset(tarr,0,sizeof(tarr));
    map<pair<int,int>,pair<int,int>>mp;
    for(int x=0;x<len;x++)
    {
      for(int y=0;y<len;y++)
      {
        if(vis[x+st.X][y+st.Y])mp.insert({{x+st.X,y+st.Y},{y+st.X,len-x-1+st.Y}}); //회전된 탈출자 좌표모음
        if(arr[x+st.X][y+st.Y]>0)arr[x+st.X][y+st.Y]--;
        tarr[y+st.X][len-x-1+st.Y]=arr[x+st.X][y+st.Y];
      }
    }
    vector<pair<int,int>> backup;
    for(auto cur:earr)
    {
      if(mp.find(cur)!=mp.end())
      {
        backup.push_back({mp[cur]});
      }
      else
      {
        backup.push_back(cur);
      }
    }
    earr=backup;
    eupdate();
    for(int x=st.X;x<st.X+len;x++)
    {
      for(int y=st.Y;y<st.Y+len;y++)
      {
        if(tarr[x][y]==-1)ept={x,y};
        arr[x][y]=tarr[x][y];
      }
    }
    

}

void spin()
{
  //정사각형찾기
  int slen;
  pair<int,int>st;
  pair<int,pair<int,int>> temp=sfind();
  slen=temp.X;st=temp.Y;
  func(st,slen);
}
bool echeck()
{
  vector<pair<int,int>>backup;
  for(auto cur:earr)
  {
    if(cur==ept)continue;
    backup.push_back(cur);
  }
  earr=backup;

  return earr.empty();
}

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>N>>M>>K;
  for(int i=1;i<=N;i++)
  {
    for(int j=1;j<=N;j++)
    {
      cin>>arr[i][j]; 
    }
  }
  int r,c;
  for(int i=0;i<M;i++)
  {
    cin>>r>>c;
    earr.push_back({r,c});
    vis[r][c]=true;
  }
  cin>>r>>c;
  ept={r,c};
  arr[r][c]=-1;
  int k=K;
  while(k--)
  {
    emove();
    if(echeck())break;
    eupdate();
    spin();
  }
  cout<<ans<<'\n';
  cout<<ept.X<<' '<<ept.Y;
}