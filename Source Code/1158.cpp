#include <list>
#include <iostream>
#include <ranges>
#include <vector>
#include <iterator>

using namespace std;

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	int N{}, K{}; cin >> N >> K;

	list<int> l;
	for (int i : std::views::iota(0) | std::views::take(N)) l.push_back(i + 1);
	
	vector<int> result;
	auto it = begin(l);
	while (l.size() != 1) {
		// advance(it, K - 1);
		for (int k{}; k < K - 1; ++k) {
			if (it == end(l)) it = begin(l);
			it++;
		}
		if (it == end(l)) it = begin(l);
		result.push_back(*it);
		it = l.erase(it);
	}
	result.push_back(l.back()); // 마지막 남은

	cout << '<';
	for (int i{};i<N;++i) {
	    cout << result[i];
	    if(i!=N-1) cout << ", ";
    }
	cout << '>';

	return 0;
}
