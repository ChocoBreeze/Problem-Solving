#include<iostream>
#include<string>
int main()
{
	std::string input;
	std::cin >> input;
	int count = 0;
	for (int i = 0; i<input.length(); ++i) {
		if (input.substr(i, 2).compare("c=") == 0) ++i;
		else if (input.substr(i, 2).compare("c-") == 0) ++i;
		else if (input.substr(i, 3).compare("dz=") == 0) i+=2;
		else if (input.substr(i, 2).compare("d-") == 0) ++i;
		else if (input.substr(i, 2).compare("lj") == 0) ++i;
		else if (input.substr(i, 2).compare("nj") == 0) ++i;
		else if (input.substr(i, 2).compare("s=") == 0) ++i;
		else if (input.substr(i, 2).compare("z=") == 0) ++i;
		++count;
	}
	std::cout << count;
	return 0;
}