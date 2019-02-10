#include <iostream>

using namespace std;

class X
{
  private:
  public:
    int i;
    int *pi;
    X() : pi(new int) {}                //user defined default constructor
    X(int i, int *pi) : i(i), pi(pi) {} //user defined default constructor with initializer
    //X(const X &copy) : i(copy.i), pi(copy.pi) {} // user defined copy constructor shallow copy
    X(const X &copy) : i(copy.i), pi(new int(*copy.pi)) {} // user defined copy constructor shallow copy
};

int main()
{

    int p[] = {2, 3};
    X x0;
    x0.pi = p;
    X x1(1, p);
    X x2(x1);  //cc
    X x3 = x1; //cc
    X x4;
    x4 = x1; //as
    x2.pi[0] = -2;
    x2.i = 2;
    x1.i = -100;
    cout << x0.i << " - " << *x0.pi << endl;
    cout << x1.i << " - " << *x1.pi << endl;
    cout << x2.i << " - " << *x2.pi << endl;
    cout << x3.i << " - " << *x3.pi << endl;
    cout << x4.i << " - " << *x4.pi << endl;

    //default constructor (default default or user-defined default!):
    //discussing shallow or deep does not even make sense :D no copy

    //copy constructor
    //i member of class is always deep copied (different)
    //pi member of class is always shallow copied (same) unless a user defined copy constructor with deep copy implemented
    return 0;
}