#include <iostream>
#include <string>

using namespace std;

int main()
{
    string a = "mammad", b = "ammat";
    long aa = (long)a.c_str(), bb = (long)b.c_str();

    aa = aa ^ bb;
    bb = aa ^ bb;
    aa = aa ^ bb;

    cout << (char *)(aa) << endl;
}