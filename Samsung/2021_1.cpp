#include <bits/stdc++.h>
using namespace std;
#define X first 
#define Y second
int dx[4]={0,1,0,-1}; // -> 아래 <- 위 방향 순서  
int dy[4]={1,0,-1,0};
int dir; //0,1,2,3
pair<int,int> cur;
int dice[6]={1,2,3,4,5,6};
int n,m;
int arr[20][20]; //격자판
long long ans;
bool over(int x,int y)
{
    if(x<0||x>=n||y<0||y>=n)return true;
    return false;
}
void bfs()
{
    bool vis[20][20]={0};
    int temp=arr[cur.X][cur.Y];
    vis[cur.X][cur.Y]=true;
    ans+=temp;
    queue<pair<int,int>> q;
    q.push(cur);
    while(!q.empty())
    {
        auto cu=q.front();
        q.pop();
        for(int i=0;i<4;i++)
        {
            int nx=cu.X+dx[i];
            int ny=cu.Y+dy[i];
            if(over(nx,ny))continue;
            if(arr[nx][ny]!=temp||vis[nx][ny])continue;
            vis[nx][ny]=true;
            ans+=temp;
            q.push({nx,ny});
        }
    }
}
void refl()
{
    if(dir==0)dir=2;
    else if(dir==1)dir=3;
    else if(dir==2)dir=0;
    else if(dir==3)dir=1;
}
void change()
{
    if(dir==0) //동쪽이동 
    {
        swap(dice[2],dice[5]);
        swap(dice[2],dice[3]);
        swap(dice[2],dice[0]);
    }
    else if(dir==1)//남쪽이동 
    {
        swap(dice[1],dice[5]);
        swap(dice[1],dice[4]);
        swap(dice[1],dice[0]);

    }
    else if(dir==2) //서쪽 
    {
        swap(dice[3],dice[5]);
        swap(dice[3],dice[2]);
        swap(dice[3],dice[0]);
    }
    else
    {
        swap(dice[4],dice[5]);
        swap(dice[4],dice[1]);
        swap(dice[4],dice[0]);
    }
}

//dir은 전역변수 
void go()
{
    int nx=cur.X+dx[dir];
    int ny=cur.Y+dy[dir];
    if(over(nx,ny))
    {
        refl();
        go();
        return;
    }
    cur={nx,ny};
    change();
    bfs();
    //cout<<dice[2]<<' '<<ans<<'\n';
    //방향바꿔주기 
    if(dice[5]>arr[nx][ny])
    {
        dir=(dir+1)%4;
    }
    else if(dice[5]<arr[nx][ny])
    {
        dir--;
        if(dir==-1)dir=3;
    }
}


int main() {
    

    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>arr[i][j];
        }
    }
    cur={0,0};
    while(m--)
    {
        go();
    }

    cout<<ans;

    return 0;
}
