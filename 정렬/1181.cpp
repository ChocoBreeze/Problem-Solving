#include<vector>
#include<iostream>
#include<algorithm>
#include<string>

int main() {
	int N;
	std::string temp;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<std::string> str_list;
	for (int i = 0; i < N; ++i) {
		std::cin >> temp;
		if(std::find(str_list.begin(), str_list.end(), temp)==str_list.end())
			str_list.push_back(temp);
	}

	auto comparable = [](std::string a, std::string b) {
		if (a.length() < b.length()) return true;
		else if (a.length() == b.length() && a.compare(b) < 0) return true;
		else return false;
	};

	std::sort(str_list.begin(), str_list.end(), comparable);
	for (auto i = str_list.begin(); i != str_list.end(); ++i) {
		std::cout << *i << "\n";
	}
	return 0;
}