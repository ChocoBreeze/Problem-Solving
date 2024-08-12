## ToC

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

