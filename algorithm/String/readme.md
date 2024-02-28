

c++에서 문자열 처리 문제에 관한 것을 정리하기 위한 페이지이다.

c++에서는 문자열을 단일 문자나 공백으로  split을 해주는 함수가 따로없기에 istringstream과 getline()함수를 이용하여 구현한다.

```
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens; // 분할된 문자열을 저장할 벡터
    string token; // 각 토큰을 임시로 저장할 문자열
    istringstream tokenStream(s); // 입력 문자열을 스트림으로 변환

    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token); // 구분자로 분할된 각 문자열을 벡터에 추가
    }

    return tokens;
}

int main() {
    string s = "This is a sample string";
    char delimiter = ' '; // 공백을 구분자로 사용
    vector<string> tokens = split(s, delimiter);

    for (const auto& token : tokens) {
        cout << token << endl;
    }

    return 0;
}
```

**시간복잡도*O(n)


문자열을 기준으로 구분하는 함수는 find와 substr을 활용하여 구현가능하다.

```
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& s, const string& delimiter) {
    vector<string> tokens;
    size_t start = 0;
    size_t end = s.find(delimiter);

    while (end != string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
        end = s.find(delimiter, start);
    }

    tokens.push_back(s.substr(start));
    return tokens;
}

int main() {
    string s = "This=is=a=sample=string";
    string delimiter = "=";
    vector<string> tokens = split(s, delimiter);

    for (const auto& token : tokens) {
        cout << token << endl;
    }

    return 0;
}

```
시간복잡도 O(N*M) : N:문자열의 길이 M: 구분 문자열의 길이 

-문자열 함수들
-
substr(size_t pos = 0, size_t len = npos) const: pos 위치부터 시작하여 len 길이만큼의 부분 문자열을 반환합니다. len을 지정하지 않으면, pos부터 문자열의 끝까지의 부분 문자열을 반환합니다.

erase(size_t pos, size_t len = npos): pos에서 시작하여 len 길이만큼의 문자열을 삭제합니다. len이 지정되지 않으면 pos부터 문자열의 끝까지 모두 삭제됩니다.

erase(iterator first, iterator last): first 반복자 위치부터 last 반복자 바로 전 위

find(const std::string& str, size_t pos ) const: pos 위치부터 시작하여 문자열 str을 찾습니다. 찾은 위치를 반환하고, 찾지 못하면 std::string::npos를 반환합니다.

find(char c, size_t pos ) const: pos 위치부터 시작하여 문자 c를 찾습니다. 위와 같이 찾은 위치를 반환하고, 찾지 못하면 std::string::npos를 반환합니다.

replace(size_t pos, size_t len, const std::string& str): pos 위치부터 len 길이의 문자열을 str로 교체합니다.

append(const std::string& str): 현재 문자열의 끝에 str을 추가합니다.

nsert(size_t pos, const std::string& str)


