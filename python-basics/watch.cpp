//Write a recursive function named stretch that replaces each single binary tree node with multiple nodes with smaller val ues.Your function accepts two parameters : a reference to a TreeNode pointer representing the root of a binary tree, and an integer "stretching factor" K.Your function should replace each node N with K nodes, each of which stores a data value that is 1 / K of N 's original value, using integer division. The new clones of node N should extend from their parent in the same direction that N extends from its parent. For example, if N is its parent' s left child, the stretched clones of N should also be their parent's left child, and vice versa if N was a right child. The root node is a special case because it has no parent; we will handle this by saying that its stretched clones should extend to the left. Signature: stretch(root *TreeNode, stretchAmount int) 

#include <iostream>

using namespace std;

struct Node
{
    int data;               //4
    unique_ptr<Node> left;  //8
    unique_ptr<Node> right; //8
};
void insert(unique_ptr<Node> &node, int data)
{
    auto new_node = make_unique<Node>();
    new_node->data = data;
    node = move(new_node);
}
void stretch_h(unique_ptr<Node> &root, int stretchAmount, int dir)
{
    if (root == nullptr)
    {
        cout << "null" << endl;
        return;
    }
    stretch_h(root->left, stretchAmount, 0);
    stretch_h(root->right, stretchAmount, 1);
    cout << "stretch_h:" << root->data << endl;

    root->data = root->data / stretchAmount;
    if (dir == 0)
    {
        cout << "L:" << root->data << endl;
        auto left = move(root->left);
        for (int i = 0; i < stretchAmount - 1; i++) //s-1
        {
            cout << "left" << endl;
            insert(root->left, root->data / stretchAmount);
            root = move(root->left);
        }
        root->left = move(left);
    }
    else
    {
        cout << "R:" << root->data << endl;
        auto right = move(root->right);
        for (int i = 0; i < stretchAmount - 1; i++) //s-1
        {
            insert(root->right, root->data / stretchAmount);
            cout << "right" << endl;
            root = move(root->right);
        }
        root->right = move(right);
    }
}
void stretch(unique_ptr<Node> &root, int stretchAmount)
{
    stretch_h(root, stretchAmount, 0);
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

int main()
{
    //string line = "22 -1 3 100 7 40 -7 6 -9 -30 20 21 19";
    unique_ptr<Node> root = nullptr;
    insert(root, 12);
    insert(root->left, 81);
    insert(root->right, 34);
    insert(root->left->right, 56);
    insert(root->right->left, 19);
    insert(root->right->right, 6);
    display(root);
    cout << "here" << endl;
    stretch(root, 2);

    cout << "disp: " << root->data << endl; // root is pointing to a wrong root!!!
    display(root);

    return 0;
}
