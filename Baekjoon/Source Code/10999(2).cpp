// https://m.blog.naver.com/kks227/220824350353
// ������ ®�� �� ���� �̰� �� �����ϴ�!

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

// ���׸�Ʈ Ʈ�� ����ü
struct SegTree {
    int start; // leaf node ������
    vector<ll> arr, lazy;

    // ������
    SegTree(int tmpN) : start(tmpN >> 1), arr(tmpN, 0), lazy(tmpN, 0) { }

    // ���� ������ ���� ���� �Է��� �� ��ü ���׸�Ʈ Ʈ�� ����
    void construct() {
        for (int i{ start - 1 }; i > 0; --i) {
            arr[i] = arr[i * 2] + arr[i * 2 + 1];
        }
    }

    // ���� [ns, ne)�� node�� lazy ���� propagate
    void propagate(int node, int ns, int ne) {
        // lazy ���� �����ϸ� ����
        if (lazy[node] != 0) {
            // ���� ��尡 �ƴϸ� �ڽĵ鿡�� lazy �̷�
            if (node < start) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            // �ڽſ� �ش��ϴ� ��ŭ�� ���� ����
            arr[node] += lazy[node] * (ne - ns);
            lazy[node] = 0;
        }
    }

    // ���� [s, e)�� k�� ���϶�
    void add(int s, int e, ll k) { add(s, e, k, 1, 0, start); }
    void add(int s, int e, ll k, int node, int ns, int ne) {
        // �ϴ� propagate
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return; // �ش�Ǵ� ������ �ƴ�.
        if (s <= ns && ne <= e) {
            // �� ��尡 ������ ������ ���ԵǸ� lazy �ο� �� propagate
            lazy[node] += k;
            propagate(node, ns, ne);
            return;
        }
        int mid = ns + (ne - ns) / 2;
        add(s, e, k, node * 2, ns, mid);
        add(s, e, k, node * 2 + 1, mid, ne);
        // �������� �ڽĵ��� ���� ����� �ٽ� �ڽ��� �� ����
        arr[node] = arr[node * 2] + arr[node * 2 + 1];
    }

    // ���� [s, e)�� ���� ���϶�
    long long sum(int s, int e) { return sum(s, e, 1, 0, start); }
    long long sum(int s, int e, int node, int ns, int ne) {
        // �ϴ� propagate
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return 0; // �´� ������ �ƴ�
        if (s <= ns && ne <= e) return arr[node]; // ��Ȯ�� ���ԵǴ� ����

        int mid = ns + (ne - ns) / 2;
        return sum(s, e, node * 2, ns, mid) + sum(s, e, node * 2 + 1, mid, ne);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // �ʱ� ���׸�Ʈ Ʈ�� �Է¹ޱ�
    int N, M, K; // ���� ����, ������ �Ͼ�� Ƚ��, ������ ���� ���ϴ� Ƚ��
    cin >> N >> M >> K;
    int tmpN{ 1 }; // leaf node ����
    while (tmpN < N) {
        tmpN <<= 1;
    }
    tmpN <<= 1;

    SegTree ST(tmpN);
    for (int i{}; i < N; ++i) { // leafnode�� �Է¹ޱ�
        cin >> ST.arr[ST.start + i];
    }
    ST.construct();

    // ���� ó��
    for (int i{}; i < M + K; ++i) {
        int a{}, b{}, c{};
        ll d{};
        cin >> a;
        if (a == 1) {
            cin >> b >> c >> d;
            ST.add(b - 1, c, d);
        }
        else {
            cin >> b >> c;
            cout << ST.sum(b - 1, c) << '\n';
        }
    }
    return 0;
}