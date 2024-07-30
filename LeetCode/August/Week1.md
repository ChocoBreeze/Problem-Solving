## ToC

# August Week 1
## 24.07.29 - 1395. Count Number of Teams
[문제 링크](https://leetcode.com/problems/count-number-of-teams/description/?envType=daily-question&envId=2024-07-29)

### 나
```cpp
// 2783ms, 11.52MB
class Solution {
public:
    int numTeams(vector<int>& rating) {
        const int SIZE = static_cast<int>(rating.size());
        int answer{};
        
        for (int i{}; i < SIZE - 2; ++i) {
            for (int j = i + 1; j < SIZE - 1; ++j) {
                for (int k = j + 1; k < SIZE; ++k) {
                    if ((rating[i] < rating[j] && rating[j] < rating[k]) ||
                        (rating[i] > rating[j] && rating[j] > rating[k])) {
                        ++answer;
                    }
                }
            }
        }
        
        return answer;
    }
};
```

### gpt
Since I couldn't access the page directly, I'll provide an outline on how to solve the "Count Number of Teams" problem typically found on LeetCode.


#### Brute Force
<h3> Problem Description </h3>

You are given an array of integers representing the rating of soldiers. You need to count the number of teams of 3 soldiers where either:
- The ratings are in increasing order (i < j < k).
- The ratings are in decreasing order (i > j > k).

<h3> Solution </h3>

We can solve this problem using a nested loop approach to count valid teams. Here's a step-by-step solution in C++:

1. **Initialization**: We need an array `rating` and its length `n`.
2. **Nested Loops**: Use three nested loops to check each combination of three soldiers.
3. **Condition Checking**: Check for increasing or decreasing order.
4. **Counting Teams**: Increment a counter whenever a valid team is found.

<h3> Example Code </h3>
Here’s a C++ solution for the problem:

```cpp
class Solution {
public:
    int numTeams(vector<int>& rating) {
        int n = rating.size();
        int count = 0;
        
        // Iterate over all possible triplets (i, j, k)
        for (int i = 0; i < n - 2; ++i) {
            for (int j = i + 1; j < n - 1; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    if ((rating[i] < rating[j] && rating[j] < rating[k]) ||
                        (rating[i] > rating[j] && rating[j] > rating[k])) {
                        ++count;
                    }
                }
            }
        }
        
        return count;
    }
};
```

<h3> Explanation </h3>

1. **Triple Loop**: The loops run through all combinations of indices (i, j, k) with i < j < k.
2. **Condition Check**: The condition checks if the ratings are in either strictly increasing or decreasing order.
3. **Count Increment**: The counter `count` is incremented whenever a valid team is found.

<h3> Optimizations </h3>
This triple loop approach works fine for small arrays but may not be efficient for larger ones due to O(n^3) complexity. For larger arrays, consider more efficient solutions involving dynamic programming or prefix/suffix arrays to reduce time complexity.

#### Dynamic Programming
To solve the "Count Number of Teams" problem using a more efficient approach with dynamic programming, we can use the following strategy:

1. **Count of Smaller and Larger Elements**: For each soldier, count the number of soldiers with a lower rating before it and the number of soldiers with a higher rating after it. Similarly, count the number of soldiers with a higher rating before it and the number of soldiers with a lower rating after it.
2. **Count Valid Teams**: Using these counts, we can determine the number of valid increasing and decreasing teams.

<h3> Example Code </h3>
Here is a more efficient C++ solution:

```cpp
class Solution {
public:
    int numTeams(vector<int>& rating) {
        int n = rating.size();
        int result = 0;
        
        for (int j = 0; j < n; ++j) {
            int less_left = 0, greater_left = 0;
            int less_right = 0, greater_right = 0;
            
            // Count elements smaller/greater than rating[j] to the left of j
            for (int i = 0; i < j; ++i) {
                if (rating[i] < rating[j]) {
                    ++less_left;
                } else if (rating[i] > rating[j]) {
                    ++greater_left;
                }
            }
            
            // Count elements smaller/greater than rating[j] to the right of j
            for (int k = j + 1; k < n; ++k) {
                if (rating[k] < rating[j]) {
                    ++less_right;
                } else if (rating[k] > rating[j]) {
                    ++greater_right;
                }
            }
            
            // Calculate the number of valid teams with j as the middle soldier
            result += less_left * greater_right + greater_left * less_right;
        }
        
        return result;
    }
};
```

<h3> Explanation </h3>

1. **Initialization**: Initialize counters for elements smaller and greater than the current element both to the left and right.
2. **Loop Through Array**: For each element in the array, count elements smaller and greater to its left and right.
3. **Count Valid Teams**: The number of valid teams with the current element as the middle soldier is the sum of products of valid left and right combinations.

<h3> Complexity </h3>

This approach reduces the time complexity to O(n^2), which is more efficient than the O(n^3) solution but still manageable for moderately sized arrays. For very large arrays, further optimizations may be necessary.

#### prefix/suffix arrays
To solve the "Count Number of Teams" problem using prefix/suffix arrays, we can optimize the counting of elements that are smaller or larger than the current element. Here's how:

1. **Prefix Arrays**: Use prefix arrays to count the number of elements smaller or larger than the current element up to that index.
2. **Suffix Arrays**: Use suffix arrays to count the number of elements smaller or larger than the current element from that index to the end.
3. **Counting Valid Teams**: Use these counts to determine the number of valid teams.

<h3> Example Code </h3>

Here's a C++ solution using prefix and suffix arrays:

```cpp
class Solution {
public:
    int numTeams(vector<int>& rating) {
        int n = rating.size();
        vector<int> lessLeft(n, 0), greaterLeft(n, 0);
        vector<int> lessRight(n, 0), greaterRight(n, 0);
        
        // Fill the prefix arrays
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (rating[j] < rating[i]) {
                    ++lessLeft[i];
                } else if (rating[j] > rating[i]) {
                    ++greaterLeft[i];
                }
            }
        }
        
        // Fill the suffix arrays
        for (int i = n - 2; i >= 0; --i) {
            for (int j = n - 1; j > i; --j) {
                if (rating[j] < rating[i]) {
                    ++lessRight[i];
                } else if (rating[j] > rating[i]) {
                    ++greaterRight[i];
                }
            }
        }
        
        int count = 0;
        
        // Count the number of valid teams
        for (int i = 0; i < n; ++i) {
            count += lessLeft[i] * greaterRight[i] + greaterLeft[i] * lessRight[i];
        }
        
        return count;
    }
};
```

<h3> Explanation </h3>

1. **Prefix Arrays**: `lessLeft[i]` and `greaterLeft[i]` store the count of elements smaller and greater than `rating[i]` to the left of `i`.
2. **Suffix Arrays**: `lessRight[i]` and `greaterRight[i]` store the count of elements smaller and greater than `rating[i]` to the right of `i`.
3. **Counting Teams**: For each index `i`, the number of valid teams is calculated using the counts from prefix and suffix arrays:
   - `lessLeft[i] * greaterRight[i]` gives the count of teams where `rating[i]` is the middle element in an increasing sequence.
   - `greaterLeft[i] * lessRight[i]` gives the count of teams where `rating[i]` is the middle element in a decreasing sequence.

This approach is more efficient than the brute-force solution, reducing the overall complexity to O(n^2). For further improvements, more advanced data structures like Fenwick Trees or Segment Trees could be used to reduce the complexity to O(n log n).

## 24.07.30 - 1653. Minimum Deletions to Make String Balanced
[문제 링크](https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/description/)

### 나
```cpp
// 82ms, 23.68MB
class Solution {
public:
    int minimumDeletions(string s) {
        int totA{};
        for(auto c : s) {
            if(c == 'a') ++totA;
        }

        int answer = totA;
        int cntA{}, cntB{};
        for(auto c : s) {
            if(c == 'a') ++cntA;
            else if(c == 'b') ++cntB;

            answer = min(answer, cntB + totA - cntA);
        }
        return answer;
    }
};
```

### gpt
To solve the problem of finding the minimum number of deletions required to make a string balanced, we need to ensure that all 'a's in the string appear before all 'b's. This problem can be approached using dynamic programming or a more optimized two-pass strategy with prefix sums.

Here’s the detailed approach:

<h3> Two-Pass Approach with Prefix Sums </h3>

1. **Prefix Calculation**:
   - Calculate the number of 'b's to the left of each position (prefix_b).
   - Calculate the number of 'a's to the right of each position (suffix_a).

2. **Compute Minimum Deletions**:
   - For each position, compute the total deletions needed to make the string balanced if the split occurs at that position.
   - Track the minimum deletions across all possible split positions.

Here’s the implementation:

```cpp
// 87ms, 53.17MB
class Solution {
public:
    int minimumDeletions(string s) {
        int n = s.size();
        std::vector<int> prefix_b(n + 1, 0); // number of 'b's to the left of i (exclusive)
        std::vector<int> suffix_a(n + 1, 0); // number of 'a's to the right of i (exclusive)
        
        // Fill prefix_b array
        for (int i = 1; i <= n; ++i) {
            prefix_b[i] = prefix_b[i - 1] + (s[i - 1] == 'b' ? 1 : 0);
        }
        
        // Fill suffix_a array
        for (int i = n - 1; i >= 0; --i) {
            suffix_a[i] = suffix_a[i + 1] + (s[i] == 'a' ? 1 : 0);
        }
        
        // Compute minimum deletions
        int min_deletions = n; // Initialize with maximum possible deletions (all characters)
        for (int i = 0; i <= n; ++i) {
            min_deletions = std::min(min_deletions, prefix_b[i] + suffix_a[i]);
        }
        
        return min_deletions;
    }
};
```

<h3> Explanation: </h3>

1. **Prefix Array Calculation**:
   - `prefix_b[i]` counts the number of 'b's in the substring `s[0...i-1]`.
   - Iterate through the string and populate `prefix_b`.

2. **Suffix Array Calculation**:
   - `suffix_a[i]` counts the number of 'a's in the substring `s[i...n-1]`.
   - Iterate through the string in reverse and populate `suffix_a`.

3. **Finding the Minimum Deletions**:
   - For each possible split point `i`, compute the sum of `prefix_b[i]` (deletions needed for 'b's before `i`) and `suffix_a[i]` (deletions needed for 'a's after `i`).
   - Track the minimum of these sums.

<h3> Complexity: </h3>

- **Time Complexity**: O(n), where n is the length of the string. This is because we iterate through the string a constant number of times.
- **Space Complexity**: O(n) for the prefix and suffix arrays.

This approach ensures that the solution is efficient and optimal for the given problem constraints.

