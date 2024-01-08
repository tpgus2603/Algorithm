#include <iostream>

using namespace std;

long long cnt = 0;
int n;

bool col[20];       // 열
bool mark[20][20];  // 퀸 들어가는 자리 마킹용
bool r_di[40]; // 우측 방향 대각선: 행과열의 합이 같으면 같은 우 대각선 
bool l_di[40]; // 좌측 방향 대각선: 행과 열의 차가 같으면 같은 좌 대각선

void Search(int row) //백트랙킹으로 서치구현 , row행의 0~19 열에서 퀸이 들어갈 열 찾음 
{
  if (row == n) //재귀 종료조건 모든 행을 탐색후 한번 더 호출한 경우 조건만족 
  {
    cnt++;
    if (cnt == 1)
    {
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++)
        {
          if (mark[i][j])
            cout << "Q";
          else
            cout << "_";
        }
        cout<<'\n';
      }
    
    }
    return;
  }
  for (int i = 0; i < n; i++)
  {                                                     // 각 행마다 0~n-1까지의 열을 순회
    if (col[i] || r_di[i + row] || l_di[row - i + n-1]) // 퀸을 못놓는 열인경우(열,좌,우대각선에 퀸이있는경우) 프루닝 ,n-1은 인덱스가 음수가 안되게 하기 위한 보정값
      continue;
    col[i] = 1;
    mark[row][i] = 1;
    r_di[i + row] = 1;
    l_di[row - i + n-1] = 1;
    Search(row + 1);
    col[i] = 0;
    mark[row][i]=0;
    r_di[i + row] = 0;
    l_di[row - i + n-1] = 0;
  }
}
int main(void)
{
  cin >> n;
  Search(0);
  cout << cnt;
}