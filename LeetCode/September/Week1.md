## ToC
- [September Week 1](#september-week-1)
  - [24.09.01 - 2022. Convert 1D Array Into 2D Array](#240901---2022-convert-1d-array-into-2d-array)
    - [나](#나)
    - [gpt](#gpt)
  - [24.09.02 - 1894. Find the Student that Will Replace the Chalk](#240902---1894-find-the-student-that-will-replace-the-chalk)
    - [나](#나-1)
    - [Solution](#solution)
      - [Approach 1: Prefix Sum](#approach-1-prefix-sum)
      - [Approach 2: Binary Search](#approach-2-binary-search)
  - [24.09.03 - 1945. Sum of Digits of String After Convert](#240903---1945-sum-of-digits-of-string-after-convert)
    - [나](#나-2)
    - [gpt](#gpt-1)
  - [24.09.04 - 874. Walking Robot Simulation](#240904---874-walking-robot-simulation)
    - [나](#나-3)
    - [Solution](#solution-1)
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
    - [해설](#해설)
  - [24.09.08 - 725. Split Linked List in Parts](#240908---725-split-linked-list-in-parts)
    - [나](#나-7)
    - [gpt](#gpt-5)

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

### Solution

#### Approach 1: Prefix Sum

<h3> Intuition </h3>

In this problem, we have an array `chalk` of `n` elements representing the number of chalks used by each student, and an integer `k` indicating the total number of chalks available. The brute force approach would involve repeatedly subtracting the number of chalks from `k` until it reaches zero, cycling through the array if necessary. Given that `k` can be as large as 1,000,000,000, this approach is impractical.

To optimize, observe that the total number of chalks used in one complete cycle through the array is given by `sum`, the sum of all elements in `chalk`. If `k` is less than `sum`, we will reach zero within the first cycle. If `k` is greater than `sum`, after the first cycle, `k` will be reduced to `k - sum`, and after subsequent cycles, it will be reduced further. This process continues until `k` becomes less than `sum`, which is equivalent to computing `k \% sum`.

> This is because `k` reduced by multiples of `sum` will eventually be less than `sum`, and this final value is equivalent to `k \% sum`.

We then need to find the first index in the `chalk` array where the remaining `k \% sum` becomes negative. We do this by maintaining a running prefix sum of `chalk` elements and iterating through the array to find the index where the prefix sum exceeds `k \% sum`.

<h3> Algorithm </h3>

1. Initialize an integer variable `sum` to 0.
2. Iterate over the chalk array from 0 to `chalk.size() - 1`:
   - Add the value at the current index `i` to `sum`.
   - If at any point `sum` exceeds `k`, exit the loop.
3. Calculate `k` as `k \% sum`, representing the remaining chalk after full rounds.
4. Iterate over the chalk array again from `0` to `chalk.size() - 1`:
   - If `k` is less than the value at the current index `i`, return `i` as the index of the student who will run out of chalk.
   - Otherwise, subtract the value at `chalk[i]` from `k`.
5. If no student is found within the loop, return `0` (though this should not be reached given the problem constraints).

<h3> Implementation </h3>

```cpp
// 96ms, 77.05MB
class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        // Find the sum of all elements.
        int sum = 0;
        for (int i = 0; i < chalk.size(); i++) {
            sum += chalk[i];
            if (sum > k) {
                break;
            }
        }
        // Find modulo of k with sum.
        k = k % sum;
        for (int i = 0; i < chalk.size(); i++) {
            if (k < chalk[i]) {
                return i;
            }
            k = k - chalk[i];
        }
        return 0;
    }
};
```

<h3> Complexity Analysis </h3>

Let n be the size of the chalk array.

- Time complexity: $O(n)$  
We iterate through the `chalk` array exactly twice. Apart from this, all operations are performed in constant time. Therefore, the total time complexity is given by $O(n)$.

- Space complexity: $O(1)$  
No additional space is used proportional to the array size `n`. Therefore, the space complexity is given by $O(1)$.

#### Approach 2: Binary Search

<h3> Intuition </h3>

Instead of iterating through the array to find the first index, we can use binary search. Binary search is ideal here because it quickly narrows down the search space in a sorted array.

We start by defining a predicate function that checks if the prefix sum at a given index is greater than the `k modulo sum`. This function returns `true` for indices where the prefix sum exceeds the target and `false` otherwise. Since the array is sorted based on the prefix sums, `true` indicates indices with no chalk left, while `false` indicates indices with some chalk remaining.

Using binary search, we locate the smallest index where the predicate returns `true`.

- If the predicate returns `true`, it means there might be smaller indices with `true` values, so we adjust the upper bound of the search space to the current index.
- If the predicate returns `false`, it means all `true` values are beyond the current index, so we adjust the lower bound of the search space to the current index.

<h3> Algorithm </h3>

Main Function - `chalkReplacer(chalk, k)`:

1. Create an array `prefixSum` of length `n` to store prefix sums.
2. Initialize `prefixSum[0]` with `chalk[0]`.
3. Iterate through the chalk array from index `1` to `n-1` and update `prefixSum[i]` as the sum of `prefixSum[i-1]` and `chalk[i]`.
4. Calculate `sum` as `prefixSum[n-1]`, representing the total chalk needed for one full round.
5. Calculate `remainingChalk` as `k \% sum`.
6. Call the helper function `binarySearch(prefixSum, remainingChalk)` to find the student who will run out of chalk and return the result of `binarySearch`.

Helper Function - `binarySearch(arr, remainingChalk)`:

1. Set `low` to 0 and `high` to `arr.length - 1`.
2. While `low` is less than `high`:
   - Calculate `mid` as the average of `low` and `high`.
   - If `arr[mid]` is less than or equal to `remainingChalk`, update `low to mid + 1`.
   - Otherwise, update `high` to `mid`.
3. Return `high` as the index of the student who will run out of chalk.

<h3> Implementation </h3>

```cpp
// 89ms, 83.93MB
class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        int n = chalk.size();

        vector<long> prefixSum(n);
        prefixSum[0] = chalk[0];
        for (int i = 1; i < n; i++) {
            prefixSum[i] = prefixSum[i - 1] + chalk[i];
        }

        long sum = prefixSum[n - 1];
        long remainingChalk = (k % sum);

        return binarySearch(prefixSum, remainingChalk);
    }

private:
    int binarySearch(vector<long>& arr, long tar) {
        int low = 0, high = arr.size() - 1;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] <= tar) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        return high;
    }
};
```

<h3> Complexity Analysis </h3>

Let $n$ be the size of the `chalk` array.

- **Time complexity**: $O(n)$  
  We iterate through the `chalk` array once. Apart from this, the binary search operation takes $O(\log n)$ time. Therefore, the total time complexity is given by $O(n)$.

- **Space complexity**: $O(n)$  
  We initialize an array `prefixSum` of size `n` to store the prefix sums of the `chalk` array. Apart from this, no additional space is used. Therefore, the space complexity is given by $O(n)$.

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

### Solution

<h3> Overview </h3>

We have a robot facing north at the origin `(0, 0)` of an infinite 2D grid. The robot receives a series of instructions from a given list of `commands`, where instruction can be of three types:

1. `-2`: Turn left 90 degrees while staying at the current coordinate.
2. `-1`: Turn right 90 degrees while staying at the current coordinate.
3. Any positive integer `k` from 1 to 9: Advance `k` units in the current direction.

Additionally, we are given a list of `obstacles` containing the coordinates of various obstacles on the grid. If the robot encounters an obstacle while moving forward, it stops its motion at the coordinate just before the obstacle and proceeds to the next command.

Our goal is to find the farthest squared distance from the origin that the robot reaches during its journey. In other words, we need to find the maximum value of $x \times x + y \times y$ that can be achieved at any point `(x, y)` visited by the robot.

Keep in mind when planning your approach that the farthest traveled distance during the robot's journey is not the same as its distance from the origin at the end of its journey.

> Note: An obstacle may exist at the origin (0, 0). In this case, the robot can move away from the starting point but will be unable to return to (0, 0).

#### Approach: Simulation

<h3> Intuition </h3>

The robot's state is defined by two factors:

1. The coordinates of the robot's position: we can use a simple integer array `[x, y]`.
2. The direction the robot is facing: we can use an integer value (0, 1, 2, 3) representing North, East, South, and West respectively. Consequently, we need a `directions` array representing the direction of motion of the robot, where each index corresponds to [North, East, South, West].

The presence of obstacles prevents us from being able to simply loop over each command and simulate the robot's motion on the grid. A naive approach would be to loop through the obstacle array to check if the next attempted move is blocked by an obstacle. However, this results in quadratic complexity, which is inefficient given our constraints.

Checking whether a given coordinate is an obstacle using hash sets allows for constant-time lookups. If you're unfamiliar with hash sets, this LeetCode [Explore Card](https://leetcode.com/explore/learn/card/hash-table/183/combination-with-other-algorithms/1130/) provides an in-depth explanation.

Our challenge becomes how to look up coordinates in a hash set.

We solve this by hashing the coordinates of each obstacle to a unique integer value and storing these values in the hash set. To check if a coordinate contains an obstacle, we hash the coordinates using the same function and check if the value is present in the hash set.

There are various methods to create [hashing functions](https://en.wikipedia.org/wiki/List_of_hash_functions). For this problem, we'll create a simple one that generates a unique integer value for all coordinates within the given problem constraints.

```python
hash(x, y) = x + HASH_MULTIPLIER * y
```

Where `HASH_MULTIPLIER` is a constant slightly larger than twice the maximum possible coordinate value. In this case, we choose `60013`.

> We choose `60013` because it is the smallest prime number greater than 60000 (twice the maximum possible coordinate). This helps reduce the number of potential collisions in our hash function.

slideshow 생략

<h3> Algorithm </h3>

- Create a constant `HASH_MULTIPLIER` to use in the hashing function.

`robotSim` Function:
- Convert the list of obstacles into a set of hashed coordinates for quick lookup during the simulation.
- Define the four possible movement directions corresponding to North, East, South, and West.
- Initialize the robot's starting position at the origin `(0, 0)` and set the initial maximum distance squared to zero.
- Initialize the current direction of the robot facing North.
- Iterate through the list of commands:
  - If the command is `-1`, turn the robot 90 degrees to the right by adjusting the current direction index.
  - If the command is `-2`, turn the robot 90 degrees to the left by adjusting the current direction index.
  - Otherwise, for a positive command, move the robot forward step by step:
    - Calculate the next potential position by adding the current direction vector to the robot's position.
    - If the next position is an obstacle, stop moving forward.
    - Otherwise, update the robot's position to the new coordinates.
  - Update the maximum distance squared if the current position is farther from the origin than before.
- Return the maximum distance squared as the result of the simulation.

`hashCoordinates` Function:
- Combine the `x` and `y` coordinates into a unique hash value by multiplying the `y` coordinate by a constant multiplier and adding the `x` coordinate.
- Return the computed hash value to be used for obstacle lookup.

<h3> Implementation </h3>

```cpp
// 76ms, 38.18MB
class Solution {
private:
    static const long long HASH_MULTIPLIER =
        60013;  // Slightly larger than 2 * max coordinate value

    // Hash function to convert (x, y) coordinates to a unique integer value
    long long hashCoordinates(long long x, long long y) {
        return x + HASH_MULTIPLIER * y;
    }

public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        // Store obstacles in an unordered_set for efficient lookup
        unordered_set<long long> obstacleSet;
        for (auto& obstacle : obstacles) {
            obstacleSet.insert(hashCoordinates(obstacle[0], obstacle[1]));
        }

        // Define direction vectors: North, East, South, West
        vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        vector<int> currentPosition = {0, 0};
        int maxDistanceSquared = 0;
        int currentDirection = 0;  // 0: North, 1: East, 2: South, 3: West

        for (int command : commands) {
            if (command == -1) {
                // Turn right
                currentDirection = (currentDirection + 1) % 4;
                continue;
            }
            if (command == -2) {
                // Turn left
                currentDirection = (currentDirection + 3) % 4;
                continue;
            }

            // Move forward
            vector<int> direction = directions[currentDirection];
            for (int step = 0; step < command; step++) {
                int nextX = currentPosition[0] + direction[0];
                int nextY = currentPosition[1] + direction[1];
                if (obstacleSet.contains(hashCoordinates(nextX, nextY))) {
                    break;
                }
                currentPosition[0] = nextX;
                currentPosition[1] = nextY;
            }

            maxDistanceSquared =
                max(maxDistanceSquared,
                    currentPosition[0] * currentPosition[0] +
                        currentPosition[1] * currentPosition[1]);
        }

        return maxDistanceSquared;
    }
};
```

<h3> Complexity Analysis </h3>

Let $m$ and $n$ be the length of `commands` and `obstacles`, respectively.

- **Time complexity**: $O(m + n)$  
  The algorithm initially iterates over the `obstacles` array and hashes each obstacle’s coordinates, taking $O(n)$ time.
  
  The algorithm then loops over the `commands` array. In the worst case, each command is a positive integer `k`. Since the maximum value of `k` is limited to 9, this step has a time complexity of $O(9 \cdot m) = O(m)$.

  Thus, the overall time complexity of the algorithm is $O(n) + O(m) = O(m + n)$.

- **Space complexity**: $O(n)$  
  The only additional space used by the algorithm is the `obstacleSet`, which stores up to $n$ hashed obstacle positions. The `directions` and `currentPosition` arrays and all other primitive variables use constant space.

  Thus, the space complexity of the algorithm is $O(n)$.

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

## 24.09.08 - 725. Split Linked List in Parts
[문제 링크](https://leetcode.com/problems/split-linked-list-in-parts/description/?envType=daily-question&envId=2024-09-08)

### 나
```cpp
// 0ms, 13.9MB
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
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int cnt{};
        /*
        // 이 부분이 틀렸네..
        for(ListNode* now = head;now->next;now = now->next, ++cnt)
        if(head) ++cnt; // 초기 원소 누락
        */
        ListNode* now = head;
        while (now) {
            ++cnt;
            now = now->next;
        }

        int quotient = cnt / k, remainder = cnt % k;
        vector<int> sizes(k, quotient); // 크기 k, 원소 값: quotient
        for(int i{};i<remainder;++i) sizes[i]++;

        vector<ListNode*> answer;
        now = head;
        for(int i{}; i<k; ++i) {
            answer.push_back(now); // if nullptr => push_back nullptr.

            for(int j{};j<sizes[i] && now;++j) {
                if(j == sizes[i] - 1) {
                    ListNode* tmp = now->next; // 마지막 원소 연결 끊기
                    now->next = nullptr;
                    now = tmp;
                }
                else now = now->next;
            }
        }

        return answer;
    }
};
```

개수 카운팅할 때
```cpp
for(ListNode* now = head;now->next;now = now->next, ++cnt)
if(head) ++cnt; // 초기 원소 누락
```
위의 코드에서 틀렸는데, 반례가 없을까..

수정한 코드
```cpp
for(ListNode* now = head;now;now = now->next) { // 조건 수정
    ++cnt;
}
```
OR
```cpp
ListNode* now = head;
while (now) {
    ++cnt;
    now = now->next;
}
```

### gpt
To solve the problem **"Split Linked List in Parts"**, the idea is to divide the linked list into `k` parts where each part has an approximately equal number of nodes. The first few parts may have an extra node if the number of nodes is not perfectly divisible by `k`.

<h3> Steps to Solve: </h3>

1. **Calculate the Length** of the Linked List:
   Traverse the entire list to determine its total length `N`.

2. **Determine the Size of Each Part**:
   - Each part should have a base size of `N // k`.
   - There will be `N % k` parts that need one extra node. These parts should be handled first.

3. **Split the List**:
   Traverse the list again to split it into parts. For each part:
   - Determine its size (either `N // k` or `N // k + 1`).
   - Detach it from the main list by updating the `next` pointer.

4. **Handle Remaining Parts**:
   If `k` is larger than `N`, the remaining parts will be empty (`null`).

<h3> Code Example in C++: </h3>

```cpp
// 5ms, 13.88MB
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
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        vector<ListNode*> result(k, nullptr);
        int length = 0;
        ListNode* temp = head;

        // Step 1: Calculate the total length of the linked list
        while (temp != nullptr) {
            length++;
            temp = temp->next;
        }

        int base_size = length / k;
        int extra = length % k;

        temp = head;
        for (int i = 0; i < k; ++i) {
            result[i] = temp;
            int part_size = base_size + (i < extra ? 1 : 0);

            // Split the list and prepare the next part
            for (int j = 0; j < part_size - 1; ++j) {
                if (temp != nullptr) {
                    temp = temp->next;
                }
            }

            if (temp != nullptr) {
                ListNode* next_part = temp->next;
                temp->next = nullptr;
                temp = next_part;
            }
        }

        return result;
    }
};
```

<h3> Complexity: </h3>

- **Time Complexity**: $O(N)$, where `N` is the number of nodes in the list (two passes).
- **Space Complexity**: $O(k)$ for storing the result.

