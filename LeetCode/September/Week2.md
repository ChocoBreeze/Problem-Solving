## ToC
- [September Week 2](#september-week-2)
  - [24.09.09 - 2326. Spiral Matrix IV](#240909---2326-spiral-matrix-iv)
    - [나](#나)
    - [gpt](#gpt)
  - [24.09.10 - 2807. Insert Greatest Common Divisors in Linked List](#240910---2807-insert-greatest-common-divisors-in-linked-list)
    - [나](#나-1)
    - [gpt](#gpt-1)
  - [24.09.11 - 2220. Minimum Bit Flips to Convert Number](#240911---2220-minimum-bit-flips-to-convert-number)
    - [나](#나-2)
    - [gpt](#gpt-2)
  - [24.09.12 - 1684. Count the Number of Consistent Strings](#240912---1684-count-the-number-of-consistent-strings)
    - [나](#나-3)
    - [gpt](#gpt-3)
  - [24.09.13 - 1310. XOR Queries of a Subarray](#240913---1310-xor-queries-of-a-subarray)
    - [나](#나-4)
    - [Solution](#solution)
      - [Iteratve Approach](#iteratve-approach)
      - [Prefix XOR Array](#prefix-xor-array)
  - [24.09.14 - 2419. Longest Subarray With Maximum Bitwise AND](#240914---2419-longest-subarray-with-maximum-bitwise-and)
    - [나](#나-5)
    - [Solution](#solution-1)

# September Week 2
## 24.09.09 - 2326. Spiral Matrix IV
[문제 링크](https://leetcode.com/problems/spiral-matrix-iv/description/?envType=daily-question&envId=2024-09-09)

### 나
```cpp
// 195ms, 147.44MB
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        // x: 0,1,0,-1 -> "1210"
        // y: 1,0,-1,0 -> "2101"
        
        std::string dx = "1210", dy ="2101";
        vector answer (m, vector(n, -1));
        vector visited (m, vector(n, 0));
        ListNode* now = head;

        int x{}, y{-1}, d{};
        int cnt{}, dCnt{};
        while(now && cnt < m * n) {
            int nx = x + dx[d] - '1', ny = y + dy[d] - '1';
            if(nx < 0 || nx >= m || ny < 0 || ny >= n || visited[nx][ny]) { // 방향 전환
                d = (d+1)%4;
                ++dCnt;
                if(dCnt == 4) break; // 갈 곳이 없음.
                continue;
            }
            dCnt = 0;
            visited[nx][ny] = 1;
            answer[nx][ny] = now->val;
            now = now ->next;
            x = nx, y = ny;
            ++cnt;
        }

        return answer;
    }
};
```

### gpt
The **Spiral Matrix IV** problem on LeetCode involves filling a matrix of size `m x n` with values from a linked list in spiral order, starting from the top-left corner. If there are remaining cells after exhausting the linked list, they should be filled with `-1`.

<h3> Approach: </h3>

1. **Initialize the Matrix**: Create a matrix `ans` of size `m x n` and initialize all its elements to `-1`.
2. **Set Directional Boundaries**: Use an array to represent four possible movement directions: right, down, left, and up.
3. **Iterate through the Linked List**:
   - Begin at the top-left corner.
   - Move in a spiral pattern, and at each step, check if the next move is valid (i.e., within the matrix bounds and not already filled).
   - If an invalid move is detected, change direction and continue filling.
4. **Fill the Matrix**: For each node in the linked list, assign its value to the current cell and move to the next cell. Once the linked list is exhausted, leave the remaining cells as `-1`.

<h3> Code in C++: </h3>

```cpp
// 162ms, 130.48MB
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> ans(m, vector<int>(n, -1));
        int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int x = 0, y = 0, d = 0;
        
        for (ListNode* curr = head; curr; curr = curr->next) {
            ans[x][y] = curr->val;
            int nx = x + dirs[d][0], ny = y + dirs[d][1];
            
            if (nx < 0 || nx >= m || ny < 0 || ny >= n || ans[nx][ny] != -1) {
                d = (d + 1) % 4;
                nx = x + dirs[d][0];
                ny = y + dirs[d][1];
            }
            x = nx;
            y = ny;
        }
        
        return ans;
    }
};
```

<h3> Time Complexity: </h3>

- $O(m * n)$ since we traverse each cell of the matrix once, and each step involves checking bounds and filling a value.

<h3> Space Complexity: </h3>

- $O(m * n)$ for storing the matrix.

This approach efficiently simulates the spiral filling, and handles edge cases like small matrix sizes and lists shorter than `m * n`.

## 24.09.10 - 2807. Insert Greatest Common Divisors in Linked List
[문제 링크](https://leetcode.com/problems/insert-greatest-common-divisors-in-linked-list/description/?envType=daily-question&envId=2024-09-10)

### 나
```cpp
// 41ms, 35.6MB
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        ListNode* now = head;
        while(now) {
            ListNode* next = now->next;
            if(next == nullptr) break;
            int num = [](int a ,int b) -> int {
                while(b) {
                    int tmp = b;
                    b = a%b;
                    a = tmp;
                }
                return a;
            } (now->val, next->val);
            ListNode *tmp = new ListNode{num, next};
            now->next = tmp;

            now = next;
        }
        return head;
    }
};
```

```cpp
// 38ms, 35.5MB
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        ListNode* now = head;
        while(now) {
            ListNode* next = now->next;
            if(next == nullptr) break;
            int num = gcd(now->val, next->val);
            ListNode *tmp = new ListNode{num, next};
            now->next = tmp;

            now = next;
        }
        return head;
    }
private:
    int gcd(int a,int b) {
        if(b==0) return a;
        return gcd(b, a%b);
    }
};
```

### gpt
To solve the problem "Insert Greatest Common Divisors in Linked List," you need to modify the linked list by inserting a new node between every two adjacent nodes. The value of the new node should be the Greatest Common Divisor (GCD) of the values of these two adjacent nodes. Here's a step-by-step approach to solve this:

<h3> Steps: </h3>

1. **Traverse the Linked List**: Start at the head of the linked list and traverse through each node.
2. **Calculate GCD**: For every pair of adjacent nodes, compute the GCD of their values.
3. **Insert a New Node**: Create a new node with the GCD value and insert it between the two adjacent nodes.
4. **Continue**: Move to the next node and repeat the process until the end of the list.

<h3> Algorithm in C++: </h3>

```cpp
// 37ms, 35.58MB
class Solution {
public:
    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        ListNode* curr = head;
        while (curr->next != nullptr) {
            // Calculate GCD of curr and next node values
            int gcdValue = gcd(curr->val, curr->next->val);
            // Create a new node with the GCD value
            ListNode* newNode = new ListNode(gcdValue, curr->next);
            // Insert the new node between curr and the next node
            curr->next = newNode;
            // Move curr to the node after the newly inserted one
            curr = newNode->next;
        }
        return head;
    }

private:
    int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }
};
```

<h3> Explanation: </h3>

- **GCD Calculation**: The `gcd()` function uses the Euclidean algorithm to compute the GCD of two integers.
- **Insertion Logic**: The loop goes through each node in the list and calculates the GCD between the current node's value and the next node's value. A new node with the GCD is created and inserted between these two nodes. The traversal continues with the next node after the newly inserted one.
  
<h3> Time Complexity: </h3>

The time complexity is $O(n \log M)$, where $n$ is the number of nodes in the linked list, and $M$ is the maximum value of the node values. This accounts for both the list traversal and the GCD calculation.

## 24.09.11 - 2220. Minimum Bit Flips to Convert Number
[문제 링크](https://leetcode.com/problems/minimum-bit-flips-to-convert-number/description/?envType=daily-question&envId=2024-09-11)

### 나
```cpp
// 0ms, 7.5MB
class Solution {
public:
    int minBitFlips(int start, int goal) {
        int tmp = start ^ goal;
        int cnt{};
        while(tmp) {
            if(tmp&1) ++cnt;
            tmp >>= 1;
        }
        return cnt;
    }
};
```

### gpt
The problem "Minimum Bit Flips to Convert Number" can be solved using a simple bit manipulation technique. Here's how:

<h3> Problem Summary: </h3>

Given two integers `start` and `goal`, the task is to determine the minimum number of bit flips required to convert `start` into `goal`. A "bit flip" refers to changing a bit from 0 to 1 or from 1 to 0 in the binary representation.

<h3> Approach: </h3>

1. **Use XOR**: Perform XOR (`^`) between `start` and `goal`. XOR will set bits to `1` where the bits of `start` and `goal` differ and to `0` where they are the same.
2. **Count 1s in the Result**: After XOR, count the number of `1`s in the result. Each `1` represents a bit that needs to be flipped.

<h3> Example: </h3>

For `start = 10` and `goal = 7`:
- Binary of `10` is `1010`.
- Binary of `7` is `0111`.
- XOR of `1010 ^ 0111` = `1101`. There are 3 ones, so 3 bit flips are needed.

<h3> C++ Code Implementation: </h3>

```cpp
// 3ms, 7.7MB
class Solution {
public:
    int minBitFlips(int start, int goal) {
        int xorResult = start ^ goal;
        int bitCount = 0;
        while (xorResult > 0) {
            bitCount += xorResult & 1;
            xorResult >>= 1;
        }
        return bitCount;
    }
};
```

<h3> Time Complexity: </h3>

- $O(log(max(start, goal)))$: This is because we are counting the number of bits in the XOR result.
- **Space Complexity**: $O(1)$, since we use a constant amount of space.

## 24.09.12 - 1684. Count the Number of Consistent Strings
[문제 링크](https://leetcode.com/problems/count-the-number-of-consistent-strings/description/)

### 나
```cpp
// 46ms, 33.92MB
class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        int dat[27]{};
        for(char c : allowed) {
            dat[c - 'a'] = 1;
        }

        int answer{};
        for(string word : words) {
            auto ret = [&]() -> bool {
                for(char c : word) {
                    if(!dat[c - 'a']) return false;
                }
                return true;
            } ();
            if(ret) ++answer;
        }

        return answer;
    }
};
```

### gpt
The problem "Count the Number of Consistent Strings" on LeetCode asks you to find how many strings in an array consist only of characters found in a given string called `allowed`.

<h3> Solution Approach: </h3>

1. **Input**: A string `allowed` and an array of strings `words`.
2. **Output**: Count how many strings in `words` consist only of characters from `allowed`.
3. **Plan**:
   - Convert the `allowed` string into a set for fast lookups.
   - For each word, check if all its characters belong to this set.
   - Count the words that meet the condition.

<h3> C++ Code: </h3>

```cpp
// 43ms, 34.11MB
class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        unordered_set<char> allowed_set(allowed.begin(), allowed.end());
        int count = 0;
        for (const auto& word : words) {
            bool is_consistent = true;
            for (char c : word) {
                if (allowed_set.find(c) == allowed_set.end()) {
                    is_consistent = false;
                    break;
                }
            }
            if (is_consistent) {
                ++count;
            }
        }
        return count;
    }
};
```

<h3> Explanation: </h3>

1. **Set for allowed characters**: This speeds up the check for each character in `words`.
2. **Loop over words**: For each word, verify if all characters are in the `allowed` set.
3. **Return the count** of consistent strings.

## 24.09.13 - 1310. XOR Queries of a Subarray
[문제 링크](https://leetcode.com/problems/xor-queries-of-a-subarray/description/?envType=daily-question&envId=2024-09-13)

### 나
```cpp
// 52ms, 42.22MB
class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        const int SIZE = static_cast<int>(arr.size());
        vector<int> preXor(SIZE + 1, 0);
        for(int s{}, e{SIZE};s<e;++s){
            preXor[s+1] = preXor[s] ^ arr[s];
        }

        vector<int> answer;
        for(vector<int>& query : queries) {
            int start = query[0], finish = query[1]; // [0, 1]
            answer.push_back(preXor[finish + 1] ^ preXor[start]);
        }

        return answer;
    }
};
```

### Solution
#### Iteratve Approach
```cpp
// 1960ms, 41.83MB
// Iterative Approach
class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        vector<int> result;
        // Process each query
        for (const auto& q : queries) {
            int xorSum = 0;
            // Calculate XOR for the range [q[0], q[1]]
            for (int i = q[0]; i <= q[1]; i++) {
                xorSum ^= arr[i];
            }
            result.push_back(xorSum);
        }
        return result;
    }
};
```


#### Prefix XOR Array
```cpp
// 69ms, 42.13MB
// Prefix XOR Array
class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        int n = arr.size();
        vector<int> prefixXOR(n + 1, 0);

        // Build prefix XOR array
        for (int i = 0; i < n; i++) {
            prefixXOR[i + 1] = prefixXOR[i] ^ arr[i];
        }

        vector<int> result;
        // Process each query using prefix XOR
        for (const auto& q : queries) {
            result.push_back(prefixXOR[q[1] + 1] ^ prefixXOR[q[0]]);
        }
        return result;
    }
};
```

## 24.09.14 - 2419. Longest Subarray With Maximum Bitwise AND
[문제 링크](https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/description/?envType=daily-question&envId=2024-09-14)

### 나
```cpp
// 108ms, 84.96MB
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int answer{}, maxVal{};
        for(int num : nums) {
            maxVal = max(maxVal, num);
        }

        int cnt{};
        for(int num : nums) {
            if(maxVal == num) ++cnt;
            else cnt = 0;

            answer = max(answer, cnt);
        }

        return answer;
    }
};
```

한 번에 답 구하고 싶었는데, 조금 꼬였다.

### Solution
[링크](https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/editorial)

<h3> Overview </h3>

We need to find the longest subarray in an integer array where the bitwise AND of all elements equals the maximum possible bitwise AND of any subarray. The bitwise AND results in a value that is always less than or equal to the operands. This operation is commonly used in fields like network filtering, hardware design, and cryptography for tasks such as subnet masking, configuration checks, and data analysis.

<h3> Approach: Longest consecutive sequence of the maximum value </h3>

<h4> Intuition </h4>

To understand this problem, we first need to understand what a bitwise AND operation is. In simple terms, a bitwise AND operation takes two binary representations of an integer and performs the logical AND operation on each pair of the corresponding bits. If both bits are 1, the result is 1; otherwise, it's 0.

For example, take the numbers 12 (which is `1100` in binary) and 7 (`0111` in binary).

Performing a bitwise AND on these numbers gives the following:

| Bit Position   | 3rd Bit | 2nd Bit | 1st Bit | 0th Bit |
| :-------------: | :-------: | :-------: | :-------: | :-------: |
| Number 12      | 1       | 1       | 0       | 0       |
| Number 7       | 0       | 1       | 1       | 1       |
| Bitwise AND    | 0       | 1       | 0       | 0       |

As we can see, the result is `0100`, which is the binary representation of `4`.

Now, let’s look at the problem. We're given an array, and the goal is to find a subarray where the bitwise AND of all the numbers is as large as possible. A subarray is a continuous portion of the array, and we want to return the length of the subarray that has the highest bitwise AND value.

The maximum possible bitwise AND of a subarray would be the maximum number in the array itself. This is because the bitwise AND operation with a larger number and a smaller number would always result in a number less than or equal to the smaller number. Therefore, the maximum possible bitwise AND of a subarray can only be achieved when all the numbers in the subarray are equal to the maximum number in the array.

Let’s look at some examples of subarrays and their bitwise AND results:

| Subarray         | Bitwise AND Calculation                  | Result |
| :-------: | :-------: | :-------: |
| [4, 6]           | 4 AND 6 = 0100 AND 0110                  | 0100 = 4 |
| [4, 6, 7]        | 4 AND 6 AND 7 = 0100 AND 0110 AND 0111   | 0100 = 4 |
| [4, 6, 7, 8]     | 4 AND 6 AND 7 AND 8 = 0100 AND 0110 AND 0111 AND 1000 | 0000 = 0 |
| [6, 7]           | 6 AND 7 = 0110 AND 0111                  | 0110 = 6 |
| [6, 7, 8]        | 6 AND 7 AND 8 = 0110 AND 0111 AND 1000   | 0000 = 0 |
| [7, 8]           | 7 AND 8 = 0111 AND 1000                  | 0000 = 0 |
| [8, 8]           | 8 AND 8 = 1000 AND 1000                  | 1000 = 8 |

From this, we can see that the largest bitwise AND can only be achieved when all the elements in the subarray are equal to the maximum number. So, the task is to find the longest subarray where all the numbers are the maximum value in the array.

<h4> Algorithm </h4>

1. Initialize `max_val = 0`, `ans = 0`, and `current_streak = 0` to track the maximum value, the length of the longest subarray, and the current streak of elements, respectively.
2. Iterate through each element `num` in the array `nums`.
3. If `max_val < num`, update `max_val` to `num`, and reset `ans` and `current_streak` to 0 since a new maximum value is found.
4. If `max_val == num`, increment `current_streak` by 1 because the current element is equal to the maximum value.
5. If `max_val != num`, reset `current_streak` to 0 as the current element breaks the streak of numbers equal to the maximum value.
6. Update `ans` to be the maximum of `ans` and `current_streak` to ensure `ans` holds the length of the longest subarray with the maximum value.
7. After the loop finishes, return `ans`, which represents the length of the longest subarray where the bitwise AND equals the maximum value.

<h4> Implementation </h4>
 
Let $N$ be the length of `nums`.

- **Time Complexity**: $O(N)$  
  The time complexity is $O(N)$ because the function processes each element of the `nums` list exactly once. This is done through a single loop that iterates over the array. Each operation inside the loop—whether it's comparisons, assignments, or finding the maximum—takes constant time. As a result, the total time required scales linearly with the size of the input array.

- **Space Complexity**: $O(1)$  
  The function uses a fixed amount of extra space regardless of the size of the input array `nums`. Specifically, it only requires a few variables (`max_val`, `ans`, `current_streak`, and `num`) to keep track of intermediate values. This fixed space usage means the space complexity remains constant.
