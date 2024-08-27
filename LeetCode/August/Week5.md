## ToC
- [August Week 5](#august-week-5)
  - [24.08.26 - 590. N-ary Tree Postorder Traversal](#240826---590-n-ary-tree-postorder-traversal)
    - [나](#나)
    - [gpt](#gpt)

# August Week 5
## 24.08.26 - 590. N-ary Tree Postorder Traversal
[문제 링크](https://leetcode.com/problems/n-ary-tree-postorder-traversal/description/?envType=daily-question&envId=2024-08-26)

### 나
```cpp
// 14ms, 15.2MB
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<int> postorder(Node* root) {
        if(root) MakePostOrder(root); // left - right - root
        return answer;
    }
private:
    vector<int> answer;
    void MakePostOrder(Node* now) {
        for(Node* next : now->children) {
            MakePostOrder(next);
        }
        answer.push_back(now->val);
    }
};
```

### gpt
The problem you've shared involves performing a postorder traversal on an N-ary tree. In an N-ary tree, each node can have any number of children. The goal is to return the postorder traversal of the tree's nodes' values.

<h3> Problem Summary </h3>

In postorder traversal, for each node, you:
1. Traverse all its children in order.
2. Visit the node itself after all its children have been visited.

Given the root of an N-ary tree, you need to return the postorder traversal of its nodes' values.

<h3> Solution </h3>

<h4> Recursive Approach </h4>

The recursive approach is straightforward and mirrors the definition of postorder traversal.

```cpp
// 9ms, 15.3MB
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    void postorder(Node* node, vector<int>& result) {
        if (node == nullptr) return;
        
        // Traverse all children
        for (Node* child : node->children) {
            postorder(child, result);
        }
        
        // Visit the node itself
        result.push_back(node->val);
    }
    
    vector<int> postorder(Node* root) {
        vector<int> result;
        postorder(root, result);
        return result;
    }
};
```

<h4> Iterative Approach (Using One Stack) </h4>

An iterative solution can be implemented using a stack. This approach can be a bit trickier since you need to manage the order in which nodes are processed.

```cpp
// 15ms, 15.3MB
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> result;
        if (root == nullptr) return result;
        
        stack<Node*> stack;
        stack.push(root);
        
        while (!stack.empty()) {
            Node* node = stack.top();
            stack.pop();
            result.push_back(node->val);
            
            // Push all children to the stack
            for (Node* child : node->children) {
                stack.push(child);
            }
        }
        
        // Since we traversed in reverse postorder, reverse the result to get the correct order
        reverse(result.begin(), result.end());
        return result;
    }
};
```

<h3> Explanation </h3>

1. **Recursive Approach**:
   - The `postorder` function recursively traverses all the children of the current node before adding the node's value to the result list.
   - This approach is simple and directly follows the definition of postorder traversal for an N-ary tree.

2. **Iterative Approach**:
   - A stack is used to simulate the postorder traversal.
   - Nodes are processed in a reverse order (node before children) and then reversed at the end to get the correct postorder sequence.
   - This approach is useful when dealing with deep trees where recursion might cause a stack overflow.

<h3> Time Complexity </h3>

Both approaches have a time complexity of $O(n)$, where `n` is the number of nodes in the tree, since each node is visited exactly once.

<h3> Space Complexity </h3>

- **Recursive Approach**: $O(h)$, where `h` is the height of the tree, due to the recursive call stack.
- **Iterative Approach**: $O(h)$, where `h` is the height of the tree, due to the stack used for traversal.

<h3> Final Note </h3>

The recursive approach is generally simpler and easier to understand, while the iterative approach might be necessary for very large trees where recursion could lead to a stack overflow. Both solutions should work correctly for the problem provided on LeetCode.

