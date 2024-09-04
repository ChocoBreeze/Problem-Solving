## ToC
- [September Week 1](#september-week-1)
  - [24.09.01 - 2022. Convert 1D Array Into 2D Array](#240901---2022-convert-1d-array-into-2d-array)
    - [나](#나)
    - [gpt](#gpt)
  - [24.09.02 - 1894. Find the Student that Will Replace the Chalk](#240902---1894-find-the-student-that-will-replace-the-chalk)
    - [나](#나-1)
    - [해설](#해설)
      - [Approach 1: Prefix Sum](#approach-1-prefix-sum)
      - [Approach 2: Binary Search](#approach-2-binary-search)

# September Week 1
## 24.09.01 - 2022. Convert 1D Array Into 2D Array
[문제 링크](https://leetcode.com/problems/convert-1d-array-into-2d-array/description/?envType=daily-question&envId=2024-09-01)

### 나
```cpp
// 81ms, 89.91MB
class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        int SIZE = original.size();

        vector<vector<int>> answer;
        if(m * n != SIZE) return answer;

        for(int i{};i<m;++i) {
            answer.push_back(vector<int>(n, 0));
            for(int j{};j<n;++j) {
                answer[i][j] = original[n * i + j];
            }
        }

        return answer;
    }
};
```

### gpt
The **"Convert 1D Array Into 2D Array"** problem requires transforming a given 1D array into a 2D array with specified row and column dimensions. If the total number of elements in the 1D array doesn't match `rows * cols`, return an empty array. 

<h3> Approach: </h3>

1. Check if the conversion is possible by verifying the array size.
2. Traverse the 1D array and map each element to the corresponding position in the 2D array.

Here's the C++ code to solve it:

```cpp
// 78ms, 88.03MB
class Solution {
public:
    vector<vector<int>> construct2DArray(vector<int>& original, int m, int n) {
        if (original.size() != m * n)
            return {};
        
        vector<vector<int>> result(m, vector<int>(n));
        for (int i = 0; i < original.size(); ++i) {
            result[i / n][i % n] = original[i];
        }
        return result;
    }
};
```

<h3> Explanation: </h3>

1. **Check Validity:** If the size of the 1D array isn't `m * n`, return an empty array.
2. **Filling the 2D Array:** Use integer division and modulus to map each element from the 1D array into the appropriate 2D position.

<h3> Time Complexity: </h3>

- $O(m \times n)$ for filling the 2D array.

## 24.09.02 - 1894. Find the Student that Will Replace the Chalk
[문제 링크](https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/description/?envType=daily-question&envId=2024-09-02)

### 나
```cpp
// 79ms, 77.10MB
class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        int answer{};
        int sum{}; // k <= 10^9 : no need to long long
        for(int s{}, e{static_cast<int>(chalk.size())}; s<e; ++s) {
            sum += chalk[s];
            if(sum > k) {
                answer = s; // 조기 종료
                break;
            }
        }
        if(answer) return answer;

        k %= sum;
        sum = 0;
        for(int s{}, e{static_cast<int>(chalk.size())}; s<e; ++s) {
            sum += chalk[s];
            if(sum > k) {
                answer = s; // 조기 종료
                break;
            }
        }

        return answer;
    }
};
```

### 해설

#### Approach 1: Prefix Sum
[링크](https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/editorial/?envType=daily-question&envId=2024-09-02#approach-1-prefix-sum)

#### Approach 2: Binary Search
[링크](https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/editorial/?envType=daily-question&envId=2024-09-02#approach-2-binary-search)

