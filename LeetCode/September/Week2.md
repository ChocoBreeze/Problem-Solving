## ToC
- [September Week 2](#september-week-2)
  - [24.09.09 - 2326. Spiral Matrix IV](#240909---2326-spiral-matrix-iv)
    - [나](#나)
    - [gpt](#gpt)
  - [24.09.10 - 2807. Insert Greatest Common Divisors in Linked List](#240910---2807-insert-greatest-common-divisors-in-linked-list)
    - [나](#나-1)
    - [gpt](#gpt-1)

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

