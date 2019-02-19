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
    int col = 5;
    int row = 4;
    int r = 7;

    int rings = min(col, row) / 2;
    cout << "rings: " << rings << endl;
    int temp_element;
    for (int ring = 0; ring < rings; ring++)
    {
        //avoid 360 rotation for each ring
        int rotations = r % (2 * (col + row - 4 * ring) - 4);
        for (int rot = 0; rot < rotations; rot++)
        {
            for (int urow = ring; urow < row - ring - 1; urow++)
            {
                temp_element = v[ring][urow];
                v[ring][urow] = v[ring][urow + 1];
                v[ring][ring + 1] = temp_element;
            }
            for (int rcol = ring; rcol < col - ring - 1; rcol++)
            {
                temp_element = v[rcol][row - ring - 1];
                v[rcol][row - ring - 1] = v[rcol + 1][row - ring - 1];
                v[rcol + 1][row - ring - 1] = temp_element;
            }
            for (int brow = row - ring - 1; brow > ring; brow--)
            {
                temp_element = v[ring][brow];
                v[ring][brow] = v[col - ring - 1][brow - 1];
                v[col - ring - 1][brow - 1] = temp_element;
            }
            for (int lcol = col - ring - 1; lcol > ring; lcol--)
            {
                temp_element = v[lcol][ring];
                v[lcol][ring] = v[lcol - 1][ring];
                v[lcol - 1][ring] = temp_element;
            }
        }
    }
    for (int c = 0; c < col; c++)
        cout << v[c] << endl;
    return 0;
}