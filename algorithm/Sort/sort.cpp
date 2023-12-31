#include<iostream>
#include<vector>

using namespace std;

vector<int> merge(vector<int>&left,vector<int>&right)
{
	vector<int> merge;
	auto it1 = left.begin();
	auto it2 = right.begin();
	while (it1!=left.end()|| it2!=right.end()) 
	{
		if (it1!=left.end()&&(it2 == right.end() ||*it1 <= *it2))
		{
			merge.push_back(*it1++);
		}
		else
		{
			merge.push_back(*it2++);
		}
	}
		return merge;
}

vector<int> mergesort( const vector<int> &arr) //[ )
{
	if (arr.size() < 2)
		return arr;
	auto center = arr.begin();
	advance(center, distance(arr.begin(), arr.end()) / 2);
	auto left = mergesort(vector<int>(arr.begin(),center));
	auto right = mergesort(vector<int>(center, arr.end()));
	return merge(left,right);
}
// int main()
// {
// 	vector<int> arr = { 10,4,5,9,11,13,15 };
// 	arr=mergesort(arr);
// 	for (auto k : arr)
// 		cout << k << ' ';
// }



using namespace std;

int n = 10;
int arr[1000001] = { 15, 25, 22, 357, 16, 23, -53, 12, 46, 3 };
int tmp[1000001]; 


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

void bubble_sort(int arr[],int size)
{
	for(int i=0;i<size-1;i++)
	{

		for(int j=0;j<size-i-2;j++)
		{
			if(arr[j]>arr[j+1])
				swap(arr[j],arr[j+1]);
		}
	}


}

void inser_sort(int arr[],int size,int k) //k element까지 정렬된 부분일때
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


}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	merge_sort(0, n);
	for (int i = 0; i < n; i++) cout << arr[i] << ' ';  // -53 3 12 15 16 22 23 25 46 357
	cout<<'\n';
	int arr[10]={7,8,9,5,4,3,2,1,6,10};
	bubble_sort(arr,10);
	for(auto k:arr)
		cout<<k<<' ';
}