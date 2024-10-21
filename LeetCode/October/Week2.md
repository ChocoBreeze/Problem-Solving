## ToC
- [October Week 2](#october-week-2)
  - [24.10.07 - 2696. Minimum String Length After Removing Substrings](#241007---2696-minimum-string-length-after-removing-substrings)
    - [나](#나)
  - [24.10.08 - 1963. Minimum Number of Swaps to Make the String Balanced](#241008---1963-minimum-number-of-swaps-to-make-the-string-balanced)
    - [나](#나-1)
    - [Solution](#solution)
      - [Approach 1: Stack](#approach-1-stack)
      - [Approach 2: Space-Optimized Stack](#approach-2-space-optimized-stack)

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


## 24.10.08 - 1963. Minimum Number of Swaps to Make the String Balanced
[문제 링크](https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/description/?envType=daily-question&envId=2024-10-08)

### 나
딱히 아이디어가 없다..

### Solution
#### Approach 1: Stack
```cpp
// 111ms, 35.1MB
class Solution {
public:
    int minSwaps(string s) {
        stack<char> stack;
        int unbalanced = 0;
        for (int i = 0; i < s.size(); i++) {
            char ch = s[i];
            // If an opening bracket is encountered, push it in the stack.
            if (ch == '[')
                stack.push(ch);
            else {
                // If the stack is not empty, pop it.
                if (!stack.empty()) stack.pop();
                // Otherwise increase the count of unbalanced brackets.
                else
                    unbalanced++;
            }
        }
        return (unbalanced + 1) / 2;
    }
};
```

#### Approach 2: Space-Optimized Stack
```cpp
// 8ms, 32.71MB
class Solution {
public:
    int minSwaps(string s) {
        int stackSize = 0;
        int n = s.size();

        for (int i = 0; i < n; i++) {
            char ch = s[i];
            // If character is opening bracket, increment the stack size.
            if (ch == '[')
                stackSize++;
            else {
                // If the character is closing bracket, and we have an opening
                // bracket, decrease the stack size.
                if (stackSize > 0) stackSize--;
            }
        }
        return (stackSize + 1) / 2;
    }
};
```