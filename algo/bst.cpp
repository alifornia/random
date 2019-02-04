#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include <queue>

using namespace std;

struct Node
{
    int data;
    unique_ptr<Node> left;
    unique_ptr<Node> right;
};

//const
//when not changing
void display(const unique_ptr<Node> &root)
{
    if (root != nullptr)
    {
        display(root->left);
        cout << root->data << " ";
        display(root->right);
    }
}

unique_ptr<Node> create(int data)
{
    auto node = make_unique<Node>();
    node->data = data;
    return move(node);
}

void insert(unique_ptr<Node> &root, int data)
{
    if (root == nullptr)
        root = move(create(data));
    else if (data < root->data)
        insert(root->left, data);
    else
        insert(root->right, data);
}

int main()
{
    unique_ptr<Node> root = nullptr;
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