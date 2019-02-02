#include <iostream>
#include <sstream>
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
    // read line by line till CTRL+D (no matter how many lines)
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

    for (int i = 0; i < v.size(); i++)
        cout << v[i] << endl;
    return 0;
}