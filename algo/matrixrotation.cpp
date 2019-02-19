#include <iostream>
#include <vector>
#include <sstream>

using namespace std;
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v)
{ // print util CMT laterrr
    copy(v.begin(), v.end(), ostream_iterator<T>(cout, " "));
    return os;
}

int main()
{
    vector<vector<int>> v;
    string line;
    int value;
    while (getline(cin, line))
    {
        v.push_back(vector<int>());
        stringstream split(line);
        while (split >> value)
            v.back().push_back(value);
    }

    return 0;
}