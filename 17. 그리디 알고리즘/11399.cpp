#include<iostream>
#include<vector> 
#include<algorithm>
int main() 
{
	int N;
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	std::cin >> N;
	std::vector<int> people(N,0);
	for (int i = 0; i < N; ++i) {
		std::cin >> people[i];
	}
	std::sort(people.begin(), people.end());
	int sum = people[0], sum_ac = people[0];
	for (int i = 1; i < N; ++i) {
		sum_ac += people[i];
		sum += sum_ac;
	}
	std::cout << sum;
	return 0;
}