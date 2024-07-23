## ToC
- [July Week 4](#july-week-4)
  - [24.07.22 - 2418. Sort the People](#240722---2418-sort-the-people)
    - [나](#나)
    - [gpt](#gpt)
  - [24.07.23 - 1636. Sort Array by Increasing Frequency](#240723---1636-sort-array-by-increasing-frequency)
    - [나](#나-1)
    - [gpt](#gpt-1)

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