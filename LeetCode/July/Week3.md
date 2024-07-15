## ToC
- [July Week 3](#july-week-3)
  - [24.07.15 - 2196. Create Binary Tree From Descriptions](#240715---2196-create-binary-tree-from-descriptions)
    - [나](#나)
    - [gpt](#gpt)

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

