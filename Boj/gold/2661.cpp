#include<bits/stdc++.h>
using namespace std;
// int n;
// string ans;
// bool check(string &str)//좋은 수열이면 true반환
// {
//   int len =str.length();
//   //if(len==n)cout<<str<<'\n';
//   for(int i=1;i<=len/2;i++)// 끝에서부터 i개 끊어서 비교 
//   {
//     int right=len-i;
//     int left=right-i;
//     string st=str.substr(left,i);
//     string ed=str.substr(right);
//     //if(len==n)cout<<st<<' '<<ed<<'\n';
//     if(st==ed)return false;
//   }
//   return true;

// }
// void func(string str,int cur)
// {
//   if(cur==n)
//   {
//     ans=str;
//     return;
//   }
//   for(int i=1;i<=3;i++)
//   {
//     string temp=str+to_string(i);
//     if(check(temp))
//     {
//       func(temp,cur+1);
//       if(ans.length()!=0)return;
//     }
//   }
// }

// int main()
// {
//   ios::sync_with_stdio(0);cin.tie(0);
//   cin>>n;
//   string str ="1";
//   func(str,1);
//   cout<<ans;


// }

bool good(const std::string& s)
{
    int len = s.size();
    for (int k = 1; k <= len / 2; ++k)
        if (std::equal(s.end() - k, s.end(),
                       s.end() - 2 * k))
            return false;              // 인접 부분 수열이 일치 → 나쁜 수열
    return true;
}
string dfs(string& cur, int depth, int N)
{
    if (depth == N)
        return cur;

    for (char c = '1'; c <= '3'; ++c)
    {
        cur.push_back(c);
        if (good(cur))
        {
            string res = dfs(cur, depth + 1, N);
            if (!res.empty())
                return res;             // 답 발견 → 전파
        }
        cur.pop_back();
    }
    return "";                           // 실패
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    string cur;
    cur.reserve(N);
    cout << dfs(cur, 0, N) << '\n';
}