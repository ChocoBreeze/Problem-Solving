// ���Ʈ���� �˰���
// 500 * 500 * 256 = 64000000
#include <iostream>
#include <vector>
#include <ranges>
#include <climits>

using namespace std;

int N, M; // 1 ~ 500
int B;    // 64000000

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    cin >> N >> M >> B;

    vector<vector<int>> Map(N, vector<int>(M, 0));
    for (auto &row : Map)
    {
        for (int &v : row)
        {
            cin >> v;
        }
    }

    int ansH{};            // �� ����
    int ansTime = INT_MAX; // �� ���

    for (int h : ranges::iota_view{0, 257})
    { // ���� �� �ǳ�
        // vector<vector<int>> tempMap(begin(Map), end(Map));

        int blockCnt{B};
        int time{};

        auto result = [&]()
        {
            for (auto &row : Map)
            {
                for (int &v : row)
                {
                    if (v < h)
                    { // �޲ٱ� - 1��
                        time += (h - v);
                        // if (blockCnt < (h - v)) return false;
                        blockCnt -= (h - v);
                    }
                    else
                    { // ��� - 2��
                        time += (v - h) * 2;
                        blockCnt += (v - h);
                    }

                    if (time > ansTime)
                        return false;
                }
            }
            return true;
        }();

        if (result && blockCnt >= 0)
        {
            if (ansTime > time)
            {
                ansTime = time;
                ansH = h;
            }
            else if (ansTime == time)
            {
                ansH = h;
            }
        }
    }

    cout << ansTime << ' ' << ansH << '\n';
    return 0;
}