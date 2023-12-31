#include <vector>
#include <iostream>
using namespace std;
int n = 15;
int arr[1000001] = {0};
int k = 3; //k=자리수 최대값 
int p10[3]; //10의 지수값 저장배열 
int digitnum(int x, int a)
{
	return (x / p10[a]) % 10;
}

int count[100001];
vector<int> sort;
void countsort()  //o(n+k)알고리즘 k는 수의 범위 n은 수의 개수 배열공간이 수의범위만큼 필요해 커질수록 메모리 부담이 큼 
{
	int temp;
	int k;
	cin >> k;
	for(auto k:arr)
	{
		count[k]++;
	}
	for (int i = 0; i <= k; i++)
	{
		if (count[i] != 0)
		{
			while (count[i]--)
				sort.push_back(k);
		}
	}
}

//O(k(n+r)) //k=3 r=10
vector<int> l[10];//  배열 속 자리수 들의 값에 해당하는 리스트  
int main()
{
	p10[0] = 1;
	for (int i = 1; i < k; i++)  //지수값 채우기 
		p10[i] = p10[i - 1] * 10;
	for (int i = 0; i < k; i++) //
	{
		for (int j = 0; j < 10; j++)
			l[j].clear();
		for (int j = 0; j < n; j++)
			l[digitnum(arr[j], i)].push_back(arr[j]);
		int aidx = 0;
		for (int j = 0; j < 10; j++)
		{
			for (auto x : l[j])
				arr[aidx++] = x;
		}
	}
}