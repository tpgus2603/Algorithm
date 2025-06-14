#include <iostream>
#include <vector>
#include <queue>
#include<algorithm>
#include<cmath>
using namespace std;
#define X first 
#define Y second

int arr[101][101][4][101]; //1-based 도망자 위치 ,방향값 인덱스,턴수를 인덱스로 값을 인원수 넣음 
bool tree[101][101]; //트리위치 
int ddx[4] ={0,0,1,-1};    //도망자   
int ddy[4]={-1,1,0,0};
int pdx[4]={-1,0,1,0}; //술래 시계방향 
int pdy[4]={0,1,0,-1};
pair<int,int> pt; //술래위치 
int pdir=0;
int n,m,h,k;
int ans;

bool over(int x,int y)
{
    if(x<=0||x>n||y<=0||y>n)return true;
    return false;
}

int refl(int dir)
{
    switch(dir)
    {
        case 0: return 1;
        case 1: return 0;
        case 2: return 3;
        case 3: return 2;
    }
    return 0;
}
int tag,cnt,num; //tag가 2일때 cnt가 num칸 num+1 tag=0 ; 기본적으로 cnt가 num칸 이동시 tag++,방향 전환  
int cl; //0이면 시계 1이면 반시계 
//술래 움직임 시계방향으로 1,1,2,2,3,3,4,4칸 ..씩 
//반 시게 방향으론 4,4,
void pmove(int t) 
{
    //술래 이동 
    if(pt.X==n/2+1&&pt.Y==n/2+1) //중앙에 온 경우 
    {
        cl=0;
        tag=0;
        cnt=0;
        num=1;
        pdir=0;//위방향 
    }
    else if(pt.X==1&&pt.Y==1)
    {
        cl=1;
        tag=-1;
        cnt=0;
        pdir=2; //아래방향 
    }
    pt.X+=pdx[pdir];
    pt.Y+=pdy[pdir];
    cnt++;
    if(cnt==num)
    {
        cnt=0;
        tag++;
        if(cl==0) //시계인경우 
        {
            if(tag==2) //그중에서도 두번 수행한경우 
            {
                num++;
                if(num==n)num--; //격자 길이-1이 최대 
                tag=0;
            }
            pdir=(pdir+1)%4;
        }
        else{ //반시계인경우 
            if(tag==2)
            {
                num--;
                tag=0;
            }
             pdir--;
            if(pdir==-1)pdir=3;
        }
    }
    //cout<<pt.X<<' '<<pt.Y<<'\n';
    
    //술래  도망자 잡기 (현재 칸 포함 3칸)
    
    //현재칸 
    if(!tree[pt.X][pt.Y])
    {
        for(int dir=0;dir<4;dir++)
        {
            ans+=arr[pt.X][pt.Y][dir][t]*t;
            arr[pt.X][pt.Y][dir][t]=0;
        }
    }
    int nx=pt.X;
    int ny=pt.Y;
    int idx=2;
    while(idx--)
    {
        nx=nx+pdx[pdir];
        ny=ny+pdy[pdir];
        if(over(nx,ny))break;
        if(tree[nx][ny])continue;
        for(int dir=0;dir<4;dir++)
        {
            ans+=arr[nx][ny][dir][t]*t;
            arr[nx][ny][dir][t]=0;
        }
    }
}
void dmove(int t) //도망자 움직임  움직인놈이 또 움직이면안됨(턴수 도입 )
{
    for(int x=1;x<=n;x++)
    {
        for(int y=1;y<=n;y++)
        {
            for(int dir=0;dir<4;dir++)
            {
                if(arr[x][y][dir][t-1]==0)continue;//없는경우 
                if(abs(x-pt.X)+abs(y-pt.Y)>3)
                {
                    arr[x][y][dir][t]+=arr[x][y][dir][t-1]; //남겨줌 
                    continue; //거리가 3넘는 경우 
                }
                int nx=x+ddx[dir];
                int ny=y+ddy[dir];
                if(over(nx,ny)) //격자 벗어나는 경우 
                {
                    int next=refl(dir); // 반대로 
                    nx=x+ddx[next];
                    ny=y+ddy[next];
                    if(pt.X==nx&&pt.Y==ny)//술래가 있는경우 
                    {
                        arr[x][y][dir][t]+=arr[x][y][dir][t-1]; //남겨줌 
                        continue;
                    }
                    //도망자 이동 
                    arr[nx][ny][next][t]+=arr[x][y][dir][t-1];
                }
                else //격자 안 벗어남 
                {
                    if(pt.X==nx&&pt.Y==ny)
                    {
                        arr[x][y][dir][t]+=arr[x][y][dir][t-1]; //남겨줌 
                        continue;
                    }
                    arr[nx][ny][dir][t]+=arr[x][y][dir][t-1]; //이동 
                }
            }
        }
    }
}


int main() {
    
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>h>>k;
    //도망자 입력 
    int x,y,d;
    for(int i=0;i<m;i++)
    {
        cin>>x>>y>>d;
        arr[x][y][d][0]++; 
    }
    for(int i=0;i<h;i++)
    {
        cin>>x>>y;
        tree[x][y]=true;
    }
    pt.X=n/2+1;pt.Y=n/2+1;
    for(int t=1;t<=k;t++)
    {
        dmove(t);
        pmove(t);
    }
    cout<<ans;

    return 0;
}