#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;
int arr[1000001] = { 0 }; //수가 최대 100만이므로 dp를 이용하여 하나씩 쌓아도 메모리에 지장이없다 
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	arr[1] = 0;
	for (int i = 2; i <= n; i++)
	{
		arr[i] = arr[i - 1] + 1; //기본은 이전 항에 +1
		if (i % 2 == 0)arr[i] = min(arr[i], arr[i / 2] + 1); //2의배수인경우 이전의 arr[i]와 arr[i/2]+1중 최소값 고름 
		if (i % 3 == 0)arr[i] = min(arr[i], arr[i / 3] + 1);
	}

	cout << arr[n];

}