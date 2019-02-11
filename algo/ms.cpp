#include <string>
#include <iostream>

using namespace std;

// 26= 26     Z  1 0
// 27= 26 1   A  1 1
// 51= 26 25  AY 1 25
// 52 = 26 26 AZ 2 0
string xls(int n)
{
    string ret;
    while (n > 0)
    {
        int r = n % 26;

        if (r == 0)
        {
            ret = "Z" + ret;
            n /= 26 - 1;
        }
        else
        {
            char x = (r - 1) + 'A';
            ret = x + ret;
            n /= 26;
        };
    }
    return ret;
}
int main()
{
    cout << xls(705) << endl;
    return 0;
}