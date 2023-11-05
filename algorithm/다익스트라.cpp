#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;

#define D first
#define V second
#define I INT_MAX
vector<pair<int, int>> adj[20001];
int d[20001];
bool closed[20001];
int v = 10;
void dijkstra_native(int st) // O(v^2+E)
{
  fill(d, d + v + 1, INT_MAX);
  d[st] = 0;
  while (true)
  {
    int idx = -1; // �湮�� ����� �ε���
    for (int i = 1; i <= v; i++)
    {
      if (closed[i])
        continue;
      if (idx == -1)
        idx = i; // �湮�� ���
      else if (d[i] < d[idx])
        idx = i; // ����� �Ÿ� ��
    }
    if (idx == -1 || d[idx] == INT_MAX) // ������ ���� ������
      break;
    closed[idx] = 1; // ���� Ȯ��
    for (auto nxt : adj[idx])
      d[nxt.V] = min(d[nxt.V], d[idx] + nxt.D); // ��������+�����Ÿ��� ������ ��
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
  // �Ÿ��� �̿����� ������ ��� ��
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  d[st] = 0;
  pq.push({d[st], st});
  while (!pq.empty())
  {
    auto cur = pq.top();
    pq.pop();
    if (d[cur.V] != cur.D) // ���̺��� ���� ���ӿ� ���� �Ÿ��� �ٸ���
      continue;
    for (auto nxt : adj[cur.V])
    {
      if (d[nxt.V] <= d[cur.V] + nxt.D) // ����+������ �ּҰ��� �ƴѰ��
        continue;
      d[nxt.V] = d[cur.V] + nxt.D; // �ּҰ� ����
      pq.push({d[nxt.V], nxt.V});   // �����ֱ�
    }
  }
}