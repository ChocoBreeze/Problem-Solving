#include<iostream>
#include<queue>
int main()
{
    int N, temp;
    // max heap --> priority_queue
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    std::priority_queue<int> P_Q;
    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        std::cin >> temp;
        if (temp == 0) {
            if (P_Q.empty()) std::cout << 0 << "\n";
            else {
                std::cout << P_Q.top() << "\n";
                P_Q.pop();
            }
        }
        else {
            P_Q.push(temp);
        }
    }
    return 0;
}