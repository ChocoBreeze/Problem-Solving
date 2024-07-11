## ToC
- [July Week 2](#july-week-2)
  - [24.07.10 - 1598. Crawler Log Folder](#240710---1598-crawler-log-folder)
    - [나](#나)
    - [gpt](#gpt)
  - [24.07.11 - 1190. Reverse Substrings Between Each Pair of Parentheses](#240711---1190-reverse-substrings-between-each-pair-of-parentheses)
    - [나](#나-1)
    - [gpt](#gpt-1)

# July Week 2

## 24.07.10 - 1598. Crawler Log Folder
[문제 링크](https://leetcode.com/problems/crawler-log-folder/?envType=daily-question&envId=2024-07-10)

### 나
```cpp
// 9ms, 14.06MB
class Solution {
public:
    int minOperations(vector<string>& logs) {
        int depth{};
        for(auto& log : logs) {
            if(log == "../"s) {
                if(depth > 0) --depth;
            }
            else if(log == "./"s) {
                // do nothing.
            }
            else {
                ++depth;
            }
        }
        return depth;
    }
};
```

### gpt
```cpp
#include <vector>
#include <string>

int minOperations(std::vector<std::string>& logs) {
    int depth = 0;
    for (const std::string& log : logs) {
        if (log == "../") {
            if (depth > 0) {
                --depth;
            }
        } else if (log != "./") {
            ++depth;
        }
    }
    return depth;
}
```

<details>
<summary> <b> gpt - 궁금증 묻기 </b> </summary> <br/>

Then I have a question

I got 3ms in this code.

```cpp
class Solution {
public:
    int minOperations(vector<string>& logs) {
        int depth{};
        for(auto& log : logs) {
            if(log.substr(0, 3) == "../"s) {
                if(depth > 0) --depth;
            }
            else if(log.substr(0, 2) == "./"s) {
                // do nothing.
            }
            else {
                ++depth;
            }
        }
        return depth;
    }
};
```

but i got 9ms in this code

```cpp
class Solution {
public:
    int minOperations(vector<string>& logs) {
        int depth{};
        for(auto& log : logs) {
            if(log.length() == 3 && log == "../"s) {
                if(depth > 0) --depth;
            }
            else if(log.length() == 2 && log == "./"s) {
                // do nothing.
            }
            else {
                ++depth;
            }
        }
        return depth;
    }
};
```

I think substr is slow and just check the length makes similar effect, but I don't know why second code takes more time than first code.
please explain this?

The difference in execution time between your two codes can be attributed to how C++ handles string comparisons and operations internally.

<h3> Key Points: </h3>

1. **String Comparison (`==`) vs. Substring (`substr`):**
   - In the first code, `log.substr(0, 3) == "../"` and `log.substr(0, 2) == "./"` create temporary substrings and then compare them.
   - In the second code, `log.length() == 3 && log == "../"` and `log.length() == 2 && log == "./"` do direct comparisons.

2. **Short-Circuit Evaluation:**
   - In the second code, the `log.length()` checks are intended to reduce unnecessary comparisons. However, this introduces extra conditional checks (`log.length() == 3` and `log.length() == 2`) before the string comparisons.

3. **Implementation Details:**
   - The first code relies on `substr` to extract the prefix before comparing, which involves creating a new string object but this can be very efficient due to short-circuit optimizations in modern C++ libraries.
   - The second code avoids `substr` but introduces additional length checks and direct string comparisons, which could be less optimized than expected.

<h3> Possible Performance Insights: </h3>

- **Substr Optimizations:** Modern C++ libraries might optimize `substr` operations for short strings, making them surprisingly fast.
- **Branch Prediction:** Additional conditional checks in the second code might affect CPU branch prediction negatively, causing slower performance.
- **Inlining and Micro-optimizations:** The first code might benefit from better inlining and micro-optimizations by the compiler.

<h3> Improved Code </h3>

Combining the benefits of both approaches:
```cpp
class Solution {
public:
    int minOperations(vector<string>& logs) {
        int depth{};
        for(const auto& log : logs) {
            if (log == "../") {
                if(depth > 0) --depth;
            } else if (log != "./") {
                ++depth;
            }
        }
        return depth;
    }
};
```
This approach avoids `substr` and unnecessary length checks while ensuring concise string comparisons.

Understanding performance implications in C++ often requires a deep dive into compiler optimizations and hardware behaviors. For practical purposes, testing different approaches and profiling your code can provide the most reliable insights.

</details>

## 24.07.11 - 1190. Reverse Substrings Between Each Pair of Parentheses
[문제 링크](https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/description/?envType=daily-question&envId=2024-07-11)

### 나
```cpp
// 0ms, 9.64MB
class Solution {
public:
    int i{};

    string reverseParentheses(string s) {
        string answer;
        for(int e = static_cast<int>(s.length());i<e;++i) {
            if(s[i] == '(') {
                ++i;
                answer += reverseParentheses(s);
            }
            else if(s[i] == ')') {
                break;
            }
            else answer.push_back(s[i]);
        }
        if(i != static_cast<int>(s.length()))
            reverse(begin(answer), end(answer));
        return answer;
    }
};
```

### gpt
Got it! Let's dive into how we can solve this problem. We'll use a stack to handle the parentheses and reverse the substrings.

Here's a step-by-step breakdown of the solution:

1. **Use a stack** to help us reverse substrings within parentheses.
2. Iterate through each character in the string:
   - If the character is '(', push the current string onto the stack and start a new substring.
   - If the character is ')', reverse the current substring and append it to the string popped from the stack.
   - Otherwise, append the character to the current substring.
3. At the end, the current substring will contain the final result.

Here's a sample implementation in C++:

```cpp
class Solution {
public:
    int i{};

    string reverseParentheses(string s) {
        std::stack<std::string> st;
        std::string current;
    
        for (char& ch : s) {
            if (ch == '(') {
                st.push(current); // 괄호 이전에 쌓은 애들 stack에 누적
                current.clear();
            } else if (ch == ')') {
                std::reverse(current.begin(), current.end()); // 쌓은애들 거꾸로 뒤집기
                current = st.top() + current;
                st.pop();
            } else {
                current += ch;
            }
        }
        
        return current;
    }
};
```
> 비재귀로도 가능~ 훨씬 더 좋은 듯!

<h3> Explanation: </h3>

1. **Stack usage**: The stack `st` keeps track of the string parts before encountering a '('.
2. **Current substring**: `current` holds the ongoing substring that we are processing.
3. **Character check**:
   - On '(': Push the current substring onto the stack and clear it.
   - On ')': Reverse the current substring, pop from the stack, and append the reversed substring to the popped string.
   - Otherwise, just append the character to the current substring.
4. **Final result**: After the loop, `current` holds the final result without any parentheses.

This solution efficiently handles the problem constraints and provides the correct output. If you have any questions or need further explanations, feel free to ask!

