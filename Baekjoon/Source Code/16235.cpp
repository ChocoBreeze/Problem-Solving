/*
N x N
��
�ڽ��� ���̸�ŭ ����� �԰� ���̰� 1 ����.
���̰� � �������� ����� ����.
�ڽ��� ���̸�ŭ ����� �� ������ ��� ����

����
���� ���� ������ ������� ����. -> ���̸� 2�� ���� ���� ������ �ִ� ĭ�� ������� �߰�

����
���� ����(���̰� 5�� ������� ��)
������ 8ĭ�� ���̰� 1�� ������ ����

�ܿ�
���� ��� �߰� - [r][c]�� A[r][c]��ŭ.
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
    vector<vector<int>> nutrient(N, vector<int>(N, 5)); // ���� ó���� ����� ��� ĭ�� 5��ŭ ����ִ�.
    vector<vector<int>> A(N, vector<int>(N, 0));        // �ܿ￡ �߰��� ���
    vector<vector<int>> Ayear(N, vector<int>(N, 0));    // ���� ����
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
                        nowNutrient -= a; // ���̸�ŭ ����
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
                            Map[ni][nj].push_back(1); // �� ��
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

    // K ���� ���� �� ���� ���� ��
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