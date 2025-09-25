#include<iostream>
#include<queue>
#include<utility>
#include<vector>
#include<algorithm>
#define X first
#define Y second
using namespace std;
int dx[4]={0,0,-1,1}; //동서북남
int dy[4]={1,-1,0,0};

/* 주사위 인덱스로 활용 
  2 
4 1 3.   //1이 맨위 6이 맨아래  
  5 
  6 
*/
int dice[7];
int arr[22][22];
int n,m,k;
pair<int,int> cur; //현재 주사위 위치 

void move(int dir)
{
  if(dir==0) //동쪽으로 이동한경우 2랑 5는 그대로
  {
    swap(dice[1],dice[3]);
    swap(dice[1],dice[6]);
    swap(dice[1],dice[4]);
  }
  else if(dir==1)//서쪽     
  {
    swap(dice[1],dice[4]);
    swap(dice[1],dice[6]);
    swap(dice[1],dice[3]);
  }
  else if(dir==2)//북쪽 
  {
    swap(dice[1],dice[2]);
    swap(dice[1],dice[6]);
    swap(dice[1],dice[5]);
  }
  else //남쪽
  {
    swap(dice[1],dice[5]);
    swap(dice[1],dice[6]);
    swap(dice[1],dice[2]);
  }
}
bool over(int x,int y)
{
  if(x<0||x>=n||y<0||y>=m)return true;
  return false;
}
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n>>m>>cur.X>>cur.Y>>k;
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
    {
      cin>>arr[i][j];
    }
  }
  vector<int> dlist;
  int d;
  for(int i=0;i<k;i++)
  {
    cin>>d;
    dlist.push_back(d);
  }
  for(auto d: dlist)
  { 
    int nx=cur.X+dx[d-1];
    int ny=cur.Y+dy[d-1];
    if(over(nx,ny))continue;
    move(d-1);
    if(arr[nx][ny]==0)arr[nx][ny]=dice[6];
    else{
      dice[6]=arr[nx][ny];
      arr[nx][ny]=0;
    }
    cur={nx,ny};
    cout<<dice[1]<<'\n';
  }
}