#include<iostream>
#include<queue>
#include<algorithm>
#include<utility>
#include<cmath>
#define X first 
#define Y second
using namespace std;

int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};

int n,m,k;
int arr[11][11]; //미로 1-based 
int runner[11][11][101]; 
int ans;
pair<int,int> ex; //출구 위치 (값을 10으로지정)

bool far(pair<int,int>cur,pair<int,int>next ) //기존칸보다 가까운지 판단
{
  int a=abs(cur.X-ex.X)+abs(cur.Y-ex.Y);
  int b=abs(next.X-ex.X)+abs(next.Y-ex.Y);
  if(a<=b)return true;
  return false;
}
bool over(int x,int y)
{
  if(x<=0||x>n||y<=0||y>n)return true;
  return false;
}

void move(int t)//참가자이동
{
  
  for(int x=1;x<=n;x++)
  {
    for(int y=1;y<=n;y++)
    {
      if(!runner[x][y][t-1])continue; //없는경우 
      bool flag=false; //이동 성공 유무 플래그
      for(int dir=0;dir<4;dir++)
      {
        int nx=x+dx[dir];
        int ny=y+dy[dir];
        if(over(nx,ny))continue;
        if(arr[nx][ny]!=10&&arr[nx][ny]!=0)continue;//벽인경우 넘어감 
        if(far({x,y},{nx,ny}))continue; //멀면 스킵 
        ans+=runner[x][y][t-1];
        if(!(nx==ex.X&&ny==ex.Y)) //탈출구가 아닌경우 
        {
          runner[nx][ny][t]+=runner[x][y][t-1]; //이동 
        }
        flag=true;
        break;
      }
      if(!flag)runner[x][y][t]+=runner[x][y][t-1]; //이동실패 
    }
  }
}
bool incl(pair<int,int> st,int len,int t)
{
  int cnt=0;
  bool flag=false; //탈출구 포함여부
  for(int x=st.X;x<=st.X+len-1;x++)
  {
    for(int y=st.Y;y<=st.Y+len-1;y++)
    {
      cnt+=runner[x][y][t];
      if(x==ex.X&&y==ex.Y)flag=true;
    }
  }
  if(cnt>0&&flag)return true;
  return false;
}

void sqare(int t)
{
  //정사각형 만들기 //좌측상단 좌표구하기 +길이 정하기 
  int len=1e9; 
  pair<int,int> st={1,1};
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
    {
      for(int z=2;z<=n;z++) //정사각형길이 정하기 
      {
        if(over(i+z-1,j+z-1))continue;
        if(incl({i,j},z,t)) //가능한 경우
        {
          if(len>z)
          {
            st={i,j};
            len=z;
          }
        }
      }
    }
  }
  //cout<<"len:"<<len<<'\n';
  for(int layer=0;layer<len/2;layer++)
  {
    
    int top=st.X+layer;
    int bot=st.X+len-1-layer;
    int left=st.Y+layer;
    int right =st.Y+len-1-layer;
    vector<int> temp1; //벽
    vector<int> temp2; //도망자
    for(int i=left;i<right;i++)
    {
      temp1.push_back(arr[top][i]);
      temp2.push_back(runner[top][i][t]);
    }
    for(int i=top;i<bot;i++)
    {
      temp1.push_back(arr[i][right]);
      temp2.push_back(runner[i][right][t]);
    }
    for(int i=right;i>left;i--)
    {
      temp1.push_back(arr[bot][i]);
      temp2.push_back(runner[bot][i][t]);
    }
    for(int i=bot;i>top;i--)
    {
      temp1.push_back(arr[i][left]);
      temp2.push_back(runner[i][left][t]);
    }
    rotate(temp1.begin(),temp1.end()-len+1+2*layer,temp1.end());
    rotate(temp2.begin(),temp2.end()-len+1+2*layer,temp2.end());
    int idx=0;
    for(int i=left;i<right;i++)
    {
      arr[top][i]=temp1[idx];
      runner[top][i][t]=temp2[idx++];
    }
    for(int i=top;i<bot;i++)
    {
      arr[i][right]=temp1[idx];
      runner[i][right][t]=temp2[idx++];
    }
    for(int i=right;i>left;i--)
    {
      arr[bot][i]=temp1[idx];
      runner[bot][i][t]=temp2[idx++];
    }
    for(int i=bot;i>top;i--)
    {
      arr[i][left]=temp1[idx];
      runner[i][left][t]=temp2[idx++];
    }
  }
  //탈출구 위치 바꿔주기 
  for(int x=st.X;x<=st.X+len-1;x++)
  {
    for(int y=st.Y;y<=st.Y+len-1;y++)
    {
      if(arr[x][y]==0)continue;
      if(arr[x][y]==10)
      {
        ex.X=x;
        ex.Y=y;
        continue;
      }
      arr[x][y]--;
    }
  }
}
bool finish(int t)
{
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
      if(runner[i][j][t])return false;
  }
  return true;
}

int main()
{
 ios::sync_with_stdio(0);cin.tie(0);
 cin>>n>>m>>k;
 for(int i=1;i<=n;i++)
 {
  for(int j=1;j<=n;j++)
    cin>>arr[i][j];
 }
 int r,c;
 for(int j=0;j<m;j++)
 {
    cin>>r>>c;
    runner[r][c][0]++;
 }
 cin>>r>>c;
 ex.X=r;ex.Y=c;//탈출구 좌표 
 arr[ex.X][ex.Y]=10;//탈출구마킹
 for(int t=1;t<=k;t++)
 {
  move(t);
  if(finish(t))break;
  sqare(t);
}
cout<<ans<<'\n';
cout<<ex.X<<' '<<ex.Y<<'\n';



}