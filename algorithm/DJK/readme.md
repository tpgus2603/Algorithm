-다익스트라 알고리즘:
-
아직 거리가 확정되지 않은 정점들중 가장 가까운 정점을 택함(그리디)    O(V^2)->heap을 이용하지 않고 연결된 정점 확인하는경우   ,O(ElogE):heap을 이용한경우 
하나의 시작점으로부터 다른 모든 정점까지의 최단거리를 구하는 알고리즘, 음수 간선 처리 불가능, heap(최소 힙)을 이용하여 구현 

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
    if (idx == -1 || d[idx] == I) // 선택할 정점 없을
      break;
    closed[idx] = 1;                            // 최소값 찾고 정점 확정
    for (auto nxt : adj[idx])                   // 테이블 갱신
      d[nxt.V] = min(d[nxt.V], d[idx] + nxt.D); // 선택정점+간선거리와 원래값 비교
  }
}

int v, e;


int back[20001];

void dk(int st) //경로기능 구현 된 다익스트라 
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
-플로이드 알고리즘: 
-
모든 정점 쌍 사이의 최단거리를 구하는 알고리즘으로 2차원 dp를 활용한다.

k=1~n까지 정점 k를 거쳐가는 최소경로 테이블 업데이트  (cf 최소값 갱신에 min함수 사용보다 필요할때만 갱신이 일어나도록 하는것이 유리)

 다익스트라 알고리즘과 비교하여 음수 간선을 처리 할 수있다. 하지만 음수 사이클을 처리하진 못함 

```
int dp[101][101];

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
    if (dp[a][b] > c)   //노드와 노드 사이의 경로가 여러개인 경우도 있으면 이렇게 테이블을 채운다 
      dp[a][b] = c;
  }
  for (int k = 1; k <= n; k++)
  {
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        //dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]); 
        if(dp[i][k]+dp[k][j]<dp[i][j])
          dp[i][j]=dp[i][k]+dp[k][i];
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
}

```






