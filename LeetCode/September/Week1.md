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
  - [24.09.03 - 1945. Sum of Digits of String After Convert](#240903---1945-sum-of-digits-of-string-after-convert)
    - [나](#나-2)
    - [gpt](#gpt-1)
  - [24.09.04 - 874. Walking Robot Simulation](#240904---874-walking-robot-simulation)
    - [나](#나-3)
    - [해설](#해설-1)
      - [Approach: Simulation](#approach-simulation)
    - [gpt](#gpt-2)
  - [24.09.05 - 2028. Find Missing Observations](#240905---2028-find-missing-observations)
    - [나](#나-4)
    - [gpt](#gpt-3)
  - [24.09.06 - 3217. Delete Nodes From Linked List Present in Array](#240906---3217-delete-nodes-from-linked-list-present-in-array)
    - [나](#나-5)
    - [gpt](#gpt-4)
  - [24.09.07 - 1367. Linked List in Binary Tree](#240907---1367-linked-list-in-binary-tree)
    - [나](#나-6)
    - [해설](#해설-2)

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

## 24.09.03 - 1945. Sum of Digits of String After Convert
[문제 링크](https://leetcode.com/problems/sum-of-digits-of-string-after-convert/description/?envType=daily-question&envId=2024-09-03)

### 나
```cpp
// 5ms, 10.12MB
class Solution {
public:
    int getLucky(string s, int k) {
        string convertedS;
        for(char c : s) {
            convertedS += to_string(c - 'a' + 1);
        }
        int num{};
        for(int i{};i<k;++i) {
            num = 0;
            for(char c : convertedS) {
                num += c - '0';
            }
            convertedS = to_string(num);
        }
        return  num;
    }
};
```

### gpt
The **"Sum of Digits of String After Convert"** problem asks you to convert a string into its numeric form based on the position of each letter in the alphabet (a = 1, b = 2, ..., z = 26). After that, you perform a transformation `k` times where you sum the digits of the resulting number.

<h3> Approach: </h3>

1. Convert the string to a numeric string based on the alphabet's position.
2. Sum the digits of this number for `k` iterations.

<h3> C++ Solution: </h3>

```cpp
// 6ms, 10.19MB
class Solution {
public:
    int getLucky(string s, int k) {
        // Convert string to a numerical string based on alphabetic position
        string numStr = "";
        for (char c : s) {
            numStr += to_string(c - 'a' + 1);
        }

        // Perform the transformation k times
        int sum = 0;
        for (int i = 0; i < k; ++i) {
            sum = 0;
            for (char c : numStr) {
                sum += c - '0';  // Sum digits
            }
            numStr = to_string(sum);  // Update the number as string
        }
        return sum;
    }
};
```

<h3> Explanation: </h3>

1. **Step 1: Conversion:** Convert each character in the string to its position in the alphabet. For example, "zbax" becomes "26213124".
2. **Step 2: Transformation:** Sum the digits of the resulting number and repeat this process `k` times.

<h3> Time Complexity: </h3>

- $O(n + k \times d)$, where $n$ is the length of the string and $d$ is the number of digits in the number after conversion.

## 24.09.04 - 874. Walking Robot Simulation
[문제 링크](https://leetcode.com/problems/walking-robot-simulation/description/)

### 나
simulation은 생각했는데, 장애물 처리 아이디어가 없다.
- 또 궁금했던 건 장애물이 (0, 0)에 있을 때 그냥 못 가는 건지, 처음에는 갈 수 있는 건지 도 애매했는 것 같다.
  - 장애물 처리 아이디어 해설 참고!

$\Rightarrow$ 해설 참고

### 해설

#### Approach: Simulation
[링크](https://leetcode.com/problems/walking-robot-simulation/editorial/#approach-simulation)


### gpt
In the **"Walking Robot Simulation"** problem, you are given a robot starting at the origin of a 2D plane, facing north. The robot receives a series of commands (positive for movement and negative for turns) and obstacles scattered on the plane. The goal is to determine the farthest distance (squared) the robot can be from the origin after executing all commands while avoiding obstacles.

<h3> Approach: </h3>

1. **Movement Logic**: Track robot's position and direction (north, east, south, west).
2. **Obstacle Handling**: Skip commands that would move the robot into obstacles.

<h3> C++ Code Solution: </h3>

```cpp
// 124ms, 39.64MB
class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        // Directions: north, east, south, west
        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        unordered_set<string> obsSet;

        // Add obstacles to a hash set for O(1) lookup
        for (const auto& obs : obstacles) {
            obsSet.insert(to_string(obs[0]) + "," + to_string(obs[1]));
        }

        int x = 0, y = 0;  // Robot's position
        int dir = 0;  // Start facing north
        int maxDist = 0;

        for (int cmd : commands) {
            if (cmd == -1) {
                // Turn right (clockwise)
                dir = (dir + 1) % 4;
            } else if (cmd == -2) {
                // Turn left (counterclockwise)
                dir = (dir + 3) % 4;
            } else {
                // Move forward by 'cmd' units
                for (int step = 0; step < cmd; ++step) {
                    int newX = x + directions[dir][0];
                    int newY = y + directions[dir][1];

                    if (obsSet.count(to_string(newX) + "," + to_string(newY))) {
                        break;  // Hit an obstacle, stop moving
                    }

                    x = newX;
                    y = newY;
                    maxDist = max(maxDist, x * x + y * y);  // Update max distance
                }
            }
        }

        return maxDist;
    }
};
```

<h3> Explanation: </h3>

1. **Direction Control**: Use an array to manage directional changes (north, east, south, west).
2. **Obstacle Checking**: Store obstacles in a hash set for quick lookup and stop movement when hitting one.
3. **Distance Calculation**: Track the maximum squared distance from the origin.

<h3> Time Complexity: </h3>

- $O(n + m)$, where $n$ is the number of commands and $m$ is the number of obstacles.

## 24.09.05 - 2028. Find Missing Observations
[문제 링크](https://leetcode.com/problems/find-missing-observations/description/)

### 나
```cpp
// 98ms, 126.21MB
class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int sum{};
        for(int roll : rolls) sum += roll;
        int m = rolls.size();

        int rest = mean * (n + m) - sum; // missing: n

        vector<int> answer;
        if(n <= rest && rest <= 6 * n) { // 답 만들 수 있음.
            // n개의 수로 others 만들기.
            for(;rest != n;--n) {
                int r = rest - (n - 1);
                if(1 <= r && r <= 6) {
                    answer.push_back(r);
                    rest -= r;
                }
                else {
                    answer.push_back(6);
                    rest -= 6;
                }
            }
            for(int i{};i<n;++i) answer.push_back(1);
        }
        
        return answer;
    }
};
```

### gpt
To solve the LeetCode problem ["Find Missing Observations"](https://leetcode.com/problems/find-missing-observations/), you need to find `n` missing dice rolls given `m` observed rolls and the mean of all `n + m` rolls. 

The task is to determine what values those missing rolls should have to maintain the overall average.

<h3> Approach: </h3>

1. **Calculate the total sum**:
   - The sum of all `n + m` rolls must be `mean * (n + m)`.
   - Calculate the sum of the observed rolls (`rolls[]`) and subtract it from this total to get the sum of the missing rolls.
   
2. **Check for feasibility**:
   - The sum of the missing `n` rolls should be between `n` (all 1s) and `6 * n` (all 6s) because each dice roll is between 1 and 6.
   - If the sum is outside this range, it's impossible to generate valid rolls, and you return an empty array.

3. **Distribute the sum**:
   - Distribute the sum of the missing rolls evenly. Start by assigning each missing roll the floor value of the average (`total_sum_of_missing // n`).
   - Then, distribute the remainder (`total_sum_of_missing % n`) by adding `1` to the first few rolls to balance the total.

<h3> Code Implementation: </h3>

```cpp
// 107ms, 116.37MB
class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int m = rolls.size();
        int total_sum = mean * (n + m);
        int observed_sum = 0;
        
        for (int roll : rolls) {
            observed_sum += roll;
        }
        
        int missing_sum = total_sum - observed_sum;
        
        // Check if it's possible to generate valid missing rolls
        if (missing_sum < n || missing_sum > 6 * n) {
            return {};
        }
        
        // Distribute the missing_sum
        vector<int> result(n, missing_sum / n);
        int remainder = missing_sum % n;
        
        for (int i = 0; i < remainder; ++i) {
            result[i]++;
        }
        
        return result;
    }
};
```

<h3> Explanation: </h3>

- We first compute the total sum of all `n + m` rolls.
- Then, subtract the observed sum to get the sum of the missing rolls.
- If this sum is not within the valid range (`n <= sum <= 6 * n`), return an empty vector because it's impossible.
- Otherwise, we distribute the sum evenly among the missing rolls, ensuring that the total remains consistent.

<h3> Time Complexity: </h3>

- The time complexity is $O(m + n)$, where `m` is the size of `rolls` and `n` is the number of missing rolls.

<h3> Space Complexity: </h3>

- The space complexity is $O(n)$ for the result array.

## 24.09.06 - 3217. Delete Nodes From Linked List Present in Array
[문제 링크](https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/description/?envType=daily-question&envId=2024-09-06)

### 나
```cpp
// 387ms, 319.5MB
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
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        const int SIZE = 100'010;
        vector<int> dat(SIZE, 0);
        for(int num : nums) dat[num] = 1;

        // 시작점 찾기
        while(head -> next) {
            if(dat[head->val]) {
                head = head->next;
            }
            else break;
        }

        ListNode* now = head; // 첫 시작점은 무조건 존재하는 head
        while(now -> next) {
            ListNode* next = now -> next;
            if(dat[next->val]) {
                now -> next = next -> next;
            }
            else {
                if(!(now->next)) break;
                now = now -> next;
            }
        }

        return head;
    }
};
```

### gpt
To solve the problem "Delete Nodes From Linked List Present in Array" on LeetCode, the goal is to remove all nodes from the linked list whose values are present in the given array `nums`. Here's an efficient approach using a hash set for constant-time lookups.

<h3> Approach: </h3>

1. **Create a Set**: Store all elements from the array `nums` in an unordered set for $O(1)$ lookup time.
2. **Use a Dummy Node**: Create a dummy node pointing to the head of the linked list. This simplifies edge cases like removing the head node.
3. **Traverse the List**: Iterate through the linked list and check if the value of the current node's `next` is in the set:
   - If it is, bypass that node by adjusting the pointers.
   - Otherwise, move to the next node.
4. **Return the Modified List**: Finally, return the list starting from `dummy.next` (to skip the dummy node itself).

<h3> C++ Solution: </h3>

```cpp
// 405ms, 258.36MB
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
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        unordered_set<int> values(nums.begin(), nums.end());
        ListNode* dummy = new ListNode(0, head);
        ListNode* current = dummy;
        
        while (current->next != nullptr) {
            if (values.count(current->next->val)) {
                current->next = current->next->next;  // Remove the node
            } else {
                current = current->next;
            }
        }
        
        return dummy->next;  // Return the modified list
    }
};
```

<h3> Complexity: </h3>

- **Time Complexity**: $O(n + m)$, where `n` is the size of the array `nums` and `m` is the number of nodes in the linked list.
- **Space Complexity**: $O(n)$, for storing the elements of `nums` in a set.

This approach efficiently handles large inputs due to its linear complexity. 

## 24.09.07 - 1367. Linked List in Binary Tree
[문제 링크](https://leetcode.com/problems/linked-list-in-binary-tree/description/?envType=daily-question&envId=2024-09-07)

### 나
TLE가 나서 해설 참고..

```cpp
// TLE
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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool answer{};
    ListNode* listStart;
    void traverseSubPath(ListNode* head, TreeNode* root) {
        if(answer) return;
        
        if(head == nullptr) { // reach the end.
            answer = true;
            return;
        }

        if(root == nullptr) return; // leaf

        if(head->val == root->val) { // 같다면 유지
            traverseSubPath(head->next, root->left);
            traverseSubPath(head->next, root->right);
        }

        // 아닌 경우 새로 시작
        traverseSubPath(listStart, root->left);
        traverseSubPath(listStart, root->right);
    }

    bool isSubPath(ListNode* head, TreeNode* root) {
        listStart = head;
        traverseSubPath(head, root);

        return answer;
    }
};
```

### 해설
[링크](https://leetcode.com/problems/linked-list-in-binary-tree/editorial)

추후 작성.

