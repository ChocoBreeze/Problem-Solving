#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}; cin >> N;
	vector<int> students(N, 0);
	for (int& s : students) cin >> s;

	int now = 1, index{};
	stack<int> onlyOnePeople;
	while(now <= N) {
		if (index < N && now == students[index]) {
			now++;
		}
		else {
			while (!onlyOnePeople.empty() && onlyOnePeople.top() == now) {
				now++;
				onlyOnePeople.pop();
			}
			if(index < N) onlyOnePeople.push(students[index]);
		}
		if(index < N) index++;
		
		if (index >= N && !onlyOnePeople.empty() && onlyOnePeople.top() != now) {
			break;
		}
	}

	if (now > N && onlyOnePeople.empty()) cout << "Nice\n";
	else cout << "Sad\n";

	return 0;
}