// 기존 코드 갱신 + 다시 공부
// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=jh20s&logNo=221351546136
// O(Q*lgN*lgN)
// segTree 전역변수화
// 처음에 트리 만드는 방식 변경 (408ms -> 196ms)

#include <iostream>
#include <vector>

using namespace std;

int leafNode = 1;
vector<vector<int>> segTree;
// 1024 * 1024 * 1000 = 1,048,576,000

void make_tree_y(int i, int j)
{
    while (j > 1)
    { // 기존 1차원 트리
        int parent = j >> 1;
        segTree[i][parent] = segTree[i][parent * 2] + segTree[i][parent * 2 + 1];
        j = parent;
    }
}

void update(int i, int j)
{ // make_tree_x
    i += leafNode;
    j += leafNode;
    make_tree_y(i, j);
    while (i > 1)
    {
        int parent_i = i >> 1;
        segTree[parent_i][j] = segTree[parent_i * 2][j] + segTree[parent_i * 2 + 1][j];
        make_tree_y(parent_i, j);
        i = parent_i;
    }
}

int get_sum_y(int x, int y1, int y2)
{ // 기존 1차원 seg tree
    y1 += leafNode;
    y2 += leafNode;
    int sum = 0;
    while (y1 <= y2)
    {
        if ((y1 & 1) == 1)
            sum += segTree[x][y1];
        if ((y2 & 1) == 0)
            sum += segTree[x][y2];

        y1 = (y1 + 1) >> 1;
        y2 = (y2 - 1) >> 1;
    }
    return sum;
}

int get_sum(int x1, int y1, int x2, int y2)
{
    // x 범위
    int sum = 0;
    x1 += leafNode;
    x2 += leafNode;
    while (x1 <= x2)
    {
        if ((x1 & 1) == 1)
            sum += get_sum_y(x1, y1, y2);
        if ((x2 & 1) == 0)
            sum += get_sum_y(x2, y1, y2);

        x1 = (x1 + 1) >> 1;
        x2 = (x2 - 1) >> 1;
    }

    return sum;
}

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int N, M, w;
    cin >> N >> M;
    while (leafNode < N)
    {
        leafNode <<= 1;
    }

    leafNode <<= 1;
    segTree.assign(leafNode, vector<int>(leafNode, 0));
    leafNode >>= 1;

    // leafnode 채우기
    for (int i = 0; i < N; ++i)
    {
        int iIdx{i + leafNode};
        for (int j = 0; j < N; ++j)
        {
            int jIdx{j + leafNode};
            cin >> segTree[iIdx][jIdx];
        }
    }

    // 다른 tree 만들기
    for (int i{leafNode - 1}; i >= 1; --i)
    {
        int iLeftChild{i << 1}, iRightChild{(i << 1) + 1};
        for (int j{N + leafNode - 1}; j >= leafNode; --j)
        {
            segTree[i][j] = segTree[iLeftChild][j] + segTree[iRightChild][j];
        }
        for (int j{leafNode - 1}; j >= 1; --j)
        {
            int jLeftChild{j << 1}, jRightChild{(j << 1) + 1};
            segTree[iLeftChild][j] = segTree[iLeftChild][jLeftChild] + segTree[iLeftChild][jRightChild];
            segTree[iRightChild][j] = segTree[iRightChild][jLeftChild] + segTree[iRightChild][jRightChild];
            segTree[i][j] = segTree[iLeftChild][j] + segTree[iRightChild][j];
        }
    }

    for (int i = 0; i < M; ++i)
    {
        cin >> w;
        if (w == 0)
        { // (x, y) -> c
            int x, y, c;
            cin >> x >> y >> c;
            x--;
            y--;
            segTree[x + leafNode][y + leafNode] = c;
            update(x, y);
        }
        else
        { // (x1, y1) ~ (x2, y2) 합
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--;
            y1--;
            x2--;
            y2--;
            cout << get_sum(x1, y1, x2, y2) << '\n';
        }
    }

    return 0;
}