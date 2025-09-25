#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
#include<utility>
#include<set>
#include<queue>
#include<tuple>
#define X first 
#define Y second
#define B first 
#define F second
using namespace std;

pair<int,string> arr[52][52]; //학생들 
int N,T; //T일 만큼 시행 
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
void breakfast()
{
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<N;j++) arr[i][j].B++;
  }
}
vector<pair<int,int>> candi;
int group[52][52]; //특정좌표가 무슨 그룹인지 담김  
//bfs기바능로 그룹화하기 
bool over(int x,int y)
{
  if(x<0||x>=N||y<0||y>=N)return true;
  return false;
}
//그룹화 하면서 대표자 선출 
void make_group()
{
  int gidx=0;
  candi.clear();
  memset(group,-1,sizeof(group));
  bool vis[52][52]={0};
  for(int x=0;x<N;x++)
  {
    for(int y=0;y<N;y++)
    {
      vector<tuple<int,int,int>>path; //신앙심*-1,x,y좌표
      int cnt=0;
      if(vis[x][y])continue;
      vis[x][y]=true;
      queue<pair<int,int>> q;
      q.push({x,y});
      string f=arr[x][y].F;
      path.push_back({arr[x][y].B*-1,x,y});
      group[x][y]=gidx;
      while(!q.empty())
      {
        auto cur=q.front();
        cnt++;
        arr[cur.X][cur.Y].B--; //신앙심 1감소시킴
        q.pop();
        for(int dir=0;dir<4;dir++)
        { 
          int nx=cur.X+dx[dir];
          int ny=cur.Y+dy[dir];
          if(over(nx,ny)||arr[nx][ny].F!=f||vis[nx][ny])continue;
          vis[nx][ny]=true;
          group[nx][ny]=gidx;
          q.push({nx,ny});
          path.push_back({arr[nx][ny].B*-1,nx,ny});
        }
      }
      gidx++;
      sort(path.begin(),path.end());
      int b,r,c;
      tie(b,r,c)=path[0];
      candi.push_back({r,c});
      arr[r][c].B+=cnt; //대표자 신앙심 더해주기 
    }
  }
}

bool cmp(pair<int,int> a,pair<int,int>b)
{
  int alen=arr[a.X][a.Y].F.length();
  int blen=arr[b.X][b.Y].F.length();
  int ab=arr[a.X][a.Y].B;
  int bb=arr[b.X][b.Y].B;
  if(alen==blen) //음식길이가 같은경우 
  {
    if(ab==bb)return a<b;
    else return ab>bb;
  }
  else return alen<blen;
}
void dinner()
{
  sort(candi.begin(),candi.end(),cmp);
  bool vis[52][52]={0};
  // for(int i=0;i<N;i++)
  // {
  //     for(int j=0;j<N;j++)cout<<arr[i][j].B<<' ';
  //     cout<<'\n';
  // }
  //전파
  // for(auto cur: candi)
  // {
  //   cout<<cur.X+1<<' '<<cur.Y+1<<'\n';
  // }
  // cout<<'\n';
  for(auto cur:candi)
  {
    if(vis[cur.X][cur.Y])continue;
    int x=arr[cur.X][cur.Y].B-1;
    arr[cur.X][cur.Y].B=1;
    auto f=arr[cur.X][cur.Y].F;
    //격자 밖orx=0이하되면 탈출
    int dir=(x+1)%4;
    while(x>0)
    {
      int nx=cur.X+dx[dir];
      int ny=cur.Y+dy[dir];
      if(over(nx,ny))break;
      cur={nx,ny};
      if(arr[nx][ny].F==f)continue;
      vis[nx][ny]=true;
      int y=arr[nx][ny].B;
      //강한전파
      if(x>y)
      { 
        arr[nx][ny].F=f;
        arr[nx][ny].B++;
        x-=(y+1);
      }
      else
      {
        //전파자 음식결정 
        set<char> s;
        string food="";
        for(auto c:f)
        {
          s.insert(c);
        }
        for(auto c:arr[nx][ny].F)
        {
          s.insert(c);
        }
        for(auto c:s)
        {
          food+=c;
        }
        //신앙심
        arr[nx][ny].B+=x;
        arr[nx][ny].F=food;
        x=0;
      }
    }
    //   for(int i=0;i<N;i++)
    // {
    //     for(int j=0;j<N;j++)cout<<arr[i][j].B<<' ';
    //     cout<<'\n';
    // }
    // cout<<'\n';
  }
}
void calc()
{
  vector<int> sum(7,0);
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
          auto f=arr[i][j].F;
          auto b=arr[i][j].B;
          if(f=="CMT")sum[0]+=b;
          else if(f=="CT")sum[1]+=b;
          else if(f=="MT")sum[2]+=b;
          else if(f=="CM")sum[3]+=b;
          else if(f=="M")sum[4]+=b;
          else if(f=="C")sum[5]+=b;
          else sum[6]+=b;
        }
    }
    for(auto c:sum)
    {
      cout<<c<<' ';
    }
    cout<<'\n';
}

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>N>>T;
  string temp;
  for(int i=0;i<N;i++)
  {
    cin>>temp;
    for(int j=0;j<N;j++) arr[i][j]={0,string(1,temp[j])};
  }
  int b;
  for(int i=0;i<N;i++)
  {
    for(int j=0;j<N;j++)
    {
      cin>>b;
      arr[i][j].B=b;
    }
  }
  int t=T;
  while(t--)
  {
    //1.아침
    breakfast();

    //2.점심시간
    make_group();
    //3.저녁시간 
    dinner();

    //4.출력
    calc();

  }


}