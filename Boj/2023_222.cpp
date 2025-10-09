#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cmath>
#include<cstring>
#define X first 
#define Y second
using namespace std;

struct santa{
  int x,y,num,t;   // 좌표, 번호, "기절이 끝나는 턴"(turn+1로 관리)
  bool iskill;     // 탈락 여부
};

int dx[8]={-1,0,1,0, 1,1,-1,-1};   // 0~3: 상우하좌(산타), 0~7: 8방향(루돌프)
int dy[8]={ 0,1,0,-1,1,-1, 1,-1};

int N,M,P,C,D;
pair<int,int> pt;                  // 루돌프 위치(1-based)
vector<santa> slist;               // 1..P (0은 더미)
map<pair<int,int>,int> smap;       // (x,y) -> 산타번호(1..P), 없으면 0
vector<int> score;                 // 1..P
int turn=1;
int knum=0;

inline bool over(int x,int y){
  return (x<=0 || x>N || y<=0 || y>N);
}
inline int dis(pair<int,int> a, pair<int,int> b){
  return (a.X-b.X)*(a.X-b.X) + (a.Y-b.Y)*(a.Y-b.Y);
}

/* knock: 산타 idx를 dir 방향으로 steps칸 넉백.
   최종 도착칸 (sx+dx*steps, sy+dy*steps)이 맵 밖이면 탈락.
   도착칸이 다른 산타로 차 있으면 그 산타를 같은 방향으로 '1칸' 재귀 밀치기 후 내가 들어감.
   호출 전: 호출자가 idx의 '현재 위치를 smap에서 비워둔' 상태가 안전(충돌칸에서 바로 튕길 때 등).
*/
void knock(int idx, int dir, int steps){
  if(slist[idx].iskill) return;
  int sx = slist[idx].x, sy = slist[idx].y;
  int tx = sx + dx[dir]*steps;
  int ty = sy + dy[dir]*steps;

  if(over(tx,ty)){
    slist[idx].iskill = true;
    knum++;
    return;
  }

  int occ = smap[{tx,ty}];
  if(occ > 0){
    // 그 산타를 1칸 먼저 밀어 공간 만들기
    // (점유칸을 비운 뒤 재귀로 밀어낸다)
    smap[{tx,ty}] = 0;
    knock(occ, dir, 1); // 점유자 1칸 연쇄 밀치기
  }

  // idx 배치 (살아있으면)
  if(!slist[idx].iskill){
    slist[idx].x = tx; slist[idx].y = ty;
    smap[{tx,ty}] = idx;
  }
}

// 루돌프 이동 + 충돌 처리
void rmove(){
  // 타겟 산타: 거리^2 최소, 동률이면 x 큰, 그래도 동률이면 y 큰
  int best=-1, bestd=1e9, bx=-1, by=-1;
  for(int i=1;i<=P;i++){
    if(slist[i].iskill) continue;
    int dd = dis({slist[i].x,slist[i].y}, pt);
    if(dd<bestd || (dd==bestd && (slist[i].x>bx || (slist[i].x==bx && slist[i].y>by)))){
      best=i; bestd=dd; bx=slist[i].x; by=slist[i].y;
    }
  }
  if(best==-1) return;

  // 8방향 한 칸 중 타겟과의 거리^2가 최소가 되는 칸
  int cdir=0, mind=1e9, nx=pt.X, ny=pt.Y;
  for(int d=0; d<8; d++){
    int tx = pt.X + dx[d], ty = pt.Y + dy[d];
    if(over(tx,ty)) continue;
    int td = dis({tx,ty},{bx,by});
    if(td < mind){ mind=td; cdir=d; nx=tx; ny=ty; }
  }

  // 충돌?
  int occ = smap[{nx,ny}];
  if(occ>0){
    // 점수 C, 기절 turn+1
    score[occ] += C;
    slist[occ].t = turn + 1;
    // 충돌칸 비우고 occ 넉백(C칸, 루돌프 진행방향, 8방향)
    smap[{nx,ny}] = 0;
    knock(occ, cdir, C);
  }

  // 루돌프 위치 갱신
  pt = {nx,ny};
}

// 산타 이동(1..P)
void smove(){
  for(int i=1;i<=P;i++){
    if(slist[i].iskill) continue;
    if(slist[i].t >= turn) continue; // 기절이면 스킵

    int cx=slist[i].x, cy=slist[i].y;
    int base = dis({cx,cy}, pt);

    // 상(0)우(1)하(2)좌(3) 중, 거리^2를 엄격히 줄이는 칸
    int cdir=-1, bestd=base, nx=cx, ny=cy;
    for(int d=0; d<4; d++){
      int tx=cx+dx[d], ty=cy+dy[d];
      if(over(tx,ty)) continue;
      if(smap[{tx,ty}]>0) continue;
      int td = dis({tx,ty}, pt);
      if(td < bestd){ bestd=td; cdir=d; nx=tx; ny=ty; }
    }
    if(cdir==-1) continue; // 못 감

    // 원래 자리 비움
    smap[{cx,cy}] = 0;

    // 루돌프와 충돌?
    if(nx==pt.X && ny==pt.Y){
      // 점수 D, 기절 turn+1
      score[i] += D;
      slist[i].t = turn + 1;

      // 계산 시작좌표를 "충돌칸"으로 맞춰야 함
      slist[i].x = nx; slist[i].y = ny;

      // 반대방향으로 D칸 넉백 (산타는 4방향)
      int od = (cdir + 2) % 4;
      knock(i, od, D);
      continue;
    }

    // 충돌 없음 → 배치
    slist[i].x = nx; slist[i].y = ny;
    smap[{nx,ny}] = i;
  }
}

// 턴 종료: 생존자 +1점
void fin(){
  for(int i=1;i<=P;i++){
    if(!slist[i].iskill) score[i]++;
  }
}

int main(){
  ios::sync_with_stdio(0);cin.tie(0);

  cin>>N>>M>>P>>C>>D;
  cin>>pt.X>>pt.Y;

  slist.assign(P+1, {0,0,0,-1,false});
  score.assign(P+1,0);
  smap.clear();

  for(int i=0;i<P;i++){
    int p,x,y; cin>>p>>x>>y;
    slist[p].num=p; slist[p].x=x; slist[p].y=y;
    smap[{x,y}] = p;
  }

  for(turn=1; turn<=M; ++turn){
    if(knum==P) break;
    rmove();
    smove();
    fin();
  }

  for(int i=1;i<=P;i++){
    cout<<score[i]<<' ';
  }
  return 0;
}
