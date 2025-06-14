#include <bits/stdc++.h>
using namespace std;

#define X first 
#define Y second
#define TUPLE tuple<int,int,int>
//몬스터 이동
int dx[8]={-1,-1,0,1,1,1,0,-1}; 
int dy[8]={0,-1,-1,-1,0,1,1,1}; 

//팩맨이동 방향 
int fdx[4]={-1,0,1,0};
int fdy[4]={0,-1,0,1};
//몬스터는 시체,알,생명 상태  (턴,상태,방향) 3가지 값을 가지고있어야하며   시체는 2턴부터 소멸 
vector<pair<int,int>> monster[4][4]; //몬스터 방향,이동상태   
vector<int> egg[4][4]; //알 방향 기록  
vector<int> death[4][4]; //시체 현재 턴수 기록  

int fdir[3]; // 팩맨이 3가지 이동방향 0 상 1 좌 2 하 3 우 
pair<int,int> fpt; //현재 팩맨 위치 
int m, t; //몬스터 마리수 턴수 


bool over(int x ,int y)
{
    if(x<0||x>=4||y<0||y>=4)return true;
    return false;
}

void dupl()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(monster[i][j].empty())continue;
            for(auto cur: monster[i][j])
            {
                int dir=cur.X;
                egg[i][j].push_back(dir);
            }

        }
    }
}
void mmove() //몬스터이동 
{
    for(int x=0;x<4;x++)
    {
        for(int y=0;y<4;y++)
        {
            if(monster[x][y].empty())continue;
            vector<pair<int,int>> temp;//복구배열 
            for(auto cur: monster[x][y])
            {
                if(cur.Y!=0) //이동한적 있는 몬스터 
                {
                  temp.push_back(cur);
                  continue;
                }
                int dir=cur.X;
                int t=dir;
                bool flag=false; //이동유무 
                do
                {
                    int nx=x+dx[dir];
                    int ny=y+dy[dir];
                    if(over(nx,ny)||(nx==fpt.X&&ny==fpt.Y)||!death[nx][ny].empty())
                    {
                        dir++;
                        if(dir==8)dir=0;
                    }
                    else //이동가능 
                    {
                        monster[nx][ny].push_back({dir,1});//이동표시 
                        flag=true;
                        break;
                    }     
                }while(dir!=t);
                if(!flag)temp.push_back(cur);
            }
            monster[x][y]=temp;
        }
    }
}
int maxn=0;
int tdir[3];
bool vis[4][4];
//재방문을 허용해야 최적경로에서 길이 막히는 경우를 방지할 수 있다.....
void fmove(pair<int,int> cur, int cnt, int depth) {
    if (depth == 3) {
        if (cnt > maxn) {
            maxn = cnt;
            for (int i = 0; i < 3; ++i) fdir[i] = tdir[i];
        }
        return;
    }
    for (int dir = 0; dir < 4; ++dir) {
        int nx = cur.X + fdx[dir];
        int ny = cur.Y + fdy[dir];
        if (over(nx, ny)) continue;
        tdir[depth] = dir;
        bool first = !vis[nx][ny];                  // 처음 밟는 칸인가?
        vis[nx][ny] = true;                         // 칸 자체는 표시
        fmove({nx, ny}, cnt + (first ? monster[nx][ny].size() : 0), depth + 1);
        vis[nx][ny] = !first;                       // 원복: 처음 밟은 경우만 해제
    }
}
void eat() //실제로 경로돌면서 먹기 
{
    for(int i=0;i<3;i++)
    {
      int di=fdir[i];
      fpt.X+=fdx[di];
      fpt.Y+=fdy[di];
      if(!monster[fpt.X][fpt.Y].empty())
      {
        monster[fpt.X][fpt.Y].clear();
        death[fpt.X][fpt.Y].push_back(0);
      }
    }
    maxn=0;
}
void disappear()
{
  for(int i=0;i<4;i++)
  {
    for(int j=0;j<4;j++)
    {
      vector<int> temp;//복구배열 
      for(auto t: death[i][j])
      {
        if(t>=2)continue; //시체 소멸 
        temp.push_back(t+1); //시체 턴+1로 넣어줌 
      }
      death[i][j]=temp;
    }
  }
}
void wakeup() 
{
  for(int i=0;i<4;i++)
  {
    for(int j=0;j<4;j++)
    {
      for(auto dir: egg[i][j])
      {
        monster[i][j].push_back({dir,0});
      }
      egg[i][j].clear();
    }
  }
}
//이동표시 리셋
void reset()
{
  for(int x=0;x<4;x++)
  {
    for(int y=0;y<4;y++)
    {
      int len=monster[x][y].size();
      for(int i=0;i<len;i++)
      {
        monster[x][y][i].Y=0;
      }
      vis[x][y]=false;
    }
  }
}


int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>m>>t;
    cin>>fpt.X>>fpt.Y;
    fpt.X--;
    fpt.Y--;
    int r,c,d;
    for(int i=0;i<m;i++)
    {
        cin>>r>>c>>d;
        //cout<<r<<' '<<c<<' '<<d<<'\n';
        monster[r-1][c-1].push_back({d-1,0});
    }
    while(t--)
    {
        dupl();
        mmove();
        vis[fpt.X][fpt.Y]=true;
        fmove(fpt,0,0);
        eat();
        disappear();
        wakeup();
        reset();
    }
    int ans=0;
    for(int i=0;i<4;i++)
    {
      for(int j=0;j<4;j++)
      {
        ans+=monster[i][j].size();
      }
    }
    cout<<ans;


    return 0;

}