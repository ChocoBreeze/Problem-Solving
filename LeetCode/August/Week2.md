## ToC
- [August Week 2](#august-week-2)
  - [24.08.05 - 2053. Kth Distinct String in an Array](#240805---2053-kth-distinct-string-in-an-array)
    - [나](#나)
    - [gpt](#gpt)

# August Week 2
## 24.08.05 - 2053. Kth Distinct String in an Array
[문제 링크](https://leetcode.com/problems/kth-distinct-string-in-an-array/)

### 나
```cpp
// 16ms, 18.34MB
class Solution {
public:
    string kthDistinct(vector<string>& arr, int k) {
        std::unordered_map<std::string, int> um;
        for(string& s : arr) {
            if(um.find(s)!=um.end()) {
                um[s]++;
            }
            else {
                um.emplace(s, 1);
            }
        }

        int i{};
        for(string& s : arr) {
            if(um[s] == 1) {
                ++i;
                if(i == k) {
                    return s;
                }
            }
        }
        return "";
    }
};
```

### gpt
Sure, let's solve the problem "Kth Distinct String in an Array" on LeetCode. Here's a detailed explanation and solution in C++.

<h3> Problem Description </h3>

You are given a string array `arr` and an integer `k`. A string is called **distinct** if it appears exactly once in the array. Return the `k`th distinct string in the array. If there are fewer than `k` distinct strings, return an empty string `""`.

<h3> Steps to Solve the Problem </h3>

1. **Count Occurrences:** Use a hash map to count the occurrences of each string in the array.
2. **Identify Distinct Strings:** Traverse the array again to collect strings that occur exactly once.
3. **Find the k-th Distinct String:** Check if we have at least `k` distinct strings and return the `k`th one, otherwise return an empty string.

<h3> Solution in C++ </h3>
Here's the solution implemented in C++:

```cpp
// 13ms, 20.38MB
class Solution {
public:
    string kthDistinct(vector<string>& arr, int k) {
        // Step 1: Count occurrences of each string
        std::unordered_map<std::string, int> countMap;
        for (const auto& str : arr) {
            countMap[str]++;
        }

        // Step 2: Collect distinct strings (those that appear exactly once)
        std::vector<std::string> distinctStrings;
        for (const auto& str : arr) {
            if (countMap[str] == 1) {
                distinctStrings.push_back(str);
            }
        }

        // Step 3: Return the k-th distinct string if it exists
        if (k <= distinctStrings.size()) {
            return distinctStrings[k - 1];
        } else {
            return "";
        }
    }
};
```

<h3> Explanation </h3>

1. **Counting Occurrences:**
   - We use an `unordered_map` (hash map) to count the occurrences of each string in the array.
   - `countMap[str]++` increments the count for each string.

2. **Identifying Distinct Strings:**
   - We traverse the array again to collect strings that have a count of 1 (i.e., they appear exactly once).
   - These distinct strings are stored in a vector `distinctStrings`.

3. **Returning the k-th Distinct String:**
   - We check if `k` is within the bounds of the `distinctStrings` vector.
   - If yes, we return the `k`th string (note that the index is `k-1` because vectors are 0-indexed).
   - If no, we return an empty string `""`.

<h3> Conclusion </h3>

This solution efficiently finds the k-th distinct string in the array by using a hash map to count occurrences and then collecting the distinct strings. The time complexity is $O(n)$ where n is the number of strings in the array, making it suitable for large inputs.

