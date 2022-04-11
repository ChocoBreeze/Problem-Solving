#include<iostream>
int main() {
    int N, temp, min = 1000001, max = -1000001;
    std::cin>>N;
    for(int i=0;i<N;i++) {
        std::cin >> temp;
        if(min>temp) min = temp;
        if(max<temp) max = temp;
    }
    std::cout << min << " " << max;
    return 0;
}