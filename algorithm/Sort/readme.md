
-in-place sort: swap을 이용하며 추가 메모리가 sort에 필요하지 않은 경우(merge sort,radix sort)제외

-Comparison sort: 두 값을 비교하여 sort구현

-Stable sort: sort를 할때 우선순위가 같은 원소가 여러개일때 원래의 순서를 따라가도록 하는 정렬을 stable sort라고한다.

-InutInsensitive:  input에 상관없이 sort하는데 일정한 시간이 걸리는 정렬방법(선택정렬,버블정렬)

-버블정렬: 가장 큰 원소를 뒤로 보내는 방식의 정렬  

```
for(int i=0;<n;i++)
{
  for(int j=0;j<n-i-1;j++)
  {
    if(arr[j]>arr[j+1}) swap(arr[j],arr[j+1]);
  }
}
```
-선택정렬:가장 큰(작은) 원소를 찾아서 마지막 원소(맨앞)와 swap한다   시간복잡도는 O(N^2)이지만 swap횟수가 buble sort보다 적음 
```
for(int i=n-1;i>0;i--)
  {
      swap(*max_element(arr,arr+i+1),arr[i]);
   }
```

-삽입정렬(Insertion sort): Input sensitive한 정렬로 sort된 부분과 sort되지 않는 부분을 나눠서 정렬되지 않은 부분을 정렬된 부분의
마지막 원소와 비교하면서 들어갈 위치를 탐색하게한다. O(N^2)의 시간복잡도를 지니지만 정렬된 부분을 알고있을때 일부분에만 정렬을 시행하면된다.
```
void insert_sort(int arr[],int size,int k) //k element까지 정렬된 부분일때
{
	for(int i=k+1;i<size-1;i++)
	{
		int cur=arr[i];
		int j=i;
		while(j>=0 && arr[j-1]>cur) //정렬된 자리에 들어갈 자리 찾기
		{
			arr[j]=arr[j-1];
			j=j-1;
		}
		arr[j]=cur;
	}
}
```
-Shell sort: 선택정렬을 개선한 정렬로 가장 작은 값이 맨 오른쪽에 있는경우 상당히 오래걸리는 경우를 보안하기위해 gap을 만들어  큰 간격으로 그룹을 만들어 비교를  그룹별로 
수행하면서 작은값들을 앞으로 보낸다.  여러가지 gap을 사용하며 큰 gap부터 작은 gap으로 줄여나간다.
```
void shell_sort(int arr[],int size)
{
	int gap[3];
	for(int g=0;g<3;g++)
	{
		for(int i=gap[g];i<size;i++)
		{
			int cur=arr[i];
			int j=i;
			while(j>=0&&arr[j-gap[g]]>cur)
			{
				arr[j]=arr[j-gap[g]];
				j-=gap[g];
			}
			arr[j]=cur;
		}

	}
```

-MergeSort: 분할정복 기법을 이용하여 수열을 나눠 각 각 정렬한 후 합치는 정렬방법 O(nlogn)의 시간복잡도를 지니고 별도의 메모리공간이 필요하다.
새로운 메모리를 할당하고 각 분할된 배열의 첫번째 원소에 커서를 잡고 비교를 하면서 작은 원소를 할당한 메모리에 넣는다  

```
void merge(int st, int en) {
	int mid = (st + en) / 2;
	int right = mid;
	int left = st;
	for (int i = st; i < en; i++)
	{
		if (left != mid && (arr[left] <= arr[right] || right == en)) 
			tmp[i] = arr[left++];
		else
			tmp[i] = arr[right++];
	}
	for (int i = left; i < en; i++)
	{
		arr[i] = tmp[i];
	}
}

void merge_sort(int st, int en) { //[ )
	if (en - st <= 1) return; 
	int mid = (st + en) / 2;
	merge_sort(st, mid); 
	merge_sort(mid, en); 
	merge(st, en); 
}
```
-Qucik sort: 분할정복 기법을 통해 구현된다. Pivot이라는 기준점(배열의 첫요소 혹은 끝요소)과 정렬된 양쪽 배열의 첫 요소로 left cursor와 right cursor를 잡고 right cursor는 pivot값보다 큰 값으로 설정한다.
반복문을 통해 left cursor가 pivot보다 크거나 같은값을 가리키고  right cursor가 pivot보다 작은 값을 가리키면 swap하여 위치를 바꾼다. 두 커서가 교차가 될때 right/left cursor의 위치는 pivot의 위치이다.

평균 O(NlogN)의 시간복잡도를 지니지만 피벗 설정이 좋지 않된 경우 worst case에서 O(N^2)의 시간복잡도를 지니기도 한다.
```
int partition(int st, int en)
{
  int pivot = st;
  int left = st + 1;
  int right = en;
  while (1)
  {
    while (left <= right && arr[left] <= arr[pivot]) // 피봇보다 큰거 찾기
      left++;
    while (left <= right && arr[right] >= arr[pivot])
      right--;
    if (left > right) //교차되면 반복문 종료 
      break;
    swap(arr[left], arr[right]);
  }
  swap(arr[right], arr[st]); //피벗위치 찾기 
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
```
Heapsort: 우선순위큐(Heap)를 활용하여 정렬을한다 heapify를 통하여 O(N)으로 모든 배열의 요소를 heap에 집어넣은 후 heap에서 원소를 하나씩 꺼내어 정렬을 구현한다. 







