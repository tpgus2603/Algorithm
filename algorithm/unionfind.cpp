#include <iostream>
#include <vector>

using namespace std;
#define MAX_SIZE 100
struct NaiveDisjointSet
{
  vector<int> parent;
  NaiveDisjointSet(int n) : parent(n)
  {
    for (int i = 0; i < n; ++i)
      parent[i] = i; // �ʱ�ȭ
  }
  // u�� ���� Ʈ���� ��ȣ�� ��ȯ
  int find2(int u) const
  {
    if (u == parent[u])
      return u; // u�� ��Ʈ�� ���
    return find2(parent[u]);
  }
  // u�� ���� Ʈ���� v�� ���� Ʈ���� ��ģ��
  void merge(int u, int v)
  { // union�� C/C++ ������ �ٸ� �ܾ�� ��ü
    u = find2(u);
    v = find2(v);
    // �̹� u�� v�� ���� Ʈ���� ��츦 �ɷ�����
    if (u == v)
      return;
    parent[u] = v;// v�� u�� �θ� �� 
  }
};

struct OptimizedDisJointSet
{
  vector<int> parent, rank;
  OptimizedDisJointSet(int n) : parent(n), rank(n, 1)
  { // Ʈ���� ��ũ�� ������ ���� ����
    for (int i = 0; i < n; ++i)
      parent[i] = i;
  }

  int find(int u)
  {
    if (u == parent[u])
      return u;
    return parent[u] = find(parent[u]);
  }

  void merge(int u, int v)
  {
    u = find(u);
    v = find(v);
    if (u == v)
      return;
    if (rank[u] > rank[v])
      swap(u, v);
    // ���� v�� ��ũ�� u�� ��ũ���� ���� �����Ƿ� u�� v�� �ڽ����� ������
    parent[u] = v;
    if (rank[u] == rank[v])
      rank[v]++;
  }
  void merge2(int u, int v)
  {
    u = find(u);
    v = find(v);
    if (u == v) // ��Ʈ�� ������ ��ġ���ʰ� ����
      return;
    if (rank[u] > rank[v]) // u�� ���̰� �� ������
      parent[v] = u;
    else if (rank[u] < rank[v])
      parent[u] = v;
    else
    {
      parent[u] = v;
      rank[v]++;
    }
    // ���� v�� ��ũ�� u�� ��ũ���� ���� �����Ƿ� u�� v�� �ڽ����� ������
  }
};
