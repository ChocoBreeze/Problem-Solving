#include<iostream>
#include<string>
#include<vector>
using std::cin;
using std::cout;
using std::vector;
using std::string;
int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int x, y;
	cin >> x >> y;
	int sum = y;
	vector<string> days = { "MON", "TUE", "WED","THU","FRI","SAT","SUN" };
	for (int i = 1; i < x; ++i) {
		if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) sum += 31;
		else if (i == 2) sum += 28;
		else sum += 30;
	}
	cout << days[(sum - 1) % 7];
	return 0;
}