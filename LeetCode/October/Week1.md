## ToC

# October Week 1
## 24.10.01 - 1497. Check If Array Pairs Are Divisible by k
[문제 링크](https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/description/?envType=daily-question&envId=2024-10-01)

### 나
아이디어가 없다

### Solution
#### Approach 1: Hashing / Counting
```cpp
class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        unordered_map<int, int> remainderCount;

        // Store the count of remainders in a map.
        for (auto i : arr) remainderCount[(i % k + k) % k]++;

        for (auto i : arr) {
            int rem = (i % k + k) % k;

            // If the remainder for an element is 0, then the count
            // of numbers that give this remainder must be even.
            if (rem == 0) {
                if (remainderCount[rem] % 2 == 1) return false;
            }

            // If the remainder rem and k-rem do not have the
            // same count then pairs cannot be made.
            else if (remainderCount[rem] != remainderCount[k - rem])
                return false;
        }
        return true;
    }
};
```
#### Approach 2: Sorting and Two-Pointers
```cpp
class Solution {
public:
    // Custom comparator to sort based on mod values.
    struct Comparator {
        int k;
        Comparator(int k) { this->k = k; }
        bool operator()(int i, int j) {
            return (k + i % k) % k < (k + j % k) % k;
        }
    };

    bool canArrange(vector<int>& arr, int k) {
        sort(arr.begin(), arr.end(), Comparator(k));

        // Assign the pairs with modulo 0 first.
        int start = 0, end = arr.size() - 1;
        while (start < end) {
            if (arr[start] % k != 0) break;
            if (arr[start + 1] % k != 0) return false;
            start = start + 2;
        }

        // Now, pick one element from the beginning and one element from the
        // end.
        while (start < end) {
            if ((arr[start] + arr[end]) % k != 0) return false;
            start++;
            end--;
        }
        return true;
    }
};
```

## 24.10.02 - 1331. Rank Transform of an Array
[문제 링크](https://leetcode.com/problems/rank-transform-of-an-array/description/?envType=daily-question&envId=2024-10-02)

### 나
```cpp
// 93ms, 51.36MB
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        set<int> s;
        for(int a : arr) {
            s.insert(a);
        }

        unordered_map<int, int> um;
        int index = 1;
        for(int e : s) {
            um.emplace(e, index++);
        }

        vector<int> answer;
        for(int a : arr) {
            answer.push_back(um[a]);
        }

        return answer;
    }
};
```

## 24.10.03 - 1590. Make Sum Divisible by P
[문제 링크](https://leetcode.com/problems/make-sum-divisible-by-p/description/?envType=daily-question&envId=2024-10-03)

### 나
아이디어 없음.

### Solution
#### Approach 2: Prefix Sum Modulo
```cpp
class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int n = nums.size();
        int totalSum = 0;

        // Step 1: Calculate total sum and target remainder
        for (int num : nums) {
            totalSum = (totalSum + num) % p;
        }

        int target = totalSum % p;
        if (target == 0) return 0;  // The array is already divisible by p

        // Step 2: Use a hash map to track prefix sum mod p
        unordered_map<int, int> modMap;
        modMap[0] =
            -1;  // To handle the case where the whole prefix is the answer
        int currentSum = 0, minLen = n;

        // Step 3: Iterate over the array
        for (int i = 0; i < n; ++i) {
            currentSum = (currentSum + nums[i]) % p;

            // Calculate what we need to remove
            int needed = (currentSum - target + p) % p;

            // If we have seen the needed remainder, we can consider this
            // subarray
            if (modMap.find(needed) != modMap.end()) {
                minLen = min(minLen, i - modMap[needed]);
            }

            // Store the current remainder and index
            modMap[currentSum] = i;
        }

        // Step 4: Return result
        return minLen == n ? -1 : minLen;
    }
};
```

## 24.10.04 - 2491. Divide Players Into Teams of Equal Skill
[문제 링크](https://leetcode.com/problems/divide-players-into-teams-of-equal-skill/description/?envType=daily-question&envId=2024-10-04)

### 나
간단하게 생각하기

```cpp
// 70ms, 56.40MB
// 간단하게 생각하기.
class Solution {
public:
    long long dividePlayers(vector<int>& skill) {
        sort(begin(skill), end(skill));

        int team = skill.front() + skill.back();
        long long answer{};

        for(int s{}, e{static_cast<int>(skill.size())};s < e / 2;++s) {
            int curr = skill[s] + skill[e - s - 1];

            if(curr != team) return -1;

            answer += (long long)skill[s] * skill[e - s - 1];
        }

        return answer;
    }
};
```

### Solution
#### Approach 2: Frequency Table
```cpp
class Solution {
public:
    long long dividePlayers(vector<int>& skill) {
        int n = skill.size();
        int totalSkill = 0;
        vector<int> skillFrequency(1001, 0);

        // Calculate total skill and skill frequency
        for (int playerSkill : skill) {
            totalSkill += playerSkill;
            skillFrequency[playerSkill]++;
        }

        // Check if total skill can be evenly distributed among teams
        if (totalSkill % (n / 2) != 0) {
            return -1;
        }

        int targetTeamSkill = totalSkill / (n / 2);
        long long totalChemistry = 0;

        // Calculate total chemistry while verifying valid team formations
        for (int playerSkill : skill) {
            int partnerSkill = targetTeamSkill - playerSkill;

            // Check if a valid partner exists
            if (skillFrequency[partnerSkill] == 0) {
                return -1;
            }

            totalChemistry += (long long)playerSkill * (long long)partnerSkill;
            skillFrequency[partnerSkill]--;
        }

        // Return half of totalChemistry as each pair is counted twice
        return totalChemistry / 2;
    }
};
```

#### Approach 3: Map
```cpp
class Solution {
public:
    long long dividePlayers(vector<int>& skill) {
        int n = skill.size();
        int totalSkill = 0;
        unordered_map<int, int> skillMap;

        // Calculate total skill and build frequency map
        for (int s : skill) {
            totalSkill += s;
            skillMap[s] = skillMap[s] + 1;
        }

        // Check if total skill can be evenly distributed among teams
        if (totalSkill % (n / 2) != 0) {
            return -1;
        }

        int targetSkill = totalSkill / (n / 2);
        long long totalChemistry = 0;

        // Iterate through unique skill values
        for (auto& [currSkill, currFreq] : skillMap) {
            int partnerSkill = targetSkill - currSkill;

            // Check if valid partner skill exists with matching frequency
            if (skillMap.find(partnerSkill) == skillMap.end() ||
                currFreq != skillMap[partnerSkill]) {
                return -1;
            }

            // Calculate chemistry for all pairs with this skill
            totalChemistry += (long long)currSkill * (long long)partnerSkill *
                              (long long)currFreq;
        }

        // Return half of total chemistry (as each pair is counted twice)
        return totalChemistry / 2;
    }
};
```