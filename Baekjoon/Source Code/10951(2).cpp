#include <iostream>
int main()
{
    int A, B;
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    while (!(std::cin >> A >> B).eof())
    {
        std::cout << A + B << "\n";
    }
    return 0;
}