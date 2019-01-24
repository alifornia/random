#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int find_nonrecurring(vector<int> v)
{
    unordered_map<int, int> hash;
    for (const auto &vi : v)
    {
        hash[vi]++;
    }
    for (const auto &h : hash)
    {
        if (h.second < 2)
            cout << h.first << " ";
    }
    cout << endl;
    return 0;
}

int main()
{
    vector<int> v = {1, 1, 1, 2, -1, -1, 0};
    find_nonrecurring(v);
    return 0;
}