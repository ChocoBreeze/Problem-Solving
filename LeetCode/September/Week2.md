## ToC
- [September Week 2](#september-week-2)
  - [24.09.09 - 2326. Spiral Matrix IV](#240909---2326-spiral-matrix-iv)
    - [나](#나)
    - [gpt](#gpt)

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

