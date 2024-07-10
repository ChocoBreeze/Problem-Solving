// unique_ptr
// 7304KB, 112ms
#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct Trie
{
    bool isFinished;
    // Trie* next[10]; // 0 ~ 9
    unique_ptr<Trie> next[10];
    Trie(bool isFinished) : isFinished(isFinished)
    {
        for (int i = 0; i < 10; ++i)
        {
            next[i] = nullptr;
        }
    }
    ~Trie() = default;
};

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    int T{};
    cin >> T;

    for (int tc{1}; tc <= T; ++tc)
    {
        int n;
        cin >> n; // ��ȭ��ȣ ��
        unique_ptr<Trie> head = make_unique<Trie>(new Trie(false));
        head->isFinished = false;
        for (int i{}; i < 10; ++i)
        { // ��� �� ��
            head->next[i] = nullptr;
        }

        bool chk{true}; // false : �ϰ��� ���� ����
        for (int i{}; i < n; ++i)
        {
            string str;
            cin >> str;

            if (chk)
            { // �̹� chk�� false�� ��� ������ �ʿ� ����
                bool result = [&]() -> bool
                {
                    int idx{0};
                    int startNum = str[idx] - '0';
                    if (head->next[startNum] == nullptr)
                    { // ���� �Ҵ�
                        head->next[startNum] = make_unique<Trie>(new Trie(false));
                        head->next[startNum]->isFinished = false; // �� �ʱ�ȭ�� �� �Ǵ� ����?
                    }
                    else
                    { // �̹� �ִ�
                        if (head->next[startNum]->isFinished)
                        {
                            return false; // �� ���ڿ��� ���� ģ���� �ִ�.
                        }
                        else if ((int)str.length() == 1)
                        { // startNum�� ������ ������ ���
                            return false;
                        }
                    }
                    Trie *now = head->next[startNum].get();

                    for (; idx + 1 < (int)str.length(); ++idx)
                    {
                        int nextNum = str[idx + 1] - '0';
                        if (now->next[nextNum] == nullptr)
                        { // ����
                            now->next[nextNum] = unique_ptr<Trie>(new Trie(false));
                            now->next[nextNum]->isFinished = false; // �� �ʱ�ȭ�� �� �Ǵ� ����?
                                                                    // now->next[nextNum] = make_unique<Trie>(new Trie(false));
                        }
                        else
                        { // ����
                            if (now->next[nextNum]->isFinished)
                            { // ���⼭ ���� ģ���� �ִ� ���
                                return false;
                            }
                            else if (idx + 1 == (int)str.length() - 1)
                            { // nextNum�� ������ ������ ���
                                return false;
                            }
                        }
                        now = now->next[nextNum].get(); // copy impossible
                    }
                    now->isFinished = true;
                    return true;
                }();
                if (!result)
                    chk = false; // �ϰ��� ����
            }
        }

        if (chk)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}