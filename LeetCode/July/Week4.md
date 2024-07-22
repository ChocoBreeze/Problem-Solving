## ToC

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