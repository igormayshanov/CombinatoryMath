#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/timer.hpp>

int main()
{
	boost::timer t;
	t.restart();

	int numOfElements;
	std::cout << "Enter the number of elements to permutate: ";
	std::cin >> numOfElements;
	std::cout << "\n";

	const int borderMarks = 2;
	int fullConteinerSize = numOfElements + borderMarks;

	std::vector<int> currentPermutation(fullConteinerSize);
	std::vector<int> reversePermutation(fullConteinerSize);
	std::vector<int> directions(fullConteinerSize);
		
	for (int i = 1; i <= numOfElements; i++)
	{
		currentPermutation[i] = i;
		reversePermutation[i] = i;
		directions[i] = i;
	}
	
	directions.front() = 0;
	currentPermutation.front() = currentPermutation.back() = numOfElements + 1;
	int mobileNumber = 0;
	while (mobileNumber != 1)
	{
		copy(currentPermutation.begin(), currentPermutation.end(), std::ostream_iterator<size_t>(std::cout, " "));
		std::cout << "\n";
		mobileNumber = numOfElements;
		while (currentPermutation[reversePermutation[mobileNumber] + directions[mobileNumber]] > mobileNumber && mobileNumber > 1)
		{
			directions[mobileNumber] = -directions[mobileNumber];
			mobileNumber = mobileNumber - 1;
		}

		std::swap(currentPermutation[reversePermutation[mobileNumber]],
			currentPermutation[reversePermutation[mobileNumber] + directions[mobileNumber]]);
		std::swap(reversePermutation[currentPermutation[reversePermutation[mobileNumber]]],
			reversePermutation[mobileNumber]);
	}
	double duration = t.elapsed();
	std::cout << duration << "\n";
}