export module Utils;

import std;

export namespace Utils
{
	std::vector<int> factorial_sequence = { 0, 1 };

	int get_factorial(int n)
	{
		for (int i = factorial_sequence.size(); i <= n; i++)
		{
			factorial_sequence.push_back(factorial_sequence[i - 1] * i);
		}
		return factorial_sequence[n];
	}
}