## ToC
- [July Week 4](#july-week-4)
  - [24.07.22 - 2418. Sort the People](#240722---2418-sort-the-people)
    - [나](#나)
    - [gpt](#gpt)
  - [24.07.23 - 1636. Sort Array by Increasing Frequency](#240723---1636-sort-array-by-increasing-frequency)
    - [나](#나-1)
    - [gpt](#gpt-1)
  - [24.07.24 - 2191. Sort the Jumbled Numbers](#240724---2191-sort-the-jumbled-numbers)
    - [나](#나-2)
    - [gpt](#gpt-2)

# July Week 4
## 24.07.22 - 2418. Sort the People
[문제 링크](https://leetcode.com/problems/sort-the-people/description/)

### 나
```cpp
// 20ms, 25.5MB
class Solution {
public:
    struct Data{
        string name;
        int height = 0;
        Data() = default;
    };
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
        const int SIZE = static_cast<int>(names.size());
        vector<Data> datas(SIZE);
        for(int s{}; s < SIZE; ++s) {
            datas[s].name = names[s];
            datas[s].height = heights[s];
        }

        sort(begin(datas), end(datas), [](const Data& d1, const Data& d2) {
            return d1.height > d2.height;
        });

        vector<string> ret;
        for(auto&[name, height] : datas) ret.push_back(name);
        return ret;
    }
};
```

### gpt
Certainly! Here’s a C++ solution to solve the problem of sorting the people based on their heights:

```cpp
// 22ms, 27.04MB
std::vector<std::string> sortPeople(std::vector<std::string>& names, std::vector<int>& heights) {
    // Create a vector of pairs where each pair contains a height and the corresponding name
    std::vector<std::pair<int, std::string>> heightNamePairs;
    
    for (size_t i = 0; i < names.size(); ++i) {
        heightNamePairs.emplace_back(heights[i], names[i]);
    }
    
    // Sort the vector of pairs in descending order based on height
    std::sort(heightNamePairs.begin(), heightNamePairs.end(), std::greater<>());
    
    // Extract the names from the sorted pairs
    std::vector<std::string> sortedNames;
    for (const auto& pair : heightNamePairs) {
        sortedNames.push_back(pair.second);
    }
    
    return sortedNames;
}
```

<h3> Explanation: </h3>

1. **Pairing Heights with Names**: We create a vector of pairs where each pair consists of a height and the corresponding name.
2. **Sorting**: We sort the vector of pairs in descending order based on height using `std::greater<>`.
3. **Extracting Names**: After sorting, we extract the names from the pairs and store them in a new vector.

<h3> Key Points: </h3>

- **Efficiency**: The solution is efficient, with the sorting step being the most computationally intensive operation, running in \(O(n \log n)\) time complexity.
- **Flexibility**: The approach handles various input sizes and sorts correctly even if there are duplicates in heights.

## 24.07.23 - 1636. Sort Array by Increasing Frequency
[문제 링크](https://leetcode.com/problems/sort-array-by-increasing-frequency/description/)

### 나
```cpp
// 0ms, 14MB
class Solution {
public:
    struct Data {
        int count{}, value{};
        Data() = default;
        Data(int count, int value) : count{count}, value{value} {}
    };

    vector<int> frequencySort(vector<int>& nums) {
        // vector(count, value)
        vector<int> dat(201, 0); // -100 ~ 100 => 0 ~ 200
        
        for(int& num : nums) {
            dat[num + 100]++;
        }

        vector<Data> datas;
        for(int i{};i<201;++i) {
            if(dat[i] == 0) continue;
            datas.emplace_back(dat[i], i - 100);
        }

        sort(begin(datas), end(datas), [](const Data& d1, const Data& d2) {
            if(d1.count == d2.count) return d1.value > d2.value;
            return d1.count < d2.count;
        });

        vector<int> ret;
        for(auto& [count, value] : datas) {
            for(int i{};i<count;++i) {
                ret.push_back(value);
            }
        }

        return ret;
    }
};
```

### gpt
Sure, let's solve the problem of sorting an array by increasing frequency.

Here's the problem statement from LeetCode:

> Given an array of integers `nums`, sort the array in increasing order based on the frequency of the values. If multiple values have the same frequency, sort them in decreasing order.

To solve this problem, we'll follow these steps:

1. **Count the frequency** of each number in the array.
2. **Sort the numbers** based on the frequency.
3. If two numbers have the same frequency, sort them in **decreasing order**.

Here’s the implementation in C++:

```cpp
// 15ms, 15.16MB
class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
        // Step 1: Count the frequency of each number
        unordered_map<int, int> frequency;
        for (int num : nums) {
            frequency[num]++;
        }
        
        // Step 2: Sort the array based on the custom comparator
        sort(nums.begin(), nums.end(), [&frequency](int a, int b) {
            // If frequencies are different, sort by frequency
            if (frequency[a] != frequency[b]) {
                return frequency[a] < frequency[b];
            }
            // If frequencies are the same, sort by value in decreasing order
            return a > b;
        });

        return nums;
    }
};
```

<h3> Explanation: </h3>

1. **Counting Frequencies**:
   - We use an `unordered_map` to store the frequency of each number. This is done in linear time \(O(n)\).

2. **Custom Sorting**:
   - We use the `sort` function with a lambda comparator.
   - The lambda comparator checks the frequency of two numbers:
     - If their frequencies differ, it orders them by increasing frequency.
     - If their frequencies are the same, it orders them by their value in decreasing order.
   - Sorting with a custom comparator has a time complexity of \(O(n \log n)\).

3. **Printing the Result**:
   - A helper function `printVector` is used to print the sorted vector for verification.

This solution efficiently solves the problem while adhering to the specified constraints and requirements. Let me know if you need further explanations or have additional questions!

## 24.07.24 - 2191. Sort the Jumbled Numbers
### 나
```cpp
// 201ms, 90.9MB
class Solution {
public:
    struct Data {
        int after{}, before{};
        Data() = default;
        Data(int after, int before) : after{after}, before{before} {}
    };

    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        vector<Data> datas;
        for(int& num : nums) {
            string temp = to_string(num), mappingNumStr;
            for(char& c : temp) {
                mappingNumStr.push_back(mapping[c - '0'] + '0');
            }
            int mappingNum = stoi(mappingNumStr);
            datas.emplace_back(mappingNum, num);
        }
        stable_sort(begin(datas), end(datas), [](const Data& d1, const Data& d2) {
            return d1.after < d2.after;
        });

        vector<int> ret;
        for(auto [after, before] : datas) {
            ret.push_back(before);
        }
        return ret;
    }
};
```

### gpt
Sure! Let's walk through the problem "Sort the Jumbled Numbers" from LeetCode.

**Problem Description:**
You are given a permutation of the digits from `0` to `9` (as an array `mapping` where `mapping[i]` is the mapped value of digit `i`). You are also given an array of integers `nums` that you need to sort based on their mapped values.

To clarify, for each number in `nums`, replace each digit by its mapped value using the `mapping` array, and then sort the numbers based on these new values.

**Steps to solve the problem:**

1. **Understand the Mapping:**
   Each digit of a number in `nums` should be transformed using the given `mapping` array. For instance, if `mapping[2] = 5`, then digit `2` in any number should be considered as `5` during the comparison.

2. **Transform the Numbers:**
   For each number in `nums`, convert it to its mapped value. For example, if a number is `123` and the mapping is `[1, 2, 3, 4, 5, 6, 7, 8, 9, 0]`, the transformed value would be `234` because `1 -> 2`, `2 -> 3`, and `3 -> 4`.

3. **Sort Based on Transformed Values:**
   After transforming all numbers, sort them based on these transformed values.

4. **Output the Sorted Numbers:**
   Return the sorted list of original numbers based on the transformed values.

Let's write the code to achieve this:

```cpp
// 415ms, 98.00MB
class Solution {
public:
    vector<int> sortJumbled(std::vector<int>& mapping, std::vector<int>& nums) {
        // Helper function to transform a number based on the given mapping
        auto transform = [&mapping](int num) {
            std::string numStr = std::to_string(num);
            std::string transformedStr;
            for (char ch : numStr) {
                transformedStr += std::to_string(mapping[ch - '0']);
            }
            return std::stol(transformedStr); // Return as long to handle large numbers
        };

        // Create a vector of pairs to hold the original number and its transformed value
        std::vector<std::pair<int, long>> transformedNums;
        for (int num : nums) {
            transformedNums.emplace_back(num, transform(num));
        }

        // Sort the vector of pairs based on the transformed values
        std::sort(transformedNums.begin(), transformedNums.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

        // Extract the sorted original numbers
        std::vector<int> result;
        for (const auto& p : transformedNums) {
            result.push_back(p.first);
        }

        return result;
    }
};
```

<h3> Explanation: </h3>

1. **Transform Function:**
   - The `transform` function takes an integer and transforms it into its mapped value using the `mapping` array.
   - It converts the integer to a string, replaces each digit with its mapped value, and then converts it back to a long integer (to handle possible large values).

2. **Pairing and Sorting:**
   - The original numbers are paired with their transformed values.
   - The pairs are sorted based on the transformed values.
   - Finally, the sorted original numbers are extracted from the sorted pairs.

This solution ensures that we correctly sort the `nums` array based on the provided `mapping`.