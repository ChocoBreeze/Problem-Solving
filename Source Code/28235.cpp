#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	unordered_map<string, string> um{
		{"SONGDO", "HIGHSCHOOL"},
		{"CODE", "MASTER"},
		{"2023", "0611"},
		{"ALGORITHM", "CONTEST"}
	};
	string in; cin >> in;
	cout << um[in];
	return 0;
}