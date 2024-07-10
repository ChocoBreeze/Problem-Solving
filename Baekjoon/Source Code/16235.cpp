/*
N x N
봄
자신의 나이만큼 양분을 먹고 나이가 1 증가.
나이가 어린 나무부터 양분을 먹음.
자신의 나이만큼 양분을 못 먹으면 즉시 죽음

여름
봄에 죽은 나무가 양분으로 변함. -> 나이를 2로 나눈 값이 나무가 있던 칸에 양분으로 추가

가을
나무 번식(나이가 5의 배수여야 함)
인접한 8칸에 나이가 1인 나무가 생김

겨울
땅에 양분 추가 - [r][c]에 A[r][c]만큼.
*/

#include <iostream>
#include <vector>
#include <algorithm>

int dx[]{-1, -1, -1, 0, 0, 1, 1, 1};
int dy[]{-1, 0, 1, -1, 1, -1, 0, 1};

using namespace std;

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int N, M, K;
    cin >> N >> M >> K;

    vector<vector<vector<int>>> Map(N, vector<vector<int>>(N));
    vector<vector<int>> nutrient(N, vector<int>(N, 5)); // 가장 처음에 양분은 모든 칸에 5만큼 들어있다.
    vector<vector<int>> A(N, vector<int>(N, 0));        // 겨울에 추가될 양분
    vector<vector<int>> Ayear(N, vector<int>(N, 0));    // 죽은 나무
    for (auto &row : A)
    {
        for (int &v : row)
        {
            cin >> v;
        }
    }

    for (int m{}; m < M; ++m)
    {
        int x, y, age;
        cin >> x >> y >> age;
        x--, y--;
        Map[x][y].push_back(age);
    }

    for (int k{}; k < K; ++k)
    { // year
        // spring + summer
        for (int i{}; i < N; ++i)
        {
            for (int j{}; j < N; ++j)
            {
                sort(begin(Map[i][j]), end(Map[i][j])); // asc
                vector<int> tempTrees;
                int &nowNutrient = nutrient[i][j];
                bool enoughNutrient = true;
                for (int &a : Map[i][j])
                {
                    if (enoughNutrient && nowNutrient < a)
                        enoughNutrient = false;
                    if (enoughNutrient)
                    {
                        nowNutrient -= a; // 나이만큼 감소
                        tempTrees.push_back(a + 1);
                    }
                    else
                    {
                        Ayear[i][j] += a / 2;
                    }
                }
                Map[i][j].swap(tempTrees);
            }
        }

        // fall
        for (int i{}; i < N; ++i)
        {
            for (int j{}; j < N; ++j)
            {
                for (int &a : Map[i][j])
                { // age
                    if (a % 5 == 0)
                    {
                        for (int d{}; d < 8; ++d)
                        {
                            int ni = i + dx[d], nj = j + dy[d];
                            if (ni < 0 || ni >= N || nj < 0 || nj >= N)
                                continue;
                            Map[ni][nj].push_back(1); // 한 살
                        }
                    }
                }
            }
        }

        // winter
        for (int i{}; i < N; ++i)
        {
            for (int j{}; j < N; ++j)
            {
                nutrient[i][j] += A[i][j] + Ayear[i][j];
                Ayear[i][j] = 0;
            }
        }
    }

    // K 년이 지난 후 남은 나무 수
    int sum{};
    for (int i{}; i < N; ++i)
    {
        for (int j{}; j < N; ++j)
        {
            sum += static_cast<int>(size(Map[i][j]));
        }
    }

    cout << sum << '\n';
    return 0;
}