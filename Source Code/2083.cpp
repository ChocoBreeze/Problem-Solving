// 2024KB, 0ms
#include <iostream>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	while (1) {
		string str;
		int age{}, weight{};
		cin >> str >> age >> weight;
		if (str == "#" && !age && !weight) {
			break;
		}
		cout << str << ' ';
		if (age > 17 || weight >= 80) {
			cout << "Senior\n";
		}
		else {
			cout << "Junior\n";
		}
	}
	return 0;
}