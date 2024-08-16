## ToC
- [August Week 3](#august-week-3)
  - [24.08.12 - 703. Kth Largest Element in a Stream](#240812---703-kth-largest-element-in-a-stream)
    - [나](#나)
    - [gpt](#gpt)
  - [24.08.13 - 40. Combination Sum II](#240813---40-combination-sum-ii)
    - [나](#나-1)
    - [gpt](#gpt-1)
  - [24.08.14 - 719. Find K-th Smallest Pair Distance](#240814---719-find-k-th-smallest-pair-distance)
    - [나](#나-2)
    - [gpt](#gpt-2)

# August Week 3
## 24.08.12 - 703. Kth Largest Element in a Stream
[문제 링크](https://leetcode.com/problems/kth-largest-element-in-a-stream/description/)

### 나
```cpp
// 675ms, 25.64MB
// https://en.cppreference.com/w/cpp/algorithm/nth_element
constexpr int SIZE = 20'010;
class KthLargest {
public:
    int arr[SIZE]{}, s{}, kth{};
    KthLargest(int k, vector<int>& nums) {
        kth = k - 1;
        for(int e{static_cast<int>(nums.size())};s<e;++s) {
            arr[s] = nums[s];
        }
    }
    
    int add(int val) { // kth largest element (At most 10^4 calls will be made to add.)
        arr[s++] = val;
        nth_element(arr, arr + kth, arr + s, greater<>());
        return arr[kth];
    }
};
// sort는 TLE
```

### gpt
The problem "Kth Largest Element in a Stream" from LeetCode requires you to design a data structure that can efficiently add elements from a stream and retrieve the Kth largest element in constant time. Here’s a solution approach:

<h3> Solution Approach </h3>

1. **Use a Min-Heap (Priority Queue):**
   - Maintain a min-heap of size `k`.
   - The root of this heap will always be the Kth largest element.
   - As new elements arrive, add them to the heap.
   - If the heap size exceeds `k`, remove the smallest element.

<h3> Implementation </h3>

Here is an example in C++:

```cpp
#include <queue>
#include <vector>

class KthLargest {
private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    int k;

public:
    KthLargest(int k, std::vector<int>& nums) {
        this->k = k;
        for(int num : nums) {
            add(num);
        }
    }

    int add(int val) {
        minHeap.push(val);
        if(minHeap.size() > k) {
            minHeap.pop();
        }
        return minHeap.top();
    }
};
```

<h3> Explanation: </h3>

- The constructor initializes the class with `k` and the initial elements. It then adds each element using the `add` function.
- The `add` function inserts the new value into the min-heap. If the size of the heap exceeds `k`, it removes the smallest element (ensuring the heap only contains the largest `k` elements).
- The top element of the min-heap is the Kth largest element.

This approach ensures the Kth largest element can be efficiently retrieved after each addition.

You can find more details and test cases on the [LeetCode problem page](https://leetcode.com/problems/kth-largest-element-in-a-stream/).

> 더 간단한 아이디어가 있었다.. (`nth_element`에 꽂혀버려서 다른 생각을 못 했다.)

## 24.08.13 - 40. Combination Sum II
[문제 링크](https://leetcode.com/problems/combination-sum-ii/description/)

### 나
DP가 될 수 있을 것 같아서 삽질 겁나 했다.. 결국 실패
- 점화식은 어떻게 어떻게 된 것 같은데, 개수가 아니고 조합을 구해야 해서 복구할 때 어려움이 있었다. 
- 구하려면 어떻게 할 수 있을 것 같긴 한데.., 과연 그게 효율적인지 모르겠다.

결국 backtracking으로 풀었다. (배열 길이가 100개라 시간초과날 줄 알아서 처음부터 안 하긴 했는데, 다른 방법이 없어서 저걸로 했더니 풀리더라.)
- 조합 만드는 거 오랜만에 하려니 생각보다 시간이 더 걸림.
```cpp
// 4ms, 13MB
class Solution {
public:
    vector<vector<int>> answer;
    vector<int> sequence, realCandidates;
    int SIZE, realTarget;

    void backtracking(int index, int sum) {
        if(sum == realTarget) {
            answer.push_back(sequence);
            return;
        }

        int lastUse{};
        for(int i{index};i<SIZE;++i) {
            if(lastUse == realCandidates[i]) continue;
            if(sum + realCandidates[index] > realTarget) break;

            lastUse = realCandidates[i];
            sequence.push_back(realCandidates[i]);
            backtracking(i + 1, sum + realCandidates[i]);
            sequence.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        realTarget = target;
        for(int candi : candidates) { // eliminate element larger than target
            if(candi > target) continue;
            realCandidates.push_back(candi);
        }

        sort(begin(realCandidates), end(realCandidates)); // sort ascending
        SIZE = static_cast<int>(realCandidates.size());

        backtracking(0, 0);

        return answer;
    }
};
```

### gpt
The problem "Combination Sum II" on LeetCode requires finding all unique combinations in a list of numbers where the chosen numbers sum to a target value. Each number in the list can only be used once in a combination.

Here’s a structured approach to solve the problem:

<h3> Problem Breakdown </h3>

Given a list of integers `candidates` and an integer `target`, you need to find all unique combinations where the candidate numbers sum to the target. Each number in `candidates` may only be used once in the combination.

<h3> Constraints and Considerations </h3>

1. The list `candidates` may contain duplicates.
2. The solution should not contain duplicate combinations.
3. Each combination must be in non-descending order.

<h3> Approach </h3>

We can solve this problem using backtracking. Here's how:
1. **Sort the Array**: This allows us to easily skip duplicates.
2. **Backtracking Function**: Create a recursive function that tries to build valid combinations.
3. **Pruning**: Skip over elements that would lead to the same combination or exceed the target.

<h3> Implementation in C++ </h3>

```cpp
// 0ms, 12.85MB
// GPT
class Solution {
public:
    void backtrack(int start, int target, std::vector<int>& candidates, 
                   std::vector<int>& currentCombination, 
                   std::vector<std::vector<int>>& result) {
        // Base case: if the target is met
        if (target == 0) {
            result.push_back(currentCombination);
            return;
        }
        
        for (int i = start; i < candidates.size(); i++) {
            // Skip duplicates
            if (i > start && candidates[i] == candidates[i - 1]) {
                continue;
            }
            
            // If the current number exceeds the target, break the loop
            if (candidates[i] > target) {
                break;
            }
            
            // Include candidates[i] in the current combination
            currentCombination.push_back(candidates[i]);
            
            // Recurse with reduced target and next start position
            backtrack(i + 1, target - candidates[i], candidates, currentCombination, result);
            
            // Backtrack: remove the last added element
            currentCombination.pop_back();
        }
    }
    
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> result;
        std::vector<int> currentCombination;
        
        // Sort the candidates to handle duplicates and facilitate pruning
        std::sort(candidates.begin(), candidates.end());
        
        // Start backtracking
        backtrack(0, target, candidates, currentCombination, result);
        
        return result;
    }
};
```

<h3> Explanation </h3>

1. **Sorting**: We start by sorting the `candidates` array. This helps in skipping duplicates efficiently.
2. **Backtracking**:
   - The `backtrack` function is used to explore possible combinations starting from index `start`.
   - We skip duplicates by checking if `candidates[i] == candidates[i - 1]` for elements beyond the first in the loop.
   - We include the current candidate in the combination and reduce the `target` accordingly.
   - If the `target` becomes `0`, a valid combination is found and added to the result.
   - We backtrack by removing the last added element to explore other possibilities.
3. **Edge Cases**: The function handles cases where the array is empty or the target is impossible to achieve by the loop termination conditions.

<h3> Time Complexity </h3>

- The time complexity is $O(2^n)$, where $n$ is the length of the `candidates` array, as each element can either be included or excluded from a combination.
- Sorting takes $O(n \log n)$.

This method is efficient and should work well within typical input constraints on LeetCode.

<h3> Can it be solved with DP? </h3>

The "Combination Sum II" problem is generally better suited to a backtracking approach due to the nature of the problem (finding all combinations), but it is possible to solve it using Dynamic Programming (DP). However, the DP approach can be more complex and less intuitive compared to backtracking for this particular problem.

<h3> DP Approach Explanation </h3>

In DP, we can maintain a 2D table `dp[i][j]` where:
- `i` represents the number of elements considered from the `candidates` array.
- `j` represents the current target sum.

The value at `dp[i][j]` would be a set of all possible combinations that sum up to `j` using the first `i` elements from `candidates`.

<h3> Key Steps </h3>

1. **Initialization**: 
   - Start with `dp[0][0]` being an empty set because there’s only one way to achieve the target sum of 0 (by using no elements).
   - Other `dp[0][j]` for `j > 0` would be empty because no combination of zero elements can achieve a positive target sum.

2. **Filling the DP Table**:
   - For each element `candidates[i]`, update the table by considering whether to include this element or not.
   - For every target `j`, check the combinations formed by either including `candidates[i]` or excluding it.
   - Use a set to avoid duplicates.

3. **Result**:
   - The answer will be in `dp[n][target]`, where `n` is the number of elements in the `candidates` array.

<h3> Implementation in C++ </h3>

Here is an implementation of this approach:

```cpp
// wrong answer..!
class Solution {
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
        int n = candidates.size();
        
        // Sort candidates to handle duplicates
        std::sort(candidates.begin(), candidates.end());

        // DP table: dp[i] will store the list of combinations that sum up to 'i'
        std::vector<std::set<std::vector<int>>> dp(target + 1);
        
        // Initialize the DP with an empty combination for sum 0
        dp[0].insert({});
        
        for (int num : candidates) {
            // Iterate backwards to avoid overwriting dp[j]
            for (int j = target; j >= num; --j) {
                // Update the dp[j] by adding the current number to each combination
                for (const auto& comb : dp[j - num]) {
                    std::vector<int> newComb = comb;
                    newComb.push_back(num);
                    dp[j].insert(newComb);
                }
            }
        }
        
        // Convert set to vector of vectors for the result
        std::vector<std::vector<int>> result(dp[target].begin(), dp[target].end());
        return result;
    }
};
```

<h3> Explanation </h3>

1. **Initialization**:
   - We start with `dp[0]` containing an empty vector to represent the empty combination.

2. **Filling the DP Table**:
   - We iterate through each candidate number and update the DP table by considering including this number to form new combinations.
   - We work backward from `target` to `num` to avoid overwriting combinations in the current iteration.

3. **Avoiding Duplicates**:
   - Using a `set` helps to automatically remove duplicate combinations.

4. **Result**:
   - After processing all candidates, the DP table entry `dp[target]` contains all unique combinations that sum up to the target.

<h3> Time Complexity </h3>

The DP approach has a time complexity of $O(n \times target \times k)$, where:
- $n$ is the number of candidates.
- `target` is the target sum.
- $k$ is the average size of combinations.

This DP approach is more complex and generally slower compared to the backtracking solution. However, it provides an alternative method to solving the problem using dynamic programming, which may be interesting from an educational perspective.

<h3> But it makes wrong answer. </h3>

You're right. The DP approach I initially described doesn't account for duplicate elements correctly in the context of the "Combination Sum II" problem. The issue arises because simply using a set in the DP table to avoid duplicates doesn't respect the uniqueness constraint correctly when duplicate elements are involved. Let's explore why that happens and how to fix it.

<h3> Problem with the Previous DP Approach </h3>

In "Combination Sum II," each element in the `candidates` array can be used only once per combination, and the array may contain duplicates. The previous DP solution didn't correctly handle cases where we need to ensure that each candidate is used at most once in any specific combination.

<h3> Corrected DP Approach </h3>

To correct the DP approach, we need to ensure that we do not consider the same candidate multiple times at the same position in forming a combination, and we should also respect the fact that candidates can have duplicates.

<h3> Updated Strategy </h3>

We can tweak the DP approach by making sure that when we're forming combinations for a specific sum, we only consider using each candidate exactly once. This can be done by using a different state in the DP table or by iterating carefully to avoid reuse of the same candidate in a way that would violate the uniqueness constraint.

However, due to the complexity of handling duplicate elements correctly in a DP-based solution and ensuring combinations are unique, a backtracking solution is typically more natural and easier to implement correctly.

<h3> Conclusion </h3>

Given the constraints of this problem, the most effective and correct approach remains backtracking. The DP solution is theoretically possible but significantly more complex to implement correctly while ensuring no duplicates and considering the uniqueness of combinations. Thus, the backtracking approach that was provided earlier is more reliable and efficient for this particular problem.

<h3> 그럼 처음부터 안 된다고 하지.. </h3>

## 24.08.14 - 719. Find K-th Smallest Pair Distance
[문제 링크](https://leetcode.com/problems/find-k-th-smallest-pair-distance/description/?envType=daily-question&envId=2024-08-14)

### 나
아이디어:
- 정렬 $\rightarrow$ binary search
  - `left = 0`, `right = nums.back() - nums.front()`
  - mid 이하인 애들 개수 구해서 정확한 mid 찾기.

**gpt 코드 참고**
```cpp
// 3ms, 12.91MB
class Solution {
public:
    int countPairs(const std::vector<int>& nums, int mid) {
        int cnt{}, j{};
        
        for(int i{}, e{static_cast<int>(nums.size())}; i < e; ++i) {
            while(j < e && nums[j] - nums[i] <= mid) {
                ++j;
            }
            cnt += j - i - 1; // i를 시작점으로 거리가 mid 이하인 것들의 개수
        }
        
        return cnt;
    }

    int smallestDistancePair(std::vector<int>& nums, int k) {
        sort(begin(nums), end(nums));
        int left{}, right = nums.back() - nums.front();
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (countPairs(nums, mid) >= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
};
```

**참고**
```cpp
while(s < e) // ~
// s = mid + 1 && e = mid 방식 구현은 처음 지점을 찾는 것 → [ s, e )
// s = mid && e = mid - 1 방식은 마지막 지점을 찾는 것 → ( s, e ]
```

### gpt
To solve the problem of finding the k-th smallest pair distance on LeetCode, we'll use a binary search combined with a two-pointer technique. Here's a step-by-step explanation:

<h3> Problem Summary </h3>

Given an array `nums` and an integer `k`, the task is to find the k-th smallest distance among all pairs `(i, j)` where `0 <= i < j < len(nums)`.

<h3> Solution Strategy </h3>

1. **Sort the Array:**
   Start by sorting the array `nums`. Sorting helps in simplifying the problem because the distance between any two elements is minimized when they are close to each other in the sorted order.

2. **Binary Search on Distance:**
   We perform a binary search on the possible range of distances. The minimum possible distance is `0` (if there are duplicate elements), and the maximum possible distance is `nums[n-1] - nums[0]` where `n` is the length of `nums`.

3. **Counting Pairs with Distance <= mid:**
   For each midpoint `mid` in the binary search, we count how many pairs have a distance less than or equal to `mid`. This can be efficiently done using a two-pointer technique. 

4. **Adjust the Search Range:**
   - If the count of pairs with distance less than or equal to `mid` is greater than or equal to `k`, it means the k-th smallest distance might be `mid` or smaller, so we move the upper bound.
   - Otherwise, we move the lower bound up.

5. **Convergence:**
   The process continues until the lower and upper bounds converge, at which point we've found the k-th smallest distance.

<h3> Implementation </h3>

```cpp
// 3ms, 12.88MB
class Solution {
public:
    int countPairs(const std::vector<int>& nums, int mid) {
        int count = 0;
        int left = 0;
        for (int right = 0; right < nums.size(); ++right) {
            while (nums[right] - nums[left] > mid) {
                ++left;
            }
            count += right - left;
        }
        return count;
    }

    int smallestDistancePair(std::vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());
        int low = 0;
        int high = nums.back() - nums.front();
        
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (countPairs(nums, mid) >= k) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        
        return low;
    }
};
```

<h3> Explanation: </h3>

- **Sorting:** The `nums` array is sorted first.
- **Binary Search:** The binary search is performed between the minimum and maximum possible distances.
- **Counting pairs:** The `countPairs` function counts how many pairs have a distance less than or equal to `mid` using a two-pointer technique.
- **Binary Search Adjustment:** Based on the count of pairs, the binary search range is adjusted until convergence.

<h3> Complexity: </h3>

- **Time Complexity:** `O(n log n + n log d)` where `n` is the number of elements in `nums` and `d` is the difference between the maximum and minimum elements.
- **Space Complexity:** `O(1)` additional space apart from the input array.

This solution efficiently finds the k-th smallest pair distance, even for large inputs.
