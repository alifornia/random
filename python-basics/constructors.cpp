#include <iostream>

using namespace std;

class X
{
  private:
  public:
    int i;
    int *pi;
    X() : pi(new int) {}
    X(int i, int *pi) : i(i), pi(pi) {}
    //X(const X &copy) : i(copy.i), pi(copy.pi) {} // shallow copy
    X(const X &copy) : i(copy.i), pi(new int(*copy.pi)) {} // deep copy
};

int main()
{

    int p[] = {1, -1, 0};
    X x1(1, p);
    X x2(x1);
    x2.pi[0] = 2;
    cout << *x1.pi << endl;
    cout << *x2.pi << endl;

    return 0;
}