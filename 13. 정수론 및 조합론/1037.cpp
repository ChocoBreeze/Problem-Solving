#include<iostream>
#include<vector>
#include<algorithm>
int main()
{
	std::cin.tie(NULL);
	std::ios::sync_with_stdio(false);
	int N;
	std::cin >> N;
	std::vector<unsigned long long int> cd(N, 0);
	for (int i = 0; i < N; ++i) {
		std::cin >> cd[i];
	}
	std::sort(cd.begin(), cd.end());
	std::cout << cd[0] * cd[cd.size()-1];
	return 0;
}