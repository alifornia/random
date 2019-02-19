#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int time;
    bool vidited = false;
    vector<Node *> child;
};

int dfs(Node *&root)
{
    int sum = 0;
    if (root != nullptr)
    {
        if (root->vidited == false)
        {
            for (int i = 0; i < root->child.size(); i++)
                if (root->child[i]->vidited)
                    dfs(root->child[i]);
        }
    }
    return sum;
    if (root)
    {
    }
}
int main()
{

    int r = 0;
    return r;
}