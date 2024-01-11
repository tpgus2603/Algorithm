
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
-Shell sort: 선택정렬을 개선한 정렬로 가장 작은 값이 맨 오른쪽에 있는경우 상당히 오래걸리는 

-MergeSort: 분할정복 기법을 이용하여 수열을 나눠 정렬한 후 합치는 정렬방법 O(nlogn)의 시간복잡도를 지니고 별도의 메모리공간이 필요하다 




