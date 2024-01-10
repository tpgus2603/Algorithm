
백트랙킹: 현재 상태에서 가능한 모든 후보군을 따라 들어가며 탐색하는 알고리즘, 탐색을 하면서 원하는 해가 아니라 바로 전단계로 돌아가서 다시 해를 찾아감(branch)

반목문안에 재귀 함수를 넣는 방식으로 함수 호출이 종료되면 자연스럽게 백트랙킹이 된다. 

ex) n과m시리즈 ,nqueen문제 
void func(int k) { // 현재 k+1자리수를 택함 
	if (k == m) { // m개를 모두 택했으면
		for (int i = 0; i < m; i++)
			cout << arr[i] << ' '; // arr에 기록해둔 수를 출력
		cout << '\n';
		return;
	}
	for (int i = 1; i <= n; i++) { // 1부터 n까지의 수에 대해
		if (!isused[i]) { // 아직 i가 사용되지 않았으면
			arr[k] = i; // k번째 수를 i로 정함
			isused[i] = 1; // i를 사용되었다고 표시
			func(k + 1); // 다음 수를 정하러 한 단계 더 들어감
			isused[i] = 0; //돌아왔으면 다 정한거니 마지막에 채운수 미사용으로 바꿈 
		}
	}
 
 void func(int cur) {  //cur은 현재행
   if (cur == n) { // 
       cnt++;
       return;
   }
   for (int i = 0; i < n; i++) { // 0~n-1까지의 열을 순회 
       if (isused1[i] || isused2[i + cur] || isused3[cur - i + n - 1]) // 퀸을 못놓는 자리인경우  n-1은 인덱스가 음수가 안되기 위해
           continue;
       isused1[i] = 1;
       isused2[i + cur] = 1;
       isused3[cur - i + n - 1] = 1;
       func(cur + 1);
       isused1[i] = 0;
       isused2[i + cur] = 0;
       isused3[cur - i + n - 1] = 0;
   }
}
