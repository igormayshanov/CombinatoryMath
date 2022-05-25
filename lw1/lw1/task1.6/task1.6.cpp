#include <iostream>
#include <vector>
#include <boost/timer.hpp>

using namespace std;

int main()
{
	int N;
	cout << "Enter number of elements: ";
	cin >> N;
	cout << "\n";

	boost::timer t;
	t.restart();

	vector<int> v(N, 0);

	while (v[v.size() - 1] != 1)
	{
		copy(v.begin(), v.end() - 1, std::ostream_iterator<size_t>(std::cout, " "));
		cout << "\n";
		int i = 0;
		while (v[i] == 1)
		{
			v[i] = 0;
			i = i + 1;
		}
		v[i] = 1;
	}

	double duration = t.elapsed();
	cout << duration << "\n";
}
