#include<iostream>
int main() {
    int N, max = 0,temp;
    double sum = 0;
    std::cin>>N;
    for(int i=0;i<N;i++) {
        std::cin >> temp;
        sum+=temp;
        if(max<temp) max=temp;
    }
    std::cout << std::fixed;
    std::cout.precision(6);
    std::cout << (sum/N)/max*100;
    return 0;
}