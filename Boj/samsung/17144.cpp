#include<iostream>
#include<utility>
#include<vector>

#define X first 
#define Y second 
using namespace std;


int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
int R,C,T;
vector<pair<int,int>> air; //

bool over(int x,int y)
{
  if(x<0||x>=R||y<0||y>=C)return true;
  if(x==air[0].X&&y==air[0].Y)return true;
  if(x==air[1].X&&y==air[1].Y)return true;
  return false;
}

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>R>>C>>T;
  vector<vector<int>> arr(R,vector<int>(C,0));
  for(int i=0;i<R;i++)
  {
    for(int j=0;j<C;j++)
    {
      cin>>arr[i][j];
      if(arr[i][j]==-1) air.push_back({i,j});
    }
  }

  //확산 
  while(T--)
  {
    vector<vector<int>> temp(R,vector<int>(C,0));
    temp=arr;
    for(int x=0;x<R;x++)
    {
      for(int y=0;y<C;y++)
      {
        if(over(x,y))continue;
        //미세먼지칸인경우 시행x
        int k=arr[x][y]/5; //확산값
        for(int dir=0;dir<4;dir++)
        {
          int nx=x+dx[dir];
          int ny=y+dy[dir];
          if(over(nx,ny))continue;
          temp[nx][ny]+=k;
          temp[x][y]-=k;
        }
      }
    }

    arr=temp;
    // for(int i=0;i<R;i++)
    // {
    //   for(int j=0;j<C;j++)
    //     cout<<arr[i][j]<<' ';
    //   cout<<'\n';
    // }
    //위 air[0]기준 반시계 이동 
    int left=air[0].Y;
    int right=C-1;
    int top=0;
    int bot=air[0].X;
    for(int x=bot-1;x>top;x--)arr[x][left]=arr[x-1][left];
    for(int y=left;y<right;y++)arr[0][y]=arr[0][y+1];
    for(int x=top;x<bot;x++)arr[x][right]=arr[x+1][right];
    for(int y=right;y>left+1;y--)arr[bot][y]=arr[bot][y-1];
    arr[bot][left+1]=0;
    //아래기준 시계이동
    top=air[1].X;
    bot=R-1;
    for(int x=top+1;x<bot;x++)arr[x][left]=arr[x+1][left];
    for(int y=left;y<right;y++)arr[bot][y]=arr[bot][y+1];
    for(int x=bot;x>top;x--)arr[x][right]=arr[x-1][right];
    for(int y=right;y>left+1;y--)arr[top][y]=arr[top][y-1];
    arr[top][left+1]=0;
    // for(int i=0;i<R;i++)
    // {
    //   for(int j=0;j<C;j++)
    //     cout<<arr[i][j]<<' ';
    //   cout<<'\n';
    // }
  }
  int ans=0;
  for(int i=0;i<R;i++)
    for(int j=0;j<C;j++)ans+=arr[i][j];
  cout<<ans+2;
      
  
}