#include <iostream>

using namespace std;

long long cnt = 0;
int n;

bool col[20];       // ��
bool mark[20][20];  // �� ���� �ڸ� ��ŷ��
bool r_di[40]; // ���� ���� �밢��: ������� ���� ������ ���� �� �밢�� 
bool l_di[40]; // ���� ���� �밢��: ��� ���� ���� ������ ���� �� �밢��

void Search(int row) //��Ʈ��ŷ���� ��ġ���� , row���� 0~19 ������ ���� �� �� ã�� 
{
  if (row == n) //��� �������� ��� ���� Ž���� �ѹ� �� ȣ���� ��� ���Ǹ��� 
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
  {                                                     // �� �ึ�� 0~n-1������ ���� ��ȸ
    if (col[i] || r_di[i + row] || l_di[row - i + n-1]) // ���� ������ ���ΰ��(��,��,��밢���� �����ִ°��) ����� ,n-1�� �ε����� ������ �ȵǰ� �ϱ� ���� ������
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