#include <iostream>
#include <vector>

using namespace std;

class Graph
{
  private:
    struct Node
    {
        int data;
        vector<unique_ptr<Node>> neighbours;
    };

  public:
};
int main()
{

    return 0;
}