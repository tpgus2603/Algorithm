#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

// 네가 늘 쓰는 방향: 0=상, 1=우, 2=하, 3=좌
int dx[4] = {-1, 0, 1, 0};
int dy[4] = { 0, 1, 0,-1};

int A[MAXN][MAXN];                       // 채운 값(센터→바깥)
vector<pair<int,int>> P_center;          // 경로(순서대로, 0-based 좌표)

// 범위 체크(0-based)
inline bool over(int x, int y, int n) {
    return (x < 0 || x >= n || y < 0 || y >= n);
}

// 센터에서 시작해 좌→하→우→상 순으로 나선 채우기 (센터는 0 유지)
void spiral_from_center(int n) {
    // 초기화
    for (int i = 0; i < n; ++i) fill(A[i], A[i] + n, 0);
    P_center.clear();

    int x = n / 2, y = n / 2;    // 시작: 중앙(0-based)
    long long num = 0;           // 채울 값 (센터는 0 유지)
    int dist = 1;                // 한 번에 이동할 칸 수

    // 우리의 기본 방향(상,우,하,좌)에서 '좌,하,우,상' 순서를 만들기 위한 매핑
    // 좌(3) → 하(2) → 우(1) → 상(0)
    int order[4] = {3, 2, 1, 0};
    int idx = 0;                 // order 인덱스

    // 센터 좌표도 경로에 포함(값은 0 유지)
    P_center.push_back({x, y});

    // 전체 칸 n*n 중 센터 제외 n*n - 1 칸을 채움
    while (num < 1LL * n * n - 1) {
        // 같은 dist로 두 방향을 처리(좌→하), 이후 dist 증가
        for (int rep = 0; rep < 2; ++rep) {
            int dir = order[idx];

            for (int step = 0; step < dist; ++step) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                // 한 칸 전진은 항상 수행
                x = nx; y = ny;

                // 범위 밖이면 채우기/기록은 건너뜀
                //if (over(x, y, n)) continue;

                ++num;
                A[x][y] = (int)num;
                P_center.push_back({x, y});

                if (num == 1LL * n * n - 1) break;
            }
            if (num == 1LL * n * n - 1) break;

            // 방향 인덱스 회전
            idx = (idx + 1) % 4;
        }
        ++dist;
    }
}

// ===== 바깥→안 나선 =====
int B[MAXN][MAXN];
vector<pair<int,int>> P_corner;

void spiral_from_corner(int n) {
    for (int i = 0; i < n; ++i) fill(B[i], B[i] + n, 0);
    P_corner.clear();

    long long num = 1;
    int top = 0, left = 0, bottom = n-1, right = n-1;

    while (top <= bottom && left <= right) {
        // 우
        for (int y = left; y <= right; ++y) {
            int x = top;
            B[x][y] = (int)num++;
            P_corner.push_back({x,y});
        }
        ++top;
        // 하
        for (int x = top; x <= bottom; ++x) {
            int y = right;
            B[x][y] = (int)num++;
            P_corner.push_back({x,y});
        }
        --right;
        if (top > bottom || left > right) break;
        // 좌
        for (int y = right; y >= left; --y) {
            int x = bottom;
            B[x][y] = (int)num++;
            P_corner.push_back({x,y});
        }
        --bottom;
        // 상
        for (int x = bottom; x >= top; --x) {
            int y = left;
            B[x][y] = (int)num++;
            P_corner.push_back({x,y});
        }
        ++left;
    }
}

// ===== 출력 =====
void print_arr(int arr[MAXN][MAXN], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << arr[i][j] << (j + 1 == n ? '\n' : ' ');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 5;

    // 센터→바깥
    spiral_from_center(n);
    cout << "[center->out 배열값]\n";
    print_arr(A, n);

    cout << "경로 first 8: ";
    for (int i = 0; i < (int)P_center.size() && i < 8; ++i) {
        cout << "(" << P_center[i].first << "," << P_center[i].second << ") ";
    }
    cout << "\n\n";

    // 바깥→안
    spiral_from_corner(n);
    cout << "[corner->in 배열값]\n";
    print_arr(B, n);

    cout << "경로 first 8: ";
    for (int i = 0; i < (int)P_corner.size() && i < 8; ++i) {
        cout << "(" << P_corner[i].first << "," << P_corner[i].second << ") ";
    }
    cout << "\n";

    return 0;
}
