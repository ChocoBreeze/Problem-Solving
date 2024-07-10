// https://m.blog.naver.com/kks227/220824350353
// ������ ®�� �� ���� �̰� �� �����ϴ�!
// ������ ¦���� ��� ������ �ʿ� ����.(¦�� �� XOR�� �ǹ� ����)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// ���׸�Ʈ Ʈ�� ����ü
struct SegTree {
    int start; // leaf node ������
    vector<int> arr, lazy;

    // ������
    SegTree(int tmpN) : start(tmpN >> 1), arr(tmpN, 0), lazy(tmpN, 0) { }

    // ���� ������ ���� ���� �Է��� �� ��ü ���׸�Ʈ Ʈ�� ����
    void construct() {
        for (int i{ start - 1 }; i > 0; --i) {
            arr[i] = arr[i * 2] ^ arr[i * 2 + 1];
        }
    }

    // ���� [ns, ne)�� node�� lazy ���� propagate
    void propagate(int node, int ns, int ne) {
        // lazy ���� �����ϸ� ����
        if (lazy[node] != 0) {
            if (node < start) { // ���� ��尡 �ƴϸ� �ڽĵ鿡�� lazy �̷�
                lazy[node * 2] ^= lazy[node];
                lazy[node * 2 + 1] ^= lazy[node];
            }
            else { // ���� ����̸� �� ����
                arr[node] ^= lazy[node];
            }
            lazy[node] = 0;
        }
    }

    // ���� [s, e)�� k�� XOR�ϱ�.
    void Query(int s, int e, int k) { Query(s, e, k, 1, 0, start); }
    void Query(int s, int e, int k, int node, int ns, int ne) {
        // �ϴ� propagate
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return; // �ش�Ǵ� ������ �ƴ�.
        if (s <= ns && ne <= e) {
            // �� ��尡 ������ ������ ���ԵǸ� lazy �ο� �� propagate
            lazy[node] ^= k; // 0 ^ k = k
            propagate(node, ns, ne);
            return;
        }
        int mid = ns + (ne - ns) / 2;
        Query(s, e, k, node * 2, ns, mid); // left
        Query(s, e, k, node * 2 + 1, mid, ne); // right
        // �������� �ڽĵ��� ���� ����� �ٽ� �ڽ��� �� ����
        arr[node] = arr[node * 2] ^ arr[node * 2 + 1];
    }

    // ���� [s, e)�� XOR�� ���϶�
    int XOR(int s, int e) { return XOR(s, e, 1, 0, start); }
    int XOR(int s, int e, int node, int ns, int ne) {
        // �ϴ� propagate
        propagate(node, ns, ne);

        if (e <= ns || ne <= s) return 0; // �´� ������ �ƴ�
        if (s <= ns && ne <= e) return arr[node]; // ��Ȯ�� ���ԵǴ� ����

        int mid = ns + (ne - ns) / 2;
        return XOR(s, e, node * 2, ns, mid) ^ XOR(s, e, node * 2 + 1, mid, ne);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // �ʱ� ���׸�Ʈ Ʈ�� �Է¹ޱ�
    int N; cin >> N; // ���� ����

    int tmpN{ 1 }; // leaf node ���� * 2
    while (tmpN < N) {
        tmpN <<= 1;
    }
    tmpN <<= 1;

    SegTree ST(tmpN);
    for (int i{ST.start}; i < ST.start + N; ++i) { // leafnode�� �Է¹ޱ�
        cin >> ST.arr[i];
    }
    ST.construct();

    int M{}; cin >> M; // ���� ����
    for (int i{}; i < M; ++i) {
        int a{}, b{}, c{}, d{};
        cin >> a;
        if (a == 1) {
            cin >> b >> c >> d;
            ST.Query(b, c + 1, d);
        }
        else {
            cin >> b >> c;
            cout << ST.XOR(b, c + 1) << '\n';
        }
    }
    return 0;
}