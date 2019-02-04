#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include <queue>

using namespace std;

struct Node
{
    int data;
    unique_ptr<Node> l;
    unique_ptr<Node> r;
    Node *left;
    Node *right;
};

//const
//when not changing
void display(const Node *root)
{
    if (root != NULL)
    {
        display(root->left);
        cout << root->data << " ";
        display(root->right);
    }
}

Node *create(int data)
{
    Node *node = new Node();
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

//ref to ptr:
//when you want the callee to change the pointer itself, not the object to which it points
void insert(Node *&root, int data)
{
    if (root == NULL)
        root = create(data);
    else if (data < root->data)
        insert(root->left, data);
    else
        insert(root->right, data);
}

int main()
{
    Node *root = NULL;
    vector<int> nodes;

    string line;
    int value;
    getline(cin, line);
    stringstream split(line);
    while (split >> value)
        nodes.push_back(value);

    for (int i = 0; i < nodes.size(); i++)
        insert(root, nodes[i]);
    display(root);
    return 0;
}
//5 4 6 3 2
//7 4 8 3 5 2
//2 -1 3 100 7 40 -7 -9 -30 20 21
//1 3 6 8 10 14 13 4 7