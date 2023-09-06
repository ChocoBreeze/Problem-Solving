/*
1. 각 직사각형마다 세로변 2개씩 추출(x를 가로로 보면 -> x축 값)
2. 뽑은 세로변을 오름차순 크기 순으로 정렬 후 작은 순서부터 sweeping
3. 바로 전에 훑은 세로변과의 x좌표 차이를 dx라고 하면, 
   현재 y좌표 구간들 중 1 이상의 값을 가진 개수를 센 뒤 dx와 곱해서 결과에 더하기
4. 이번 세로변이 시작하는 세로변인 경우에, 세로변 안에 속하는 y 좌표 구간들에 1을 더하기.
   끝나는 세로변이면, 구간들에 1을 빼기.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
constinit const int SIZE = 30000;

struct SegmentTree {
	int start;
	vector<int> arr, lazy;

	SegmentTree(int N) : start(N >> 1), arr(N, 0), lazy(N, 0) {}
	// construct 필요 없음

	void propagate(int node, int ns, int ne) {
		if (lazy[node]) {
			if (node < start) {
				lazy[node * 2] += lazy[node];
				lazy[node * 2 + 1] += lazy[node];
			}
			arr[node] += lazy[node] * (ne - ns);
			lazy[node] = 0;
		}
	}

	// [s, e)
	void add(int s, int e, int k) { 
		add(s, e, k, 1, 0, start); 
	}

	void add(int s, int e, int k, int node, int ns, int ne) {
		propagate(node, ns, ne);

		if (e <= ns || ne <= s) return;
		if (s <= ns && ne <= e) {
			lazy[node] += k;
			propagate(node, ns, ne);
			return;
		}
		int mid = ns + (ne - ns) / 2;
		add(s, e, k, node << 1, ns, mid);
		add(s, e, k, (node << 1) + 1, mid, ne);
		arr[node] = arr[node * 2] + arr[node * 2 + 1];
	}

	// [s, e) 에 1이상인 값 개수 세기
	int count(int s, int e) {
		return count(s, e, 1, 0, start);
	}
	int count(int s, int e, int node, int ns, int ne) {
		propagate(node, ns, ne);

		if (e <= ns || ne <= s) return 0;
		if (arr[node] == 0) return 0; // 더 이상 갈 필요 없음.
		// if (s <= ns && ne <= e) return 1;
		if (node >= start) { // leaf
			if (arr[node]) return 1;
			else return 0;
		}

		int mid = ns + (ne - ns) / 2;
		return count(s, e, node << 1, ns, mid) + count(s, e, (node << 1) + 1, mid, ne);
	}
};

struct Info {
	int x; // 세로변 x 좌표
	int y1, y2; // x 좌표에 해당하는 y1 ~ y2 범위
	int start; // 시작하는 세로변인지
	Info(int x, int y1, int y2, int start) : x(x), y1(y1), y2(y2), start(start) {}
};

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N; cin >> N; // 지도 개수
	int tmpN{ 1 };
	while (tmpN < 30000) tmpN <<= 1;
	tmpN <<= 1;
	SegmentTree st(tmpN); // y구간
	
	vector<Info> infos;
	for (int n{}; n < N; ++n) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		infos.emplace_back(x1, y1, y2, 1); // 시작하는 세로변
		infos.emplace_back(x2, y1, y2, 0); // 끝나는 세로변
	}

	sort(begin(infos), end(infos), [](const Info& r1, const Info& r2) {
		return r1.x < r2.x;
	});

	int lastX = infos[0].x;
	int answer{};
	for (Info& i : infos) {
		answer += (i.x - lastX) * st.count(0, SIZE);
		if (i.start) st.add(i.y1, i.y2, 1);
		else st.add(i.y1, i.y2, -1);
		lastX = i.x;
	}
	cout << answer << '\n';

	return 0;
}