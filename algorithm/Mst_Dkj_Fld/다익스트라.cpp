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
    int idx = -1; // 방문할 노드의 인덱스 
    for (int i = 1; i <= v; i++) //방문안한 노드탐색 
    {
      if (closed[i])
        continue;
      if (idx == -1) //모두 방문하면 idx=-1인상태로 반복문종료  
        idx = i; // 방문할 노드
      else if (d[i] < d[idx])
        idx = i; // 가까운 거리 택
    }
    if (idx == -1 || d[idx] == I) // 선택할 정점 없을떄
      break;
    closed[idx] = 1; // 최소값 찾고 정점 확정
    for (auto nxt : adj[idx]) //테이블 갱신 
      d[nxt.V] = min(d[nxt.V], d[idx] + nxt.D); // 선택정점+간선거리와 원래값 비교
  }
}

int v, e;
void dkstra(int st)
{
  fill(d, d + v + 1, I);
  while (e--)
  {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({w, v});
  }
  // 거리와 이웃정점 정보를 담는 힙
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  d[st] = 0;
  pq.push({d[st], st});
  while (!pq.empty())
  {
    auto cur = pq.top();
    pq.pop();
    if (d[cur.V] != cur.D) // 테이블의 값과 힙속에 저장된 거리가 다르면 (넘김,확정되기전 거리)
      continue;
    for (auto nxt : adj[cur.V]) //최소정점 찾고 확정 후 연결 간선 확인 
    {
      if (d[nxt.V] <= d[cur.V] + nxt.D) // 정점+간선이 최소값이 아닌경우
        continue;
      d[nxt.V] = d[cur.V] + nxt.D; // 최소값 갱신
      pq.push({d[nxt.V], nxt.V});   // 힙에넣기
    }
  }
}

int back[20001];

void dk(int st)
{
  fill(d,d+v+1,I);
  d[st]=0;
  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
  pq.push({d[st],st});
  while(!pq.empty())
  {
    auto cur=pq.top();
    pq.pop();
    if(cur.D!=d[cur.V])
      continue;
    for(auto nxt:adj[cur.V])
    {  
      if(d[nxt.V]>d[cur.V]+nxt.D)
      {  
        d[nxt.V]=d[cur.V]+nxt.D;
        back[nxt.V]=cur.V;
        pq.push({d[nxt.V],nxt.V});
      }
    }

  }
  vector<int> path;
  for(int cur=v;cur!=st;cur=back[cur])
  {
    path.push_back(cur);
  }
  path.push_back(st);

}