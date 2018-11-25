/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Animal
{
public:
  string name;

  virtual void print_name();
  Animal(){
    cout << "Default constructor is called" << endl;
    name = "no name";
  }
  Animal(string given_name){
    cout << "Parameterized constructor is called" << endl;
    name = given_name;
  }
  Animal(const Animal &animal){
    cout << "Copy constructor is called" << endl;
    name = animal.name;
  }
  Animal& operator=(const Animal &animal){
    cout << "Assignment operator is called" << endl;
    name = animal.name;
    return  *this;
  }
  ~Animal(){
    //cout << "Deconstructor is called for (scope ends): " << name << endl;
    
  }
  
};
void Animal::print_name(){
  cout << "I'm an animal and my name is " << name << endl;
}

class Dog :  public Animal
{
public:
  string name_dog;

  void print_name();
};
void Dog::print_name(){
  cout << "I'm a dog and my name is " << name << endl;
}

vector<int> merge_two_array(vector<int> &a, vector<int> &b){
    vector<int> c;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(c));
    auto it = unique(c.begin(), c.end());
    c.erase(it, c.end());

    for(auto & ic : c) cout << ic << endl;

    return c;
}

vector<int> merge_two_array_algo(vector<int> &a, vector<int> &b){
    vector<int> c;
    unordered_map<int,int> hash;
    for(auto & ia : a){
      if(hash.find(ia) == hash.end()){
        hash[ia] = 1;
        c.push_back(ia);
      }
    }
    for(auto & ib : b){
      if(hash.find(ib) == hash.end()){
        hash[ib] = 1;
        c.push_back(ib);
      }
    }

    for(auto & ic : c) cout << ic << endl;

    return c;
}
int main()
{
    //vectors
    vector<int> a = {2,-4,0,111};
    vector<int> b = {3455,0,9,-1,2};
    vector<int> c1, c2;
    c1 = merge_two_array(a,b);
    c2 = merge_two_array_algo(a,b);
    
    //OO
    //initialization by default constructor
    Animal animal1;           animal1.print_name();
    animal1.name = "Zik";     animal1.print_name();

    //initialization by parameterized constructor
    Animal animal2("Bean");   animal2.print_name();

    //initialization by copy constructor 
    Animal animal3(animal1);  animal3.print_name();
    animal1.name = "Ziky";    animal3.print_name(); //shallow copy

    //initialization by copy constructor also
    Animal animal4 = animal2; animal4.print_name();

    //assignment by copy assignment operator (since animal4 is not new and already exists)
    animal4 = animal1;        animal4.print_name();


    Dog dog1;
    dog1.name_dog = "Doggy";
    dog1.name = "Animaly";    dog1.print_name();



    return 0;
}
