// 자잘하게 놓친 부분이 많았음
#include <iostream>
#include <string>

using namespace std;

int StrToInt(string& s) {
    int ret{}, place = 1;
    for(auto it = rbegin(s); it!=rend(s);++it) {
        if(*it=='1') {
            ret += place;
        }
        place <<= 1;
    }
    return ret;
}

int main() {
    cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
    string str, answer;
    cin >> str;
    int strLen = static_cast<int>(str.length());
    for(int i{1}; i <= strLen/3 + 1; ++i) {
    	if(i==strLen/3+1) {    	    
            string temp = str.substr(0, strLen%3);
    	    answer.push_back(StrToInt(temp)+'0');
    	    if(answer.back()=='0') answer.pop_back();
    	}
    	else {
    	    string temp = str.substr(strLen - 3*i, 3);
    	    answer.push_back(StrToInt(temp)+'0');
    	}
    	// cout << i << ' ' << answer << '\n';
    }
    if(answer.empty()) {
        cout << 0;
    }
    else {
        for(auto it = rbegin(answer); it!=rend(answer);++it) {
            cout << *it;
        }
    }
    cout << '\n';
    return 0;
}