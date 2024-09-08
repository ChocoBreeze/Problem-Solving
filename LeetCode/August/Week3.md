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
  - [24.08.15 - 860. Lemonade Change](#240815---860-lemonade-change)
    - [나](#나-3)
    - [gpt](#gpt-3)
  - [24.08.16 - 624. Maximum Distance in Arrays](#240816---624-maximum-distance-in-arrays)
    - [나](#나-4)
    - [gpt](#gpt-4)
  - [24.08.17 - 1937. Maximum Number of Points with Cost](#240817---1937-maximum-number-of-points-with-cost)
    - [나](#나-5)
    - [gpt](#gpt-5)
    - [Solution](#solution)
      - [Overview](#overview)
      - [Approach 1: Dynamic Programming](#approach-1-dynamic-programming)
      - [Approach 2: Dynamic Programming (Optimized)](#approach-2-dynamic-programming-optimized)
  - [24.08.18 - 264. Ugly Number II](#240818---264-ugly-number-ii)
    - [나](#나-6)
    - [gpt](#gpt-6)
      - [Min Heap](#min-heap)
      - [DP](#dp)

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

## 24.08.15 - 860. Lemonade Change
[문제 링크](https://leetcode.com/problems/lemonade-change/description/?envType=daily-question&envId=2024-08-15)

### 나
문제 이해하는데 조금 힘들었음.
- 달러 종류는 5, 10, 20 밖에 없음.

```cpp
// 74ms, 86.1MB
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int canUse{};
        int dollar5{}, dollar10{}, dollar20{};
        for(int bill : bills) {
            if(bill == 5) dollar5++;
            else if(bill == 10) {
                if(dollar5 >= 1) {
                    dollar10++;
                    dollar5--;
                }
                else return false;
            }
            else {
                if(dollar10>=1 && dollar5>=1) {
                    dollar10--;
                    dollar5--;
                }
                else if(dollar5>=3) {
                    dollar5-=3;
                }
                else return false;
            }
        }
        return true;
    }
};
```

### gpt
The "Lemonade Change" problem is a classic greedy algorithm problem where you need to determine if you can provide the correct change to every customer in a queue. Let's break down the problem and provide an efficient solution.

<h3> Problem Summary </h3>

You're running a lemonade stand, and every lemonade costs $5. Customers pay with a $5, $10, or $20 bill. You must give back the exact change using the bills you have received so far. The goal is to determine if you can provide change to every customer in the queue.

<h3> Strategy </h3>

To solve this problem, you can use a greedy algorithm approach:

1. **Track the Available Bills:** 
   Keep track of how many $5 and $10 bills you have, since these are the only bills you might need to give as change.

2. **Process Each Customer:**
   - If a customer pays with a $5 bill, simply accept it.
   - If a customer pays with a $10 bill, you need to give back one $5 bill as change.
   - If a customer pays with a $20 bill, you should ideally give back one $10 bill and one $5 bill (to minimize the number of $5 bills you spend). If that's not possible, you give back three $5 bills.

3. **Check Feasibility:** 
   At each step, check if you can provide the necessary change. If at any point you can't, return `false`.

4. **Final Result:**
   If you successfully provide change to every customer, return `true`.

<h3> Implementation </h3>

Here’s how you can implement this strategy in C++:

```cpp
// 81ms, 85.91MB
class Solution {
public:
    bool lemonadeChange(std::vector<int>& bills) {
        int five_dollars = 0, ten_dollars = 0;
        
        for (int bill : bills) {
            if (bill == 5) {
                // Just accept the $5 bill
                five_dollars++;
            } else if (bill == 10) {
                // Give back one $5 bill as change
                if (five_dollars > 0) {
                    five_dollars--;
                    ten_dollars++;
                } else {
                    return false; // Can't give change
                }
            } else if (bill == 20) {
                // Prefer to give back one $10 bill and one $5 bill
                if (ten_dollars > 0 && five_dollars > 0) {
                    ten_dollars--;
                    five_dollars--;
                } else if (five_dollars >= 3) {
                    // Otherwise, give back three $5 bills
                    five_dollars -= 3;
                } else {
                    return false; // Can't give change
                }
            }
        }
        
        return true;
    }
};
```

<h3> Explanation: </h3>

- **Counters for Bills:** We use two variables, `five_dollars` and `ten_dollars`, to track the number of $5 and $10 bills we have.
- **Decision Making:**
  - For a $10 bill, you give a $5 bill as change if available.
  - For a $20 bill, you try to give one $10 and one $5 bill first. If that's not possible, you try to give three $5 bills.
- **Greedy Choice:** The greedy choice is to minimize the depletion of $5 bills by preferring to give a $10 bill as change when possible.

<h3> Complexity: </h3>

- **Time Complexity:** `O(n)`, where `n` is the number of customers.
- **Space Complexity:** `O(1)`, as we are only using a few extra variables.

This solution efficiently checks if you can provide the correct change to every customer, returning `true` if you can and `false` otherwise.

## 24.08.16 - 624. Maximum Distance in Arrays
[문제 링크](https://leetcode.com/problems/maximum-distance-in-arrays/description/)

### 나
서로 다른 배열에서 최댓값, 최솟값 뽑기
```cpp
// 229ms, 107.68MB
class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        const int MIN = -10001, MAX = 10001;
        int totMin{MAX}, totMax{MIN};

        int answer{-1};
        for(vector<int>& array : arrays) {
            int nowMin{MAX}, nowMax{MIN};
            for(int num : array) {
                nowMin = min(nowMin, num);
                nowMax = max(nowMax, num);
            }
            answer = max({answer, nowMax - totMin, totMax - nowMin});
            totMin = min(totMin, nowMin);
            totMax = max(totMax, nowMax);
        }
        return answer;
    }
};
```

근데 배열 자체를 순회 안 해도 시간 차이 얼마 안 남..
```cpp
// 226ms, 107.96MB
class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        const int MIN = -10001, MAX = 10001;
        int totMin{MAX}, totMax{MIN};

        int answer{-1};
        for(vector<int>& array : arrays) {
            int nowMin = array.front(), nowMax = array.back();
            answer = max({answer, nowMax - totMin, totMax - nowMin});
            
            totMin = min(totMin, nowMin);
            totMax = max(totMax, nowMax);
        }
        return answer;
    }
};
```

### gpt
The "Maximum Distance in Arrays" problem on LeetCode requires finding the maximum distance between two elements, where one element comes from one array and the other element comes from a different array. The distance is defined as the absolute difference between these two elements.

<h3> Problem Summary </h3>

You are given a list of arrays, and you need to find the maximum distance between any two elements from different arrays. The distance between two elements `a` from array `i` and `b` from array `j` is calculated as `|a - b|` where `i != j`.

<h3> Strategy </h3>

1. **Track the Minimum and Maximum Values:**
   - As you iterate through the list of arrays, maintain the global minimum and maximum values encountered so far, excluding the current array in consideration.
  
2. **Calculate Maximum Distance:**
   - For each array, calculate the distance using the current array's minimum and maximum values combined with the previously tracked global minimum and maximum values from other arrays.
   - Keep track of the maximum distance encountered.

3. **Update the Global Minimum and Maximum:**
   - After processing each array, update the global minimum and maximum values to include the current array’s minimum and maximum values.

<h3> Implementation </h3>

Here’s a C++ implementation:

```cpp
// 224ms, 107.94MB
class Solution {
public:
    int maxDistance(std::vector<std::vector<int>>& arrays) {
        int max_dist = 0;
        int current_min = arrays[0].front();
        int current_max = arrays[0].back();

        for (int i = 1; i < arrays.size(); ++i) {
            int array_min = arrays[i].front();
            int array_max = arrays[i].back();

            // Calculate the maximum distance with the current array
            max_dist = std::max(max_dist, std::max(std::abs(array_max - current_min), std::abs(current_max - array_min)));

            // Update the global minimum and maximum values
            current_min = std::min(current_min, array_min);
            current_max = std::max(current_max, array_max);
        }

        return max_dist;
    }
};
```

<h3> Explanation: </h3>

1. **Initialization:**
   - Start by setting `current_min` and `current_max` to the first array’s minimum and maximum values. This is our baseline for comparison.
  
2. **Iterate through the Arrays:**
   - For each subsequent array:
     - Calculate the potential maximum distance using the current array's minimum and maximum values with the previously tracked `current_min` and `current_max`.
     - Update `max_dist` to keep track of the maximum distance found so far.
  
3. **Update for Next Iteration:**
   - After processing the current array, update `current_min` and `current_max` to include this array's values, ensuring they represent the global minimum and maximum across all processed arrays.

<h3> Complexity: </h3>

- **Time Complexity:** `O(n)`, where `n` is the number of arrays. Each array is processed once.
- **Space Complexity:** `O(1)`, since only a few variables are used for tracking the minimum, maximum, and maximum distance.

This approach efficiently calculates the maximum possible distance between elements from different arrays, ensuring it operates within optimal time and space constraints.

## 24.08.17 - 1937. Maximum Number of Points with Cost
[문제 링크](https://leetcode.com/problems/maximum-number-of-points-with-cost/description/)

### 나
DP일 거라곤 생각도 못 했다.  
gpt 코드 봐도 이해가 안 된다..

### gpt
Here's a C++ solution using dynamic programming to solve the "Maximum Number of Points with Cost" problem:

```cpp
// 233ms, 129.12MB
class Solution {
public:
    long long maxPoints(vector<vector<int>>& points) {
        int m = points.size(), n = points[0].size();
        vector<long long> prev(n, 0);

        for (int j = 0; j < n; ++j)
            prev[j] = points[0][j];

        for (int i = 1; i < m; ++i) {
            vector<long long> left(n, 0), right(n, 0), curr(n, 0);

            left[0] = prev[0];
            for (int j = 1; j < n; ++j)
                left[j] = max(left[j-1], prev[j] + j);

            right[n-1] = prev[n-1] - (n-1);
            for (int j = n-2; j >= 0; --j)
                right[j] = max(right[j+1], prev[j] - j);

            for (int j = 0; j < n; ++j)
                curr[j] = max(left[j] - j, right[j] + j) + points[i][j];

            prev = curr;
        }

        return *max_element(prev.begin(), prev.end());
    }
};
```

<h3> Explanation: </h3>

1. **Dynamic Programming (DP) Approach**:
   - `prev` stores the maximum points possible for each element in the previous row.
   - `left` and `right` arrays are used to track maximum points considering the left and right movements.
   - For each row, calculate the maximum points for each element using `left` and `right` arrays.

2. **Time Complexity**: $O(m \times n)$, where $m$ is the number of rows and $n$ is the number of columns.

This solution efficiently computes the maximum possible points while accounting for the cost of moving horizontally between elements in successive rows.

---
> please explain recurrence relation(점화식)

The recurrence relation for this problem is based on finding the maximum points for each element in the current row, considering the cost of moving from any element in the previous row.

Let `dp[i][j]` represent the maximum points achievable at row `i` and column `j`.

The recurrence relation is:

$$\text{dp}[i][j] = \text{points}[i][j] + \max(\text{dp}[i-1][k] - |j-k|)$$

Where:
- `points[i][j]` is the value of the current element.
- `|j-k|` is the cost of moving horizontally from column `k` in the previous row to column `j` in the current row.

<h3> Explanation: </h3>

- For each element in row `i`, you must consider all possible elements from the previous row `i-1` and take the maximum value, subtracting the cost of horizontal movement.
- This ensures you account for both the points and the movement cost.

<h3> Optimization: </h3>

- To avoid recalculating the max for each element, you can precompute the maximums using the `left` and `right` arrays as demonstrated in the code. This reduces the time complexity by efficiently tracking the best transitions.

---
> Why in the code we should calculate left and right separately?

In the code, the `left` and `right` arrays are calculated separately to efficiently compute the maximum points for each column `j` in the current row `i` while considering the costs of moving from any column `k` in the previous row `i-1`.

<h3> Reasoning: </h3>

- **Left Array**: Tracks the maximum value considering left-to-right transitions.
- **Right Array**: Tracks the maximum value considering right-to-left transitions.

By calculating these arrays, you can determine the maximum possible value at each column in constant time, instead of recalculating it for every possible transition. This reduces the complexity from $O(n^2)$ to $O(n)$ for each row.

In the code, the expressions `prev[j] + j` and `prev[j] - j` are used to optimize the calculation of the maximum points when moving left-to-right or right-to-left, respectively. Here's why:

<h4> Left Array (<code>left[j] = max(left[j-1], prev[j] + j)</code>): </h4>

- **Purpose**: To keep track of the maximum possible value when moving from left to right.
- **`prev[j] + j`**: The `+ j` compensates for the cost of moving to the right. If you're moving from `prev[k]` to `j`, the cost is `j - k`. Adding `j` allows you to track the maximum value by storing the best possible score considering all previous left-side elements up to `j`.

<h4> Right Array (<code>right[j] = max(right[j+1], prev[j] - j)</code>): </h4>

- **Purpose**: To track the maximum possible value when moving from right to left.
- **`prev[j] - j`**: The `- j` compensates for the cost of moving to the left. If you're moving from `prev[k]` to `j`, the cost is `k - j`. Subtracting `j` allows you to track the maximum value considering all previous right-side elements up to `j`.

<h3> Combined Use: </h3>

By precomputing these values, you efficiently determine the maximum possible score for each element in the current row without having to re-evaluate all possible transitions from the previous row.

---
> Why we have to compensate with `j`?

We need to compensate with `j` in `prev[j] + j` and `prev[j] - j` to efficiently incorporate the horizontal movement cost into the dynamic programming transition.

<h3> Breakdown: </h3>

1. **Transition Cost**:
   - Moving from column `k` to column `j` incurs a cost of `|j - k|`.
   - Instead of calculating `|j - k|` explicitly in each transition, we precompute adjusted values to handle this implicitly.

2. **Left Array (`left[j]`)**:
   - `left[j]` must track the best score considering movement from any previous column `k` to `j` with cost `j - k`.
   - `prev[k] - k + j` is broken down into `prev[k] + k` (precomputed) and `j` (adjusted later).

3. **Right Array (`right[j]`)**:
   - `right[j]` must track the best score considering movement from any previous column `k` to `j` with cost `k - j`.
   - `prev[k] + k - j` is similarly split into `prev[k] - k` (precomputed) and `-j` (adjusted later).

These adjustments allow efficient calculation of the maximum possible score while moving across rows in linear time.

> 잘 이해 안 가는데, 일단 넘어가자... (하단 솔루션 참고)

### Solution
참고: [Solution](https://leetcode.com/problems/maximum-number-of-points-with-cost/editorial)

#### Overview

Our goal with this problem is to determine the maximum number of points we can get by picking one cell from each row of a given matrix. The possible score for each row consists of two components:

1. The point value of the selected cell.
2. A penalty equal to the horizontal distance between the current cell and the selected cell in the previous row.

The problem constraints hint that an efficient solution is needed. Specifically, since the problem is constrained by $m \times n \leq 10^5$, we should aim for an $O(m \times n)$ solution.

In a brute-force approach, the idea would be to explore every possible combination of selecting one element from each row. Starting with the first row, we'd pick an element, then move to the next row and try every possible element there, repeating this process until we've chosen an element from each row. For each of these combinations, we would calculate the sum of the selected elements while also accounting for the cost incurred when switching columns between consecutive rows.

This approach involves using nested loops to compare every possible cell in each row, resulting in an exponential number of possibilities. As the number of rows and columns increases, the number of potential paths grows rapidly, making this method computationally infeasible for large grids. Instead, we need to optimize how we transition from one row to the next while keeping track of the maximum points we can accumulate.

Before attempting this problem, it may be helpful to solve related problems like "[121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)" and "[1014. Best Sightseeing Pair](https://leetcode.com/problems/best-sightseeing-pair/)." These problems involve similar concepts of optimizing a series of decisions or transitions, which is a key aspect of solving the matrix points problem efficiently. Understanding the strategies used in those problems will build a foundation for approaching this one.

#### Approach 1: Dynamic Programming

**Intuition**

Our goal is to create a solution that efficiently finds the maximum points possible while moving from the top row to the bottom row of the matrix. To do this, we initialize an array called `previousRow` with the values of the first row of the matrix. We can then operate off this array to build another array, `currentRow`. Each element in `currentRow` will represent the number of points we can gain by picking that cell, taking into account both the point value of the cell and the penalty for choosing it.

A straightforward approach to build `currentRow` would be to iterate over all cells in `previousRow` and apply the penalty for the horizontal distance:

    // For the Xth and (X+1)th rows of the points matrix
    currentRow[i] = max(previousRow[j] - abs(j - i) for j in range(n)) + points[X+1][i];

Since this approach directly checks every cell in `previousRow` for each cell in `currentRow`, it involves repeated and redundant calculations and has a time complexity of $O(n^2)$ for each row, where $n$ is the number of columns. Given that we need to repeat this process for every row, this solution would not meet the problem's constraints, especially for large matrices.

Instead of recalculating the possible scores from every cell in `previousRow` for each cell in `currentRow`, we can use two auxiliary arrays, `leftMax` and `rightMax`, to store the maximum possible contributions from the left and right, respectively. This allows us to simply compare these two precomputed values to determine the best score for each cell in `currentRow`.

To construct `leftMax`:

1. Set `leftMax[0]` equal to `previousRow[0]`, as there are no values to its left.
2. For each subsequent index `i`, compute `leftMax[i]` as the maximum of `previousRow[i]` and `leftMax[i-1] - 1`. The subtraction accounts for the penalty incurred when moving horizontally to the next cell.

Similarly, construct `rightMax` by iterating from right to left.

With `leftMax` and `rightMax` prepared, we can compute the maximum points for each cell in `currentRow` using:

    currentRow[i] = max(leftMax[i], rightMax[i]) + points[X+1][i];

This allows us to efficiently calculate the maximum points for each row in $O(n)$ time, making the overall time complexity $O(m \times n)$, where $m$ is the number of rows.

We apply this optimized process iteratively from the first row to the last row of the matrix. After processing all rows, the array `previousRow` will contain the maximum possible points for each cell in the last row. The final answer is the maximum value found in this array, which represents the highest score achievable while moving from the top to the bottom of the matrix.

**Algorithm**

- Set `rows` and `cols` as the number of rows and columns in the input matrix `points`.
- Create an array `previousRow`. Initialize it with values of the first row of the input matrix.
- Iterate from the 0th to rows-2th row. For each `row`:
  - Initialize arrays:
    - `leftMax`: for maximum points achievable from left to right.
    - `rightMax`: for maximum points achievable from right to left.
    - `currentRow`: for the maximum points achievable for each cell in the current row.
  - Set the first element of `leftMax` to the first element of `previousRow`.
  - Loop `col` from 1 to the end of `cols`:
    - Set `leftMax[col]` to the maximum of `leftMax[col - 1] - 1` and `previousRow[col]`.
  - Set the last element of `rightMax` to the last element of `previousRow`.
  - Loop `col` from `cols - 2` to 0:
    - Set `rightMax[col]` to the maximum of `rightMax[col + 1] - 1` and `previousRow[col]`.
  - Loop `col` from 0 to the end of `cols`:
    - Calculate the maximum points for each cell in the current row:
      - Take the value from `points` for the next row (`points[row + 1][col]`).
      - Add the maximum of `leftMax[col]` and `rightMax[col]` to it.
    - Set the calculated value to `currentRow[col]`.
  - Update `previousRow` to be `currentRow`.
- Initialize a variable `maxPoints` to store the overall maximum points.
- Loop through all values of `previousRow` and set `maxPoints` to the maximum.
- Return `maxPoints` as our answer.

**Implementation**

```cpp
// 198ms, 129.08MB
class Solution {
public:
    long long maxPoints(vector<vector<int>>& points) {
        int rows = points.size(), cols = points[0].size();
        vector<long long> previousRow(cols);

        // Initialize the first row
        for (int col = 0; col < cols; ++col) {
            previousRow[col] = points[0][col];
        }

        // Process each row
        for (int row = 0; row < rows - 1; ++row) {
            vector<long long> leftMax(cols);
            vector<long long> rightMax(cols);
            vector<long long> currentRow(cols);

            // Calculate left-to-right maximum
            leftMax[0] = previousRow[0];
            for (int col = 1; col < cols; ++col) {
                leftMax[col] = max(leftMax[col - 1] - 1, previousRow[col]);
            }

            // Calculate right-to-left maximum
            rightMax[cols - 1] = previousRow[cols - 1];
            for (int col = cols - 2; col >= 0; --col) {
                rightMax[col] = max(rightMax[col + 1] - 1, previousRow[col]);
            }

            // Calculate the current row's maximum points
            for (int col = 0; col < cols; ++col) {
                currentRow[col] =
                    points[row + 1][col] + max(leftMax[col], rightMax[col]);
            }

            // Update previousRow for the next iteration
            previousRow = currentRow;
        }

        // Find the maximum value in the last processed row
        long long maxPoints = 0;
        for (int col = 0; col < cols; ++col) {
            maxPoints = max(maxPoints, previousRow[col]);
        }

        return maxPoints;
    }
};
```

**Complexity Analysis**

Let $m$ and $n$ be the height and width of `points`.

- **Time complexity:** $O(m \times n)$
  - The outer loop runs $m - 1$ times. Inside it, two inner loops run $n - 1$ times and another one runs $n$ times. Thus, the overall time complexity is $O(m \times n)$.
  
- **Space complexity:** $O(n)$
  - We use four additional arrays, each of which takes $n$ space. All other variables take constant space.

---

#### Approach 2: Dynamic Programming (Optimized)

**Intuition**

In the previous approach, we used auxiliary arrays to keep track of the maximum points achievable from the left and right directions. This time, we streamline the process by using the `previousRow` array itself as temporary storage for the left-side maximums and then update it with the right-side maximums in a single pass.

Thus, we will require two passes to do this.

1. **First Pass: Left-to-Right Sweep**
   - We begin by iterating through the row from left to right. As we move, we store the maximum points achievable from the left in the `previousRow` array. This step essentially builds the equivalent of the `leftMax` array directly within `previousRow`.
   - At the start, `runningMax` is initialized to `0`. At the beginning of each iteration, `runningMax` will hold the maximum value that can be achieved from the left till $i-1$.
   - For each cell $i$, we update `runningMax` to the maximum of `previousRow[i]` and `runningMax - 1`, where the subtraction accounts for the horizontal distance penalty.
   - This process ensures that `previousRow[i]` contains the maximum points that can be accumulated when moving from the left to the $i$-th cell.

2. **Second Pass: Right-to-Left Sweep**
   - Next, we perform a second loop, this time iterating from right to left. This pass starts from the right and combines the results from the left-to-right pass with the maximum values from the right.
   - We reset `runningMax` to `0` before starting this pass. Similar to the left-to-right pass, we update `runningMax` for each column.
   - We take the maximum of the current `previousRow[col]` (which now contains the best value from the left) and the new `runningMax` (best value from the right).
   - We add `row[col]` to this maximum, incorporating the points from the current cell in the current row.

After processing all rows, the array `previousRow` (which now holds the updated values) will contain the maximum points that can be accumulated for each cell in the last row of the matrix. The maximum value in this array is our final answer, representing the highest possible score from the top to the bottom of the matrix.

**Algorithm**

- Set `cols` as the number of columns in `points`.
- Create an array `previousRow` of size `cols`.
- Iterate through each `row` in the `points` matrix:
  - Initialize a variable `runningMax` to `0`.
  - Iterate `col` from `0` to `cols-1`:
    - Update `runningMax` to the maximum of `runningMax - 1` and `previousRow[col]`.
    - Set `previousRow[col]` equal to `runningMax`.
  - Now, iterate `col` in the reverse order:
    - Update `runningMax` to the maximum of `runningMax - 1` and `previousRow[col]`.
    - Update `previousRow[col]` by taking the maximum of its current value and `runningMax`, then add the current cell's value.
- Loop through all values of `previousRow` and set `maxPoints` to the maximum.
- Return `maxPoints`.

**Implementation**

```cpp
// 159ms, 86.5MB
class Solution {
public:
    long long maxPoints(vector<vector<int>>& points) {
        int cols = points[0].size();
        vector<long long> previousRow(cols);

        for (auto& row : points) {
            // runningMax holds the maximum value generated in the previous
            // iteration of each loop
            long long runningMax = 0;

            // Left to right pass
            for (int col = 0; col < cols; ++col) {
                runningMax = max(runningMax - 1, previousRow[col]);
                previousRow[col] = runningMax;
            }

            runningMax = 0;
            // Right to left pass
            for (int col = cols - 1; col >= 0; --col) {
                runningMax = max(runningMax - 1, previousRow[col]);
                previousRow[col] = max(previousRow[col], runningMax) + row[col];
            }
        }

        // Find maximum points in the last row
        long long maxPoints = 0;
        for (int col = 0; col < cols; ++col) {
            maxPoints = max(maxPoints, previousRow[col]);
        }

        return maxPoints;
    }
};
```

**Complexity Analysis**

Let $m$ and $n$ be the height and width of `points`.

- **Time complexity:** $O(m \times n)$
  - The main loop iterates through each row of `points`. Inside this loop, the algorithm uses two nested loops, each iterating $n$ times. Overall, this takes $O(m \times n)$ time.
  - The final loop to find the maximum points also iterates $n$ times.

- **Space complexity:** $O(n)$
  - The algorithm uses an array `previousRow` of length $n$. Thus, the space complexity of the algorithm is $O(n)$.


## 24.08.18 - 264. Ugly Number II
[문제 링크](https://leetcode.com/problems/ugly-number-ii/description/)

### 나
```cpp
// 96ms, 34.43MB
class Solution {
public:
    using ll = long long;
    int nthUglyNumber(int n) {
        priority_queue<ll, std::vector<ll>, std::greater<ll>> pq;
        unordered_set<ll> us;
        pq.emplace(1LL);
        us.insert(1LL);

        ll cnt{}, answer{};
        while(!pq.empty()) {
            ll now = pq.top(); pq.pop(); ++cnt;
            if(cnt == n) {
                answer = now;
                break;
            }
            if(us.count(now * 2) == 0) {
                pq.push(now * 2);
                us.insert(now * 2);
            }
            if(us.count(now * 3) == 0) {
                pq.push(now * 3);
                us.insert(now * 3);
            }
            if(us.count(now * 5) == 0) {
                pq.push(now * 5);
                us.insert(now * 5);
            }
        }
        return answer;
    }
};
```

### gpt
The problem "Ugly Number II" on LeetCode asks you to find the $n$th "ugly number." An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5. You need to develop an efficient algorithm to generate and return the $n$th ugly number.

Here’s how you can approach it:

1. **Min-Heap Approach**: Use a min-heap to generate numbers by multiplying 2, 3, and 5.
2. **Dynamic Programming Approach**: Use three pointers to track the multiples of 2, 3, and 5, and iteratively generate the next ugly number.

Would you like a specific code implementation in C++?

#### Min Heap
To solve the "Ugly Number II" problem using the min-heap approach, follow these steps:

1. **Initialize a Min-Heap**: Start with the smallest ugly number, which is 1. Insert it into the min-heap.

2. **Use a Set for Duplicates**: Maintain a set to track numbers already in the heap to avoid duplicates.

3. **Generate Ugly Numbers**:
   - Pop the smallest number from the heap.
   - Multiply it by 2, 3, and 5, and push the results back into the heap if they haven't been seen before.
   - Repeat until you reach the $n$th ugly number.

Here’s a C++ implementation of this approach:

```cpp
// 87ms, 34.15MB
class Solution {
public:
    int nthUglyNumber(int n) {
        priority_queue<long, vector<long>, greater<long>> minHeap;
        unordered_set<long> seen;

        minHeap.push(1);
        seen.insert(1);

        long ugly = 1;
        vector<int> factors = {2, 3, 5};

        for (int i = 1; i < n; ++i) {
            ugly = minHeap.top();
            minHeap.pop();

            for (int factor : factors) {
                long nextUgly = ugly * factor;
                if (seen.find(nextUgly) == seen.end()) {
                    minHeap.push(nextUgly);
                    seen.insert(nextUgly);
                }
            }
        }

        return minHeap.top();
    }
};
```

<h3> Explanation: </h3>

- **Min-Heap**: Keeps track of the smallest current ugly number.
- **Set**: Ensures we do not insert duplicates.
- **Factors**: Multiplying by 2, 3, and 5 generates new candidates.

This approach ensures that you efficiently generate the $n$th ugly number in ascending order.

#### DP
To solve the "Ugly Number II" problem using the dynamic programming (DP) approach, you can follow these steps:

1. **Initialize**: Create an array `dp` where `dp[i]` will store the $i$th ugly number. Initialize `dp[0]` as 1.

2. **Three Pointers**: Maintain three pointers, `p2`, `p3`, and `p5`, for the multiples of 2, 3, and 5, respectively. Initialize all pointers to 0.

3. **Generate Ugly Numbers**:
   - Compute the next ugly number by taking the minimum of `dp[p2] * 2`, `dp[p3] * 3`, and `dp[p5] * 5`.
   - Move the pointer(s) that matched the minimum forward.
   - Continue this process until you fill the array `dp` with `n` ugly numbers.

Here’s the C++ code implementing this approach:

```cpp
// 3ms, 9.65MB
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n);
        dp[0] = 1;

        int p2 = 0, p3 = 0, p5 = 0;

        for (int i = 1; i < n; ++i) {
            int next_ugly = min({dp[p2] * 2, dp[p3] * 3, dp[p5] * 5});
            dp[i] = next_ugly;

            if (next_ugly == dp[p2] * 2) p2++;
            if (next_ugly == dp[p3] * 3) p3++;
            if (next_ugly == dp[p5] * 5) p5++;
        }

        return dp[n - 1];
    }
};
```

<h3> Explanation: </h3>

- **dp Array**: Stores the ugly numbers sequentially.
- **Pointers**: `p2`, `p3`, and `p5` track the smallest multiples of 2, 3, and 5, respectively, and ensure the sequence is built in order.
- **Next Ugly Number**: Always computed as the minimum of the next possible multiples.

This approach runs in $O(n)$ time and $O(n)$ space, which is efficient for finding the $n$th ugly number.