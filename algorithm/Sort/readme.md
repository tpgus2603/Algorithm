
-in-place sort: swap을 이용하며 추가 메모리가 sort에 필요하지 않은 경우(merge sort,radix sort)제외

-comparison sort: 두 값을 비교하여 sort구현

-Stable sort: sort를 할때 우선순위가 같은 원소가 여러개일때 원래의 순서를 따라가도록 하는 정렬을 stable sort라고한다.

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




