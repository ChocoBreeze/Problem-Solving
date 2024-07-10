/*
1. �� ���簢������ ���κ� 2���� ����(x�� ���η� ���� -> x�� ��)
2. ���� ���κ��� �������� ũ�� ������ ���� �� ���� �������� sweeping
3. �ٷ� ���� ���� ���κ����� x��ǥ ���̸� dx��� �ϸ�, 
   ���� y��ǥ ������ �� 1 �̻��� ���� ���� ������ �� �� dx�� ���ؼ� ����� ���ϱ�
4. �̹� ���κ��� �����ϴ� ���κ��� ��쿡, ���κ� �ȿ� ���ϴ� y ��ǥ �����鿡 1�� ���ϱ�.
   ������ ���κ��̸�, �����鿡 1�� ����.
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
	// construct �ʿ� ����

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

	// [s, e) �� 1�̻��� �� ���� ����
	int count(int s, int e) {
		return count(s, e, 1, 0, start);
	}
	int count(int s, int e, int node, int ns, int ne) {
		propagate(node, ns, ne);

		if (e <= ns || ne <= s) return 0;
		if (arr[node] == 0) return 0; // �� �̻� �� �ʿ� ����.
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
	int x; // ���κ� x ��ǥ
	int y1, y2; // x ��ǥ�� �ش��ϴ� y1 ~ y2 ����
	int start; // �����ϴ� ���κ�����
	Info(int x, int y1, int y2, int start) : x(x), y1(y1), y2(y2), start(start) {}
};

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N; cin >> N; // ���� ����
	int tmpN{ 1 };
	while (tmpN < 30000) tmpN <<= 1;
	tmpN <<= 1;
	SegmentTree st(tmpN); // y����
	
	vector<Info> infos;
	for (int n{}; n < N; ++n) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		infos.emplace_back(x1, y1, y2, 1); // �����ϴ� ���κ�
		infos.emplace_back(x2, y1, y2, 0); // ������ ���κ�
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