#include<iostream>
#include<string>
int main() {
	int N;
	std::string str;
	std::cin >> N;
	for (int i = 0; i < N; i++) {
		std::cin >> str;
		int cnt = 0, sum=0;
		for (int j = 0; j < str.length(); j++) {
			if (str[j] == 'O') cnt++;
			else cnt = 0;
			sum += cnt;
		}
		std::cout << sum << "\n";
	}
	return 0;
}