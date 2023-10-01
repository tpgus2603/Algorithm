#include<iostream>
#include<vector>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;
bool vis[101];
vector<int>adj[101];
int dist[101];

void bfs(queue<int>& q)
{
	int cur = q.front();
	dist[cur] = 0;
	while (!q.empty())
	{
		cur = q.front();
		vis[cur] = 1;
		q.pop();
		cout << cur << "->";
		for (auto nxt : adj[cur])
		{
			if (vis[nxt])continue;
			q.push(nxt);
			vis[nxt] = 1;
			dist[nxt] = dist[cur] + 1;
		}

	}
}

int p[10];
int depth[10]; //트리의 뎁스 계산 
void treebfs(int root) //트리에서 bfs
{
  queue<int> q;
  q.push(root);
  while(!q.empty())
  {
			int cur=q.front();
			q.pop();
			cout<<cur<<"->";
			for(auto nxt:adj[cur])
			{
					if(p[cur]==nxt)continue; //연결된 노드가 부모노드인 경우 스킵
					q.push(nxt);
					p[nxt]=cur; //부모노드 기록하기
					depth[nxt]=depth[cur]+1;
			}	
  }
}

int main()
{

	cout << dist[30];



}

