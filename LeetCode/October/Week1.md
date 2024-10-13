## ToC

# October Week 1
## 24.10.01 - 1497. Check If Array Pairs Are Divisible by k
[문제 링크](https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/description/?envType=daily-question&envId=2024-10-01)

### 나
아이디어가 없다

### Solution
#### Approach 1: Hashing / Counting
```cpp
class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        unordered_map<int, int> remainderCount;

        // Store the count of remainders in a map.
        for (auto i : arr) remainderCount[(i % k + k) % k]++;

        for (auto i : arr) {
            int rem = (i % k + k) % k;

            // If the remainder for an element is 0, then the count
            // of numbers that give this remainder must be even.
            if (rem == 0) {
                if (remainderCount[rem] % 2 == 1) return false;
            }

            // If the remainder rem and k-rem do not have the
            // same count then pairs cannot be made.
            else if (remainderCount[rem] != remainderCount[k - rem])
                return false;
        }
        return true;
    }
};
```
#### Approach 2: Sorting and Two-Pointers
```cpp
class Solution {
public:
    // Custom comparator to sort based on mod values.
    struct Comparator {
        int k;
        Comparator(int k) { this->k = k; }
        bool operator()(int i, int j) {
            return (k + i % k) % k < (k + j % k) % k;
        }
    };

    bool canArrange(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end(), Comparator(k));

        // Assign the pairs with modulo 0 first.
        int start = 0, end = arr.size() - 1;
        while (start < end) {
            if (arr[start] % k != 0) break;
            if (arr[start + 1] % k != 0) return false;
            start = start + 2;
        }

        // Now, pick one element from the beginning and one element from the
        // end.
        while (start < end) {
            if ((arr[start] + arr[end]) % k != 0) return false;
            start++;
            end--;
        }
        return true;
    }
};
```

## 24.10.02 - 1331. Rank Transform of an Array
[문제 링크](https://leetcode.com/problems/rank-transform-of-an-array/description/?envType=daily-question&envId=2024-10-02)

### 나
```cpp
// 93ms, 51.36MB
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        set<int> s;
        for(int a : arr) {
            s.insert(a);
        }

        unordered_map<int, int> um;
        int index = 1;
        for(int e : s) {
            um.emplace(e, index++);
        }

        vector<int> answer;
        for(int a : arr) {
            answer.push_back(um[a]);
        }

        return answer;
    }
};
```

