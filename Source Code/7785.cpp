#include <iostream>
#include <set>

using namespace std;

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int N;
	set<string> enter_people;
	cin >> N;
	string name, status;
	for (int i = 0; i < N; ++i) {
		cin >> name >> status;
		if (status == "enter") enter_people.insert(name);
		else enter_people.erase(name);
	}
	for (auto it = rbegin(enter_people); it != rend(enter_people); ++it) {
		cout << *it << '\n';
	}
	return 0;
}