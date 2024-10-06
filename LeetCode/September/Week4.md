## ToC
- [September Week 4](#september-week-4)
  - [24.09.23 - 2707. Extra Characters in a String](#240923---2707-extra-characters-in-a-string)
    - [나](#나)
    - [Solution](#solution)

# September Week 4
## 24.09.23 - 2707. Extra Characters in a String
[문제 링크](https://leetcode.com/problems/extra-characters-in-a-string/description/?envType=daily-question&envId=2024-09-23)

### 나
별도의 algorithm X, DP
```cpp
// 128ms, 89.24MB
//  별도의 String Algorithm이 필요한가?
// 그냥 DP네.. ㅋㅋ
// Approach 2: Bottom Up Dynamic Programming with Substring Method
class Solution {
public:
    int minExtraChar(string s, vector<string> dictionary) {
        int n = s.length();
        unordered_set<string> dictionarySet(dictionary.begin(), dictionary.end());
        vector<int> dp(n + 1, 0);

        for (int start = n - 1; start >= 0; --start) { // 뒤에서부터 보는 idea
            dp[start] = dp[start + 1] + 1; // default value
            
            for (int end = start; end < n; ++end) {
                auto curr = s.substr(start, end - start + 1);

                if (dictionarySet.count(curr)) { // 해당 단어 존재 시 갱신
                    dp[start] = min(dp[start], dp[end + 1]);
                }
            }
        }

        return dp[0];
    }
};
```

### Solution
추후 남기기