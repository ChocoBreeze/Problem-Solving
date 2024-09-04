## ToC
- [August Week 5](#august-week-5)
  - [24.08.26 - 590. N-ary Tree Postorder Traversal](#240826---590-n-ary-tree-postorder-traversal)
    - [나](#나)
    - [gpt](#gpt)
  - [24.08.27 - 1514. Path with Maximum Probability](#240827---1514-path-with-maximum-probability)
    - [나](#나-1)
    - [해설](#해설)
  - [24.08.28 - 1905. Count Sub Islands](#240828---1905-count-sub-islands)
    - [나](#나-2)
    - [추후 답지 정리.](#추후-답지-정리)
      - [Approach 1: Breadth-First Search (BFS)](#approach-1-breadth-first-search-bfs)
      - [Approach 2: Depth-First Search](#approach-2-depth-first-search)
      - [Approach 3: Union-Find](#approach-3-union-find)
    - [gpt](#gpt-1)
  - [24.08.29 - 947. Most Stones Removed with Same Row or Column](#240829---947-most-stones-removed-with-same-row-or-column)
    - [나](#나-3)
    - [추후 해설 참고](#추후-해설-참고)
      - [Approach 1: Depth First Search](#approach-1-depth-first-search)
      - [Approach 2: Disjoint Set Union](#approach-2-disjoint-set-union)
      - [Approach 3: Disjoint Set Union (Optimized)](#approach-3-disjoint-set-union-optimized)
    - [gpt](#gpt-2)
  - [24.08.30 - 2699. Modify Graph Edge Weights](#240830---2699-modify-graph-edge-weights)
    - [나](#나-4)
    - [해설](#해설-1)
      - [Approach 1: Traditional Dijkstra's algorithm](#approach-1-traditional-dijkstras-algorithm)
      - [Approach 2: Dijkstra's Algorithm with Min-Heap](#approach-2-dijkstras-algorithm-with-min-heap)
  - [24.08.31 - 1514. Path with Maximum Probability](#240831---1514-path-with-maximum-probability)

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

## 24.08.27 - 1514. Path with Maximum Probability
[문제 링크](https://leetcode.com/problems/path-with-maximum-probability/description/?envType=daily-question&envId=2024-08-27)

### 나
```cpp
// 271ms, 74.09MB
using pid = pair<int, double>;
class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        // undirected weighted graph
        vector<vector<GraphData>> graph(n);

        for(int s{}, e{static_cast<int>(edges.size())}; s<e; ++s) {
            int from = edges[s][0], to = edges[s][1];
            double prob = succProb[s];
            graph[from].emplace_back(to, prob);
            graph[to].emplace_back(from, prob);
        }

        // dijkstra
        priority_queue<pid> pq; // {node, probability}
        vector<double> dist(n, 0);
        pq.emplace(start_node, 1); 
        dist[start_node] = 1;

        while(!pq.empty()) {
            auto [now, nowProb] = pq.top(); pq.pop();
            if(dist[now] != nowProb) continue;
            for(auto [to, prob] : graph[now]) {
                double nextProb = nowProb * prob;
                if(nextProb > dist[to]) {
                    dist[to] = nextProb;
                    pq.emplace(to, nextProb);
                }
            }
        }

        return dist[end_node];
    }
private:
    struct GraphData {
        int to{};
        double prob{};
        GraphData() = default;
        GraphData(int to, double prob) : to{to}, prob{prob} {}
    };
};
```

### 해설
나중에 해설 읽고 정리하기. (gpt 질문하기.)
- [Approach 1: Bellman-Ford Algorithm](https://leetcode.com/problems/path-with-maximum-probability/editorial/?envType=daily-question&envId=2024-08-27#approach-1-bellman-ford-algorithm)
- [Approach 2: Shortest Path Faster Algorithm](https://leetcode.com/problems/path-with-maximum-probability/editorial/?envType=daily-question&envId=2024-08-27#approach-2-shortest-path-faster-algorithm)
- [Approach 3: Dijkstra's Algorithm](https://leetcode.com/problems/path-with-maximum-probability/editorial/?envType=daily-question&envId=2024-08-27#approach-3-dijkstras-algorithm)

## 24.08.28 - 1905. Count Sub Islands
[문제 링크](https://leetcode.com/problems/count-sub-islands/description/?envType=daily-question&envId=2024-08-28)

### 나
못 풀었다..
```cpp
// Memory Limit Exceeded
using pii = pair<int,int>;
class Solution {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        // 0: water, 1: land
        // island: a group of 1's connected 4-directionally (horizontal and vertical)
        // outside of the grid: water cells
        // An island in grid2 is considered a sub-island if there is an island in grid1 that contains all the cells that make up this island in grid2.

        int n = grid1.size(), m = grid1[0].size();
        vector island1(n, vector(m,0));
        int cnt{1};
        for(int i{};i<n;++i){
            for(int j{};j<m;++j) {
                if(grid1[i][j] && !island1[i][j]) {
                    queue<pii> q;
                    q.emplace(i,j);
                    island1[i][j] = cnt;
                    while(!q.empty()) {
                        auto [x, y] = q.front(); q.pop();

                        for(int d{};d<4;++d) {
                            int nx = x + "0211"[d] - '1', ny = y + "1102"[d] - '1';
                            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                            if(!grid1[nx][ny] || island1[nx][ny]) continue;
                            q.emplace(nx, ny);
                            island1[nx][ny] = cnt;
                        }
                    }
                }
                ++cnt;
            }
        }

        int answer{};
        vector island2(n, vector(m,0));
        for(int i{};i<n;++i){
            for(int j{};j<m;++j) {
                if(grid2[i][j] && island1[i][j] && !island2[i][j]) { 
                    auto ret = [&]() {
                        vector visited(n, vector(m,0));
                        queue<pii> q;
                        q.emplace(i,j);
                        int now = island1[i][j];
                        island2[i][j] = 1;
                        visited[i][j] = 1;
                        while(!q.empty()) {
                            auto [x, y] = q.front(); q.pop();

                            for(int d{};d<4;++d) {
                                int nx = x + "0211"[d] - '1', ny = y + "1102"[d] - '1';
                                if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                                if(!grid2[nx][ny] || visited[nx][ny]) continue;
                                if(now != island1[nx][ny]) {
                                    return false; // 다른 섬과 연결
                                }
                                q.emplace(nx, ny);
                                visited[nx][ny] = 1;
                                island2[nx][ny] = 1;
                            }
                        }
                        return true;
                    } ();
                    if(ret) ++answer;
                }
            }
        }

        return answer;
    }
};
```
너무 한 번에 하려고 했던 것 같다. (2번 각각 돌리고 나중에 한 번 더 확인하면 될 듯,)

### 추후 답지 정리.

#### Approach 1: Breadth-First Search (BFS)
[링크](https://leetcode.com/problems/count-sub-islands/editorial/?envType=daily-question&envId=2024-08-28#approach-1-breadth-first-search-bfs)

#### Approach 2: Depth-First Search
[링크](https://leetcode.com/problems/count-sub-islands/editorial/?envType=daily-question&envId=2024-08-28#approach-2-depth-first-search)

#### Approach 3: Union-Find
[링크](https://leetcode.com/problems/count-sub-islands/editorial/?envType=daily-question&envId=2024-08-28#approach-3-union-find)

### gpt

Certainly! The problem you're referring to is the "Count Sub Islands" problem on LeetCode. The challenge involves two grids, `grid1` and `grid2`, where we need to count the number of islands in `grid2` that are also "sub-islands" in `grid1`. A sub-island is an island in `grid2` that is completely surrounded by land (1s) in `grid1`.

<h3> Problem Breakdown </h3>

- **Grid1** and **Grid2** are binary matrices where `1` represents land and `0` represents water.
- An island is a group of connected 1s (connected horizontally or vertically).
- A sub-island in `grid2` means that all the land cells (1s) in this island are present in `grid1` as well.

<h3> Approach </h3>

1. **Mark Invalid Sub-Islands in Grid2:**
   - First, we'll mark the islands in `grid2` that cannot be sub-islands by comparing them with `grid1`. If a land cell in `grid2` does not correspond to a land cell in `grid1`, we'll mark the entire island in `grid2` as invalid.

2. **Count Remaining Valid Sub-Islands:**
   - After marking, we'll count the remaining valid islands in `grid2`.

<h3> Implementation </h3>

We'll implement this using Depth-First Search (DFS) to traverse and mark islands. Below is the Python code for solving the problem:

```cpp
// 199ms, 95.73MB
class Solution {
public:
    // DFS function to explore the island
    bool dfs(vector<vector<int>>& grid1, vector<vector<int>>& grid2, int x, int y) {
        // Check if we are out of bounds or on water in grid2
        if (x < 0 || x >= grid1.size() || y < 0 || y >= grid1[0].size() || grid2[x][y] == 0) {
            return true;
        }
        
        // If this part of the island in grid2 is not part of grid1, it's not a sub-island
        if (grid1[x][y] == 0) {
            return false;
        }

        // Mark the current cell in grid2 as visited by setting it to 0
        grid2[x][y] = 0;
        
        // Explore all four directions
        bool top = dfs(grid1, grid2, x - 1, y);
        bool bottom = dfs(grid1, grid2, x + 1, y);
        bool left = dfs(grid1, grid2, x, y - 1);
        bool right = dfs(grid1, grid2, x, y + 1);
        
        // The current island in grid2 is only a sub-island if all its parts are valid
        return top && bottom && left && right;
    }

    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int subIslands = 0;
        
        // Iterate over every cell in grid2
        for (int i = 0; i < grid2.size(); ++i) {
            for (int j = 0; j < grid2[0].size(); ++j) {
                // If we find an unvisited land cell in grid2, perform DFS
                if (grid2[i][j] == 1) {
                    // If DFS confirms it's a sub-island, increment the count
                    if (dfs(grid1, grid2, i, j)) {
                        ++subIslands;
                    }
                }
            }
        }
        
        return subIslands;
    }
};
```

<h3> Explanation </h3>

1. **DFS Implementation:**
   - The `dfs` function explores an island starting from a cell `(x, y)` and checks if all its parts are valid by comparing with `grid1`.
   - If any part of the island in `grid2` is not part of `grid1`, the island cannot be a sub-island.

2. **Counting Sub-Islands:**
   - For each unvisited land cell in `grid2`, we initiate a DFS. If the DFS confirms that the island is a sub-island (returns `True`), we increment our sub-island count.

3. **Time Complexity:**
   - The time complexity is $O(m * n)$, where `m` and `n` are the dimensions of the grid. Each cell is visited at most once.

## 24.08.29 - 947. Most Stones Removed with Same Row or Column
[문제 링크](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description/?envType=daily-question&envId=2024-08-29)

### 나
아이디어 생각을 못 함..
```cpp
// 58ms, 18.01MB
// 와 이게 unionfind?.. 와
// 겹치는 개수 구하고 (가장 적게 겹치는 애 지우고, 갱신 반복 아이디어) - 막막함.
class Solution {
    struct UnionFind {
        vector<int> par;

        UnionFind(int n) : par(n, -1) {}

        int Find(int a) {
            if(par[a] < 0) return a;
            return Find(par[a]);
        }

        bool Union(int a, int b) {
            a = Find(a), b = Find(b);
            if(a==b) return false;
            if(par[a] > par[b]) swap(a, b);
            par[a] += par[b];
            par[b] = a;
            return true;
        }
    };
public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        
        UnionFind uf{n};
        for(int i{};i<n;++i) {
            for(int j{i + 1};j<n;++j) {
                if(stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]) {
                    uf.Union(i, j);
                }
            }
        }

        // Union 개수 카운팅
        int answer{};
        for(int i{};i<n;++i) {
            if(uf.par[i] < 0) ++answer;
        }
        return n - answer;
    }
};
```

### 추후 해설 참고

#### Approach 1: Depth First Search
[링크](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/editorial/?envType=daily-question&envId=2024-08-29#approach-1-depth-first-search)

#### Approach 2: Disjoint Set Union
[링크](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/editorial/?envType=daily-question&envId=2024-08-29#approach-2-disjoint-set-union)

#### Approach 3: Disjoint Set Union (Optimized)
[링크](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/editorial/?envType=daily-question&envId=2024-08-29#approach-3-disjoint-set-union-optimized)


### gpt
Certainly! The problem "Most Stones Removed with Same Row or Column" on LeetCode is an interesting problem that can be approached using graph theory, specifically using the Union-Find (also known as Disjoint Set Union) algorithm. 

<h3> Problem Breakdown </h3>

- **Objective:** You are given a 2D grid with stones placed at certain integer coordinates. A stone can be removed if there is another stone in the same row or column. The goal is to remove as many stones as possible such that at least one stone remains.
- **Challenge:** Determine the maximum number of stones that can be removed.

<h3> Approach </h3>

1. **Model as a Graph:**
   - Consider each stone as a node in a graph. If two stones share the same row or column, connect them with an edge.
   - The problem now reduces to finding connected components in this graph. In each connected component, all but one stone can be removed (because we need to leave one stone to maintain the "connectedness" of the component).

2. **Union-Find Algorithm:**
   - Use Union-Find to group stones that are in the same row or column.
   - Each connected component will then allow us to remove all stones except one.

<h3> C++ Implementation </h3>

```cpp
class Solution {
public:
    // Find function with path compression
    int find(int x, unordered_map<int, int>& parent) {
        if (parent[x] != x) {
            parent[x] = find(parent[x], parent); // Path compression
        }
        return parent[x];
    }

    // Union function to merge two components
    void unionSets(int x, int y, unordered_map<int, int>& parent, unordered_map<int, int>& rank) {
        int rootX = find(x, parent);
        int rootY = find(y, parent);
        
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    int removeStones(vector<vector<int>>& stones) {
        unordered_map<int, int> parent;
        unordered_map<int, int> rank;

        // Initialize the parent of each stone (using row and column as distinct identifiers)
        for (const auto& stone : stones) {
            int x = stone[0]; // Row
            int y = stone[1] + 10000; // Column offset by 10000 to avoid collision with rows
            if (parent.find(x) == parent.end()) parent[x] = x;
            if (parent.find(y) == parent.end()) parent[y] = y;
            unionSets(x, y, parent, rank);
        }

        // Find number of unique connected components
        unordered_set<int> uniqueComponents;
        for (const auto& stone : stones) {
            int x = stone[0];
            uniqueComponents.insert(find(x, parent));
        }

        // The number of stones that can be removed is total stones minus the number of unique components
        return stones.size() - uniqueComponents.size();
    }
};
```

<h3> Explanation </h3>

1. **Union-Find Data Structure:**
   - **`parent`:** This map keeps track of the parent node for each stone (or rather, each row and column identifier).
   - **`rank`:** This map helps optimize the union operation by always attaching the smaller tree under the root of the bigger tree.

2. **Union Operation:**
   - Each stone's row and column are treated as nodes. We union the row and the column for each stone, effectively saying that the stone at `(x, y)` is connected to both its row and column.

3. **Counting Connected Components:**
   - After processing all stones, we count the number of unique root nodes using the `find` function. Each unique root represents a connected component, meaning one stone should be left in this component.

4. **Result Calculation:**
   - The maximum number of stones we can remove is the total number of stones minus the number of connected components. This is because in each connected component, all but one stone can be removed.

But It make wrong answer.
- counterexample: `[[0,0],[2,2],[10000,2]]`
- and answer is 1

Thank you for pointing out the issue. The counterexample you provided highlights a flaw in the initial approach where rows and columns are treated as separate entities with the same union-find structure. 

The problem is that in the initial solution, rows and columns that do not share a direct connection are being incorrectly considered part of the same connected component because of how the union-find was set up.

To fix this, we need to treat each stone as a unique entity in the union-find structure and only merge stones that are directly connected by either the same row or the same column.

<h3> Corrected Approach </h3>

We'll create a union-find structure that directly associates stones with each other by treating each stone as a unique node. We will only union stones that are in the same row or column.

<h3> Corrected C++ Implementation </h3>

```cpp
// 32ms, 23.60MB
class Solution {
public:
    // Find function with path compression
    int find(int x, unordered_map<int, int>& parent) {
        if (parent[x] != x) {
            parent[x] = find(parent[x], parent); // Path compression
        }
        return parent[x];
    }

    // Union function to merge two components
    void unionSets(int x, int y, unordered_map<int, int>& parent, unordered_map<int, int>& rank) {
        int rootX = find(x, parent);
        int rootY = find(y, parent);
        
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    int removeStones(vector<vector<int>>& stones) {
        unordered_map<int, int> parent;
        unordered_map<int, int> rank;

        // Initialize the parent for each stone
        for (const auto& stone : stones) {
            int x = stone[0] + 10000; // Offset to distinguish rows from columns
            int y = stone[1];         // Keep columns distinct
            
            if (parent.find(x) == parent.end()) parent[x] = x;
            if (parent.find(y) == parent.end()) parent[y] = y;
            
            // Union the row and column of the current stone
            unionSets(x, y, parent, rank);
        }

        // Find the number of unique components
        unordered_set<int> uniqueComponents;
        for (const auto& stone : stones) {
            int x = stone[0] + 10000;
            uniqueComponents.insert(find(x, parent));
        }

        // The number of stones that can be removed is total stones minus the number of unique components
        return stones.size() - uniqueComponents.size();
    }
};
```

<h3> Explanation of the Corrected Approach </h3>

1. **Union-Find Data Structure:**
   - We represent each stone's row and column uniquely by offsetting the row indices by a large number (e.g., `10000`) to avoid any overlap between row and column indices. This allows us to distinguish them in the union-find structure.

2. **Union Operations:**
   - For each stone, we union its row and column by treating them as nodes in the union-find structure. Stones that share the same row or column are connected via their corresponding row or column nodes.

3. **Counting Components:**
   - After processing all stones, we count the number of unique components by finding the root of each stone's row node. Each component represents a group of stones that are interconnected, allowing us to remove all but one stone.

4. **Result Calculation:**
   - The number of removable stones is the total number of stones minus the number of connected components. In each component, all but one stone can be removed.

<h3> Counterexample Explanation </h3>

For the input `[[0,0],[2,2],[10000,2]]`:

- The row `0` and column `0` will be connected as one component.
- The row `2` and column `2` will be connected as a separate component.
- The row `10000` and column `2` will be another separate component.

In this scenario, there are three unique components, so we can only remove `1` stone, which is correct for this particular counterexample.

## 24.08.30 - 2699. Modify Graph Edge Weights
[문제 링크](https://leetcode.com/problems/modify-graph-edge-weights/description/?envType=daily-question&envId=2024-08-30)

### 나
해설 참고 하자..

### 해설

#### Approach 1: Traditional Dijkstra's algorithm
[링크](https://leetcode.com/problems/modify-graph-edge-weights/editorial/?envType=daily-question&envId=2024-08-30#approach-1-traditional-dijkstras-algorithm)

#### Approach 2: Dijkstra's Algorithm with Min-Heap
[링크](https://leetcode.com/problems/modify-graph-edge-weights/editorial/?envType=daily-question&envId=2024-08-30#approach-2-dijkstras-algorithm-with-min-heap)


## 24.08.31 - 1514. Path with Maximum Probability
08.27 문제와 동일.

- [08.27](#240827---1514-path-with-maximum-probability)
