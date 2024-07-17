## ToC
- [July Week 3](#july-week-3)
  - [24.07.15 - 2196. Create Binary Tree From Descriptions](#240715---2196-create-binary-tree-from-descriptions)
    - [나](#나)
    - [gpt](#gpt)
  - [24.07.16 - 2096. Step-By-Step Directions From a Binary Tree Node to Another](#240716---2096-step-by-step-directions-from-a-binary-tree-node-to-another)
    - [나](#나-1)
      - [heap-use-after-free ~](#heap-use-after-free-)
      - [Memory Limit Exceeded](#memory-limit-exceeded)
      - [Memory Limit Exceeded](#memory-limit-exceeded-1)
      - [Accepted](#accepted)
    - [gpt](#gpt-1)
  - [24.07.17 - 1110. Delete Nodes And Return Forest](#240717---1110-delete-nodes-and-return-forest)
    - [나](#나-2)
    - [gpt](#gpt-2)

# July Week 3

## 24.07.15 - 2196. Create Binary Tree From Descriptions
[문제 링크](https://leetcode.com/problems/create-binary-tree-from-descriptions/description/?envType=daily-question&envId=2024-07-15)

### 나
```cpp
// 705ms, 231.82MB
class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        TreeNode nodes[200'010]{};
        set<int> rootCandidate;
        int rootVisited[200'010]{};

        for (auto& descript : descriptions) {
			auto [parent, child, isLeft] = make_tuple(descript[0], descript[1], descript[2]);
            if(rootVisited[parent] == 0) rootCandidate.emplace(parent); // 아직 안 나온 노드
            rootVisited[child] = 1;
			if (rootCandidate.count(child) == 1) { // 이미 있는 노드
				rootCandidate.erase(child);
			}
            
			nodes[parent].val = parent;
            nodes[child].val = child;
			if (isLeft) {
				nodes[parent].left = &nodes[child];
			}
			else {
				nodes[parent].right = &nodes[child];
			}
		}
        int rootIndex = *begin(rootCandidate);
        return &nodes[rootIndex];
    }
};
```
- 이 문제는
  - Output을 내가 만드는 게 아니다.
  - TreeNode는 이미 정의되어 있으므로 재정의할 필요 없음
- 루트를 찾기 위해 `rootVisited` 도입
  - 앞에 나온 루트 정보 반영을 위해 `rootVisited`가 필요함.
- 문제에는 node index가 10만(10^5)이라고 나와 있어서 `100'010`으로 잡았는데, 메모리 out of bounds 에러가 나와서 `200'010`으로 메모리를 늘렸더니 해결됨.

### gpt
Let's solve the problem "Create Binary Tree from Descriptions" from LeetCode.

<h3> Problem Description </h3>

You are given a list of `descriptions` where `descriptions[i] = [parenti, childi, isLefti]` indicates that `parenti` is the parent of `childi` in a binary tree, and `isLefti` is `1` if `childi` is the left child of `parenti`, otherwise `0`.

Your task is to construct the binary tree and return its root.

<h3> Solution </h3>

To solve this, we can follow these steps:

1. **Create Nodes:** For each `parent` and `child`, create a node if it doesn't exist.
2. **Assign Children:** For each description, assign the child to the corresponding left or right position of the parent.
3. **Identify the Root:** The root is the only node that is never a child.

Here’s the implementation in C++:

```cpp
// 688ms, 276.24MB
class Solution {
public:
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, TreeNode*> nodes;
        unordered_set<int> children;
        
        // Step 1: Create nodes and map parent-child relationships
        for (const auto& desc : descriptions) {
            int parentVal = desc[0];
            int childVal = desc[1];
            bool isLeft = desc[2];

            // Ensure the parent node exists
            if (nodes.find(parentVal) == nodes.end()) {
                nodes[parentVal] = new TreeNode(parentVal);
            }
            
            // Ensure the child node exists
            if (nodes.find(childVal) == nodes.end()) {
                nodes[childVal] = new TreeNode(childVal);
            }
            
            // Assign the child to the left or right of the parent
            if (isLeft) {
                nodes[parentVal]->left = nodes[childVal];
            } else {
                nodes[parentVal]->right = nodes[childVal];
            }

            // Mark this node as a child
            children.insert(childVal);
        }

        // Step 2: Identify the root (a node that is never a child)
        for (const auto& desc : descriptions) {
            if (children.find(desc[0]) == children.end()) {
                return nodes[desc[0]];
            }
        }

        return nullptr; // Just in case, though there should always be a root
    }
};
```

<h3> Explanation </h3>

1. **Creating Nodes and Mapping Relations:**
   - We use a map to store nodes, ensuring each node is created only once.
   - For each description, we create parent and child nodes if they don't already exist, and then link them appropriately as left or right children.

2. **Identifying the Root:**
   - A node that is never listed as a child in any description is the root.
   - We use an unordered set to keep track of all child nodes.
   - Finally, we check which parent node is not in the child set to determine the root.

This solution efficiently constructs the binary tree and identifies the root in a clear and straightforward manner.

## 24.07.16 - 2096. Step-By-Step Directions From a Binary Tree Node to Another
### 나
#### heap-use-after-free ~
```cpp
class Solution {
public:

    struct Data {
        string str;
        TreeNode* ptr = nullptr;
        Data() = default;
        Data(string str, TreeNode* ptr) : str{str}, ptr{ptr} {}
    };

    string getPath(TreeNode* root, int dest) {
        queue<Data> q;
        q.emplace("", root);
        while(!q.empty()) {
            auto& [str, ptr] = q.front(); q.pop();
            if(ptr->val == dest) return str;

            if(ptr->left != nullptr) {
                q.emplace(str + "L", ptr->left);
            }
            if(ptr->right != nullptr) {
                q.emplace(str + "R", ptr->right);
            }
        }
        return ""; // 도달하지 못하는 경우는 없음.
    }

    string getDirections(TreeNode* root, int startValue, int destValue) {
        string rootToStart = getPath(root, startValue);
        string rootToDest = getPath(root, destValue);
        int i=0, minLen = min(rootToStart.length(), rootToDest.length());
        TreeNode* commonAncestor = root; // 공통 조상
        for(;i<minLen;++i) {
            if(rootToStart[i] != rootToDest[i]) {
                break;
            }
            if(rootToStart[i] == 'L') root = root->left;
            else root = root->right;
        }
        string answer(rootToStart.length() - i, 'U'); // 개수만큼 위로 올라가야 함
        answer += rootToDest.substr(i); // 아래로 이동
        return answer;
    }
};
```
Runtime Error.

Error Message
```arduino
Line 30: Char 16:
=================================================================
==21==ERROR: AddressSanitizer: heap-use-after-free on address 0x5150000045d8 at pc 0x55fa139dc2b3 bp 0x7ffe267e0df0 sp 0x7ffe267e0de8
READ of size 8 at 0x5150000045d8 thread T0
    #0 0x55fa139dc2b2 in Solution::getPath[abi:cxx11](TreeNode*, int) solution.cpp:30:16
    #1 0x55fa139db35d in Solution::getDirections[abi:cxx11](TreeNode*, int, int) solution.cpp:30:29
    #2 0x55fa139dad56 in __helper__ solution.cpp:30:31
    #3 0x55fa139dad56 in main solution.cpp:30:43
    #4 0x7f1591e79d8f  (/lib/x86_64-linux-gnu/libc.so.6+0x29d8f) (BuildId: 490fef8403240c91833978d494d39e537409b92e)
    #5 0x7f1591e79e3f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x29e3f) (BuildId: 490fef8403240c91833978d494d39e537409b92e)
    #6 0x55fa13909e34 in _start (solution+0xb2e34)
0x5150000045d8 is located 472 bytes inside of 480-byte region [0x515000004400,0x5150000045e0)
freed by thread T0 here:
    #0 0x55fa139d8f2d in operator delete(void*) /root/llvm-project/compiler-rt/lib/asan/asan_new_delete.cpp:152:3
    #1 0x55fa139de4fc in deallocate /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/new_allocator.h:168:2
    #2 0x55fa139de4fc in deallocate /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/allocator.h:210:25
    #3 0x55fa139de4fc in deallocate /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/alloc_traits.h:516:13
    #4 0x55fa139de4fc in _M_deallocate_node /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/stl_deque.h:590:2
    #5 0x55fa139de4fc in std::deque<Solution::Data, std::allocator<Solution::Data>>::_M_pop_front_aux() /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/deque.tcc:581:7
    #6 0x55fa139dbc59 in pop /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/stl_queue.h:321:4
    #7 0x55fa139dbc59 in Solution::getPath[abi:cxx11](TreeNode*, int) solution.cpp:30:45
    #8 0x55fa139db35d in Solution::getDirections[abi:cxx11](TreeNode*, int, int) solution.cpp:30:29
    #9 0x55fa139dad56 in __helper__ solution.cpp:30:31
    #10 0x55fa139dad56 in main solution.cpp:30:43
    #11 0x7f1591e79d8f  (/lib/x86_64-linux-gnu/libc.so.6+0x29d8f) (BuildId: 490fef8403240c91833978d494d39e537409b92e)
previously allocated by thread T0 here:
    #0 0x55fa139d86cd in operator new(unsigned long) /root/llvm-project/compiler-rt/lib/asan/asan_new_delete.cpp:95:3
    #1 0x55fa139dcb59 in allocate /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/new_allocator.h:147:27
    #2 0x55fa139dcb59 in allocate /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/allocator.h:198:32
    #3 0x55fa139dcb59 in allocate /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/alloc_traits.h:482:20
    #4 0x55fa139dcb59 in _M_allocate_node /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/stl_deque.h:583:9
    #5 0x55fa139dcb59 in std::_Deque_base<Solution::Data, std::allocator<Solution::Data>>::_M_create_nodes(Solution::Data**, Solution::Data**) /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/stl_deque.h:684:21
    #6 0x55fa139dc7cd in std::_Deque_base<Solution::Data, std::allocator<Solution::Data>>::_M_initialize_map(unsigned long) /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/stl_deque.h:658:4
    #7 0x55fa139dbb74 in _Deque_base /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/stl_deque.h:460:9
    #8 0x55fa139dbb74 in deque /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/stl_deque.h:855:7
    #9 0x55fa139dbb74 in queue<std::deque<Solution::Data, std::allocator<Solution::Data> >, void> /usr/bin/../lib/gcc/x86_64-linux-gnu/13/../../../../include/c++/13/bits/stl_queue.h:167:4
    #10 0x55fa139dbb74 in Solution::getPath[abi:cxx11](TreeNode*, int) solution.cpp:30:21
    #11 0x55fa139db35d in Solution::getDirections[abi:cxx11](TreeNode*, int, int) solution.cpp:30:29
    #12 0x55fa139dad56 in __helper__ solution.cpp:30:31
    #13 0x55fa139dad56 in main solution.cpp:30:43
    #14 0x7f1591e79d8f  (/lib/x86_64-linux-gnu/libc.so.6+0x29d8f) (BuildId: 490fef8403240c91833978d494d39e537409b92e)
SUMMARY: AddressSanitizer: heap-use-after-free solution.cpp:30:16 in Solution::getPath[abi:cxx11](TreeNode*, int)
Shadow bytes around the buggy address:
  0x515000004300: fd fd fd fd fd fd fd fd fd fd fd fd fa fa fa fa
  0x515000004380: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x515000004400: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x515000004480: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x515000004500: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
=>0x515000004580: fd fd fd fd fd fd fd fd fd fd fd[fd]fa fa fa fa
  0x515000004600: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x515000004680: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x515000004700: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x515000004780: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x515000004800: 00 00 00 00 00 00 00 00 00 00 00 00 fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==21==ABORTING
```
뭔 소린지 chatgpt한테 물어봤다.

이 메시지는 AddressSanitizer (ASan)로부터의 오류 보고서로, 프로그램에서 발생한 `heap-use-after-free` 오류를 알려줍니다. 이는 프로그램이 이미 해제된 메모리를 사용하려고 할 때 발생하는 심각한 메모리 오류입니다. 보고서의 주요 내용을 설명해드리겠습니다.

<h3> 핵심 오류 메시지 </h3>

```
==21==ERROR: AddressSanitizer: heap-use-after-free on address 0x5150000045d8 at pc 0x55fa139dc2b3 bp 0x7ffe267e0df0 sp 0x7ffe267e0de8
READ of size 8 at 0x5150000045d8 thread T0
    #0 0x55fa139dc2b2 in Solution::getPath[abi:cxx11](TreeNode*, int) solution.cpp:30:16
```

이 부분에서 프로그램이 이미 해제된 주소 `0x5150000045d8`를 읽으려고 했음을 알려줍니다. `Solution::getPath` 함수에서 발생했으며, 구체적인 위치는 `solution.cpp` 파일의 30번째 줄 16번째 문자입니다.

<h3> 주요 호출 스택 </h3>

```
    #0 0x55fa139dc2b2 in Solution::getPath[abi:cxx11](TreeNode*, int) solution.cpp:30:16
    #1 0x55fa139db35d in Solution::getDirections[abi:cxx11](TreeNode*, int, int) solution.cpp:30:29
    #2 0x55fa139dad56 in __helper__ solution.cpp:30:31
    #3 0x55fa139dad56 in main solution.cpp:30:43
```

오류가 발생한 함수의 호출 스택을 보여줍니다. `getPath` 함수가 `getDirections` 함수에서 호출되었고, 그 다음에 `__helper__`와 `main` 함수로 이어집니다.

<h3> 메모리 상태 </h3>

```
0x5150000045d8 is located 472 bytes inside of 480-byte region [0x515000004400,0x5150000045e0)
freed by thread T0 here:
    #0 0x55fa139d8f2d in operator delete(void*) /root/llvm-project/compiler-rt/lib/asan/asan_new_delete.cpp:152:3
```

주소 `0x5150000045d8`는 480바이트 영역 안에 위치하며, `operator delete` 함수에 의해 해제되었습니다.

<h3> 이전 할당 위치 </h3>

```
previously allocated by thread T0 here:
    #0 0x55fa139d86cd in operator new(unsigned long) /root/llvm-project/compiler-rt/lib/asan/asan_new_delete.cpp:95:3
```

이 메모리는 `operator new` 함수에 의해 할당되었습니다.

<h3> 해결 방법 </h3>

`heap-use-after-free` 오류를 해결하려면 다음 단계를 따르세요:

1. **해제된 메모리 접근 확인**: 해제된 메모리를 사용하려고 하는 위치를 찾으세요. 이 경우 `getPath` 함수에서 발생했습니다.

2. **메모리 해제 타이밍 점검**: 메모리를 해제하는 코드와 사용하려는 코드의 타이밍을 점검하세요. 메모리가 해제된 후에 접근하려는 경우를 방지해야 합니다.

3. **스마트 포인터 사용**: 수동으로 메모리를 관리하는 대신 C++의 스마트 포인터(`std::unique_ptr`, `std::shared_ptr` 등)를 사용하여 자동으로 메모리가 관리되도록 하세요.

코드를 확인하고, 문제가 발생한 위치에서 해제된 메모리를 접근하지 않도록 조치하세요. 필요시 코드를 공유해주시면 더 구체적인 도움을 드릴 수 있습니다.

생각해보니, 
```cpp
while(!q.empty()) {
    auto& [str, ptr] = q.front(); q.pop();
    if(ptr->val == dest) return str;
    ...
```
참조로 q에서 가져오고 pop했으니.. 당연히 에러가 난다.

코드 수정~

#### Memory Limit Exceeded
```cpp
class Solution {
public:

    struct Data {
        string str;
        TreeNode* ptr = nullptr;
        Data() = default;
        Data(string str, TreeNode* ptr) : str{str}, ptr{ptr} {}
    };

    string getPath(TreeNode* root, int dest) {
        queue<Data> q;
        q.emplace("", root);
        while(!q.empty()) {
            auto [str, ptr] = q.front(); q.pop();
            if(ptr->val == dest) return str;

            if(ptr->left != nullptr) {
                q.emplace(str + "L", ptr->left);
            }
            if(ptr->right != nullptr) {
                q.emplace(str + "R", ptr->right);
            }
        }
        return ""; // 도달하지 못하는 경우는 없음.
    }

    string getDirections(TreeNode* root, int startValue, int destValue) {
        string rootToStart = getPath(root, startValue);
        string rootToDest = getPath(root, destValue);
        int i=0, minLen = min(rootToStart.length(), rootToDest.length());
        TreeNode* commonAncestor = root; // 공통 조상
        for(;i<minLen;++i) {
            if(rootToStart[i] != rootToDest[i]) {
                break;
            }
            if(rootToStart[i] == 'L') root = root->left;
            else root = root->right;
        }
        string answer(rootToStart.length() - i, 'U'); // 개수만큼 위로 올라가야 함
        answer += rootToDest.substr(i); // 아래로 이동
        return answer;
    }
};
```
머지 Queue에 길이가 긴 스트링이 많이 들어 가서 메모리 초과가 나나?라고 생각해서, 재귀로 구현

#### Memory Limit Exceeded
```cpp
class Solution {
public:
    bool isReach;
    string finalPath;
    void getPath(TreeNode* now, int dest, string path) {
        if(now->val == dest) {
            finalPath = path;
            isReach = true;
        }
        if(isReach) {
            return;
        }
        if(now->left != nullptr) {
            getPath(now->left, dest, path+'L');
            
        }
        if(now->right != nullptr) {
            getPath(now->right, dest, path+'R');
        }
    }

    string getDirections(TreeNode* root, int startValue, int destValue) {
        isReach = false, finalPath = "";
        getPath(root, startValue, "");
        string rootToStart = finalPath;

        isReach = false, finalPath = "";
        getPath(root, destValue, "");
        string rootToDest = finalPath;
        int i=0, minLen = min(rootToStart.length(), rootToDest.length());
        TreeNode* commonAncestor = root; // 공통 조상
        for(;i<minLen;++i) {
            if(rootToStart[i] != rootToDest[i]) {
                break;
            }
            if(rootToStart[i] == 'L') root = root->left;
            else root = root->right;
        }
        string answer(rootToStart.length() - i, 'U'); // 개수만큼 위로 올라가야 함
        answer += rootToDest.substr(i); // 아래로 이동
        return answer;
    }
};
```
역시나 메모리 초과..

재귀로 던질 때 `string`을 값으로 복사하게 두지 말고, 참조를 사용하자.

#### Accepted
```cpp
// 141ms, 119MB
class Solution {
public:
    bool isReach;
    string finalPath;
    void getPath(TreeNode* now, int dest, string& path) {
        if(now->val == dest) {
            finalPath = path;
            isReach = true;
        }
        if(isReach) {
            return;
        }
        if(now->left != nullptr) {
            path.push_back('L');
            getPath(now->left, dest, path);
            path.pop_back();
        }
        if(now->right != nullptr) {
            path.push_back('R');
            getPath(now->right, dest, path);
            path.pop_back();
        }
    }

    string getDirections(TreeNode* root, int startValue, int destValue) {
        string path, rootToStart, rootToDest;
        isReach = false;
        getPath(root, startValue, path);
        rootToStart = finalPath;

        isReach = false;
        getPath(root, destValue, path);
        rootToDest = finalPath;
        
        int i=0, minLen = min(rootToStart.length(), rootToDest.length());
        TreeNode* commonAncestor = root; // 공통 조상
        for(;i<minLen;++i) {
            if(rootToStart[i] != rootToDest[i]) {
                break;
            }
            if(rootToStart[i] == 'L') root = root->left;
            else root = root->right;
        }
        string answer(rootToStart.length() - i, 'U'); // 개수만큼 위로 올라가야 함
        answer += rootToDest.substr(i); // 아래로 이동
        return answer;
    }
};
```
![alt text](image.png)
- 버저비터 성공했다..

### gpt
To solve the LeetCode problem "Step-By-Step Directions From a Binary Tree Node to Another," you need to provide the shortest path from one node to another in a binary tree. Here's a detailed explanation and an example solution.

<h3> Problem Overview </h3>

You are given a binary tree, where each node has a unique value. You are also given the values of two nodes, `startValue` and `destValue`. The task is to return the directions from the node with `startValue` to the node with `destValue`. Directions are represented by 'L' (left), 'R' (right), and 'U' (up).

<h3> Steps to Solve the Problem </h3>

1. **Find Paths from Root to the Target Nodes**: First, find the path from the root to both the `startValue` and `destValue` nodes.
2. **Find the Lowest Common Ancestor (LCA)**: Determine the lowest common ancestor of the two nodes.
3. **Construct the Directions**: Construct the path from the `startValue` node to the LCA, and then from the LCA to the `destValue` node. This involves moving 'U' (up) to reach the LCA and then moving 'L' or 'R' as needed to reach the `destValue`.

<h3> Example Solution in C++ </h3>

Here's an example implementation in C++:

```cpp
// 164ms, 119.86MB
class Solution {
public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        string pathToStart, pathToDest;
        
        // Find paths from the root to the start and destination nodes
        findPath(root, startValue, pathToStart);
        findPath(root, destValue, pathToDest);
        
        // Find the first differing index
        int i = 0;
        while (i < pathToStart.size() && i < pathToDest.size() && pathToStart[i] == pathToDest[i]) {
            i++;
        }
        
        // Number of steps up to the common ancestor
        string upMoves(pathToStart.size() - i, 'U');
        
        // Remaining steps to the destination node
        string downMoves = pathToDest.substr(i);
        
        return upMoves + downMoves;
    }
    
private:
    bool findPath(TreeNode* root, int value, string &path) {
        if (!root) return false;
        if (root->val == value) return true;
        
        path.push_back('L');
        if (findPath(root->left, value, path)) return true;
        path.pop_back();
        
        path.push_back('R');
        if (findPath(root->right, value, path)) return true;
        path.pop_back();
        
        return false;
    }
};
```
> [!NOTE]
> 고민이 있었는데, 나도 위의 코드처럼 지역변수 참조로 던져서 해당 지역변수에 바로 값을 받아오면 좋을 것 같다고 생각했다.
> 
> `if`문 안에서 함수 호출을 해서 가져오면 되더라..!!!


<h3> Explanation </h3>

1. **Path Finding**: The `findPath` function recursively finds the path from the root to the given node value. It returns `true` if the node is found and `false` otherwise. The path is stored in a string, where 'L' denotes moving left and 'R' denotes moving right.
2. **Direction Construction**: In the `getDirections` function, the paths from the root to both the `startValue` and `destValue` are found. The common prefix of these paths is identified, which represents the path to the lowest common ancestor (LCA). The path from the `startValue` to the LCA is constructed using 'U' (up) moves, and then the remaining path to the `destValue` is appended.

This approach ensures that the directions are accurately computed from `startValue` to `destValue`, navigating through the LCA as needed.

## 24.07.17 - 1110. Delete Nodes And Return Forest
### 나
```cpp
// 16ms, 27.2MB
class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        vector<TreeNode*> ret;

        sort(begin(to_delete), end(to_delete));
        if(!binary_search(begin(to_delete), end(to_delete), root->val)) {
            ret.emplace_back(root);
        }

        queue<TreeNode*> q; q.emplace(root); 
        while(!q.empty()) {
            auto now = q.front(); q.pop(); 
            auto result = binary_search(begin(to_delete), end(to_delete), now->val);
            if(now->left!=nullptr) {
                q.emplace(now->left);
                if(result) { // now를 지워야하는 경우 다음 노드는 루트가 될 가능성이 있다.
                    if(!binary_search(begin(to_delete), end(to_delete), now->left->val)) {
                        ret.emplace_back(now->left);
                    }
                }
                else { // now는 남아있지만, 다음 노드를 지워야 한다면
                    if(binary_search(begin(to_delete), end(to_delete), now->left->val)) {
                        now->left = nullptr; // 연결 끊기
                    }
                }
            }
            if(now->right!=nullptr) {
                q.emplace(now->right);
                if(result) { // now를 지워야하는 경우 다음 노드는 루트가 될 가능성이 있다.
                    if(!binary_search(begin(to_delete), end(to_delete), now->right->val)) {
                        ret.emplace_back(now->right);
                    }
                }
                else { // now는 남아있지만, 다음 노드를 지워야 한다면
                    if(binary_search(begin(to_delete), end(to_delete), now->right->val)) {
                        now->right = nullptr; // 연결 끊기
                    }
                }
            }
        }

        return ret;
    }
};
```
- 내가 제거되어야 할 정점이면 다음 정점은 루트 가능성이 있다.
- 내가 제거되어야 할 정점이 아닐 때 다음 정점이 제거되어야 할 정점이면 연결을 끊어야 한다.

### gpt
Hello! The LeetCode problem "Delete Nodes And Return Forest" is an interesting problem that involves tree manipulation. Let’s walk through the problem and some potential strategies for solving it using C++.

<h3> Problem Description </h3>

You are given the root of a binary tree and a list of node values `to_delete`. You need to delete the nodes with the given values and return the forest (a collection of disjoint trees) that remains after deletion.

<h3> Approach to Solution </h3>

1. **Depth-First Search (DFS)**: We can traverse the tree using DFS. During the traversal, if we encounter a node that needs to be deleted, we detach it from its parent and recursively process its children.
2. **Handling Deletion**: For each node to be deleted, its children (if any) become the roots of new trees in the forest.
3. **Tracking the Roots of the New Forest**: Use a list to keep track of the new roots formed after deletions.

<h3> Detailed Steps </h3>

1. **Convert `to_delete` to a Set**: This allows for O(1) average-time complexity checks for whether a node should be deleted.
2. **DFS Traversal**: Traverse the tree while handling deletions. For each node:
   - If it needs to be deleted, its children are added to the forest.
   - If it does not need to be deleted, it may become part of the resulting forest if its parent was deleted.
3. **Edge Cases**: Handle the case where the root itself needs to be deleted.

Here's a C++ implementation that follows the above approach:

```cpp
// 14ms, 27.34MB
class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        unordered_set<int> to_delete_set(to_delete.begin(), to_delete.end());
        vector<TreeNode*> forest;
        
        root = dfs(root, to_delete_set, forest);
        
        // If root is not deleted, add it to the forest
        if (root) {
            forest.push_back(root);
        }
        
        return forest;
    }
    
private:
    TreeNode* dfs(TreeNode* node, unordered_set<int>& to_delete_set, vector<TreeNode*>& forest) {
        if (!node) return nullptr;
        
        node->left = dfs(node->left, to_delete_set, forest);
        node->right = dfs(node->right, to_delete_set, forest);
        
        // If this node needs to be deleted
        if (to_delete_set.count(node->val)) {
            if (node->left) forest.push_back(node->left);
            if (node->right) forest.push_back(node->right);
            delete node; // Free the memory (if needed, depending on the environment)
            return nullptr; // Return null to parent to disconnect
        }
        
        return node;
    }
};
```

> 와 이게 leaf부터 계산해서, 내가 작성한 코드의 경우 상위에서 지우고 하위에서 지워지는 경우를 여러 번 계산했어야 했는데, 훨씬 더 간단하게 된다..!!

<h3> Explanation </h3>

- **TreeNode Structure**: Defines the tree node structure.
- **Solution Class**: Implements the `delNodes` function which takes the root of the tree and a list of node values to delete.
- **dfs Function**: Performs the DFS traversal. It returns the modified subtree root after deletions.
- **Memory Management**: Deleting a node involves freeing its memory if needed, depending on the environment.

<h3> Key Points </h3>

- **Efficiency**: The algorithm runs in O(n) time complexity, where n is the number of nodes in the tree, since each node is visited once.
- **Usage of Unordered Set**: Ensures fast look-up times for deletions.
- **Handling Null Nodes**: Properly handles leaf nodes and subtrees.

