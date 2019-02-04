
#include <iostream>

using namespace std;

int main()
{
    int a = -1;
    cout << "a" << endl;
    cout << a << endl;
    cout << &a << endl
         << endl;
    const int ca = -2;
    cout << "ca" << endl;
    cout << ca << endl;
    cout << &ca << endl
         << endl;

    int *p;
    p = &a;
    //p = &ca; error
    cout << "p" << endl;
    cout << p << endl;
    cout << *p << endl;
    cout << &p << endl
         << endl;

    int *q;
    q = p;
    cout << "q" << endl;
    cout << q << endl;
    cout << *q << endl;
    cout << &q << endl
         << endl;

    //ptr to cns int
    //same as int const *
    const int *pc;
    pc = p;
    cout << "pc" << endl;
    cout << pc << endl;
    cout << *pc << endl;
    cout << &pc << endl
         << endl;

    int *const cp;
    cp = &a;
    return 0;
}