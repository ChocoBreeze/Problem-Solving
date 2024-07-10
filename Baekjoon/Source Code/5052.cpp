// 한 글자에 대한 처리가 미흡했음.
// 7304KB, 92ms
#include <iostream>
#include <string>

using namespace std;

struct Trie
{
	bool isFinished;
	Trie *next[10]; // 0 ~ 9
	Trie(bool isFinished) : isFinished(isFinished)
	{
		for (int i = 0; i < 10; ++i)
		{
			next[i] = nullptr;
		}
	}
	~Trie()
	{
		for (int i{}; i < 10; ++i)
		{
			if (next[i] != nullptr)
				delete next[i];
		}
	}
};

int main()
{
	cin.tie(NULL)->sync_with_stdio(false);
	int T{};
	cin >> T;

	for (int tc{1}; tc <= T; ++tc)
	{
		int n;
		cin >> n; // 전화번호 수
		Trie *head = new Trie(false);

		for (int i{}; i < 10; ++i)
		{
			head->next[i] = nullptr;
		}
		bool chk{true}; // false : 일관성 없는 상태
		for (int i{}; i < n; ++i)
		{
			string str;
			cin >> str;

			if (chk)
			{ // 이미 chk가 false인 경우 실행할 필요 없음
				bool result = [&]() -> bool
				{
					int idx{0};
					int startNum = str[idx] - '0';
					if (head->next[startNum] == nullptr)
					{ // 새로 할당
						head->next[startNum] = new Trie(false);
					}
					else
					{ // 이미 있다
						if (head->next[startNum]->isFinished)
						{
							return false; // 한 글자에서 끝난 친구가 있다.
						}
						else if ((int)str.length() == 1)
						{ // startNum이 마지막 문자인 경우
							return false;
						}
					}
					Trie *now = head->next[startNum];

					for (; idx + 1 < (int)str.length(); ++idx)
					{
						int nextNum = str[idx + 1] - '0';
						if (now->next[nextNum] == nullptr)
						{ // 새로
							now->next[nextNum] = new Trie(false);
						}
						else
						{ // 기존
							if (now->next[nextNum]->isFinished)
							{ // 여기서 끝난 친구가 있는 경우
								return false;
							}
							else if (idx + 1 == (int)str.length() - 1)
							{ // nextNum이 마지막 문자인 경우
								return false;
							}
						}
						now = now->next[nextNum];
					}
					now->isFinished = true;
					return true;
				}();
				if (!result)
					chk = false; // 일관성 깨짐
			}
		}
		delete head;
		if (chk)
			cout << "YES\n";
		else
			cout << "NO\n";
	}

	return 0;
}