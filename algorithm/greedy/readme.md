그리디: 가장 최적인 답을 근시안적으로 택하는 알고리즘 , 현재 선택이 나중에 발생할 문제에 영향을 주지않음, 최적의 선택을 계속해나감
 
  ->관찰을 통해 탐색 범위를 줄이는 알고리즘

  1.관찰을 통해 탐색 범위를 줄이는 방법을 고안
  
  2.탐색 범위를 줄여도 올바른 결과를 낸다는 사실을 수학적으로 증명

  3.구현해서 문제를 통과 

  ex) 회의실 배정 문제 ,로프문제

  회의실의 회의시간이 가장 빠르게 끝나는 것을 그리디하게 택한다, 만약 회의시간이 끝나는 시간이 같다면 시작시간이 빠른것을 택한다.
  
```
  bool cmp(pair<int, int> a, pair<int, int> b)
{
	if (a.Y != b.Y)
		return a.Y < b.Y; //종료시간 기준 오름차순 
	else
		return a.X <b.X;//같다면 시작시간 기준 오름차순  
}
int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	vector<pair<int, int>>arr;
	pair<int, int> temp;
	for (int i = 0; i < n; i++)
	{
		cin >> temp.X; //시작시간
		cin >> temp.Y; //종료시간 
		arr.push_back(temp);
	}
	sort(arr.begin(), arr.end(), cmp);
	stack<pair<int, int>>ruse;
	ruse.push(arr[0]);
	for (int i = 1; i < n; i++)
	{
		if (ruse.top().Y <= arr[i].X)  //마지막에 사용한 강의실의 종료시간보다 시작시간이 늦은경우 추가 
			ruse.push(arr[i]); //강의실 사용 스택에 넣음 
	}
	cout << ruse.size();
}
```
로프문제:  n개의 로프를 택하여 최대중량을 만들때 그리디하게 높은 중량을 실을 수 있는 로프를 택한다.
```
bool cmp(int a, int b) //내림차순 정렬 
{
	return a > b;
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	vector<int>lope;
	for (int i = 0; i < n; i++)
	{
		int weight;
		cin >> weight;
		lope.push_back(weight);
	}
	sort(lope.begin(), lope.end(), cmp);
	int maxweigh = lope[0];
	for (int i = 1; i <n; i++)
	{
		if (lope[i] * (i+1) > maxweigh)
			maxweigh = lope[i] * (i+1);
	}
	cout << maxweigh;


}
```



