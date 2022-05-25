#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

void GetRandomPermutation(vector<int>& input)
{
	for (int i = 0; i < input.size(); ++i)
	{
		int random = rand() % input.size();
		swap(input[i], input[random]);
	}
}

int main()
{
	srand(time(0));
	vector<int> v = { 1, 2, 3, 4, 5 };
	cout << "Input array: ";
	copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
	cout << "\n";
	char repeat = 121;
	do
	{
		GetRandomPermutation(v);
		cout << "Random permutation:\n";
		copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
		cout << "\n";

		cout << "\nGenerate random permutation again? y/n : ";
		cin >> repeat;
	} while (repeat == 121);
}