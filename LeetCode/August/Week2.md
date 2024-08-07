## ToC
- [August Week 2](#august-week-2)
  - [24.08.05 - 2053. Kth Distinct String in an Array](#240805---2053-kth-distinct-string-in-an-array)
    - [나](#나)
    - [gpt](#gpt)
  - [24.08.06 - 3016. Minimum Number of Pushes to Type Word II](#240806---3016-minimum-number-of-pushes-to-type-word-ii)
    - [나](#나-1)
    - [gpt](#gpt-1)
  - [24.08.07 - 273. Integer to English Words](#240807---273-integer-to-english-words)
    - [gpt](#gpt-2)

# August Week 2
## 24.08.05 - 2053. Kth Distinct String in an Array
[문제 링크](https://leetcode.com/problems/kth-distinct-string-in-an-array/)

### 나
```cpp
// 16ms, 18.34MB
class Solution {
public:
    string kthDistinct(vector<string>& arr, int k) {
        std::unordered_map<std::string, int> um;
        for(string& s : arr) {
            if(um.find(s)!=um.end()) {
                um[s]++;
            }
            else {
                um.emplace(s, 1);
            }
        }

        int i{};
        for(string& s : arr) {
            if(um[s] == 1) {
                ++i;
                if(i == k) {
                    return s;
                }
            }
        }
        return "";
    }
};
```

### gpt
Sure, let's solve the problem "Kth Distinct String in an Array" on LeetCode. Here's a detailed explanation and solution in C++.

<h3> Problem Description </h3>

You are given a string array `arr` and an integer `k`. A string is called **distinct** if it appears exactly once in the array. Return the `k`th distinct string in the array. If there are fewer than `k` distinct strings, return an empty string `""`.

<h3> Steps to Solve the Problem </h3>

1. **Count Occurrences:** Use a hash map to count the occurrences of each string in the array.
2. **Identify Distinct Strings:** Traverse the array again to collect strings that occur exactly once.
3. **Find the k-th Distinct String:** Check if we have at least `k` distinct strings and return the `k`th one, otherwise return an empty string.

<h3> Solution in C++ </h3>
Here's the solution implemented in C++:

```cpp
// 13ms, 20.38MB
class Solution {
public:
    string kthDistinct(vector<string>& arr, int k) {
        // Step 1: Count occurrences of each string
        std::unordered_map<std::string, int> countMap;
        for (const auto& str : arr) {
            countMap[str]++;
        }

        // Step 2: Collect distinct strings (those that appear exactly once)
        std::vector<std::string> distinctStrings;
        for (const auto& str : arr) {
            if (countMap[str] == 1) {
                distinctStrings.push_back(str);
            }
        }

        // Step 3: Return the k-th distinct string if it exists
        if (k <= distinctStrings.size()) {
            return distinctStrings[k - 1];
        } else {
            return "";
        }
    }
};
```

<h3> Explanation </h3>

1. **Counting Occurrences:**
   - We use an `unordered_map` (hash map) to count the occurrences of each string in the array.
   - `countMap[str]++` increments the count for each string.

2. **Identifying Distinct Strings:**
   - We traverse the array again to collect strings that have a count of 1 (i.e., they appear exactly once).
   - These distinct strings are stored in a vector `distinctStrings`.

3. **Returning the k-th Distinct String:**
   - We check if `k` is within the bounds of the `distinctStrings` vector.
   - If yes, we return the `k`th string (note that the index is `k-1` because vectors are 0-indexed).
   - If no, we return an empty string `""`.

<h3> Conclusion </h3>

This solution efficiently finds the k-th distinct string in the array by using a hash map to count occurrences and then collecting the distinct strings. The time complexity is $O(n)$ where n is the number of strings in the array, making it suitable for large inputs.

## 24.08.06 - 3016. Minimum Number of Pushes to Type Word II
[문제 링크](https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/description/)

### 나
```cpp
// 77ms, 24.94MB
class Solution {
public:
    int minimumPushes(string word) {
        // a string word containing lowercase English letters.
        const int SIZE = 26;
        vector dat(SIZE, 0);

        for(char c : word) {
            dat[c - 'a']++;
        }

        sort(begin(dat), end(dat), greater<>());

        int answer{};
        for(int i{};i<SIZE;++i){
            answer += dat[i] * (i / 8 + 1);
        }
        return answer;
    }
};
```

### gpt
Thank you for the clarification. The problem is to remap the keys on a telephone keypad to minimize the number of pushes needed to type a given word. Each key can be assigned a distinct set of lowercase letters, and we need to determine the optimal assignment.

<h3> Steps to Solve the Problem </h3>

1. **Character Frequency Count**: First, count the frequency of each character in the given word. This helps in understanding which characters need to be accessed most frequently.
2. **Sort Frequencies**: Sort the characters by their frequencies in descending order. The characters that appear more frequently should be assigned to the positions with fewer pushes.
3. **Assign Characters to Keys**: Map the characters to the keys such that the most frequent characters require the fewest pushes.

<h3> Solution </h3>

Here is the C++ implementation of the solution:

```cpp
class Solution {
public:
    int minimumPushes(string word) {
        // Step 1: Count frequency of each character in the word
        unordered_map<char, int> freq;
        for (char ch : word) {
            freq[ch]++;
        }

        // Step 2: Sort characters by their frequency in descending order
        vector<pair<int, char>> freqVec;
        for (auto& entry : freq) {
            freqVec.push_back({entry.second, entry.first});
        }
        sort(freqVec.rbegin(), freqVec.rend());

        // Step 3: Calculate the minimum pushes
        int totalPushes = 0;
        int pushCount = 1;
        int currentKeySize = 1;

        for (auto& entry : freqVec) {
            totalPushes += entry.first * pushCount;
            if (currentKeySize < 3) {
                currentKeySize++;
            } else {
                pushCount++;
                currentKeySize = 1;
            }
        }

        return totalPushes;
    }
};
```

<h3> Explanation </h3>

1. **Frequency Count**: We first create a frequency map (`freq`) to count how often each character appears in the word.
2. **Sorting**: We convert this frequency map into a vector of pairs (`freqVec`), where each pair consists of a frequency and a character. We then sort this vector in descending order based on frequency.
3. **Assigning Characters**: We calculate the minimum pushes required to type the word. We start with a push count of 1 and increase it whenever the current key size reaches its limit (3 characters per key on average, although this can vary as per optimization).

<h3> Complexity </h3>

- **Time Complexity**: \(O(n + k \log k)\), where \(n\) is the length of the word, and \(k\) is the number of unique characters. Counting frequencies takes \(O(n)\), and sorting the unique characters takes \(O(k \log k)\).
- **Space Complexity**: \(O(k)\), for storing the frequency map and the sorted vector.

This solution efficiently finds the minimum number of key pushes needed by leveraging the frequency of characters and strategically assigning them to keys to minimize the push count.

---
It makes wrong answer..

Thank you for the clarification. Considering that we can only use keys 2 to 9 (8 keys in total), let's adjust our approach accordingly:

1. **Frequency Calculation**: Count the frequency of each character in the word.
2. **Sort Frequencies**: Sort the characters by their frequencies in descending order.
3. **Distribute Characters to Keys**: We have 8 keys, each key can have multiple characters. We will assign characters to the keys ensuring the total number of presses is minimized.

Here’s how we can adjust our solution:

```cpp
// 114ms, 29.36MB
class Solution {
public:
    int minimumPushes(string word) {
        // Step 1: Count frequency of each character in the word
        unordered_map<char, int> freq;
        for (char ch : word) {
            freq[ch]++;
        }

        // Step 2: Create a vector of frequencies
        vector<int> frequencies;
        for (auto& entry : freq) {
            frequencies.push_back(entry.second);
        }

        // Step 3: Sort frequencies in descending order
        sort(frequencies.rbegin(), frequencies.rend());

        // Step 4: Calculate the minimum number of pushes
        int totalPushes = 0;
        int position = 0; // Tracks the current position within a key
        int keyPresses = 1; // The number of presses needed for current position

        for (int i = 0; i < frequencies.size(); ++i) {
            totalPushes += frequencies[i] * keyPresses;
            position++;
            if (position == 8) { // Move to the next set of key presses after 8 positions
                keyPresses++;
                position = 0;
            }
        }

        return totalPushes;
    }
};
```

<h3> Explanation </h3>

1. **Frequency Calculation**: We count the frequency of each character in the word.
2. **Sort Frequencies**: We sort the frequencies in descending order.
3. **Allocate Characters to Keys**: We iterate through the sorted frequencies and calculate the total presses required. Each group of 8 characters increases the key presses by 1. This is because we have 8 keys, and we need to cycle through them.

<h3> Complexity </h3>

- **Time Complexity**: $O(n + k \log k)$, where $n$ is the length of the word, and $k$ is the number of unique characters. Counting frequencies takes $O(n)$, and sorting the frequencies takes $O(k \log k)$.
- **Space Complexity**: $O(k)$, for storing the frequency map and the sorted frequencies.

This approach ensures that the total number of key presses is minimized by optimally assigning the most frequent characters to positions requiring the fewest presses.

## 24.08.07 - 273. Integer to English Words
[문제 링크](https://leetcode.com/problems/integer-to-english-words/description/)

그냥 gpt한테 바로 풀어달라고 했다..

### gpt
Sure! Let's walk through the problem "Integer to English Words" on LeetCode. This problem requires converting a non-negative integer into its English words representation.

<h3> Problem Description </h3>

Given an integer `num`, convert it to its English words representation. For example:

- Input: `123`
- Output: `"One Hundred Twenty Three"`

<h3> Steps to Solve the Problem </h3>

1. **Define English Words for Numbers**:
    - Define arrays or vectors for the English words of the numbers less than 20, tens multiples, and large numbers like "Thousand", "Million", etc.

2. **Break Down the Problem**:
    - Split the number into segments of three digits (e.g., thousands, millions).
    - Convert each segment to words and then combine them appropriately.

3. **Helper Functions**:
    - Create helper functions to convert numbers less than 1000 to words.
    - Use recursion or iteration to process each segment.

Here's the detailed solution in C++:

```cpp
class Solution {
public:
    std::string numberToWords(int num) {
        if (num == 0) return "Zero";
        
        // Define the English words for the numbers
        std::vector<std::string> below_20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        std::vector<std::string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        std::vector<std::string> thousands = {"", "Thousand", "Million", "Billion"};
        
        // Main function that processes each segment
        std::string result;
        int i = 0;
        while (num > 0) {
            if (num % 1000 != 0) {
                result = helper(num % 1000) + thousands[i] + (result.empty() ? "" : " " + result);
            }
            num /= 1000;
            i++;
        }
        
        return result;
    }
    
    // Helper function to process numbers less than 1000
    std::string helper(int num) {
        std::vector<std::string> below_20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        std::vector<std::string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        
        if (num == 0) return "";
        else if (num < 20) return below_20[num] + " ";
        else if (num < 100) return tens[num / 10] + " " + helper(num % 10);
        else return below_20[num / 100] + " Hundred " + helper(num % 100);
    }
};
```

<h3> Explanation </h3>

1. **Number Definitions**:
    - `below_20` array stores English words for numbers from 0 to 19.
    - `tens` array stores English words for multiples of ten from 20 to 90.
    - `thousands` array stores English words for large numbers like "Thousand", "Million", and "Billion".

2. **Main Function (`numberToWords`)**:
    - Iterates through the number, processing it in segments of three digits.
    - Converts each segment to words using the `helper` function.
    - Combines these segments with appropriate thousand, million, billion labels.

3. **Helper Function (`helper`)**:
    - Converts numbers less than 1000 to words.
    - Uses recursion to break down the number further into manageable parts.
    - Handles numbers below 20, numbers between 20 and 99, and numbers 100 and above separately.

This approach ensures that each part of the number is correctly converted to its English words representation and then combined to form the final result.

맨 마지막 문자에 공백이 들어가서 해당 부분만 추가했다.

```cpp
// 7ms, 13.47MB
class Solution {
public:
    std::string numberToWords(int num) {
        if (num == 0) return "Zero";
        
        // Define the English words for the numbers
        std::vector<std::string> below_20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        std::vector<std::string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        std::vector<std::string> thousands = {"", "Thousand", "Million", "Billion"};
        
        // Main function that processes each segment
        std::string result;
        int i = 0;
        while (num > 0) {
            if (num % 1000 != 0) {
                result = helper(num % 1000) + thousands[i] + (result.empty() ? "" : " " + result);
            }
            num /= 1000;
            i++;
        }
        
        if(result.back() == ' ') result.pop_back();
        return result;
    }
    
    // Helper function to process numbers less than 1000
    std::string helper(int num) {
        std::vector<std::string> below_20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        std::vector<std::string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        
        if (num == 0) return "";
        else if (num < 20) return below_20[num] + " ";
        else if (num < 100) return tens[num / 10] + " " + helper(num % 10);
        else return below_20[num / 100] + " Hundred " + helper(num % 100);
    }
};
```

`vector`는 미리 만들어놓고 공유해서 사용할 수 있을 것 같아서 그렇게 하기로 했다.

```cpp
// 2ms, 12.11MB
class Solution {
public:
    // Define the English words for the numbers
    std::vector<std::string> below_20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    std::vector<std::string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    std::vector<std::string> thousands = {"", "Thousand", "Million", "Billion"};

    std::string numberToWords(int num) {
        if (num == 0) return "Zero";

        // Main function that processes each segment
        std::string result;
        int i = 0;
        while (num > 0) {
            if (num % 1000 != 0) {
                result = helper(num % 1000) + thousands[i] + (result.empty() ? "" : " " + result);
            }
            num /= 1000;
            i++;
        }
        
        if(result.back() == ' ') result.pop_back();
        return result;
    }
    
    // Helper function to process numbers less than 1000
    std::string helper(int num) {
        if (num == 0) return "";
        else if (num < 20) return below_20[num] + " ";
        else if (num < 100) return tens[num / 10] + " " + helper(num % 10);
        else return below_20[num / 100] + " Hundred " + helper(num % 100);
    }
};
```

