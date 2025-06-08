#include<bits/stdc++.h>

using namespace std;

int k,ans;
int yellow[6][4];
int red[6][4];
int shape[4][2][2]=
  {
     {},
      {
        {1,0},
        {0,0}
      },
      {
        {1,1},
        {0,0}
      },
      {
        {1,0},
        {1,0}
      }
  };
bool yelscore() 
{
  //행에 대해서 수행 
  for(int r=5;r>=0;r--)
  { 
    bool flag=true;
    for(int c=0;c<=3;c++)
    {
      if(yellow[r][c]==0)
      {
        flag=false;
        break;
      }
    }
    if(flag)
    {
      ans++;
      //한칸씩 위에서 아래로 
      for(int i=r;i>=1;i--) 
      {
        for(int j=0;j<=3;j++ )
        {
          yellow[i][j]=yellow[i-1][j];
        }
      }
      for(int j=0;j<=3;j++)
        yellow[0][j]=0;
      return true;
    }
  }
  return false;
}
bool redscore() 
{
  //행에 대해서 수행 
  for(int r=5;r>=0;r--)
  { 
    bool flag=true;
    for(int c=0;c<=3;c++)
    {
      if(red[r][c]==0)
      {
        flag=false;
        break;
      }
    }
    if(flag)
    {
      ans++;
      //한칸씩 위에서 아래로 
      for(int i=r;i>=1;i--)
      {
        for(int j=0;j<=3;j++ )
        {
          red[i][j]=red[i-1][j];
        }
      }
      for(int j=0;j<=3;j++)
        red[0][j]=0;
      return true;
    }
  }
  return false;
}
bool over(int nx,int ny)
{
  if(nx<0||nx>=6||ny<0||ny>=6)return true;
  return false;
}
void move(int cnt,int color) //yellow 면 0 red면 1
{
  for(int i=5;i>=0;i--)
  {
    for(int j=0;j<4;j++)
    {
      if(color==0)
      {
        if(i>=2)yellow[i][j]=yellow[i-cnt][j];
        else yellow[i][j]=0;
      }
      else
      {
        if(i>=2)red[i][j]=red[i-cnt][j];
        else red[i][j]=0;
      }
    }
  }

}

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>k;
  while(k--)
  {
    int t,x,y;
    cin>>t>>x>>y;
    //yellow배치
    auto tile= shape[t];
    int ax=0;
    for(int i=0;i<6;i++) //배치 시작 x좌표  
    {
      bool flag=true;
      for(int dx=0;dx<2;dx++)
      {
        for(int dy=0;dy<2;dy++)
        {
          int nx=i+dx;int ny=y+dy;
          if(tile[dx][dy]&&over(nx,ny))flag=false; //범위 넘어간경우 
          if(tile[dx][dy]&&yellow[nx][ny])flag=false; //이미 놓여있는경우 
        }
      }
      if(flag)ax=i;
      else break;
    }
    for(int dx=0;dx<2;dx++)
    {
      for(int dy=0;dy<2;dy++)
      {
        int nx=ax+dx;int ny=y+dy;
        if(tile[dx][dy]==1)yellow[nx][ny]=1;
      }
    }
    //red배치
    if(t==3)t=2;
    else if(t==2)t=3;
    tile= shape[t];
    ax=0;
    for(int i=0;i<6;i++) //배치 시작 x좌표  
    {
      bool flag=true;
      for(int dx=0;dx<2;dx++)
      {
        for(int dy=0;dy<2;dy++)
        {
          int nx=i+dx;int ny=x+dy;
          if(tile[dx][dy]&&over(nx,ny))flag=false;
          if(tile[dx][dy]==1&&red[nx][ny]==1)flag=false;
        }
      }
      if(flag)ax=i;
      else break;
    }
    for(int dx=0;dx<2;dx++)
      {
        for(int dy=0;dy<2;dy++)
        {
          int nx=ax+dx;int ny=x+dy;
          if(tile[dx][dy]==1)red[nx][ny]=1;
        }
      }
    while(yelscore());
    while(redscore());
    //연한 영역 처리 x범위 0~1 
    //제거될 행의 개수 새기
    int cnt=0; 
    for(int i=0;i<2;i++)
    {
      for(int j=0;j<4;j++)
      {
        if(yellow[i][j]==1)
        {
          cnt++;
          break;
        }
      }
    }
    if(cnt>0)move(cnt,0);
    cnt=0;
    for(int i=0;i<2;i++)
    {
      for(int j=0;j<4;j++)
      {
        if(red[i][j]==1)
        {
          cnt++;
          break;
        }
      }
    }
    if(cnt>0)move(cnt,1);
    while(yelscore());
    while(redscore());

    // cout<<"k: "<<k<<'\n';
    // for(int i=0;i<6;i++)
    // {
    //   for(int j=0;j<4;j++)
    //   {
    //     cout<<yellow[i][j]<<' ';
    //   }
    //   cout<<'\n';
    // }
  }
  int cnt=0;
  for(int i=0;i<6;i++)
  {
    for(int j=0;j<4;j++)
    {
      if(yellow[i][j])cnt++;
      if(red[i][j])cnt++;
      //cout<<yellow[i][j]<<' ';
    }
    //cout<<'\n';
  }
  cout<<ans<<'\n'<<cnt;

}