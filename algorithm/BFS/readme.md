

BFS(breath first search):
-
너비 우선탐색 , 같은 거리,depth,level에 해당하는 노드를 우선으로 탐색하는 서치방법 ,queue를 이용하여 구현한다

1.시작노드로부터 인접한 노드를 큐에 push한다

2.큐의 front를 pop하고 해당 노드로 부터 인접한 노드중 방문하지 않는 노드를 다시 큐에 push한다 

3.push한 노드의 거리를 갱신하거나 방문표시 배열을 만들어 해당 노드를 방문 했는지 여부를 표시한다.

4.큐가 empty가 될때까지 2~3을 반복한다.


O(N)의 시간복잡도를 가지며 노드를 전부 방문하거나 특정 노드와 시작노드의 거리를 측정할때 많이 쓰임 
구현시 다차원 배열 혹은 그래프를 활용하며 다차원 배열로 구현시 stl pair<T,T>를 활용한다. graph에서는 인접리스트를 활용한다


```
#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second 
int board[502][502] =
{{1,1,1,0,1,1,0,0,0,0,0},
{1,0,0,0,1,1,0,0,0,0,0},
{1,1,1,0,1,1,0,0,0,0,0},
{1,1,0,0,1,1,0,0,0,0,0},
{0,1,0,0,1,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0} }; 
bool vis[502][502]; 
int dist[502][502]; 
int n = 8, m = 11;
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

template <typename T>
int bfsSerach(queue <T>& q)
{
	int sum = 0;
	while (!q.empty())
	{
		pair<int, int>cur = q.front(); q.pop(); sum++;
		cout << '(' << cur.X << ',' << cur.Y << ')' << "->"; 
		for (int i = 0; i < 4; i++)
		{
			int nx = cur.X + dx[i];
			int ny = cur.Y + dy[i];
			if (nx >= n || nx < 0 || ny >= m || ny < 0)continue; //격자 범위 넘어가면 스킵 
			if (dist[nx][ny]>0 || board[nx][ny] != 1)continue;
			q.push({ nx,ny });
			vis[nx][ny] = 1;//큐에 삽입과 동시에 방문했다 표시남김 같은칸에대해 중복 삽입을 막기 위해 넣자마자 바로 방문표시 
			dist[nx][ny] = dist[cur.X][cur.Y] + 1;
		}
	}
	return sum;
}
int main()
{
	queue<pair<int, int>> q;
	q.push({ 0,0 });
	vis[0][0]=1;
	int a=bfsSerach(q);
	cout << a;
}
```
BFS에서 같은 종류의 시작점이 여러개인 경우
-
이 경우에는 시작점들을 모두 큐에 넣고 시작하면 된다.

```
#include<iostream>
#include<tuple>
#include<queue>

using namespace std;

int dx[6]={1,-1,0,0,0,0};
int dy[6]={0,0,1,-1,0,0};
int dz[6]={0,0,0,0,1,-1};

int arr[101][101][101];
int day[101][101][101];
int m,n,h;
int main()
{
  ios::sync_with_stdio(0);cin.tie(0);
  cin>>m>>n>>h;
  int temp;
  queue<tuple<int,int,int>> q;
  for(int i=0;i<h;i++)
  {
    for(int j=0;j<n;j++)
    {
      for(int k=0;k<m;k++)
      {
        cin>>temp;
        arr[j][k][i]=temp;
        if(temp==1)
          q.push({j,k,i});
        if(temp==0) //안익은놈  
          day[j][k][i]=-1;
      }
    }
  }
  while(!q.empty())
  {
    auto cur=q.front();
    q.pop();
    for(int i=0;i<6;i++)
    {
      int curx,cury,curz;
      int nx,ny,nz;
      tie(curx,cury,curz)=cur;
      nx=curx+dx[i];ny=cury+dy[i];nz=curz+dz[i];
      if(nx<0||nx>=n||ny<0||ny>=m||nz<0||nz>=h)continue;
      if(day[nx][ny][nz]>=0)continue;
      q.push({nx,ny,nz});
      day[nx][ny][nz]=day[curx][cury][curz]+1;
    }
  }

  int maxday=0;
    for(int i=0;i<h;i++)
  {
    for(int j=0;j<n;j++)
    {
      for(int k=0;k<m;k++)
      {
        if(day[j][k][i]==-1)
          {
            cout<<-1;
            return 0;
          }
        if(maxday<day[j][k][i])
          maxday=day[j][k][i];
      }
    }
  }
  cout<<maxday;
  return 0;
}
```

-BFS에서는 또한 점이 다른 종류인 경우
-
즉 다르게 탐색을 진행하는 문제가 존재한다. 이런 경우 종류 각각에 맞게 거리 배열을 만들어 구현한다

만약 어떤 종류의 시작점은 다른 종류의 bfs에 영향을 안받는 경우 해당 경우 먼저 bfs를 진행하고 나중에 bfs를 진행한다. 

그 후 한 종류에 대해 bfs를 진행한 후 이전에 진행한 bfs의 거리 배열을 조건에 추가한다.

```
#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
string board[1002];
int dist1[1002][1002]; // 불의 전파 시간
int dist2[1002][1002]; // 지훈이의 이동 시간
int n, m;
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int main(void){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  for(int i = 0; i < n; i++){
    fill(dist1[i], dist1[i]+m, -1);
    fill(dist2[i], dist2[i]+m, -1);    
  }
  for(int i = 0; i < n; i++)
    cin >> board[i];  
  queue<pair<int,int> > Q1;
  queue<pair<int,int> > Q2;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if(board[i][j] == 'F'){
        Q1.push({i,j});
        dist1[i][j] = 0;        
      }
      if(board[i][j] == 'J'){
        Q2.push({i,j});
        dist2[i][j] = 0;
      }
    }
  }
  // 불에 대한 BFS
  while(!Q1.empty()){
    auto cur = Q1.front(); Q1.pop();
    for(int dir = 0; dir < 4; dir++){
      int nx = cur.X + dx[dir];
      int ny = cur.Y + dy[dir];
      if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
      if(dist1[nx][ny] >= 0 || board[nx][ny] == '#') continue; 
      dist1[nx][ny] = dist1[cur.X][cur.Y]+1;
      Q1.push({nx,ny});
    }
  }

  // 지훈이에 대한 BFS
  while(!Q2.empty()){
    auto cur = Q2.front(); Q2.pop();
    for(int dir = 0; dir < 4; dir++){
      int nx = cur.X + dx[dir];
      int ny = cur.Y + dy[dir];
      if(nx < 0 || nx >= n || ny < 0 || ny >= m){ // 범위를 벗어났다는 것은 탈출에 성공했다는 의미. 큐에 거리 순으로 들어가므로 최초에 탈출한 시간을 출력하면 됨.
        cout << dist2[cur.X][cur.Y]+1; 
        return 0;
      }
      if(dist2[nx][ny] >= 0 || board[nx][ny] == '#') continue;
      if(dist1[nx][ny] != -1 && dist1[nx][ny] <= dist2[cur.X][cur.Y]+1) continue; // 불의 전파 시간을 조건에 추가  불보다 늦게 도착한 경우는 실제로는 못가는 경우이기에 continue
      dist2[nx][ny] = dist2[cur.X][cur.Y]+1;
      Q2.push({nx,ny});
    }
  }
  cout << "IMPOSSIBLE"; // 여기에 도달했다는 것은 탈출에 실패했음

```

