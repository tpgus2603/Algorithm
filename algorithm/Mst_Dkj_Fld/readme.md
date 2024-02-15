-Spanning tree(신장트리):방향성이 없는 그래프가 주어졌을때 모든 정점을 포함하는 트리

-MST(Minimum Spanning Tree):신장 트리중에서 간선의 합이 최소인 트리->여러개가 존재할 수 있다.


-크루스칼 알고리즘:
-
union find를 이용하여 구현 , 간선 중심의 알고리즘  O(VlogV)

  1.간선의 크기를 오름차순으로 정렬하고 제일 낮은 비용의 간선 택

  2.현재 선택한 간선이 정점 u,v를 연결하는 간선이라고 할때 u와 v가 같은 그룹이면 아무것도 하지않고 넘어감, u와 v가 다른 그룹이면 같은 그룹으로 만들고 현재 택한 간선을 mst에 추가(같은 그룹 노드의 간선을 택하면 cycle이 생김)

  3.최소 신장트리에 v-1개의 간선이 추가 될때 까지 반복

  -union find: 서로 중복되지 않은 부분집합인 disjoint set을 표현시키기 위해 사용하는 알고리즘,tree로 구현시 루트노드의 번호가 집합 번호가 된다.
    
    1.make set(x):초기화, x를 유일한 원소로 하는 새로운 집합을 만듬

    2.union(x,y): 합하기, x가 속한 집합과 y가 속한 집합을 합침(루트가 다르면 y를 x의 자손으로)

    3.find(x): 찾기,x가 속한 집합의 대표값 반환 ->x의 루트노드 찾기

    비대칭 트리의 경우 union과 find의 시간 복잡도가 O(N)이 될 수 있다, 따라서 이를 개선하기 위해 경로압축과 union 최적화를 수행한다.

    1. 경로압축: find하면서 만난 모든 부모노드를 루트노드로 만들기(find연산 최적화)

    2.union최적화: tree의 높이를 측정할 배열 만들고 union할때 항상 높이가 큰 트리 밑에 낮은 트리를 넣는다. -> 합쳐진 트리 높이를 최소화함.

```
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
```
```
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
      continue;    // 같은 그룹이면 스킵
    mtotal += dst; // 다른 그룹이면 추가
    mstn++;
    merge(a, b);
    if (mstn == v - 1)
      break;
  }
  cout << mtotal;
}
```

-프림 알고리즘: 
-
힙을 통하여 구현하는 노드 중심으 알고리즘  O(ElogV)

  1. 임의의 정점을 선택해 mst에 추가, 해당 정점과 연결된 모든 간선을 heap에 추가

  2. heap에서 비용이 가장 작은 간선 선택

  3.만약 해당 간선이 mst에 포함된 두 정점을 연결하면 skip, 해당간선이 mst에 포함된 정점u와 포함되지 않은 정점 v을 연결하면 해당 간선과 v를 mst에 추가 후 정점 v와 mst에 포함되지 않은 정점을 연결하는 간선을 heap에 추가

  4. mst에 v-1개의 간선이 추가될때 까지 반복 

```
int prim() //heap을 통한 구현 
{
  bool closed[100001];
  int cnt = 0; // 선택된 간선 수
  // 거리,정점1,정점2(간선 거리와 연결된 정점 두개까지 포함한 정보 ) 오름차순
  priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
  closed[1] = 1;          // 시작점 닫기
  for (auto nxt : adj[1]) // 1과 연결된 노드들 추가
    pq.push({nxt.D, 1, nxt.N});
  int mtotal=0;  
  while (cnt < v - 1)
  { 
    int dst, a, b;
    tie(dst, a, b) = pq.top(); //힙에 있는 정점 하나 꺼내기 
    pq.pop();
    if (closed[b]) //mst와 연결된거면 스킵 
      continue;
    closed[b] = 1;
    cnt++;
    mtotal+=dst;
    for (auto nxt : adj[b]) // mst에 추가한 노드와 연결된 간선 체크
    {
      if (!closed[nxt.N]) // mst에 없는 노드면
        pq.push({nxt.D, b, nxt.N});
    }
  }
  return mtotal; 
}

```  
