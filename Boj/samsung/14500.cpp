#include<iostream>

using namespace std;

//ㅗ 모양 
int mask[4][3][3]=
{
  {{1,1,1},
  {0,1,0},
  {0,0,0}},
  {{1,0,0},
  {1,1,0},
  {1,0,0}},
  {{0,1,0},
  {1,1,1},
  {0,0,0}},
  {{0,1,0},
  {1,1,0},
  {0,1,0}},
};
int n,m;
int arr[502][502];
int ans;
bool vis[502][502];
int dx[4]={0,1,0,-1};
int dy[4]={-1,0,1,0};

bool over(int x,int y)
{
  if(x<0||x>=n||y<0||y>=m)return true;
  return false;
}

void func(int x,int y,int depth,int sum)
{

  if(depth==4)
  {
    ans=max(ans,sum);
    return;
  }
  for(int dir=0;dir<4;dir++)
  {
    int nx=x+dx[dir];
    int ny=y+dy[dir];
    if(over(nx,ny)||vis[nx][ny])continue;
    vis[nx][ny]=true;
    func(nx,ny,depth+1,sum+arr[nx][ny]);
    vis[nx][ny]=false;
  }
}

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n>>m;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
    {
      cin>>arr[i][j];
    }
  }
  //모든 칸에서 4칸씩 dfs
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
    {
      vis[i][j]=true;
      func(i,j,1,arr[i][j]);
      vis[i][j]=false;
    }
  }
  //ㅗ모양에 대해 검증
  for(int x=0;x<n;x++)
  {
    for(int y=0;y<m;y++)
    {
      for(int k=0;k<4;k++)
      {
        int temp=0;
        for(int i=0;i<3;i++)
        {
          for(int j=0;j<3;j++)
          {
            if(mask[k][i][j]==0)continue;
            if(over(x+i,y+j)){
              temp=0;
              break;
            }
            temp+=arr[x+i][y+j];
          }
        }
        ans=max(temp,ans);
      }  
    }
  }
  cout<<ans;

}