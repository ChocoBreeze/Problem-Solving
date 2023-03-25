#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, double> um{
	{"A+", 4.5}, {"A0", 4.0}, {"B+", 3.5},
	{"B0", 3.0}, {"C+", 2.5}, {"C0", 2.0},
	{"D+", 1.5}, {"D0", 1.0}, {"F", 0.0}
};

int main() {
	double sum{};
	double times{};
	cin.tie(NULL)->sync_with_stdio(false);
	for (int i{}; i < 20; ++i) {
		string str, grade;
		double time;
		cin >> str >> time >> grade;
		if (grade == "P") continue; // 계산 x
		sum += time * um[grade];
		times += time;
	}
	cout << fixed;
	cout.precision(6);
	cout << sum / times << '\n';

	return 0;
}