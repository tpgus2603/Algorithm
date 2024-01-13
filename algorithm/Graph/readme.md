-그래프: 인접행렬과 인접 리스트를 통해 구현되는 정점과 간선으로 이루어진 자료구조 

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
