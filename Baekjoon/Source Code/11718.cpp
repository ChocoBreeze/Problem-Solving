// https://restudycafe.tistory.com/513
#include<iostream>
#include<string>

using std::cin;
using std::cout;
using std::string;
using std::getline;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	string N;
	while (getline(cin, N)) {
		cout << N << "\n";
	}
	return 0;
}