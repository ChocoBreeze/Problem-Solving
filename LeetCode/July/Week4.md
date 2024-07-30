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
  - [24.07.25 - 912. Sort an Array](#240725---912-sort-an-array)
    - [merge sort](#merge-sort)
    - [heap sort](#heap-sort)
    - [intro sort](#intro-sort)
    - [quick sort](#quick-sort)
  - [24.07.26 - 1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance](#240726---1334-find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance)
    - [나](#나-3)
    - [gpt](#gpt-3)
      - [Floyd-Warshall](#floyd-warshall)
      - [Dijkstra](#dijkstra)
      - [Why Floyd-Warshall is fast??](#why-floyd-warshall-is-fast)
  - [24.07.27 - 2976. Minimum Cost to Convert String I](#240727---2976-minimum-cost-to-convert-string-i)
    - [나](#나-4)
    - [gpt](#gpt-4)
      - [TLE 개선](#tle-개선)
      - [기본 testcase 맞추기.](#기본-testcase-맞추기)
      - [TLE 개선](#tle-개선-1)
      - [overflow 개선](#overflow-개선)

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

## 24.07.25 - 912. Sort an Array
정렬을 구현하는 문제입니다.
- 시간복잡도 $O(nlog(n))$이 필요합니다.

구현하는 대신에 gpt한테 4가지 구현을 물어봤습니다.

### merge sort
Certainly! The problem you referenced is "Sort an Array" on LeetCode. The task is to implement a sorting algorithm to sort an array of integers in ascending order.

Here is a solution using C++ with the Merge Sort algorithm. Merge Sort is a classic sorting algorithm with a time complexity of $O(n \log n)$, which is efficient for large arrays.

Here's how you can implement it in C++:

```cpp
// 372ms, 178.10MB
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        mergeSort(nums, 0, nums.size() - 1);
        return nums;
    }

    void mergeSort(std::vector<int>& nums, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(nums, left, mid);
            mergeSort(nums, mid + 1, right);
            merge(nums, left, mid, right);
        }
    }

    void merge(std::vector<int>& nums, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> leftArr(n1);
        std::vector<int> rightArr(n2);

        for (int i = 0; i < n1; ++i)
            leftArr[i] = nums[left + i];
        for (int i = 0; i < n2; ++i)
            rightArr[i] = nums[mid + 1 + i];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (leftArr[i] <= rightArr[j]) {
                nums[k] = leftArr[i];
                ++i;
            } else {
                nums[k] = rightArr[j];
                ++j;
            }
            ++k;
        }

        while (i < n1) {
            nums[k] = leftArr[i];
            ++i;
            ++k;
        }

        while (j < n2) {
            nums[k] = rightArr[j];
            ++j;
            ++k;
        }
    }
};
```

<h3> Explanation </h3>

1. **mergeSort Function:**
   - This function recursively divides the array into two halves until each subarray contains only one element.
   - It then merges the subarrays in a sorted manner.

2. **merge Function:**
   - This function merges two sorted subarrays into a single sorted subarray.
   - It uses two temporary arrays to store the elements of the left and right subarrays.
   - It then merges them back into the original array in sorted order.

<h3> How to Use </h3>

- The `sortArray` method of the `Solution` class is the entry point. It takes a vector of integers `nums` and returns the sorted vector.
- In the `main` function, an instance of `Solution` is created, and the `sortArray` method is called with a sample vector.
- The sorted result is then printed to the console.

You can modify the input array `nums` in the `main` function to test with different sets of integers. This implementation is efficient and follows the divide-and-conquer approach, making it suitable for sorting large arrays.

### heap sort
Sure! Heap Sort is another efficient sorting algorithm with a time complexity of $O(n \log n)$. It uses a binary heap data structure, typically implemented as an array, to sort elements. Here's how you can implement Heap Sort in C++ to solve the "Sort an Array" problem:

```cpp
// 115ms, 69.28MB
// heap sort
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        heapSort(nums);
        return nums;
    }

    void heapSort(std::vector<int>& nums) {
        int n = static_cast<int>(nums.size());

        // Build heap (rearrange array)
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(nums, n, i);
        }

        // One by one extract elements from heap
        for (int i = n - 1; i > 0; --i) {
            // Move current root to end
            std::swap(nums[0], nums[i]);

            // Call max heapify on the reduced heap
            heapify(nums, i, 0);
        }
    }

    void heapify(std::vector<int>& nums, int n, int i) {
        int largest = i; // Initialize largest as root
        int left = 2 * i + 1; // left = 2*i + 1
        int right = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (left < n && nums[left] > nums[largest])
            largest = left;

        // If right child is larger than largest so far
        if (right < n && nums[right] > nums[largest])
            largest = right;

        // If largest is not root
        if (largest != i) {
            std::swap(nums[i], nums[largest]);

            // Recursively heapify the affected sub-tree
            heapify(nums, n, largest);
        }
    }
};
```

<h3> Explanation </h3>

1. **heapSort Function:**
   - This function first builds a max heap from the input array.
   - Then, it extracts elements one by one from the heap and places them at the end of the array, effectively sorting the array.

2. **heapify Function:**
   - This function ensures that the subtree rooted at index `i` is a max heap.
   - It compares the root with its left and right children and swaps with the largest value to maintain the heap property.
   - It is called recursively to heapify the affected sub-tree if any swapping occurs.

<h3> How to Use </h3>

- The `sortArray` method of the `Solution` class is the entry point. It takes a vector of integers `nums` and returns the sorted vector.
- In the `main` function, an instance of `Solution` is created, and the `sortArray` method is called with a sample vector.
- The sorted result is then printed to the console.

You can test this implementation with different sets of integers by modifying the input array `nums` in the `main` function. This implementation efficiently sorts the array using the heap data structure.

### intro sort
Certainly! Introspective Sort (Introsort) is a hybrid sorting algorithm that combines Quicksort, Heapsort, and Insertion Sort. It begins with Quicksort and switches to Heapsort when the recursion depth exceeds a level based on the logarithm of the number of elements being sorted to avoid Quicksort's worst-case performance. When the array size is small, it switches to Insertion Sort for efficiency.

Here's how you can implement Introsort in C++ to solve the "Sort an Array" problem:

코드가 정답이 안 나와서 반례로 계속 수정..

Thank you for your patience. Let's re-evaluate the implementation, ensuring we handle all cases correctly, particularly around the partitioning logic and the recursive calls.

Here’s the revised implementation of Introsort with correct partition logic:

```cpp
// 93ms, 70.55MB
// intro sort
class Solution {
public:
    std::vector<int> sortArray(std::vector<int>& nums) {
        if (nums.empty()) return nums;
        int depthLimit = 2 * std::log(nums.size());
        introSort(nums, 0, nums.size() - 1, depthLimit);
        return nums;
    }

    void introSort(std::vector<int>& nums, int begin, int end, int depthLimit) {
        if (begin >= end) {
            return;
        }

        if (depthLimit == 0) {
            heapSort(nums, begin, end);
            return;
        }

        if (end - begin < 16) {
            insertionSort(nums, begin, end);
            return;
        }

        int pivot = partition(nums, begin, end);
        introSort(nums, begin, pivot - 1, depthLimit - 1);
        introSort(nums, pivot, end, depthLimit - 1);
    }

    int partition(std::vector<int>& nums, int low, int high) {
        int pivot = nums[low + (high - low) / 2];
        int left = low;
        int right = high;

        while (left <= right) {
            while (nums[left] < pivot) {
                ++left;
            }
            while (nums[right] > pivot) {
                --right;
            }

            if (left <= right) {
                std::swap(nums[left], nums[right]);
                ++left;
                --right;
            }
        }

        return left;
    }

    void heapSort(std::vector<int>& nums, int begin, int end) {
        std::make_heap(nums.begin() + begin, nums.begin() + end + 1);
        std::sort_heap(nums.begin() + begin, nums.begin() + end + 1);
    }

    void insertionSort(std::vector<int>& nums, int begin, int end) {
        for (int i = begin + 1; i <= end; ++i) {
            int key = nums[i];
            int j = i - 1;
            while (j >= begin && nums[j] > key) {
                nums[j + 1] = nums[j];
                --j;
            }
            nums[j + 1] = key;
        }
    }
};
```

<h3> Key Fixes: </h3>

1. **Recursive Call Adjustment:**
   - Change the second recursive call from `introSort(nums, pivot + 1, end, depthLimit - 1);` to `introSort(nums, pivot, end, depthLimit - 1);` to ensure the pivot index is correctly handled.

2. **Partition Function:**
   - Return the `left` index at the end of the `partition` function, ensuring that the pivot is correctly placed.

3. **Edge Case Handling:**
   - Additional checks and balances to ensure recursive depth limits and size checks are properly handled.

<h3> How to Use: </h3>

- The `sortArray` method of the `Solution` class is the entry point. It takes a vector of integers `nums` and returns the sorted vector.
- In the `main` function, an instance of `Solution` is created, and the `sortArray` method is called with the provided vector.
- The sorted result is printed to the console.

This revised implementation should correctly sort the array, including handling the given counterexamples.

### quick sort
- random pivot

Sure, using a random pivot can help avoid the worst-case scenario of Quick Sort, which can occur if the pivot selection is poor, especially on already sorted or nearly sorted data. Here's how you can modify the Quick Sort implementation to use a random pivot:

```cpp
// 1533ms, 69.38MB
// quick sort
class Solution {
public:

    std::vector<int> sortArray(std::vector<int>& nums) {
        std::srand(std::time(0));  // Seed for random number generation
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }

    void quickSort(std::vector<int>& nums, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(nums, low, high);
            quickSort(nums, low, pivotIndex - 1);
            quickSort(nums, pivotIndex + 1, high);
        }
    }

    int partition(std::vector<int>& nums, int low, int high) {
        int randomIndex = low + std::rand() % (high - low + 1);
        std::swap(nums[randomIndex], nums[high]);  // Move pivot to end
        int pivot = nums[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (nums[j] < pivot) {
                ++i;
                std::swap(nums[i], nums[j]);
            }
        }

        std::swap(nums[i + 1], nums[high]);
        return i + 1;
    }
};
```

<h3> Explanation </h3>

1. **Random Pivot Selection:**
   - A random index is selected as the pivot.
   - The pivot element is then swapped with the last element in the current subarray to simplify the partitioning logic.

2. **Partition Function:**
   - The partition logic remains the same, but now the pivot is selected randomly to help avoid worst-case performance.

3. **Random Seed:**
   - The `Solution` constructor seeds the random number generator using the current time to ensure different runs use different random seeds.

4. **sortArray Method and main Function:**
   - The entry point and main function remain the same.

By using a random pivot, the implementation is more robust against cases where the input array might lead to poor performance with a fixed pivot selection strategy. This should help avoid the time limit exceeded error.

## 24.07.26 - 1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance
[문제 링크](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/?envType=daily-question&envId=2024-07-26)

### 나
```cpp
// 21ms, 15.48MB
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Return the city with the smallest number of cities that are reachable through some path at most distanceThreshold
        // multiple city => return the city with the greatest number.
        const int INF = 1 << 29;
        vector adjGraph(n, vector(n, INF));
        for(auto & edge : edges) { // bidirectional
            auto [from, to, weight] = make_tuple(edge[0], edge[1], edge[2]);
            // all pairs (from, to) are distinct.
            adjGraph[from][to] = weight;
            adjGraph[to][from] = weight;
        }

        // floyd-warshall
        for(int k{};k<n;++k) {
            for(int i{};i<n;++i) {
                for(int j{};j<n;++j) {
                    if(adjGraph[i][j] > adjGraph[i][k] + adjGraph[k][j]) {
                        adjGraph[i][j] = adjGraph[i][k] + adjGraph[k][j];
                    }
                }
            }
        }

        int answer{}, minCnt = INF;
        for(int i{};i<n;++i) {
            int cnt{};
            for(int j{};j<n;++j) {
                if(i!=j && adjGraph[i][j] <= distanceThreshold) ++cnt;
            }
            if(cnt <= minCnt) {
                if(cnt < minCnt) minCnt = cnt;
                answer = i;
            }
        }
        return answer;
    }
};
```

### gpt
#### Floyd-Warshall
You're welcome! Let's solve the problem "Find the City With the Smallest Number of Neighbors at a Threshold Distance" from LeetCode.

Here is the problem statement for clarity:

> There are n cities numbered from 0 to n-1. You are given an array edges where edges[i] = [from_i, to_i, weight_i] represents a bidirectional and weighted edge between cities from_i and to_i, and a threshold distance distanceThreshold.
>
> Return the city with the smallest number of neighbors at a threshold distance distanceThreshold, if there are multiple such cities, return the city with the greatest number.

Let's break down the problem and solve it step-by-step:

1. **Represent the Graph**: Use an adjacency matrix to store the weights of the edges.
2. **Floyd-Warshall Algorithm**: Use this algorithm to find the shortest paths between all pairs of cities.
3. **Count Neighbors within Threshold**: For each city, count how many other cities are within the threshold distance.
4. **Find the Desired City**: Identify the city with the smallest number of neighbors within the threshold distance, breaking ties by selecting the city with the greatest number.

Here is the C++ code to solve the problem:

```cpp
// 30ms, 15.52MB
class Solution {
public:
    int findTheCity(int n, std::vector<std::vector<int>>& edges, int distanceThreshold) {
        // Initialize the distance matrix with INT_MAX
        std::vector<std::vector<int>> dist(n, std::vector<int>(n, INT_MAX));

        // Distance to self is zero
        for (int i = 0; i < n; ++i)
            dist[i][i] = 0;

        // Populate the distance matrix with the given edges
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            dist[u][v] = weight;
            dist[v][u] = weight;
        }

        // Floyd-Warshall Algorithm to find the shortest paths between all pairs of nodes
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                        continue;
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        int minNeighborCount = INT_MAX;
        int cityWithMinNeighbors = -1;

        // Find the city with the minimum number of neighbors within the distance threshold
        for (int i = 0; i < n; ++i) {
            int neighborCount = 0;
            for (int j = 0; j < n; ++j) {
                if (i != j && dist[i][j] <= distanceThreshold) {
                    ++neighborCount;
                }
            }

            if (neighborCount < minNeighborCount) {
                minNeighborCount = neighborCount;
                cityWithMinNeighbors = i;
            } else if (neighborCount == minNeighborCount) {
                cityWithMinNeighbors = std::max(cityWithMinNeighbors, i);
            }
        }

        return cityWithMinNeighbors;
    }
};
```

<h3> Explanation: </h3>

1. **Graph Initialization**: An adjacency matrix `dist` is initialized to store the distances between cities. Initially, all distances are set to `INT_MAX`, except the diagonal which is set to 0 since the distance from a city to itself is zero.
2. **Input Edges**: The given edges are used to populate the adjacency matrix with the corresponding weights.
3. **Floyd-Warshall Algorithm**: This algorithm computes the shortest paths between all pairs of cities. The core idea is to iteratively update the shortest paths by considering each city as an intermediate point.
4. **Counting Neighbors**: For each city, count how many other cities are reachable within the `distanceThreshold`.
5. **Determine Result**: Track the city with the smallest number of reachable neighbors, using the city with the greatest number in case of ties.

This approach ensures that we efficiently find the city with the required properties using a time complexity of $O(n^3)$, which is feasible for the given problem constraints.

#### Dijkstra
You are right; using the Floyd-Warshall algorithm is not the most efficient approach for this problem because it has a time complexity of $O(n^3)$, which can be slow for large inputs. Instead, a more efficient approach is to use Dijkstra's algorithm to find the shortest paths from each city to all other cities. This approach will have a better performance of $O(n \cdot (m + n \log n))$, where $m$ is the number of edges.

Let's update the solution to use Dijkstra's algorithm for each city:

<h3> Updated Approach </h3>

1. **Initialize a graph representation** using an adjacency list.
2. **Run Dijkstra's algorithm** from each city to find the shortest paths to all other cities.
3. **Count the neighbors** for each city within the threshold distance.
4. **Determine the city** with the smallest number of neighbors, breaking ties by choosing the city with the greatest index.

Here's the updated C++ code:

```cpp
// 30ms, 20.32MB
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Step 1: Initialize graph representation using an adjacency list
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }
        
        // Function to perform Dijkstra's algorithm
        auto dijkstra = [&](int src) {
            vector<int> dist(n, INT_MAX);
            dist[src] = 0;
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
            pq.emplace(0, src);
            
            while (!pq.empty()) {
                auto [currentDist, u] = pq.top();
                pq.pop();
                
                if (currentDist > dist[u]) continue;
                
                for (const auto& [v, weight] : graph[u]) {
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        pq.emplace(dist[v], v);
                    }
                }
            }
            return dist;
        };
        
        // Step 3: Count the neighbors for each city within the threshold distance
        int minNeighbors = INT_MAX;
        int resultCity = -1;
        
        for (int i = 0; i < n; ++i) {
            vector<int> distances = dijkstra(i);
            int count = 0;
            for (int j = 0; j < n; ++j) {
                if (i != j && distances[j] <= distanceThreshold) {
                    count++;
                }
            }
            
            // Step 4: Determine the city with the smallest number of neighbors
            if (count < minNeighbors || (count == minNeighbors && i > resultCity)) {
                minNeighbors = count;
                resultCity = i;
            }
        }
        
        return resultCity;
    }
};

int main() {
    Solution solution;
    int n = 4;
    vector<vector<int>> edges = {{0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}};
    int distanceThreshold = 4;
    int result = solution.findTheCity(n, edges, distanceThreshold);
    cout << "The city with the smallest number of neighbors at a threshold distance is: " << result << endl;
    return 0;
}
```

<h3> Explanation </h3>

1. **Graph Representation:** We use an adjacency list to represent the graph.
2. **Dijkstra's Algorithm:** We implement Dijkstra's algorithm to find the shortest paths from a source city to all other cities.
3. **Counting Neighbors:** For each city, we count how many other cities are within the threshold distance using the results from Dijkstra's algorithm.
4. **Finding the Result:** We keep track of the city with the smallest number of neighbors, choosing the city with the greatest index in case of a tie.

This approach is more efficient and better suited for large inputs compared to the Floyd-Warshall algorithm.

#### Why Floyd-Warshall is fast??
> But Actually Floyd-warshall has higher time complexity than dijkstra. but floyd-warshall is fast.. 
Can you explain it??

You are correct that Floyd-Warshall has a higher theoretical time complexity $O(n^3)$ compared to Dijkstra's algorithm $O(n \cdot (m + n \log n))$, where $n$ is the number of vertices and $m$ is the number of edges. However, in practice, the actual performance can vary depending on the problem size, graph density, and implementation details.

<h3> Why Floyd-Warshall Can Be Faster in Practice </h3>

1. **Constant Factors and Implementation Overhead:**
   - **Simplicity of Floyd-Warshall:** The Floyd-Warshall algorithm is simpler to implement with fewer lines of code and fewer data structures (just a 2D array for distances). This can lead to lower constant factors in the runtime.
   - **Dijkstra's Overhead:** Dijkstra's algorithm requires a priority queue (usually implemented as a binary heap), which involves more complex operations and additional overhead.

2. **Graph Density:**
   - **Sparse vs. Dense Graphs:** For very dense graphs (where $m$ is close to $n^2$, the complexity of Dijkstra's algorithm can approach $O(n^3)$). In such cases, Floyd-Warshall's performance may be comparable or even better.
   - **Edge Cases:** For certain edge cases or specific types of graphs, Floyd-Warshall may outperform Dijkstra's due to lower overhead and better cache performance.

3. **Cache Efficiency:**
   - **Memory Access Patterns:** Floyd-Warshall's nested loops over a contiguous 2D array can be more cache-friendly compared to the more irregular memory access patterns in Dijkstra's algorithm, especially with a priority queue.

4. **Uniform Workload Distribution:**
   - **Uniform vs. Varying Costs:** Floyd-Warshall performs a uniform amount of work for each pair of nodes, while the work done by Dijkstra's algorithm can vary significantly depending on the graph's structure and the distribution of edge weights.

<h3> When to Use Which Algorithm </h3>

- **Floyd-Warshall:**
  - **Best for Small to Medium-sized Graphs:** Typically used when the number of vertices ($n$) is small to medium.
  - **Dense Graphs:** Suitable for dense graphs where most pairs of vertices are connected by edges.
  - **All-Pairs Shortest Paths:** Useful when all-pairs shortest paths are required, as it computes them directly.

- **Dijkstra:**
  - **Best for Large Sparse Graphs:** Preferred for large graphs where the number of edges ($m$) is much less than ($n^2$).
  - **Single-Source Shortest Path:** Ideal for scenarios where only the shortest paths from a single source to all other vertices are needed.

<h3> Updated Approach Using Floyd-Warshall </h3>

To address your concern and demonstrate the simplicity and efficiency of Floyd-Warshall in practice, let's use the same problem but solve it using Floyd-Warshall with a slightly optimized implementation:

```cpp
// 26ms, 15.57MB
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Step 1: Initialize distance matrix
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
        }
        
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            dist[u][v] = w;
            dist[v][u] = w;
        }
        
        // Step 2: Apply Floyd-Warshall algorithm
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        
        // Step 3: Find the city with the smallest number of neighbors within the threshold
        int minNeighbors = INT_MAX;
        int resultCity = -1;
        
        for (int i = 0; i < n; ++i) {
            int count = 0;
            for (int j = 0; j < n; ++j) {
                if (i != j && dist[i][j] <= distanceThreshold) {
                    count++;
                }
            }
            
            if (count < minNeighbors || (count == minNeighbors && i > resultCity)) {
                minNeighbors = count;
                resultCity = i;
            }
        }
        
        return resultCity;
    }
};
```

<h3> Summary </h3>

While Floyd-Warshall has a higher theoretical time complexity, its simplicity and consistent memory access patterns can make it more practical for certain graph sizes and densities. Dijkstra's algorithm is more suitable for larger and sparser graphs, particularly when we need single-source shortest paths.

## 24.07.27 - 2976. Minimum Cost to Convert String I
### 나
```cpp
// 171ms, 99MB
class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        const long long INF = 1 << 29;
        const int SIZE = 26;
        vector board(SIZE, vector(SIZE, INF));
        for(int s{};s<SIZE;++s){
            board[s][s] = 0; // same alphabet
        }

        for(int s{}, e = static_cast<int>(original.size()); s<e; ++s) {
            // lowercase English letters.
            int src = original[s] - 'a';
            // 더 최적화 하려면 -> int src = (original[s] & 0x1F) - 1
            int dst = changed[s] - 'a';
            board[src][dst] = min(board[src][dst], static_cast<long long>(cost[s])); // Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].
        }

        // floyd-warshall
        for(int k{};k<SIZE;++k) {
            for(int i{};i<SIZE;++i) {
                for(int j{};j<SIZE;++j) {
                    board[i][j] = min(board[i][j], board[i][k] + board[k][j]);
                }
            }
        }

        long long answer{};
        for(int s{}, e = static_cast<int>(source.length()); s<e; ++s) {
            int src = source[s] - 'a';
            int dst = target[s] - 'a';
            if(board[src][dst] == INF) return -1; // impossible to convert source to target
            answer += board[src][dst];
        }
        return answer;
    }
};
```

### gpt
Thanks for the clarification. Here’s a detailed approach to solve the problem:

<h3> Steps to Solve the Problem </h3>

1. **Create a Graph Representation**:
    - Use a graph to represent the transformations where each character is a node.
    - An edge from node `original[i]` to node `changed[i]` with weight `cost[i]` represents the allowed transformations.

2. **Find Minimum Transformation Costs**:
    - Use the Floyd-Warshall algorithm to compute the shortest path between all pairs of characters. This will help in finding the minimum cost to transform one character to another.

3. **Calculate the Total Transformation Cost**:
    - For each character in the `source` string, find the minimum cost to transform it to the corresponding character in the `target` string using the precomputed shortest paths.
    - If at any point a transformation is not possible (i.e., the cost is infinite), return -1.

<h3> Implementation in C++ </h3>

Here's how you can implement it:

```cpp
int minCostToConvertString(const std::string &source, const std::string &target, 
                           const std::vector<char> &original, const std::vector<char> &changed, const std::vector<int> &cost) {
    int n = source.size();
    std::unordered_map<char, std::unordered_map<char, int>> graph;
    
    // Initialize the graph with INF distances
    for (char c = 'a'; c <= 'z'; ++c) {
        for (char d = 'a'; d <= 'z'; ++d) {
            graph[c][d] = (c == d) ? 0 : INF;
        }
    }
    
    // Fill the graph with the given costs
    for (size_t i = 0; i < original.size(); ++i) {
        graph[original[i]][changed[i]] = std::min(graph[original[i]][changed[i]], cost[i]);
    }
    
    // Floyd-Warshall Algorithm to find all pairs shortest path
    for (char k = 'a'; k <= 'z'; ++k) {
        for (char i = 'a'; k <= 'z'; ++i) {
            for (char j = 'a'; j <= 'z'; ++j) {
                if (graph[i][k] < INF && graph[k][j] < INF) {
                    graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
    }
    
    // Calculate the minimum cost to convert source to target
    int totalCost = 0;
    for (int i = 0; i < n; ++i) {
        char s = source[i];
        char t = target[i];
        if (graph[s][t] == INF) {
            return -1; // Impossible to convert
        }
        totalCost += graph[s][t];
    }
    
    return totalCost;
}
```

<h3> Explanation </h3>

1. **Graph Initialization**: Initialize a graph with distances between all pairs of characters set to infinity (`INF`), except for the distances from a character to itself, which are set to 0.
2. **Graph Population**: Populate the graph with the given transformation costs.
3. **Floyd-Warshall Algorithm**: Compute the shortest paths between all pairs of characters using the Floyd-Warshall algorithm.
4. **Cost Calculation**: Compute the total transformation cost using the shortest paths found. If any transformation is impossible, return -1.

This solution ensures that we find the minimum cost to transform the `source` string to the `target` string, considering all possible character transformations.

> TLE..!! (기본 testcase)

#### TLE 개선
To optimize the code and avoid Time Limit Exceeded (TLE), we can use Dijkstra's algorithm for each character in `source` to compute the shortest path to the corresponding character in `target`. This approach is more efficient than Floyd-Warshall for this problem's constraints.

Here is the optimized implementation in C++:

```cpp
const int INF = std::numeric_limits<int>::max();

struct Edge {
    char to;
    int cost;
};

int dijkstra(char src, char dest, const std::unordered_map<char, std::vector<Edge>>& graph) {
    std::unordered_map<char, int> dist;
    for (char c = 'a'; c <= 'z'; ++c) {
        dist[c] = INF;
    }
    dist[src] = 0;

    std::priority_queue<std::pair<int, char>, std::vector<std::pair<int, char>>, std::greater<>> pq;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto [current_cost, u] = pq.top();
        pq.pop();

        if (current_cost > dist[u]) continue;

        for (const auto& edge : graph.at(u)) {
            char v = edge.to;
            int weight = edge.cost;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }

    return dist[dest];
}

int minCostToConvertString(const std::string &source, const std::string &target, 
                           const std::vector<char> &original, const std::vector<char> &changed, const std::vector<int> &cost) {
    int n = source.size();
    std::unordered_map<char, std::vector<Edge>> graph;

    // Build the graph
    for (size_t i = 0; i < original.size(); ++i) {
        graph[original[i]].push_back({changed[i], cost[i]});
    }

    int totalCost = 0;

    // Calculate the cost to convert each character in source to the corresponding character in target
    for (int i = 0; i < n; ++i) {
        char s = source[i];
        char t = target[i];
        if (s == t) continue;

        int cost = dijkstra(s, t, graph);
        if (cost == INF) {
            return -1; // Impossible to convert
        }
        totalCost += cost;
    }

    return totalCost;
}

int main() {
    std::string source = "abcd";
    std::string target = "acbe";
    std::vector<char> original = {'a', 'b', 'c', 'c', 'e', 'd'};
    std::vector<char> changed = {'b', 'c', 'b', 'e', 'b', 'e'};
    std::vector<int> cost = {2, 5, 5, 1, 2, 20};

    int result = minCostToConvertString(source, target, original, changed, cost);
    std::cout << "Minimum cost: " << result << std::endl;

    return 0;
}
```

<h3> Explanation: </h3>

1. **Graph Construction**: Build a graph where each character points to its possible transformations with associated costs.
2. **Dijkstra's Algorithm**: For each character in `source`, use Dijkstra's algorithm to find the shortest path to the corresponding character in `target`.
3. **Cost Calculation**: Sum the costs of transforming each character. If any transformation is not possible, return -1.

This approach is more efficient and should help avoid TLE issues.

> wrong answer.

#### 기본 testcase 맞추기.
To handle this problem correctly, you need to consider multiple-step transformations, as shown in your counterexample. Using a breadth-first search (BFS) approach with a priority queue (min-heap) for Dijkstra's algorithm should work efficiently. Here's the corrected implementation:

```cpp
class Solution {
public:
    const int INF = std::numeric_limits<int>::max();

    struct Edge {
        char to;
        int cost;
    };

    int dijkstra(char src, char dest, const std::unordered_map<char, std::vector<Edge>>& graph) {
        std::unordered_map<char, int> dist;
        for (char c = 'a'; c <= 'z'; ++c) {
            dist[c] = INF;
        }
        dist[src] = 0;

        std::priority_queue<std::pair<int, char>, std::vector<std::pair<int, char>>, std::greater<>> pq;
        pq.emplace(0, src);

        while (!pq.empty()) {
            auto [current_cost, u] = pq.top();
            pq.pop();

            if (u == dest) {
                return current_cost;
            }

            if (current_cost > dist[u]) continue;

            if (graph.find(u) != graph.end()) {
                for (const auto& edge : graph.at(u)) {
                    char v = edge.to;
                    int weight = edge.cost;

                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        pq.emplace(dist[v], v);
                    }
                }
            }
        }

        return INF;
    }
    
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        int n = source.size();
        std::unordered_map<char, std::vector<Edge>> graph;

        // Build the graph
        for (size_t i = 0; i < original.size(); ++i) {
            graph[original[i]].push_back({changed[i], cost[i]});
        }

        int totalCost = 0;

        // Calculate the cost to convert each character in source to the corresponding character in target
        for (int i = 0; i < n; ++i) {
            char s = source[i];
            char t = target[i];
            if (s == t) continue;

            int cost = dijkstra(s, t, graph);
            if (cost == INF) {
                return -1; // Impossible to convert
            }
            totalCost += cost;
        }

        return totalCost;
    }
};
```

<h3> Explanation: </h3>

1. **Graph Initialization**: Construct the graph using the `original`, `changed`, and `cost` arrays.
2. **Dijkstra's Algorithm**: Modified to handle multiple transformations using a priority queue.
3. **Cost Calculation**: For each character in `source`, find the minimum cost to transform it to the corresponding character in `target`.

This implementation ensures handling of multiple-step transformations correctly, avoiding infinite loops and checking all possible paths.

> TLE (568 Test Case).

#### TLE 개선
To avoid TLE (Time Limit Exceeded), we need a more efficient approach. Instead of running Dijkstra's algorithm from scratch for each character transformation, we can precompute the shortest transformation costs for all pairs of characters. We can achieve this using the Floyd-Warshall algorithm to find the shortest paths between all pairs of characters efficiently. 

Here's the optimized solution:

```cpp
class Solution {
public:
    const int INF = std::numeric_limits<int>::max();
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        int n = source.size();
        int m = original.size();
        
        // Create the cost matrix and initialize it with INF
        std::vector<std::vector<int>> costMatrix(26, std::vector<int>(26, INF));
        for (int i = 0; i < 26; ++i) {
            costMatrix[i][i] = 0;
        }
        
        // Fill the cost matrix with the given costs
        for (int i = 0; i < m; ++i) {
            int u = original[i] - 'a';
            int v = changed[i] - 'a';
            costMatrix[u][v] = std::min(costMatrix[u][v], cost[i]);
        }
        
        // Apply the Floyd-Warshall algorithm
        for (int k = 0; k < 26; ++k) {
            for (int i = 0; i < 26; ++i) {
                for (int j = 0; j < 26; ++j) {
                    if (costMatrix[i][k] < INF && costMatrix[k][j] < INF) {
                        costMatrix[i][j] = std::min(costMatrix[i][j], costMatrix[i][k] + costMatrix[k][j]);
                    }
                }
            }
        }
        
        // Calculate the total transformation cost
        int totalCost = 0;
        for (int i = 0; i < n; ++i) {
            char s = source[i];
            char t = target[i];
            if (s != t) {
                int u = s - 'a';
                int v = t - 'a';
                if (costMatrix[u][v] == INF) {
                    return -1; // Impossible to convert
                }
                totalCost += costMatrix[u][v];
            }
        }
        
        return totalCost;
    }
};
```

<h3> Explanation: </h3>

1. **Cost Matrix Initialization**: Initialize a 26x26 cost matrix with infinity (`INF`). Set the diagonal to zero because no cost is needed to transform a character into itself.
2. **Graph Population**: Populate the cost matrix with given transformation costs.
3. **Floyd-Warshall Algorithm**: Compute the shortest path between all pairs of characters.
4. **Cost Calculation**: Calculate the total transformation cost using the precomputed shortest paths. If a transformation is impossible, return -1. 

This solution ensures efficient computation of the minimum cost to convert `source` to `target` and should avoid TLE.

> Line 43: Char 27: runtime error: signed integer overflow: 2147447147 + 62778 cannot be represented in type 'int' (solution.cpp)
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior solution.cpp:43:27

#### overflow 개선
To address the signed integer overflow, we need to use a larger data type that can handle the sum of costs. Switching from `int` to `long long` can solve this issue. Here's the updated implementation:

```cpp
// 168ms, 98.87MB
class Solution {
public:
    const long long INF = std::numeric_limits<long long>::max();
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        int n = source.size();
        int m = original.size();
        
        // Create the cost matrix and initialize it with INF
        std::vector<std::vector<long long>> costMatrix(26, std::vector<long long>(26, INF));
        for (int i = 0; i < 26; ++i) {
            costMatrix[i][i] = 0;
        }
        
        // Fill the cost matrix with the given costs
        for (int i = 0; i < m; ++i) {
            int u = original[i] - 'a';
            int v = changed[i] - 'a';
            costMatrix[u][v] = std::min(costMatrix[u][v], static_cast<long long>(cost[i]));
        }
        
        // Apply the Floyd-Warshall algorithm
        for (int k = 0; k < 26; ++k) {
            for (int i = 0; i < 26; ++i) {
                for (int j = 0; j < 26; ++j) {
                    if (costMatrix[i][k] < INF && costMatrix[k][j] < INF) {
                        costMatrix[i][j] = std::min(costMatrix[i][j], costMatrix[i][k] + costMatrix[k][j]);
                    }
                }
            }
        }
        
        // Calculate the total transformation cost
        long long totalCost = 0;
        for (int i = 0; i < n; ++i) {
            char s = source[i];
            char t = target[i];
            if (s != t) {
                int u = s - 'a';
                int v = t - 'a';
                if (costMatrix[u][v] == INF) {
                    return -1; // Impossible to convert
                }
                totalCost += costMatrix[u][v];
            }
        }
        
        return totalCost > INF ? -1 : totalCost;
    }
};
```

<h3> Explanation: </h3>

1. **Data Type Change**: Use `long long` instead of `int` to handle large sums.
2. **Graph Initialization**: Construct the graph and initialize the cost matrix with `INF` to represent unreachable paths.
3. **Floyd-Warshall Algorithm**: Compute the shortest paths between all pairs of characters.
4. **Cost Calculation**: Calculate the total transformation cost using the precomputed shortest paths. If a transformation is impossible, return -1.

This solution efficiently handles large costs and avoids integer overflow, ensuring correct results within the problem constraints.