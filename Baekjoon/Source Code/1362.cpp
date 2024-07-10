#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    vector<int> result;
    for(int t=1;;++t) {
        int o,w;
        cin >> o >> w;
        if(!o && !w) break;
        bool alive{true};
        while(1) {
            string a, b;
            cin >> a >> b;
            if(a=="#" && b=="0") {
                break;
            }
            if(!alive) continue;
            else if(a=="F") {
                w+= stoi(b);
            }
            else if(a=="E") {
                w-= stoi(b);
                if(w<= 0) {
                    alive = false;
                }
            }
        }
        if(!alive) result.push_back(0);
        else if(w > o /2 && w < o * 2) result.push_back(1); 
        else result.push_back(2); // sad  
    }

    for(int i{}; i < static_cast<int>(result.size());++i) {
        cout << i + 1 << ' ';
        if(result[i]==0) cout << "RIP\n";
        else if(result[i]==1) cout << ":-)\n";
        else cout << ":-(\n";
    }
    return 0;
}