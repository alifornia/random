
#include <iostream>

using namespace std;
//&str1 is exactly the original str1 whose type is char *
void swapr(char *&str1, char *&str2)
{
    char *temp = str1;
    str1 = str2;
    str2 = temp;
}

//str1 is a pointer to char *
void swapp(char **str1, char **str2)
{
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

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

    char *str1 = "ONE";
    char *str2 = "TWO";
    //swapr(str1, str2);
    swapp(&str1, &str2);

    cout << "str1 is " << str1 << endl;
    cout << "str2 is " << str2 << endl;
    return 0;
}
