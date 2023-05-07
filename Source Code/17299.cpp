#include <vector>
#include <stack>
#include <iostream>

using namespace std;
constinit int SIZE = 1'000'001;

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int N{};
    cin >> N;
    vector<int> vec(N, 0), DAT(SIZE, 0);

    for (int &v : vec)
    {
        cin >> v;
        DAT[v]++;
    }

    stack<int> S;
    vector<int> answer{};
    for (auto it = rbegin(vec); it != rend(vec); ++it)
    {
        if (S.empty())
        {
            S.push(*it);
            answer.push_back(-1);
        }
        else
        {
            while (!S.empty() && DAT[S.top()] <= DAT[*it])
                S.pop();
            if (S.empty())
            {
                answer.push_back(-1);
            }
            else
            {
                answer.push_back(S.top());
            }
            S.push(*it);
        }
    }

    for (auto it = rbegin(answer); it != rend(answer); ++it)
        cout << *it << ' ';
    cout << '\n';

    return 0;
}