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
    int col, row, r;
    col = v[0][0];
    row = v[0][1];
    r = v[0][2];
    v.erase(v.begin(), v.begin() + 1);

    int rings = min(col, row) / 2;
    int temp_element;
    for (int i = 0; i < rings; i++)
    {
        //avoid 360 rotation for each ring
        int rotations = r % (2 * (col + row - 4 * i) - 4);
        for (int rot = 0; rot < rotations; rot++)
        {
            //upper row
            for (int j = i; j < row - i - 1; j++)
            {
                temp_element = v[i][j];
                v[i][j] = v[i][j + 1];
                v[i][j + 1] = temp_element;
            }
            //right column
            for (int j = i; j < col - i - 1; j++)
            {
                temp_element = v[j][row - i - 1];
                v[j][row - i - 1] = v[j + 1][row - i - 1];
                v[j + 1][row - i - 1] = temp_element;
            }
            //bottom row
            for (int j = row - i - 1; j > i; j--)
            {
                temp_element = v[col - i - 1][j];
                v[col - i - 1][j] = v[col - i - 1][j - 1];
                v[col - i - 1][j - 1] = temp_element;
            }
            //left column
            for (int j = col - i - 1; j > i + 1; j--)
            {
                temp_element = v[j][i];
                v[j][i] = v[j - 1][i];
                v[j - 1][i] = temp_element;
            }
        }
    }
    for (int c = 0; c < col; c++)
        cout << v[c] << endl;
    return 0;
}