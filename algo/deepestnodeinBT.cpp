#include <iostream>

using namespace std;

struct Node
{
    int data;
    unique_ptr<Node> left;
    unique_ptr<Node> right;
};
void insert(unique_ptr<Node> &root, int data)
{
    auto new_node = make_unique<Node>();
    new_node->data = data;
    root = move(new_node);
}

void display(const unique_ptr<Node> &root) //const if not changing
{
    if (root)
    {
        display(root->left);
        cout << root->data << " ";
        display(root->right);
    }
}

void find(unique_ptr<Node> &root, int level, int &maxLevel, int &deepest)
{
    if (root != nullptr)
    {
        find(root->left, ++level, maxLevel, deepest);
        if (level > maxLevel)
        {
            maxLevel = level;
            deepest = root->data;
        }
        find(root->right, level, maxLevel, deepest);
    }
}
int findDeepestNode(unique_ptr<Node> &root)
{
    int maxLevel = -1;
    int deepest = -1;

    find(root, 0, maxLevel, deepest);
    return maxLevel;
}
int main()
{
    unique_ptr<Node> root = nullptr;
    insert(root, 12);
    insert(root->left, 81);
    insert(root->right, 34);
    insert(root->left->right, 56);
    insert(root->right->left, 19);
    insert(root->right->right, 6);
    insert(root->right->right->right, 2);

    display(root);
    cout << endl;
    cout << findDeepestNode(root) << endl;

    return 0;
}