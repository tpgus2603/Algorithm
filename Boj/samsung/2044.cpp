#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------------
// 전역 상수/배열 (최대 N=10)
const int MAXN = 10;

int N;                                   // 한 변 길이
int A[MAXN][MAXN];                       // 지도 (0:빈칸, 1:사람, 2~10: 계단 길이)
vector<pair<int,int>> P;                 // 사람 좌표 목록 (x=row, y=col) 0-based
pair<int,int> Spos[2];                   // 계단 좌표
int Slen[2];                             // 계단 길이
int Scnt;                                // 계단 개수(=2)

// 좌표 관례: x=row, y=col
int dx[4] = {-1, 0, 1, 0};               // 상,우,하,좌 (문제엔 맨해튼만 쓰임)
int dy[4] = { 0, 1, 0,-1};

// -----------------------------------------------------
// 보조: 범위/맨해튼
inline bool over(int x, int y) {
    return (x < 0 || x >= N || y < 0 || y >= N);
}
inline int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// -----------------------------------------------------
// 케이스별 전역 초기화
inline void reset_case() {
    // 정적 배열은 반드시 매 케이스마다 초기화
    memset(A, 0, sizeof(A));

    // 벡터/컨테이너는 clear로 리셋
    P.clear();
    Spos[0] = Spos[1] = {-1,-1};
    Slen[0] = Slen[1] = 0;
    Scnt = 0;
}

// -----------------------------------------------------
// 입력 파싱(한 케이스)
inline void read_case() {
    cin >> N;
    reset_case();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
            if (A[i][j] == 1) {
                P.push_back({i, j});             // 사람 기록
            } else if (A[i][j] >= 2) {
                // 계단 2개 수집
                if (Scnt < 2) {
                    Spos[Scnt] = {i, j};
                    Slen[Scnt] = A[i][j];
                    ++Scnt;
                }
            }
        }
    }
    // 문제 조건상 Scnt==2, 사람 수 1~10
}

// -----------------------------------------------------
// 핵심 로직: 최소 이동 완료 시간 계산
//  - 사람을 두 계단 중 어느 쪽으로 보낼지 모든 할당(bitmask) 완전탐색
//  - 각 계단별로 '도착시간 -> 대기(입구) -> 계단(최대 동시 3명, K분)' 시뮬
//  - 두 계단 완료시간의 max가 해당 할당의 총 소요, 그 중 최소를 반환
int solve_one() {
    const int M = (int)P.size();         // 사람 수 (<=10)
    // 사람 수가 0일 일응 방어
    if (M == 0) return 0;

    // 미리 각 사람->계단까지 도착시간(=맨해튼)을 계산해두면 캐시 히트 좋음
    int arrive[10][2] = {0};
    for (int i = 0; i < M; ++i) {
        for (int s = 0; s < 2; ++s) {
            arrive[i][s] = manhattan(P[i].first, P[i].second, Spos[s].first, Spos[s].second);
        }
    }

    auto simulate_stair = [&](vector<int> times, int K) -> int {
        // times: 해당 계단으로 오는 사람들의 "입구 도착시간"
        // 규칙:
        //   - 입구 도착 후 1분 대기 뒤 계단에 오를 수 있음
        //   - 계단 동시 최대 3명, 계단 위에 오른 후 K분 지나면 완주
        // 구현:
        //   1) times를 오름차순 정렬
        //   2) 진행 중인 사람들의 '완주시각'을 min-heap으로 관리
        //   3) 각 사람의 실제 탑승시각 = max(도착+1, (heap.size()==3 ? heap.top()+1 : 도착+1))
        //      - 단, 3명이 꽉 차면 그 중 가장 먼저 내려오는 시각까지 기다린 뒤 +1에 탑승
        if (times.empty()) return 0;
        sort(times.begin(), times.end());
        priority_queue<int, vector<int>, greater<int>> pq; // 계단 위 3명까지의 완주시각
        int last = 0;

        for (int t_arr : times) {
            int cand = t_arr + 1; // 입구에서 1분 후 진입 시도
            // 계단이 가득 차 있으면, 누군가 내려올 때까지 대기
            while ((int)pq.size() == 3 && pq.top() >= cand) {
                // 가장 빨리 완주하는 사람을 꺼내 그 시각 이후에 진입해야 함
                cand = pq.top() + 1;
                pq.pop();
            }
            // 자리 비었으면, capacity<3일 때는 pq.size()<3이 되어 루프를 안 타고 바로 내려옴
            // 혹시 위 while을 안 탔고 size==3인 경우 cand <= pq.top() 이면 또 while로 들어갔을 것이므로 안전
            // 이제 탑승 -> 완주시각 push
            int finish = cand + K - 1; // K분 내려가므로 cand 포함하여 K-1 더함
            pq.push(finish);
            last = max(last, finish);
        }
        return last;
    };

    int best = INT_MAX;
    // 사람을 두 그룹으로 나누는 모든 비트마스크 (0 -> stair0, 1 -> stair1)
    for (int mask = 0; mask < (1 << M); ++mask) {
        vector<int> T0, T1;
        T0.reserve(M); T1.reserve(M);
        for (int i = 0; i < M; ++i) {
            if (mask & (1 << i)) T1.push_back(arrive[i][1]);
            else                 T0.push_back(arrive[i][0]);
        }
        int fin0 = simulate_stair(T0, Slen[0]);
        int fin1 = simulate_stair(T1, Slen[1]);
        best = min(best, max(fin0, fin1));
    }
    return best;
}

// -----------------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    if (!(cin >> T)) return 0;
    for (int tc = 1; tc <= T; ++tc) {
        read_case();
        int ans = solve_one();
        cout << "#" << tc << " " << ans+1 << '\n';
    }
    return 0;
}
