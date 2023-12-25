// Suffix Array : https://m.blog.naver.com/kks227/221028710658
// O(N{logN}^2)
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
vector<int> sa, pos, lcp;
// sa[i] : 사전순으로 i번째 위치의 접미사가 원래 문자열의 몇 번째 문자부터 시작하냐를 의미 => 해당 문자열 복원 = str.substr(sa[i])
// pos[i] : str[i:]가 sa의 몇 번째 index에 위치하는지 (pos[sa[i]] = i)
// lcp[i] : 사전순으로 다음에 오는 접미사와 비교하여 앞에서부터 몇 개의 글자가 일치하는지

void ConstructSA(string& str) {
	int sLen = static_cast<int>(str.length());
	sa = vector<int>(sLen, 0);
	pos = vector<int>(sLen, 0);

	// 전처리 - 제일 첫 번째 루프에서는 제자리 문자로 비교
	for (int i{}; i < sLen; ++i) {
		sa[i] = i;
		pos[i] = str[i];
	}

	int d{ 1 };
	auto cmp = [&sLen, &d](int i, int j) -> bool {
		// 1. 먼저 자신의 위치의 문자를 비교.
		if (pos[i] != pos[j]) return pos[i] < pos[j];

		// 문자가 같으면 d칸 뒤의 문자끼리 비교
		i += d, j += d;
		return (i < sLen && j < sLen) ? (pos[i] < pos[j]) : (i > j);
		};

	// d를 2배씩 늘려가면서 매번 앞에서부터 d*2글자만 보고 접미사 정렬
	for (;; d <<= 1) {
		sort(begin(sa), end(sa), cmp);

		// temp : 새로운 그룹 번호
		vector<int> temp(sLen, 0);
		// 앞에서부터 훑으면서 각 접미사가 서로 다른 그룹에 속할 때마다 그룹 번호 증가.
		for (int i{}; i < sLen - 1; ++i) {
			temp[i + 1] = temp[i] + static_cast<int>(cmp(sa[i], sa[i + 1]));
		}
		// pos 배열을 temp 배열로 대체.
		for (int i{}; i < sLen; ++i) {
			pos[sa[i]] = temp[i];
		}

		// 모든 접미사가 다른 그룹으로 나뉘어졌다면 종료
		if (temp[sLen - 1] == sLen - 1) break;
	}
}
void ConstructLCP(string& str) {
	int sLen = static_cast<int>(str.length());
	lcp = vector<int>(sLen, 0);

	// sa[i]는 사전순으로 i번째 위치의 접미사가 원래 문자열의 몇 번째 문자부터 시작하냐를 의미
	// pos[i] = str[i:]가 sa의 몇 번째에 있는가 (pos[sa[i]] = i)
	// 제일 긴 접미사(str)부터 시작함.
	// 매 루프마다 k > 0이면 k--
	for (int i{}, k{}; i < sLen; ++i, k = max(k - 1, 0)) {
		// 마지막 접미사(사전 순으로 마지막인 접미사)면 아무것도 안 함.
		if (pos[i] == sLen - 1) {
			lcp[pos[i]] = -1; // X 표시
			continue;
		}

		// 바로 아래 인접한 접미사와 비교하여 앞에서부터 몇 개의 글자가 일치하는지 카운팅
		// pos[i] + 1 (사전순으로 현재 문자열 다음 문자열의 sa index)
		int j = sa[pos[i] + 1];
		while (str[i + k] == str[j + k]) ++k;
		lcp[pos[i]] = k;
	}
}

int main() {
	cin.tie(nullptr), cout.tie(nullptr), ios::sync_with_stdio(false);
	string str; cin >> str; // 길이 1'000'000 이하
	int strLen = static_cast<int>(str.length());
	// ababc => a, ab, aba, abc, abab, ababc, b, ba, bc, bab, babc, c => 12
	// banana => a, an, ana, anan, anana, b, ba, ban, bana, banan, banana, n, na, nan, nana => 15

	ConstructSA(str);
	ConstructLCP(str);

	long long answer{};
	for (int i{}; i < strLen; ++i) {
		answer += (static_cast<long long>(strLen) - sa[i] - lcp[i]);
		// strLen - sa[i] : 이번에 카운팅하는 접미사들
		// lcp[i] : 앞에서 이미 등장한 접두사 개수(빼주기)
	}
	// 마지막 접미사에 해당하는 lcp : -1
	answer--; // -1을 빼줬으니 다시 더해주기
	cout << answer << '\n';

	return 0;
}