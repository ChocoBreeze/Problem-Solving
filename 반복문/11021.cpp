#include<iostream>
int main() {
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    int N, temp1, temp2;
    std::cin>>N;
    for(int i=0;i<N;i++) {
        std::cin >> temp1>>temp2;
        std::cout << "Case #" << i+1 << ": " << temp1+temp2 << "\n";
    }
    return 0;
}