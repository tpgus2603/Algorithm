#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
#define X first
#define Y second

/* ───── 전역 ───── */
int N, Q;
int dish[15][15];          // 현재 배양 용기
int ndish[15][15];         // 이주용 임시 용기

struct Micro{
    int id, area;
    int minR, minC, maxR, maxC;
    vector<pair<int,int>> cell; //좌표정보 
};
vector<Micro> micros;      // 이번 단계 살아남은 무리
bool dead[55];             // 영구 사망 여부

int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
bool over(int x,int y){ return x<0||x>=N||y<0||y>=N; }

/* ───── 1. 투입 ───── */
void inject(int id, int r1, int c1, int r2, int c2) {
    for (int r = r1; r < r2; r++)        
        for (int c = c1; c < c2; c++)   
            dish[r][c] = id;
}

/* ───── 2. 생존 판정 ───── */
void collect_alive(){
    micros.clear();
    int vis[15][15]={0};
    bool seen[55]={0};

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++){
            int id=dish[i][j];
            if(id==0||vis[i][j]||dead[id])continue;

            queue<pair<int,int>> q;
            q.push({i,j});
            vis[i][j]=1;

            Micro m; m.id=id; m.area=0;
            m.minR=m.minC=20; m.maxR=m.maxC=-1;

            while(!q.empty()){
                auto cur=q.front(); q.pop();
                m.cell.push_back(cur); m.area++;

                m.minR=min(m.minR,cur.X); m.minC=min(m.minC,cur.Y);
                m.maxR=max(m.maxR,cur.X); m.maxC=max(m.maxC,cur.Y);

                for(int d=0;d<4;d++){
                    int nx=cur.X+dx[d], ny=cur.Y+dy[d];
                    if(over(nx,ny)||vis[nx][ny]||dish[nx][ny]!=id)continue;
                    vis[nx][ny]=1; q.push({nx,ny});
                }
            }
            if(seen[id]) dead[id]=true;          // 두 개 이상 성분 → 전체 사망
            else{ seen[id]=true; micros.push_back(m); }
        }

    /* 사망 ID 제거 */
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(dead[dish[i][j]]) dish[i][j]=0;

    vector<Micro> alive;
    for(auto &m:micros) if(!dead[m.id]) alive.push_back(m);
    micros.swap(alive);
}

/* ───── 3. 이주 ───── */
bool cmp(const Micro& a,const Micro& b){
    if(a.area!=b.area) return a.area>b.area;
    return a.id<b.id;
}
void reset_ndish(){ memset(ndish,0,sizeof ndish); }

bool fit(const Micro& m,int sr,int sc){
    for(auto p:m.cell){ //모든 좌표에대해서 해야함 
        int nr=sr+(p.X-m.minR), nc=sc+(p.Y-m.minC);
        if(over(nr,nc)||ndish[nr][nc]) return false;
    }
    return true;
}
void place(const Micro& m,int sr,int sc){
    for(auto p:m.cell){
        int nr=sr+(p.X-m.minR), nc=sc+(p.Y-m.minC);
        ndish[nr][nc]=m.id;
    }
}
void migrate(){
    reset_ndish();
    sort(micros.begin(),micros.end(),cmp);

    for(const auto &m:micros){
        for(int r=0;r<N;r++){
            bool done=false;
            for(int c=0;c<N;c++)
                if(fit(m,r,c)){ place(m,r,c); done=true; break; }
            if(done) break;
        }
    }
    memcpy(dish,ndish,sizeof dish);
}

/* ───── 4. 점수 계산 ───── */
long long calc_score(){
    bool adj[55][55]={0};
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++){
            int a=dish[i][j]; if(!a)continue;
            for(int d=0;d<4;d++){
                int ni=i+dx[d], nj=j+dy[d];
                if(over(ni,nj))continue;
                int b=dish[ni][nj];
                if(b&&a!=b) adj[a][b]=adj[b][a]=true;
            }
        }
    long long res=0;
    for(const auto &x:micros)
        for(const auto &y:micros)
            if(x.id<y.id&&adj[x.id][y.id])
                res+=1LL*x.area*y.area;
    return res;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0);

    cin >> N >> Q;
    for (int id = 1; id <= Q; id++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;   
        inject(id, r1, c1, r2, c2);    
        collect_alive();              
        migrate();                   
        cout << calc_score() << '\n';  
    }
    return 0;
}
