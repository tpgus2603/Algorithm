
백트랙킹: 현재 상태에서 가능한 모든 후보군을 따라 들어가며 탐색하는 알고리즘, 탐색을 하면서 원하는 해가 아니라 바로 전단계로 돌아가서 다시 해를 찾아감(branch)

반목문안에 재귀 함수를 넣는 방식으로 함수 호출이 종료되면 자연스럽게 백트랙킹이 된다. 

ex) n과m시리즈 ,nqueen문제 
```
//nqeen문제 branch조건을 반복문안에 넣어 백트랙킹구현
void func(int cur)
{ 
    if (cur == n)
    { 
        cnt++;
        return;
    }
    for (int i = 0; i < n; i++)
    {                                                                   
        if (isused1[i] || isused2[i + cur] || isused3[cur - i + n - 1]) 
            continue;
        isused1[i] = 1;
        isused2[i + cur] = 1;
        isused3[cur - i + n - 1] = 1;
        func(cur + 1);
        isused1[i] = 0;
        isused2[i + cur] = 0;
        isused3[cur - i + n - 1] = 0;
    }
```
