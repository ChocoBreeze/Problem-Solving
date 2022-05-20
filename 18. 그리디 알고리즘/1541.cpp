#include<iostream>
#include<string>
#include<vector>

int main()
{
	int sum = 0, temp_sum = 0;
	std::string str;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> str;
	std::vector<int> pos;
	pos.push_back(-1);
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == '-' || str[i] == '+')  pos.push_back(i);
	}
	pos.push_back(str.size());
	for (int i = 0; i < pos.size() - 1; ++i) {
		int temp_num = std::stoi(str.substr(pos[i] + 1, pos[i + 1]));
		if (pos[i] == -1) sum += temp_num;
		else if (str[pos[i]] == '-') {
			temp_sum += temp_num;
		}
		else { // str[pos[i]]=='+'
			if (temp_sum != 0) temp_sum += temp_num;
			else sum += temp_num;
		}
	}
	std::cout << sum - temp_sum;
	return 0;
}