
#include <iostream>

using namespace std;

int main()
{
    int i = -1;
    const int ci = -2;
    int *pi;
    pi = &i;
    //pi = &ci; error
    int *qi;
    qi = pi;

    const int *pci; //ptr to cns int, same as int const *
    pci = pi;

    //int *const cp; error must be initilized
    int *const cpi = &i;
    //cpi = &i; error cuz it's const
    *cpi = i;

    const int *const cpci = &i;
    //*cpci = i; error
    //cpci = &i; error

    //int &r; error must be initilized
    int &ri = i;
    cout << &ri << endl;
    cout << &ri << endl;

    return 0;
}