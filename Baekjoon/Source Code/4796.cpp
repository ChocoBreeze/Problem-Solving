// https://www.acmicpc.net/board/view/92320

#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int L, P, V;
	for(int i=1;;++i) {
		cin >> L >> P >> V;
		if (L == 0 && P == 0 && V == 0) break;
		int answer = L * (V / P) + min(V % P, L);
		cout << "Case " << i << ": " << answer << "\n";
	}
	return 0;
}