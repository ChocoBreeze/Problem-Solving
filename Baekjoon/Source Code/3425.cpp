#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	while (1) {
		vector<string> Queries;
		string str;
		getline(cin, str);
		if (str.compare("QUIT") == 0) {
			break;
		}
		else Queries.push_back(str);
		while (str.compare("END")!=0) {
			getline(cin, str);
			if (str.compare("END") == 0) break;
			Queries.push_back(str);
		}
		int N;
		cin >> N;
		vector<long long> V(N,0);
		for (auto& i : V) {
			cin >> i;
		}
		for (auto& i : V) { // Vi마다 처리
			stack<int> S;
			S.push(i);
			bool chk = false;
			for (auto& q : Queries) {
				if (q.find("NUM") == 0) {
					S.push(stoi(q.substr(4)));
				}
				else if (q.compare("POP") == 0) {
					if (S.empty()) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					S.pop();
				}
				else if (q.compare("INV") == 0) {
					long long a = S.top() * (-1);
					S.pop();
					S.push(a);
				}
				else if (q.compare("DUP") == 0) {
					long long a = S.top();
					S.push(a);
				}
				else if (q.compare("SWP") == 0) {
					long long a, b;
					if (S.empty()) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					a = S.top(); // first
					S.pop();
					if (S.empty()) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					b = S.top(); // second
					S.pop();
					S.push(a);
					S.push(b);
				}
				else if (q.compare("ADD") == 0) {
					long long a, b;
					if (S.empty()) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					a = S.top(); // first
					S.pop();
					if (S.empty()) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					b = S.top(); // second
					S.pop();
					S.push(a + b);
					if (abs(a + b) > 1000000000) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
				}
				else if (q.compare("SUB") == 0) {
					long long a, b;
					if (S.empty()) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					a = S.top(); // first
					S.pop();
					if (S.empty()) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					b = S.top(); // second
					S.pop();
					S.push(b - a);
					if (abs(b - a) > 1000000000) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
				}
				else if (q.compare("MUL") == 0) {
					long long a, b;
					if (S.empty()) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					a = S.top(); // first
					S.pop();
					if (S.empty()) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					b = S.top(); // second
					S.pop();
					if (abs(a * b) > 1000000000) {
						cout << "ERROR\n";
						chk = true;
						break;					
					}
					S.push(a * b);
				}
				else if (q.compare("DIV") == 0) {
					long long a, b;
					if (S.empty()) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					a = S.top(); // first
					S.pop();
					if (S.empty()) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					b = S.top(); // second
					S.pop();
					if (a == 0) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					// 피제수가 나눠지는 수.
					S.push(b / a);
				}
				else if (q.compare("MOD") == 0) {
					long long a, b;
					if (S.empty()) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					a = S.top(); // first
					S.pop();
					if (S.empty()) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					b = S.top(); // second
					S.pop();
					if (a == 0) {
						cout << "ERROR\n";
						chk = true;
						break;
					}
					S.push(b % a);
				}
			}
			if (S.size() == 1 && !chk) cout << S.top() << "\n";
			else if (S.size() != 1 && !chk) cout << "ERROR\n";
		}
		getline(cin, str); // 마지막에 오는 '\n' 제거
		cin.ignore();
		cout << "\n";
	}
	return 0;
}