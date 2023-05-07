// https://www.acmicpc.net/source/58156369
// 간단 & 빠른
// 2852KB, 116ms
#include <iostream>
#include <unordered_set>
#include <string>
using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int T, N;
	bool flag;
	string str;
	cin >> T;
	while (T--)
	{
		flag = false;
		cin >> N;
		unordered_set<string> phoneMap;
		while (N--)
		{
			cin >> str;
			phoneMap.insert(str);
		}

		flag = [&]() -> bool
		{
			for (auto &p : phoneMap)
			{
				int l = p.length() - 1; // 자기 자신은 찾으면 안 되서
				int i = 0;
				str = "";
				while (i < l)
				{
					str += p[i++];
					if (phoneMap.count(str) != 0)
						return true;
				}
			}
			return false;
		}();

		if (flag)
			cout << "NO"
				 << "\n";
		else
			cout << "YES"
				 << "\n";
	}
	return 0;
}