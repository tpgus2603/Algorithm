#include <bits/stdc++.h>
using namespace std;

int main() {
    const int N = 3;
    int a[N][N] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    int b[N][N];

    // 90도 시계 방향
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            cout<<a[j][N-1-i]<<' ';
        }
        cout<<'\n';
    }
}