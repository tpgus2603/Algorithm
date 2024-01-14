-그래프: 인접행렬과 인접 리스트를 통해 구현되는 정점과 간선으로 이루어진 자료구조 

방향성이 있는 directed 그래프와 방향성이 없는 undirected 그래프가 있다.

```
int adjm[100][100]={0};
vector<int> adj [100];
int v,e;
//인접행렬
void directed()
{
  cin>>v>>e;
  int u,v;
  for(int i=0;i<e;i++)
  {
    cin>>u>>v;
    adjm[u][v]=1;
  }
}

void undirected()
{
  cin>>v>>e;
  int u,v;
  for(int i=0;i<e;i++)
  {
    cin>>u>>v;
    adjm[u][v]=1;
    adjm[v][u]=1;
  }
}

//인접리스트 
void directed2()
{
  cin>>v>>e;
  int u,v;
  for(int i=0;i<e;i++)
  {
    cin>>u>>v;
    adj[u].push_back(v);
  }
}

void undirected2()
{
  cin>>v>>e;
  int u,v;
  for(int i=0;i<e;i++)
  {
    cin>>u>>v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
}
```
-BFS그래프:  queue를 이용하여 그래프에서 bfs를 구현 

  시작점을 거리 0으로 하여 거리가 음수인 경우 방문하지 않은 노드로 간주 ,큐에서 노드 하나씩 꺼내고 노드와 연결된 노드들을 큐에 넣으면서 방문한다. 

```
void bfs2()
{
	queue<int>q;
	int v;
	cin>>v;
	fill(dist,dist+10,-1);
	q.push(v);
	for(int i=1;i<=v;i++)
	{
		while(!q.empty())
		{	
			int cur=q.front();
			cout<<cur<<"->";
			q.pop();
			for(auto nxt:adj[cur])
			{
				if(dist[nxt]!=-1)continue;
				q.push(nxt);

				dist[nxt]=dist[cur]+1;
			}
		}
	}
}
```

-DFS그래프: 스택 or재귀를 이용하여 그래프에서 dfs를 구현 
```
vector<int> adj[10];
bool vis[10];
void dfs()  //스택에 넣을때 방문 표시를 남김 
{
	stack<int>s; //스택으로 dfs구현 
	s.push(1);
	vis[1]=true;
	while(!s.empty())
	{
		int cur=s.top();
		s.pop();
		cout<<cur<<"->";
		for(auto nxt:adj[cur])
		{
			if(vis[nxt])continue;
				s.push(nxt);
				vis[nxt]=1;
		}
	}
}
void dfs2() //방문을 할때 방문표시를 남김
{
	stack<int>s;
	s.push(1);
	while(!s.empty())
	{
		int cur=s.top();
		s.pop();
		if(vis[cur])continue; //이미 방문한것을 여러번 방문하지 않기위함
		vis[cur]=true; //방문표시를 방문과 동시에남김
		cout<<cur<<"->";
		for(auto nxt:adj[cur])
		{
			if(vis[nxt])continue;
			s.push(nxt);
		}
	}
}
둘다 dfs 순회를 하지만 2번 dfs가 일반적인 dfs방문 순서와 일치함 
```

-트리: 무방향이면서 사이클이 없는 연결 그래프 v개의 정점을 가지고 v-1개의 간선을 가짐

트리는 배열을 이용하여 간단하게 구현하는것이 가능하다.

dfs와 bfs를 통해 
```
vector<int>adj[10];
int p[10];
int depth[10];
void bfs(int root)
{
  queue<int>q;
  q.push(root);
  while(!q.empty())
  {
    int cur=q.front();
    q.pop();
    cout<<cur<<"->";
    for(auto nxt:adj[cur])
    {
      if(p[cur]==nxt)continue;
      q.push(nxt);
      p[nxt]=cur;
      depth[nxt]=depth[cur]+1;
    }
  }
}

void dfs(int root)
{
  stack<int>s;
  s.push(root);
  while(!s.empty())
  {
    int cur=s.top();
    s.pop();
    cout<<cur<<"->";
    for(auto nxt:adj[cur])
    {
      if(p[cur]==nxt)continue;
      s.push(nxt);
      p[nxt]=cur;
      depth[nxt]=depth[cur]+1;
    }
  }
}
```

-트리의 순회: 재귀적으로 구현 preorder( 루트,왼쪽,오른쪽) , inorder(왼쪽,루트,오른쪽) ,postorder(왼쪽,오른쪽,루트)
```
int lc[9]={0,2,4,6,0,0,0,0,0};  //인덱스(노드번호)
int rc[9]={0,3,5,7,0,8,0,0,0};
void preorder(int cur){
  cout<<cur<<"->";
  if(lc[cur]!=0)preorder(lc[cur]); //왼쪽트리탐색
  if(rc[cur]!=0)preorder(rc[cur]); //오른쪽 트리 탐색
}
void inorder(int cur)
{
  if(lc[cur]!=0)inorder(lc[cur]);
  cout<<cur<<"->";
  if(rc[cur]!=0)inorder(rc[cur]);
}
void postorder(int cur)
{
  if(lc[cur]!=0)postorder(lc[cur]);
  if(rc[cur]!=0)postorder(rc[cur]);
  cout<<cur<<"->";
}
```













