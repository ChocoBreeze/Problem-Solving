## ToC
- [July Week 2](#july-week-2)
  - [24.07.10 - 1598. Crawler Log Folder](#240710---1598-crawler-log-folder)
    - [나](#나)
    - [gpt](#gpt)
  - [24.07.11 - 1190. Reverse Substrings Between Each Pair of Parentheses](#240711---1190-reverse-substrings-between-each-pair-of-parentheses)
    - [나](#나-1)
    - [gpt](#gpt-1)
  - [24.07.12 - 1717. Maximum Score From Removing Substrings](#240712---1717-maximum-score-from-removing-substrings)
    - [나](#나-2)
    - [gpt](#gpt-2)

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

## 24.07.12 - 1717. Maximum Score From Removing Substrings
[문제 링크](https://leetcode.com/problems/maximum-score-from-removing-substrings/description/?envType=daily-question&envId=2024-07-12)

### 나
```cpp
class Solution {
public:
    int maximumGain(string s, int x, int y) {
        int answer{};
        // x가 더 크면 ab먼저, y가 더 크면 ba 먼저? (같을 때는 상관 없음)
        string temp, temp2;
        if(x >= y) {
            // ab
            for(char c : s) {
                if(!temp.empty() && temp.back() == 'a' && c == 'b') {
                    temp.pop_back();
                    answer += x;
                }
                else temp.push_back(c);
            }

            // ba
            for(char c : temp) {
                if(!temp2.empty() && temp2.back() == 'b' && c == 'a') {
                    temp2.pop_back();
                    answer += y;
                }
                else temp2.push_back(c);
            }
        }
        else {
            // ba
            for(char c : s) {
                if(!temp.empty() && temp.back() == 'b' && c == 'a') {
                    temp.pop_back();
                    answer += y;
                }
                else temp.push_back(c);
            }

            // ab
            for(char c : temp) {
                if(!temp2.empty() && temp2.back() == 'a' && c == 'b') {
                    temp2.pop_back();
                    answer += x;
                }
                else temp2.push_back(c);
            }
        }
        return answer;
    }
};
```

### gpt
To solve LeetCode problem 1717, "Maximum Score From Removing Substrings," we need to remove specified substrings from a given string in such a way that the score is maximized. Here’s a step-by-step approach to solve this problem:

<h3> Problem Description </h3>

You are given a string `s` and two integers `x` and `y`. You need to maximize the score by performing the following operations any number of times:
1. Remove the substring `"ab"` and gain `x` points.
2. Remove the substring `"ba"` and gain `y` points.

<h3> Approach </h3>

1. **Determine the Order of Operations**: 
   - If `x > y`, prioritize removing `"ab"` first, because it gives more points.
   - If `y > x`, prioritize removing `"ba"` first.
   - If `x == y`, it doesn't matter which substring is removed first as the points are the same.

2. **Stack-based Solution**:
   - Use a stack to help efficiently remove the substrings in the desired order.
   - Traverse through the string and push characters to the stack while checking for the target substrings.

<h3> Detailed Steps </h3>

1. **Stack Simulation**:
   - Create a stack to process the string.
   - Traverse the string, pushing characters onto the stack.
   - Whenever the target substring is formed (either `"ab"` or `"ba"` depending on priority), pop characters from the stack and add the corresponding points to the score.

<h3> Example Code </h3>

Here's a complete implementation in C++:

```cpp
#include <iostream>
#include <string>
#include <stack>
using namespace std;

int maximumGain(string s, int x, int y) {
    int score = 0;
    stack<char> st;
    
    auto removeSubstring = [&](char a, char b, int points) {
        stack<char> tempStack;
        for (char c : s) {
            if (!st.empty() && st.top() == a && c == b) {
                st.pop();
                score += points;
            } else {
                st.push(c);
            }
        }
        
        // Store the intermediate result back to `s` for the next pass
        s = "";
        while (!st.empty()) {
            tempStack.push(st.top());
            st.pop();
        }
        while (!tempStack.empty()) {
            s += tempStack.top();
            tempStack.pop();
        }
    };
    
    // Determine the order based on the given points
    if (x > y) {
        removeSubstring('a', 'b', x);
        removeSubstring('b', 'a', y);
    } else {
        removeSubstring('b', 'a', y);
        removeSubstring('a', 'b', x);
    }
    
    return score;
}

int main() {
    string s = "cdbcbbaaabab";
    int x = 4;
    int y = 5;
    cout << "Maximum score: " << maximumGain(s, x, y) << endl;
    return 0;
}
```

<h3> Explanation: </h3>

- **removeSubstring** function: It removes a specific substring (`a` followed by `b`) from the string using a stack and updates the score.
- **Order of Removal**: The substrings are removed in the order which gives the highest points first.
- **Intermediate Storage**: The intermediate state of the string after each pass is stored back in `s` for the next removal operation.

This approach ensures that the operations are performed efficiently and the score is maximized based on the given points for each type of substring removal.

> [!TIP] Question
> I have a question in your approach. Please make a proof for Why this is correct.
> - If `x > y`, prioritize removing `"ab"` first, because it gives more points.
> - If `y > x`, prioritize removing `"ba"` first.
> - If `x == y`, it doesn't matter which substring is removed first as the points are the same.

To understand why prioritizing the removal of substrings `"ab"` or `"ba"` based on their respective scores (`x` and `y`) is the correct approach, let's go through the reasoning step by step.

<h3> Problem Restatement </h3>

Given a string `s` and two scores `x` and `y`:
1. Removing the substring `"ab"` gives `x` points.
2. Removing the substring `"ba"` gives `y` points.

The goal is to maximize the total score by removing these substrings in the optimal order.

<h3> Key Insight </h3>

To maximize the score, we should prioritize removing the substrings that provide the highest points first. The reason for this is based on the greedy algorithm principle: by making the locally optimal choice at each step, we aim to achieve the globally optimal solution.

<h3> Proof by Greedy Strategy </h3>

<h4> Case 1: <code>x > y</code> </h4>

- When `x > y`, removing `"ab"` first is more beneficial because it provides more points. After removing as many `"ab"` as possible, we then remove `"ba"` substrings.
- By prioritizing `"ab"`, we ensure that the high-scoring substrings are removed first, which maximizes the score. Any remaining characters after removing all possible `"ab"` substrings can then form `"ba"` substrings, which are removed next.

<h4> Case 2: <code>y > x</code> </h4>

- When `y > x`, the removal of `"ba"` gives more points. Hence, we should remove all possible `"ba"` substrings first. After that, we proceed to remove `"ab"` substrings.
- This way, we capitalize on the higher score of `"ba"` removals, ensuring that we don't miss out on the higher points before addressing the lower-scoring `"ab"` removals.

<h4> Case 3: <code>x == y</code> </h4>

- When `x == y`, the order of removal doesn't matter since both operations give the same points. Removing any of the substrings first will lead to the same total score.

<h3> Detailed Example for <code>x > y</code> </h3>

Suppose `s = "ababbab"`, `x = 5`, and `y = 3`.

1. **First Pass: Remove `"ab"` substrings**:
   - String: `"ababbab"`
   - After removing `"ab"`: `s = "abbbab"`
   - Score: `+5` (1 removal of `"ab"`)

2. **Second Pass: Remove `"ab"` again**:
   - String: `"abbbab"`
   - After removing `"ab"`: `s = "bbab"`
   - Score: `+5` (1 removal of `"ab"`)

3. **Third Pass: Remove `"ab"` again**:
   - String: `"bbab"`
   - After removing `"ab"`: `s = "bb"`
   - Score: `+5` (1 removal of `"ab"`)

4. **Final Pass: Remove `"ba"` substrings**:
   - String: `"bb"`
   - No more `"ba"` substrings can be removed.

Total Score: `15` (from 3 removals of `"ab"`)

<h3> Detailed Example for <code>y > x</code> </h3>

Suppose `s = "babaab"`, `x = 2`, and `y = 4`.

1. **First Pass: Remove `"ba"` substrings**:
   - String: `"babaab"`
   - After removing `"ba"`: `s = "baab"`
   - Score: `+4` (1 removal of `"ba"`)

2. **Second Pass: Remove `"ba"` again**:
   - String: `"baab"`
   - After removing `"ba"`: `s = "ab"`
   - Score: `+4` (1 removal of `"ba"`)

3. **Final Pass: Remove `"ab"` substrings**:
   - String: `"ab"`
   - After removing `"ab"`: `s = ""`
   - Score: `+2` (1 removal of `"ab"`)

Total Score: `10` (from 2 removals of `"ba"` and 1 removal of `"ab"`)

<h3> Conclusion </h3>
The greedy strategy works because it ensures that we always maximize the score at each step by removing the highest-scoring substrings first. This local optimization leads to the global maximum score. This approach is efficient and guarantees the best result by prioritizing the more valuable substrings based on their respective scores.
