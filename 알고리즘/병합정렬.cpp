#include<iostream>
#include<vector>

//using namespace std;
//
//vector<int> merge(vector<int>&left,vector<int>&right)
//{
//	vector<int> merge;
//	auto it1 = left.begin();
//	auto it2 = right.begin();
//	while (it1!=left.end()|| it2!=right.end()) //�Ѵ� ������ ���� ���
//	{
//		if (it1!=left.end()&&(it2 == right.end() ||*it1 <= *it2))
//		{
//			merge.push_back(*it1++);
//		}
//		else
//		{
//			merge.push_back(*it2++);
//		}
//	}
//		return merge;
//}
//
//vector<int> mergesort( const vector<int> &arr)
//{
//	if (arr.size() < 2)
//		return arr;
//	auto center = arr.begin();
//	advance(center, distance(arr.begin(), arr.end()) / 2);
//	auto left = mergesort(vector<int>(arr.begin(),center));
//	auto right = mergesort(vector<int>(center, arr.end()));
//	return merge(left,right);
//}
//int main()
//{
//	vector<int> arr = { 10,4,5,9,11,13,15 };
//	arr=mergesort(arr);
//	for (auto k : arr)
//		cout << k << ' ';
//}



using namespace std;

int n = 10;
int arr[1000001] = { 15, 25, 22, 357, 16, 23, -53, 12, 46, 3 };
int tmp[1000001]; 


void merge(int st, int en) {
	int mid = (st + en) / 2;
	int left = mid;
	int start = st;
	for (int i = st; i < en; i++)
	{
		if (st != mid && (arr[st] <= arr[left] || left == en)) 
			tmp[i] = arr[st++];
		else
			tmp[i] = arr[left++];
	}
	for (int i = start; i < en; i++)
	{
		arr[i] = tmp[i];
	}
}


void merge_sort(int st, int en) {
	if (en - st == 1) return; 
	int mid = (st + en) / 2;
	merge_sort(st, mid); 
	merge_sort(mid, en); 
	merge(st, en); // 
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	merge_sort(0, n);
	for (int i = 0; i < n; i++) cout << arr[i] << ' ';  // -53 3 12 15 16 22 23 25 46 357
}