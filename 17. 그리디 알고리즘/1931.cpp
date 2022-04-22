// 왜 그리디로 풀어도 되는지
#include<iostream>
#include<vector> 
#include<algorithm>
int main() 
{
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<std::pair<int, int>> time(N,std::pair<int,int>(0,0));
	for (int i = 0; i < N; ++i) {
		std::cin >> time[i].first >> time[i].second;
	}
	auto comparable = [](std::pair<int, int>& a, std::pair<int, int>& b) {
		if (a.second < b.second) return true;
		else if (a.second == b.second) {
			return a.first < b.first;
		}
		else return false;
	};
	std::sort(time.begin(), time.end(), comparable);
	int count = 1;
	std::pair<int, int> on_going = time[0];
	for (int i = 1; i < N; ++i) {
		if(on_going.second > time[i].first)
			continue;
		on_going = time[i];
		count++;
	}
	std::cout << count;
	return 0;
}