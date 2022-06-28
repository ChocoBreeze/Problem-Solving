#include<iostream>
#include<vector>
#include<algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::sort;

int main() {
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    vector<int> A(3,0);
    cin >> A[0] >> A[1] >> A[2];
    sort(A.begin(), A.end());
    for(auto& i : A) {
        cout << i << " ";
    } 
    return 0;
}