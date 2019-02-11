#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

vector<int> bfs_sd(pair<int, int> s, pair<int, int> d, vector<vector<int>> m)
{
    vector<int> shortest_path;
}

bool isValid(const pair<int, int> &s, const pair<int, int> &offset, const vector<vector<int>> &m)
{
    int x = s.first + offset.first;
    int y = s.second + offset.second;
    if (x < m[0].size && y < m.size)
        return m[x][y] == 1;
    return false;
}
vector<int> bfs_s(pair<int, int> s, const vector<vector<int>> m)
{
    int sx = s.first;
    int sy = s.second;
    pair<int, int> cell;
    vector<vector<bool>> visited = ;
    int l = 0;

    vector<int> shortest_path;
    queue<pair<int, int>> qcell;
    queue<int> qlen;
    queue<pair<int, int>> qpath;
    qcell.push(s);
    qlen.push(0);
    while (!qcell.empty)
    {
        cell = qcell.front();
        qcell.pop();
        l = qlen.front();
        qlen.pop();
        if (isValid(cell, {-1, 0}, m))
        {
        }
        if (isValid(cell, {0, -1}, m))
        {
        }
        if (isValid(cell, {+1, 0}, m))
        {
        }
        if (isValid(cell, {0, +1}, m))
        {
        }
    }
}

int main()
{
    vector<vector<int>> m = {{1, 1, 1, 1, 0}, {0, 2, 0, 1, 0}, {1, 1, 1, 1, 0}, {0, 1, 9, 1, 0}};
    return 0;
}