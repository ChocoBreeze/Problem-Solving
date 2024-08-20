## ToC
- [August Week 4](#august-week-4)
  - [24.08.19 - 650. 2 Keys Keyboard](#240819---650-2-keys-keyboard)
    - [나](#나)
    - [gpt](#gpt)
  - [24.08.20 - 1140. Stone Game II](#240820---1140-stone-game-ii)
    - [나](#나-1)
    - [gpt](#gpt-1)

# August Week 4
## 24.08.19 - 650. 2 Keys Keyboard
[문제 링크](https://leetcode.com/problems/2-keys-keyboard/description/)

### 나
```cpp
// TLE
class Solution {
    struct Data {
        int copyLen{}, nowLen{};
        Data() = default;
        Data(int copyLen, int nowLen) : copyLen{copyLen}, nowLen{nowLen} {}
    };
public:
    int minSteps(int n) {
        int answer{-1};
        queue<Data> q;
        q.emplace(0, 1);
        for(int t{};!q.empty();++t) {
            for(int s{}, e{static_cast<int>(q.size())}; s<e; ++s) {
                auto [copyLen, nowLen] = q.front(); q.pop();
                
                if(nowLen == n) {
                    answer = t;
                    break;
                }

                // copy
                if(copyLen != nowLen) q.emplace(nowLen, nowLen);

                // paste
                if(copyLen != 0) q.emplace(copyLen, nowLen + copyLen);
            }
            if(answer != -1) break;
        }

        return answer;
    }
};
```
다른 아이디어가 없다..

### gpt
The problem you're dealing with is a classic dynamic programming (DP) problem. The goal is to find the minimum number of operations needed to get exactly `n` 'A's on the screen starting with one 'A' using only two operations: "Copy All" and "Paste".

<h3> Problem Breakdown: </h3>

1. **Initial Setup**: You start with one 'A' on the screen.
2. **Operations**:
   - **Copy All**: Copies the entire content of the screen to a buffer.
   - **Paste**: Pastes the content of the buffer to the screen.

<h3> Approach: </h3>

The essence of the problem is to decompose `n` into its prime factors. 

If `n` can be decomposed into smaller numbers, each "Copy All" followed by a series of "Paste" operations would effectively multiply the number of 'A's on the screen.

<h4> Steps: </h4>

1. **Prime Factorization Insight**:
   - If you factorize `n`, for every factor `f` of `n`, it means you can achieve `f` 'A's on the screen by first achieving `n/f` 'A's and then applying a "Copy All" followed by `f-1` "Paste" operations.
   - The minimum operations needed to get `n` 'A's is the sum of its prime factors.

2. **Dynamic Programming Approach**:
   - You can create a DP array where `dp[i]` represents the minimum operations needed to get `i` 'A's on the screen.
   - Start with `dp[1] = 0` because you're already starting with one 'A'.
   - For each `i` from 2 to `n`, try all possible factors `j`, and update `dp[i]` as `dp[j] + i/j` if `i % j == 0`.

Here's the code implementation:

```cpp
// 5ms, 8.22MB
class Solution {
public:
    int minSteps(int n) {
        vector<int> dp(n + 1, 0);
        
        for (int i = 2; i <= n; ++i) {
            dp[i] = i; // Maximum number of operations needed is i (all Paste operations)
            for (int j = i / 2; j > 1; --j) {
                if (i % j == 0) {
                    dp[i] = dp[j] + i / j;
                    break;
                }
            }
        }
        
        return dp[n];
    }
};
```

<h3> Explanation: </h3>

- **dp[i] = i**: The worst case is if `i` is a prime number, in which you would need `i` operations (one copy and `i-1` pastes).
- **For each `i`, we check factors `j`**: If `j` is a factor of `i`, then the operations needed are those to get `j` 'A's plus the number of pastes required to go from `j` to `i`.

<h3> Complexity: </h3>

- **Time Complexity**: $O(n \sqrt n)$ because for each `i`, you're potentially checking up to $\sqrt i$ factors.
- **Space Complexity**: $O(n)$ due to the DP array.

This approach is efficient and leverages the idea of reducing the problem by breaking down the operations into smaller subproblems.

> 오호..

## 24.08.20 - 1140. Stone Game II
[문제 링크](https://leetcode.com/problems/stone-game-ii/description/)

### 나
해설을 보자.

- [Dynamic Programming (Memoization)](https://leetcode.com/problems/stone-game-ii/editorial/#approach-1-dynamic-programming-memoization)

```cpp
// 4ms, 12.3MB
class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        vector<vector<int>> memo(piles.size(), vector<int>(piles.size()));
        vector<int> suffixSum = piles;
        for (int i = suffixSum.size() - 2; i >= 0; --i)
            suffixSum[i] += suffixSum[i + 1];
        return maxStones(suffixSum, 1, 0, memo);
    }

    int maxStones(vector<int>& suffixSum, int maxTillNow, int currIndex, vector<vector<int>>& memo) {
        if (currIndex + 2 * maxTillNow >= suffixSum.size())
            return suffixSum[currIndex]; // all remaining stones can be picked.
        if (memo[currIndex][maxTillNow] > 0) 
            return memo[currIndex][maxTillNow]; // already calculated

        int res = INT_MAX;
        for (int i = 1; i <= 2 * maxTillNow; ++i) { // 선택할 수 있는 돌의 개수들
            res = min(res, maxStones(suffixSum, max(i, maxTillNow), currIndex + i, memo));
        }
        
        // 뒤에서 고를 수 있는 최소의 개수를 빼면 최대 개수
        memo[currIndex][maxTillNow] = suffixSum[currIndex] - res; 
        return memo[currIndex][maxTillNow];
    }
};
```

- [Dynamic Programming (Tabulation)](https://leetcode.com/problems/stone-game-ii/editorial/#approach-2-dynamic-programming-tabulation)

```cpp
// 58ms, 12.4MB
// Solution Code
class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int length = piles.size();
        vector<vector<int>> dp(length + 1, vector<int>(length + 1, 0));
        // dp[i][j]
        // i: the starting index of the piles
        // j: the maximum number of piles Alice can pick on her turn

        // Store suffix sum for all possible suffix
        vector<int> suffixSum(length + 1, 0);
        for (int i = length - 1; i >= 0; --i) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        // Initialize the dp array.
        for (int i = 0; i <= length; ++i) {
            dp[i][length] = suffixSum[i];
        }

        // Start from the last index to store the future state first.
        for (int index = length - 1; index >= 0; index--) { // 현재 index
            for (int maxTillNow = length - 1; maxTillNow >= 1; maxTillNow--) { // 가능한 maxTillNow
                for (int X = 1; X <= 2 * maxTillNow && index + X <= length; X++) { // 선택할 수 있는 돌의 개수들
                    dp[index][maxTillNow] = max(
                        dp[index][maxTillNow],
                        suffixSum[index] - dp[index + X][max(maxTillNow, X)]);
                }
            }
        }

        // Recursion에 비해 불필요한 연산이 많아서 오래걸리는 듯.

        return dp[0][1];
    }
};
```

### gpt
생략