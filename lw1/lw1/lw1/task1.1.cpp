
#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/timer.hpp>

int main()
{
    std::vector<size_t> v = { 7, 1, 12, 5, 9, 20, 15, 2, 3, 4, 8, 6, 10, 11 };

    //, 6, 10, 11, 13
    boost::timer t;
    t.restart();
    std::sort(v.begin(), v.end());
    do
    {
        // copy(v.begin(), v.end(), std::ostream_iterator<size_t>(std::cout, " "));
      //   std::cout << "\n";
    } while (std::next_permutation(v.begin(), v.end()));
    double duration = t.elapsed();
    std::cout << duration << "\n";
}