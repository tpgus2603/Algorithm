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
    int idx = -1; // �湮�� ����� �ε��� 
    for (int i = 1; i <= v; i++) //�湮���� ���Ž�� 
    {
      if (closed[i])
        continue;
      if (idx == -1) //��� �湮�ϸ� idx=-1�λ��·� �ݺ�������  
        idx = i; // �湮�� ���
      else if (d[i] < d[idx])
        idx = i; // ����� �Ÿ� ��
    }
    if (idx == -1 || d[idx] == I) // ������ ���� ������
      break;
    closed[idx] = 1; // �ּҰ� ã�� ���� Ȯ��
    for (auto nxt : adj[idx]) //���̺� ���� 
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
    if (d[cur.V] != cur.D) // ���̺��� ���� ���ӿ� ����� �Ÿ��� �ٸ��� (�ѱ�,Ȯ���Ǳ��� �Ÿ�)
      continue;
    for (auto nxt : adj[cur.V]) //�ּ����� ã�� Ȯ�� �� ���� ���� Ȯ�� 
    {
      if (d[nxt.V] <= d[cur.V] + nxt.D) // ����+������ �ּҰ��� �ƴѰ��
        continue;
      d[nxt.V] = d[cur.V] + nxt.D; // �ּҰ� ����
      pq.push({d[nxt.V], nxt.V});   // �����ֱ�
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