#include <boost/timer.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	cout << "Enter the number of elements: ";
	int size;
	cin >> size;
	cout << "\n";

	boost::timer t;
	t.restart();

	int sizeWithBorders = size + 2;

	vector<int> currPermutation(sizeWithBorders);
	vector<int> reversePermutation(sizeWithBorders);
	vector<int> direction(sizeWithBorders);

	for (int i = 1; i <= size; ++i)
	{
		currPermutation[i] = i;
		reversePermutation[i] = i;
		direction[i] = -1;
	}

	direction[0] = 0;
	currPermutation[0] = size + 1;
	currPermutation.back() = size + 1;

	int border = 0;

	while (border != 1)
	{
		copy(currPermutation.begin(), currPermutation.end(), std::ostream_iterator<size_t>(std::cout, " "));
		cout << "\n";
		border = size;
		while (currPermutation[reversePermutation[border] + direction[border]] > border && border > 1)
		{
			direction[border] = -direction[border];
			border = border - 1;
		}

		swap(currPermutation[reversePermutation[border]],
			currPermutation[reversePermutation[border] + direction[border]]);
		swap(reversePermutation[currPermutation[reversePermutation[border]]],
			reversePermutation[border]);
	}

	double duration = t.elapsed();
	cout << "\n"
		<< duration << "\n";
}