#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
#include <utility>
using namespace std;

#define D first
#define N second
vector<int> parent(10001);
vector<int> ranks(10001, 1);
int v, e;
tuple<int, int, int> edge[100001]; //�Ÿ�,���� u,v
vector<pair<int, int>> adj[100001]; // ������ ���� adj �Ÿ�,������ȣ

int find(int u)
{
  if (u == parent[u])
    return u;
  return parent[u] = find(parent[u]);
}

int nodecount[10001];


int  merge(int u, int v)
{
  u = find(u);
  v = find(v);
  if (u == v)
    return -1;
  if (ranks[u] > ranks[v])
    swap(u, v);
  // ���� v�� ��ũ�� u�� ��ũ���� ���� �����Ƿ� u�� v�� �ڽ����� ������
  parent[u] = v;
  if (ranks[u] == ranks[v])
    ranks[v]++;
}



int kruscal()
{
  sort(edge, edge + e);
  int mstn = 0;
  int mtotal = 0;
  for (int i = 1; i <= 10000; i++)
    parent[i] = i;
  for (int i = 0; i < e; i++)
  {
    int a, b, dst;
    tie(dst, a, b) = edge[i];
    if (find(a) == find(b))
      continue;    // ���� �׷��̸� ��ŵ
    mtotal += dst; // �ٸ� �׷��̸� �߰�
    mstn++;
    merge(a, b);
    if (mstn == v - 1)
      break;
  }
  cout << mtotal;
}

int prim() //heap�� ���� ���� 
{
  bool closed[100001];
  int cnt = 0; // ���õ� ���� ��
  // �Ÿ�,����1,����2(���� �Ÿ��� ����� ���� �ΰ����� ������ ���� ) ��������
  priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
  closed[1] = 1;          // ������ �ݱ�
  for (auto nxt : adj[1]) // 1�� ����� ���� �߰�
    pq.push({nxt.D, 1, nxt.N});
  int mtotal=0;  
  while (cnt < v - 1)
  { 
    int dst, a, b;
    tie(dst, a, b) = pq.top(); //���� �ִ� ���� �ϳ� ������ 
    pq.pop();
    if (closed[b]) //mst�� ����ȰŸ� ��ŵ 
      continue;
    closed[b] = 1;
    cnt++;
    mtotal+=dst;
    for (auto nxt : adj[b]) // mst�� �߰��� ���� ����� ���� üũ
    {
      if (!closed[nxt.N]) // mst�� ���� ����
        pq.push({nxt.D, b, nxt.N});
    }
  }
  return mtotal; 
}
