#include<iostream>
#include<queue>
#include<vector>
int main()
{
    int N, temp;
    // min heap --> priority_queue
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    std::priority_queue<int, std::vector<int>, std::greater<int>> P_Q; // min_heap 구성 매개변수 다 넣어줘야 함
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