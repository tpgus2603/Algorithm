#include <iostream>
#include <vector>
#include <stack>

using namespace std;
vector<int> adj[10];
bool vis[10];
void dfs()
{
	stack<int>s;
	s.push(1);
	vis[1]=true;
	while(!s.empty())
	{
		int cur=s.top();
		s.pop();
		cout<<cur<<"->";
		for(auto nxt:adj[cur])
		{
			if(!vis[nxt])
			{
				s.push(nxt);
				vis[nxt]=1;
			}
		}
	}
}
void dfsrecur(int cur)
{
	vis[cur]=1;
	cout<<cur<<"->";
	for(auto nxt:adj[cur])
	{
		if(!vis[nxt])
			dfsrecur(nxt);
	}

}
void dfs2()
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

int p[10];
int depth[10]; //트리의 뎁스 계산 
void treedfs(int root) //트리에서 bfs
{
  stack<int> s;
  s.push(root);
  while(!s.empty())
  {
			int cur=s.top();
			s.pop();
			cout<<cur<<"->";
			for(auto nxt:adj[cur])
			{
					if(p[cur]==nxt)continue; //연결된 노드가 부모노드인 경우 스킵
					s.push(nxt);
					p[nxt]=cur; //부모노드 기록하기
					depth[nxt]=depth[cur]+1;
			}	
  }
}
void treedfsrecur(int cur)
{
		cout<<cur<<"->";
		for(auto nxt:adj[cur])
		{
				if(p[cur]==nxt)continue;
				p[nxt]=cur;
				depth[nxt]=depth[cur]+1;
				treedfsrecur(nxt);
		}

}
