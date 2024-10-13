## ToC
- [October Week 2](#october-week-2)
  - [24.10.07 - 2696. Minimum String Length After Removing Substrings](#241007---2696-minimum-string-length-after-removing-substrings)
    - [나](#나)

# October Week 2
## 24.10.07 - 2696. Minimum String Length After Removing Substrings
[문제 링크](https://leetcode.com/problems/minimum-string-length-after-removing-substrings/description/?envType=daily-question&envId=2024-10-07)

### 나
```cpp
// 24ms, 9.98MB
// 개귀찮음.
class Solution {
public:
    int minLength(string s) {
        // Continue processing while "AB" or "CD" substrings exist
        while (s.find("AB") != -1 || s.find("CD") != -1) {
            if (s.find("AB") != -1) {
                // Remove all occurrences of "AB"
                s.erase(s.find("AB"), 2); // 이렇게 하면 간단하구나
            } else if (s.find("CD") != -1) {
                // Remove all occurrences of "CD"
                s.erase(s.find("CD"), 2); // 이렇게 하면 간단하구나
            }
        }

        return s.length();
    }
};
```

