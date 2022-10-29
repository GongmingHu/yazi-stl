#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "Vector.h"
using namespace yazi::stl;

#include <sys/time.h>

int main()
{
    // Vector<int> v;
    // v.push_back(1);
    // v.push_back(2);
    // v.push_back(3);
    // v.push_back(4);
    // v.erase(v.find(2), v.find(4));
    // v.show();

    // Vector<string> v;
    // v.push_back("a");
    // v.push_back("b");
    // v.push_back("c");
    // v.push_back("d");
    // v.erase(v.find("b"), v.find("d"));
    // v.show();

    Vector<bool> v;
    v.push_back(true);
    v.push_back(false);

    struct timeval tv;
    gettimeofday(&tv, NULL);
    int start_sec = tv.tv_sec;
    int start_usec = tv.tv_usec;

    const int max = 100000;
    Vector<bool> v2;
    for (int i = 0; i < max; i++)
    {
        v2 = v;
    }

    gettimeofday(&tv, NULL);
    int end_sec = tv.tv_sec;
    int end_usec = tv.tv_usec;
    double time_diff = (end_sec - start_sec) * 1000000 + (end_usec - start_usec);
    std::cout << time_diff / 1000 / max << "ms" << std::endl;

    return 0;
}
