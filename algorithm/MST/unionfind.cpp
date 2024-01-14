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
      parent[i] = i; // 초기화
  }
  // u가 속한 트리의 번호를 반환
  int find2(int u) const
  {
    if (u == parent[u])
      return u; // u가 루트인 경우
    return find2(parent[u]);
  }
  // u가 속한 트리와 v가 속한 트리를 합친다
  void merge(int u, int v)
  { // union이 C/C++ 예약어라서 다른 단어로 대체
    u = find2(u);
    v = find2(v);
    // 이미 u와 v가 같은 트리인 경우를 걸러낸다
    if (u == v)
      return;
    parent[u] = v;// v가 u의 부모가 됨 
  }
};

struct OptimizedDisJointSet
{
  vector<int> parent, rank;
  OptimizedDisJointSet(int n) : parent(n), rank(n, 1)
  { // 트리의 랭크를 저장할 별도 벡터
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
    // 이제 v의 랭크가 u의 랭크보다 낮지 않으므로 u를 v의 자식으로 보낸다
    parent[u] = v;
    if (rank[u] == rank[v])
      rank[v]++;
  }
  void merge2(int u, int v)
  {
    u = find(u);
    v = find(v);
    if (u == v) // 루트가 같으면 합치지않고 종료
      return;
    if (rank[u] > rank[v]) // u가 높이가 더 높으면
      parent[v] = u;
    else if (rank[u] < rank[v])
      parent[u] = v;
    else
    {
      parent[u] = v;
      rank[v]++;
    }
    // 이제 v의 랭크가 u의 랭크보다 낮지 않으므로 u를 v의 자식으로 보낸다
  }
};
