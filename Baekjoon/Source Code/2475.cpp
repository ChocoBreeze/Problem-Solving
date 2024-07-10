#include<iostream>
int main() {
    int a, sum = 0;
    for(int i=0;i<5;++i) {
        std::cin >> a;
        sum += a*a;
    }
    std::cout << sum%10;
    return 0;
}