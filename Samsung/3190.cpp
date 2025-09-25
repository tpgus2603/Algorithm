#include<iostream>
#include<queue>
#include<utility>
#include<algorithm>

#define X first 
#define Y second 
using namespace std;

//시계방향으로 증가 
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int arr[101][101]; //빈 칸 0 뱀 있는공간 1 사과 2
//방향 개념 존재 처음엔 오른쪽
//머리 몸 꼬리 존재... 
//이동칸에 사과x -> 몸길이 그대로 이동칸에 사과o -> 몸길이 증가 
//모든 이동좌표 deque에 넣고 값1로 초기화  사과아니면 한간빼기 
int n,k,l,t,dir;   // 
queue<pair<int,int>> path;
queue<pair<int,int>> dlist; //방향전환 -1이면 반시계 1이면 시계 
bool over(int x,int y)
{
  if(x<=0||x>n||y<=0||y>n||arr[x][y]==1)return true;
  return false;
}
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>n>>k;
  for(int i=0;i<k;i++)
  {
    int x,y;
    cin>>x>>y;
    arr[x][y]=2;
  }
  cin>>l;
  for(int i=0;i<l;i++)
  {
    int ti;
    char di;
    cin>>ti>>di;
    if(di=='L')
      dlist.push({ti,-1});
    else
      dlist.push({ti,1});
  }

  //게임시작
  pair<int,int> cur ={1,1}; //머리위치 
  pair<int,int> change=dlist.front();
  while(1)
  {
    t++;
    path.push(cur);
    arr[cur.X][cur.Y]=1;
    cur.X+=dx[dir];
    cur.Y+=dy[dir];
    if(over(cur.X,cur.Y))break;
    if(arr[cur.X][cur.Y]!=2) //사과 없음  
    {
      auto tail=path.front();
      path.pop();
      arr[tail.X][tail.Y]=0;
    }
    if(t==change.X) //방향전환
    {
      dir+=change.Y;
      if(dir<0)dir=3;
      if(dir>3)dir=0;
      dlist.pop();
      if(!dlist.empty())change=dlist.front();
    }
  }
  cout<<t;


}