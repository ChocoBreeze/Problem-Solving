// 2080KB, 0ms
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    int N{}, K{}; cin >> N >> K;
    vector<int> vec;
    string str, temp; cin >> str;
    istringstream iss(str);
    while(getline(iss, temp, ',')) vec.push_back(stoi(temp));
    for(int k{};k<K;++k) {
        vector<int> newVec;
        for(int s{1}, e{static_cast<int>(vec.size())}; s<e;++s) {
            newVec.push_back(vec[s]-vec[s-1]);
        }
        vec.swap(newVec);
    }
    for(int s{}, e{static_cast<int>(vec.size())}; s<e-1;++s) cout << vec[s] << ',';
    cout << vec.back();
    return 0;
}