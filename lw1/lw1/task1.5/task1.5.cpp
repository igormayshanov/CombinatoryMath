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

    int k;
    cout << "Enter number of placements: ";
    cin >> k;
    cout << "\n";

    boost::timer t;
    t.restart();

    vector<int> v(k + 1, 0);

    while (v[k] != 1)
    {
        //copy(v.begin(), v.end() - 1, std::ostream_iterator<size_t>(std::cout, " "));
        //cout << "\n";
        int i = 0;
        while (v[i] == N - 1)
        {
            v[i] = 0;
            ++i;
        }
        ++v[i];
    }
    double duration = t.elapsed();
    cout << duration << "\n";
}