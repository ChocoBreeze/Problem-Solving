// 순서 유지 필요
// unordered_set
#include<iostream>
#include<unordered_map>
#include<string>
using std::string;
using std::unordered_map;
using std::cin;
using std::cout;
int main()
{
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N, M;
	string tmp;
	unordered_map<string, int> pokemon_str; // str -> num
	unordered_map<int, string> pokemon_num; // num -> str
	cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		cin >> tmp;
		pokemon_str.insert(std::make_pair(tmp, i));
		pokemon_num.insert(std::make_pair(i, tmp));
	}
	for (int i = 0; i < M; ++i) {
		cin >> tmp;
		int number;
		try {
			number = std::stoi(tmp); // 숫자가 아니면 catch로 감
			cout << pokemon_num.at(number) << "\n";
		}
		catch (std::invalid_argument) { // 포켓몬 이름 - 반드시 도감에 존재
			cout << pokemon_str.at(tmp) << "\n";
		}
	}
	return 0;
}
