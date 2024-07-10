## ToC
- [July Week 2](#july-week-2)
  - [24.07.10 - 1598. Crawler Log Folder](#240710---1598-crawler-log-folder)
    - [나](#나)
    - [gpt](#gpt)

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