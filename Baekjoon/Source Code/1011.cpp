/*
2
1	1

---------------------------------------------
3
1	1	1

4
1	2	1

---------------------------------------------
5
1	2	1	1

6
1	2	2	1

---------------------------------------------
7
1	2	1	2	1

8
1	2	2	2	1

9
1	2	3	2	1

---------------------------------------------
10
1	2	3	2	1	1

12
1 	2	3	3	2	1
---------------------------------------------
13
16
1	2	3	4	3	2	1
17
20
1	2	3	4	4	3	2	1

1	->	1

2	->	2		1
3	->	3~4		2

4	->	5~6		2
5	->	7~9		3

6	->	10~12		3
7	->	13~16		4

8	->	17~20		4
9	->	21~25		5

10	->	26~30		6
11	->	31~36		7

*/
#include<iostream>
#include<string>
int main()
{
	long long int N, x, y;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> x >> y;
		int interval = y - x - 1, answer = 1, start_num = 1;
		while (interval!=0) {
			interval -= (start_num++);
			answer++;
			if (interval <= 0) break;

			interval -= (start_num);
			answer++;
			if (interval <= 0) break;
		}
		std::cout << answer << std::endl;
	}
	return 0;
}
