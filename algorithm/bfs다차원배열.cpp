#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second 
int board[502][502] =
{{1,1,1,0,1,1,0,0,0,0,0},
{1,0,0,0,1,1,0,0,0,0,0},
{1,1,1,0,1,1,0,0,0,0,0},
{1,1,0,0,1,1,0,0,0,0,0},
{0,1,0,0,1,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0},
{0,0,0,0,1,0,0,0,0,0,0} }; 
bool vis[502][502]; 
int dist[502][502]; 
int n = 8, m = 11;
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };

template <typename T>
int bfsSerach(queue <T>& q)
{
	int sum = 0;
	while (!q.empty())
	{
		pair<int, int>cur = q.front(); q.pop(); sum++;
		cout << '(' << cur.X << ',' << cur.Y << ')' << "->"; 
		for (int i = 0; i < 4; i++)
		{
			int nx = cur.X + dx[i];
			int ny = cur.Y + dy[i];
			if (nx >= n || nx < 0 || ny >= m || ny < 0)continue; //격자 범위 넘어가면 스킵 
			if (vis[nx][ny] || board[nx][ny] != 1)continue;
			q.push({ nx,ny });
			vis[nx][ny] = 1;//큐에 삽입과 동시에 방문했다 표시남김 같은칸에대해 중복 삽입을 막기 위해 넣자마자 바로 방문표시 
			dist[nx][ny] = dist[cur.X][cur.Y] + 1;
		}
	}
	return sum;
}
int main()
{
	queue<pair<int, int>> q;
	q.push({ 0,0 });
	vis[0][0]=1;
	int a=bfsSerach(q);
	cout << a;

}