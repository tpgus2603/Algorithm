#include <iostream>
#include <algorithm>
using namespace std;

int arr[1001];

void merge(int st, int en)
{
  int left = st;
  int mid = (st + en) / 2;
  int right = mid;
  int temp[1001];
  for (int i = st; i <= en; i++)
  {
    if (left != mid && (arr[left] <= arr[right] || right == en + 1))
      temp[i] = arr[left++];
    else
      temp[i] = arr[right++];
  }
  for (int i = st; i <= en; i++)
    arr[i] = temp[i];
}
void mergesort(int st, int en)
{
  if (en - st <= 0)
    return;
  int mid = (st + en) / 2;
  mergesort(st, mid);
  mergesort(mid + 1, en);
  merge(st, en);
}

int partition(int st, int en)
{
  int pivot = st;
  int left = st + 1;
  int right = en;
  while (1)
  {
    while (left <= right && arr[left] <= arr[pivot]) // �Ǻ����� ū�� ã��
      left++;
    while (left <= right && arr[right] >= arr[pivot])
      right--;
    if (left > right) //�����Ǹ� �ݺ��� ���� 
      break;
    swap(arr[left], arr[right]);
  }
  swap(arr[right], arr[st]); //�ǹ���ġ ã�� 
  return right;
}

void quicksort(int st, int en)
{
  if (en - st <= 0)
    return;
  int pivot = partition(st, en);
  quicksort(st, pivot - 1);
  quicksort(pivot + 1, en);
}