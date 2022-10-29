#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Vector.h"
using namespace yazi::stl;

#include <sys/time.h>

int main()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int start_sec = tv.tv_sec;
    int start_usec = tv.tv_usec;

    const int max = 10000;
    Vector<bool> v;
    for (int i = 0; i < max; i++)
    {
        v.insert(v.begin(), true);
    }

    gettimeofday(&tv, NULL);
    int end_sec = tv.tv_sec;
    int end_usec = tv.tv_usec;
    double time_diff = (end_sec - start_sec) * 1000000 + (end_usec - start_usec);
    std::cout << time_diff / 1000 / max << "ms" << std::endl;

    return 0;
}
