#include <iostream>
#include <string>

using namespace std;

int atoi(string s)
{
    int r = 0;
    int sign = 1;
    int it = 0;
    if (s.size() == 0)
        return 0;
    if (s[0] == '-')
    {
        it = 1;
        sign = -1;
    }
    if (s[0] == '+')
    {
        it = 1;
        sign = +1;
    }
    for (int i = it; i < s.size(); i++)
    {
        r += r * 10 + s[i] - '0';
    }
    return sign * r;
}
int main()
{

    cout << "hey" << endl;
    cout << 10 * atoi("-123") << endl;
    return 0;
}