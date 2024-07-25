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

구현하는 대신에 gpt한테 3가지 구현을 물어봤습니다.

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