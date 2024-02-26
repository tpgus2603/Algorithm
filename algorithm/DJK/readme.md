-다익스트라 알고리즘:
-
아직 거리가 확정되지 않은 정점들중 시작점으로 부터 가장 가까운 정점을 택한 뒤 그 정점과 연결된 정점의 거리 테이블 갱신, 그리고 갱신된 정점이 나중에 시작점으로 부터 가장 가까운 정점으로 택해지면 테이블 거리가 확정이된다.  (그리디) 

O(V^2)->heap을 이용하지 않고 연결된 정점 확인하는경우   ,O(ElogE):heap을 이용한경우 

하나의 시작점으로부터 다른 모든 정점까지의 최단거리를 구하는 알고리즘, 음수 간선 처리 불가능(그리디 조건이 깨짐 ), heap(최소 힙)을 이용하여 구현 

  1.heap에 (0,시작점)추가 

  2.heap에서 거리 가장 작은 원소 택하기 해당거리가 테이블값과 다른경우 skip한다. heap에는 값들이 누적되면서 쓰레기값도 남아있음 

  3.원소가 가리키는 정점이 v일때 v와 이웃한 정점들에 대해 최단거리 테이블값보다 v거치는 값이 더 작은 값을 가진 경우 최단거리 테이블 갱신 후 heap에 추가 

  4.heap이 빌때까지 반복 

```
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;

#define D first
#define V second
#define I 0x3f3f3f3f
vector<pair<int, int>> adj[20001];
int d[20001];
bool closed[20001];
int v = 10;
void dijkstra_native(int st) // O(v^2+E)
{
  fill(d, d + v + 1, I);
  d[st] = 0;
  while (true)
  {
    int idx = -1;                // 방문할 노드의 인덱스
    for (int i = 1; i <= v; i++) // 방문안한 노드탐색
    {
      if (closed[i])
        continue;
      if (idx == -1) // 모두 방문하면 idx=-1인상태로 반복문종료
        idx = i;     // 방문할 노드
      else if (d[i] < d[idx])
        idx = i; // 가까운 거리 택
    }
    if (idx == -1 || d[idx] == I) // 선택할 정점 없을��
      break;
    closed[idx] = 1;                            // 최소값 찾고 정점 확정
    for (auto nxt : adj[idx])                   // 테이블 갱신
      d[nxt.V] = min(d[nxt.V], d[idx] + nxt.D); // 선택정점+간선거리와 원래값 비교
  }
}

int v, e;

int back[20001];

void dk(int st) // 경로기능 구현 된 다익스트라
{
  fill(d, d + v + 1, I);
  d[st] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  pq.push({d[st], st});
  while (!pq.empty())
  {
    auto cur = pq.top();
    pq.pop();
    if (cur.D != d[cur.V])
      continue;
    for (auto nxt : adj[cur.V])
    {
      if (d[nxt.V] > d[cur.V] + nxt.D)
      {
        d[nxt.V] = d[cur.V] + nxt.D;
        back[nxt.V] = cur.V;
        pq.push({d[nxt.V], nxt.V});
      }
    }
  }
  vector<int> path;
  for (int cur = v; cur != st; cur = back[cur])
  {
    path.push_back(cur);
  }
  path.push_back(st);
}
```
플로이드 알고리즘
-

모든 정점 쌍 사이의 최단거리를 구하는 알고리즘으로 2차원 dp를 활용한다.

k=1~n까지 정점 k를 거쳐가는 최소경로 테이블 업데이트 (cf 최소값 갱신에 min함수 사용보다 필요할때만 갱신이 일어나도록 하는것이 유리)

다익스트라 알고리즘과 비교하여 음수 간선을 처리 할 수있다. 하지만 음수 사이클을 처리하진 못함

경로복원을 위해 정점에서 다음으로 거쳐가는 정점을 저장하는 테이블 을 따로 만들어 dp테이블이 갱신될때마다 경로복원용 테이블을 갱신한다.

```
#include <iostream>
#include <algorithm>
#include<vector>

using namespace std;

#define MAX 100000000
int dp[101][101];
int nxt[101][101];

int main()
{

  ios::sync_with_stdio(0);
  cin.tie(0);
  for (int i = 0; i <= 100; i++)
  {
    for (int j = 0; j <= 100; j++)
    {
      if (i == j)
        dp[i][j] = 0;
      else
        dp[i][j] = MAX;
    }
  }
  int n, m;
  cin >> n >> m;
  int a, b, c;
  for (int i = 0; i < m; i++)
  {
    cin >> a >> b >> c;
    if (dp[a][b] > c)
      dp[a][b] = c;
    nxt[a][b]=b;
  }
  for (int k = 1; k <= n; k++)
  {
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        if(dp[i][j]>dp[i][k]+dp[k][j])
        {
            dp[i][j]=dp[i][k]+dp[k][j];
            nxt[i][j]=nxt[i][k]; //k를 거쳐감 
        }
      }
    }
  }
  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= n; j++)
    {
      if(dp[i][j]==MAX)
        cout<<'0'<<' ';
      else
       cout << dp[i][j] << ' ';
    }
    cout << '\n';
  }

  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
    {
      if (dp[i][j] == 0 || dp[i][j] == MAX)
      {
        cout << "0" << '\n';
        continue;
      }
      vector<int> path;
      int st=i;
      while(st!=j)
      {
        path.push_back(st);
        st=nxt[st][j];
      }
      path.push_back(j);
      cout<<path.size()<<' ';
      for(auto k :path)
        cout<<k<<' ';
      cout<<'\n';
    }
  }

}
```

-벨만포드 알고리즘
-
다익스트라는 음수간선을 처리하지 못하고 플로이드 워셜은 음수간선 자체는 처리가 가능하지만 음수 사이클은 처리하지 못한다. 

다익스트라, 플로이드로는 음수 사이클을 처리하지 못한다.. -> 벨만포드 알고리즘 활용 (시간복잡도는   더 큼)

벨만포드 알고리즘은 그리디한 다익스트라 알고리즘과 다르게 음수사이클을 처리 할 수 있도록 모든 간선을 v-1번 만큼 방문하면서 거리 테이블을 갱신한다.

만약 간선을 v번 이상 방문할때도 거리갱신이 일어난다면 이는 음수 사이클이 존재한다는 의미이다.

또한 음수사이클이 존재하는 케이스인경우 예상보다 오버플로우가 더 자주 발생한다. 왜냐하면 음수사이클이 존재하는경우 해당 반복을 할때마다 음수사이클의 크기만큼 최소 거리 갱신이 일어나기 떄문에 

처음 예상한 간선 개수 * 간선 최대크기 범위를 넘어서 반복횟수 *간선 개수 *간선 최대크기 까지 거리테이블이 갱신될 수도 있기 때문이다.


```
#define MAX 1e9
long long  d[501];
using namespace std;

int main()
{
  ios::sync_with_stdio(0);cin.tie(0);

  int n,m;
  vector<tuple<int,int,int>> edge;
  cin>>n>>m;
  for(int i=0;i<m;i++)
  {
    int a,b,c;
    cin>>a>>b>>c;
    edge.push_back({a,b,c});
  }
  fill(d,d+n+1,MAX);
  d[1]=0;
  bool cycle=false;
  for(int i=1;i<=n;i++)
  {
    for(int j=0;j<m;j++)
    {
      int u,v,c;
      tie(u,v,c)=edge[j];
      if(d[u]==MAX)continue; //이미 방문한 정점을 시작점하는 간선의 거리를 갱신한다. 
      if(d[v]>d[u]+c)
      {
        d[v]=d[u]+c;
        if(i==n)
          cycle=true;
      }
    }
  }
```






