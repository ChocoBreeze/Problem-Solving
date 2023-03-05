// https://www.acmicpc.net/source/54704398
// 우왕..
#include <iostream>
#include <algorithm>
using namespace std;

int arr[5000];
bool parcel[400000];

int main() {
	cin.tie(NULL)->sync_with_stdio(false);

	int w, N; cin >> w >> N;
	for (int i = 0; i < N; i++)
		cin >> arr[i];
	sort(arr, arr + N);

	bool ans = false;
	[&]() {
		for (int i = 1; i < N; i++) {
			for (int j = 0; j < i; j++)
				parcel[arr[i] + arr[j]] = true;

			for (int j = i + 2; j < N; j++) {
				int remainder = w - arr[i + 1] - arr[j];
				if (remainder <= 0)
					break;
				if (400000 <= remainder)
					continue;
				if (parcel[remainder]) {
					ans = true;
					return; // 이거 때문에 람다 쓴 거 같은데..(break 여러 번 안 해도 되서 편한듯?)
				}
			}
		}
	} ();

	if (ans)
		cout << "YES\n";
	else
		cout << "NO\n";

	return 0;
}