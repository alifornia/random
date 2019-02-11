#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

vector<int> bfs_sd(pair<int, int> s, pair<int, int> d, vector<vector<int>> m)
{
    vector<int> shortest_path;
    return shortest_path;
}
void print(const vector<vector<int>> &m)
{
    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[0].size(); j++)
            cout << m[i][j] << " ";
        cout << endl;
    }
}
bool isValid(const pair<int, int> &s, const pair<int, int> offset, const vector<vector<int>> &m)
{
    int row = s.first + offset.first;
    int col = s.second + offset.second;
    //cout << "isV (" << row << "," << col << ") = " << m[row][col] << endl;
    if (-1 < row && row < m.size() && -1 < col && col < m[0].size())
        return (m[row][col] != 0);
    return false;
}
vector<int> bfs_s(pair<int, int> s, const vector<vector<int>> m)
{
    int row = s.first;
    int col = s.second;
    pair<int, int> cell;
    vector<vector<bool>> visited(m.size(), vector<bool>(m[0].size(), 0));

    int l = 0;

    vector<int> shortest_path;
    queue<pair<int, int>> qcell;
    queue<int> qlen;
    queue<pair<int, int>> qpath;
    visited[row][col] = true;
    qcell.push(s);
    qlen.push(0);

    while (!qcell.empty())
    {
        cell = qcell.front();
        qcell.pop();
        l = qlen.front();
        qlen.pop();
        cout << "w (" << cell.first << "," << cell.second << ")" << endl;
        cout << "here1" << endl;
        if (isValid(cell, {0, -1}, m) && !visited[cell.first][cell.second - 1])
        {
            cout << "1 (" << cell.first << "," << cell.second - 1 << ")" << endl;
            visited[cell.first][cell.second - 1] = true;
            qcell.push({cell.first, cell.second - 1});
        }
        cout << "here2" << endl;
        if (isValid(cell, {-1, 0}, m) && !visited[cell.first - 1][cell.second])
        {
            cout << "2 (" << cell.first - 1 << "," << cell.second << ")" << endl;
            visited[cell.first - 1][cell.second] = true;
            qcell.push({cell.first - 1, cell.second});
        }
        cout << "here3" << endl;
        if (isValid(cell, {0, +1}, m) && !visited[cell.first][cell.second + 1])
        {
            cout << "3 (" << cell.first << "," << cell.second + 1 << ")" << endl;
            visited[cell.first][cell.second + 1] = true;
            qcell.push({cell.first, cell.second + 1});
        }
        cout << "here4" << endl;
        if (isValid(cell, {+1, 0}, m) && !visited[cell.first + 1][cell.second])
        {
            cout << "4 (" << cell.first + 1 << "," << cell.second << ")" << endl;
            visited[cell.first + 1][cell.second] = true;
            qcell.push({cell.first + 1, cell.second});
        }
        cout << "there" << endl;
    }
    return shortest_path;
}

int main()
{
    vector<vector<int>> m = {{1, 1, 1, 1, 0}, {2, 0, 0, 1, 1}, {1, 1, 1, 1, 1}, {0, 1, 9, 1, 0}};
    print(m);
    bfs_s({1, 0}, m);
    return 0;
}