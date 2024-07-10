#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

struct Trie
{
    int count;
    // unique_ptr<Trie> next[26]; // 다음 알파벳
    Trie *next[26];
    Trie(int count = 0) : count(count)
    {
        for (int i{}; i < 26; ++i)
        {
            this->next[i] = nullptr;
        }
    }
    ~Trie()
    {
        for (int i{}; i < 26; ++i)
        {
            if (this->next[i] != nullptr)
                delete this->next[i];
        }
    }
};

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    // 소수점 2자리
    cout << fixed;
    cout.precision(2);

    int N;
    while (cin >> N)
    {
        // unique_ptr<Trie> head = make_unique<Trie>(new Trie);

        // 1. Trie 만들기
        Trie *head = new Trie;
        vector<string> strs(N);
        for (int n = 0; n < N; ++n)
        {
            cin >> strs[n];
            // MakeTrie
            int index = strs[n][0] - 'a';
            if (!head->next[index])
            { // nullptr
                // head->next[str[0]-'a'] = make_unique<Trie>(new Trie);
                head->next[index] = new Trie;
            }
            head->next[index]->count++;

            Trie *now = head->next[index];

            for (int s = 1; s < (int)strs[n].length(); ++s)
            {
                index = strs[n][s] - 'a';
                if (!now->next[index])
                {
                    now->next[index] = new Trie;
                }
                now->next[index]->count++;
                now = now->next[index];
            }
        }

        // 2. 개수 세기
        double total{};
        for (int n = 0; n < N; ++n)
        {
            int cnt{1}; // 첫 글자는 무조건
            int index = strs[n][0] - 'a';
            Trie *now = head->next[index];

            for (int s = 1; s < (int)strs[n].length(); ++s)
            {
                index = strs[n][s] - 'a';
                if (now->count != now->next[index]->count)
                { // 다른 문자로 가는 길이 존재함
                    ++cnt;
                }
                now = now->next[index];
            }

            total += cnt;
        }

        cout << total / N << '\n';
        delete head;
    }

    return 0;
}