// sweeping

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using pii = pair<int, int>;
using llong = long long;
int tmpN;

void make_tree(vector<int>& seg_tree, int index) {
	index += tmpN - 1;
	seg_tree[index]++; // 한 개 추가
	while (index > 1) {
		int parent = index >> 1;
		seg_tree[parent] = seg_tree[parent * 2] + seg_tree[parent * 2 + 1];
		index = parent;
	}
}

// 구간 합 구하기 
int get_pair(vector<int>& seg_tree, int s, int e) {
	s += tmpN - 1;
	e += tmpN - 1;
	int answer = 0;
	while (s <= e) {
		// 조건이?.. 잘..
		if ((s&1) == 1) answer += seg_tree[s]; // s가 right child일 때
		if ((e&1) == 0) answer += seg_tree[e]; // e가 left child일 때

		s = (s + 1) >> 1;
		e = (e - 1) >> 1;
	}
	return answer;
}

int main() {
	cin.tie(NULL)->sync_with_stdio(false);
	int T, n;
	cin >> T;
	for (int t = 0; t < T; ++t) {
		cin >> n;
		vector<pii> vec(n, make_pair(0, 0));
		for (pii& v : vec) {
			cin >> v.first >> v.second;
		}

		auto compare = [](const pii& a, const pii& b) { // y value만 이용해서 정렬
			return a.second < b.second;
		};

		sort(begin(vec), end(vec), compare);
		// y 값 새로 정하기
		int index = 1, last_y = vec[0].second;
		vec[0].second = 1; // 첫 index = 0
		for (int i = 1; i < n; ++i) {
			if (last_y < vec[i].second) { // y 더 크면 이전 값과 index 변경
				last_y = vec[i].second;
				vec[i].second = ++index;
			}
			else { // y 같으면 index 유지
				vec[i].second = index;
			}
		}
		tmpN = 1; // leaf node 개수
		while (tmpN < index) tmpN <<= 1;
		vector<int> seg_tree(tmpN * 2, 0);

		auto compare2 = [](const pii& a, const pii& b) {
			if (a.first == b.first) {
				return a.second > b.second;
			}
			else return a.first < b.first;
		};
		sort(begin(vec), end(vec), compare2);

		llong answer = 0;
		for (pii& v : vec) {
			int value = get_pair(seg_tree, v.second, index);
			answer += static_cast<llong>(value);
			make_tree(seg_tree, v.second);
		}

		cout << answer << endl;
	}

	return 0;
}