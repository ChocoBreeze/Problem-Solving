// unique_ptr
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

struct Trie
{
    int count;
    unique_ptr<Trie> next[26]; // ���� ���ĺ�
    Trie(int count = 0) : count(count) {}
    ~Trie() = default;
};

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    // �Ҽ��� 2�ڸ�
    cout << fixed;
    cout.precision(2);

    int N;
    while (cin >> N)
    {
        // 1. Trie �����
        // unique_ptr<Trie> head = make_unique<Trie>(new Trie()); // �� �̰� ��������?..
        // https://stackoverflow.com/questions/45471536/make-unique-error-in-compile-time
        unique_ptr<Trie> head = unique_ptr<Trie>(new Trie);

        vector<string> strs(N);
        for (int n = 0; n < N; ++n)
        {
            cin >> strs[n];
            // MakeTrie
            int index = strs[n][0] - 'a';
            if (!head->next[index])
            { // nullptr
                head->next[index] = unique_ptr<Trie>(new Trie);
            }
            head->next[index]->count++;

            Trie *now = head->next[index].get(); // ��������

            for (int s = 1; s < (int)strs[n].length(); ++s)
            {
                index = strs[n][s] - 'a';
                if (!now->next[index])
                {
                    now->next[index] = unique_ptr<Trie>(new Trie);
                }
                now->next[index]->count++;
                now = now->next[index].get();
            }
        }

        // 2. ���� ����
        double total{};
        for (int n = 0; n < N; ++n)
        {
            int cnt{1}; // ù ���ڴ� ������
            int index = strs[n][0] - 'a';
            Trie *now = head->next[index].get();

            for (int s = 1; s < (int)strs[n].length(); ++s)
            {
                index = strs[n][s] - 'a';
                if (now->count != now->next[index]->count)
                { // �ٸ� ���ڷ� ���� ���� ������
                    ++cnt;
                }
                now = now->next[index].get();
            }

            total += cnt;
        }

        cout << total / N << '\n';
    }

    return 0;
}