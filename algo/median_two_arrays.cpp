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

double findMedian(vector<int> &v1, vector<int> &v2)
{
    int i = 0;
    int j = 0;
    int v1s = v1.size();
    int v2s = v2.size();
    int vs = (v1s + v2s);
    int med[2] = {0, 0};
    int m = 0;
    for (int k = 0; k < vs / 2 + 1; k++)
    {
        cout << "k=" << k << ": ";
        if (i != v1s && j != v2s)
        {
            cout << "1(" << i << "," << j << ") --> ";
            if (v1[i] < v2[j])
                m = v1[i++];
            else
                m = v2[j++];
            cout << "1(" << i << "," << j << ") = " << m << endl;
        }
        else if (i == v1s)
        {
            cout << "2(" << i << "," << j << ") --> ";
            m = v2[j++];
            cout << "2(" << i << "," << j << ") = " << m << endl;
        }
        else if (j == v2s)
        {
            cout << "3(" << i << "," << j << ") --> ";
            m = v1[i++];
            cout << "3(" << i << "," << j << ") = " << m << endl;
        }
        med[0] = med[1];
        med[1] = m;
    }
    if (vs % 2 == 1) //odd
        return double(max(med[0], med[1]));
    else
        return double(med[0] + med[1]) / 2.0;
}
int main()
{
    // read
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

    cout << findMedian(v[0], v[1]) << endl;
    return 0;
}