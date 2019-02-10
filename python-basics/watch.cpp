//Write a recursive function named stretch that replaces each single binary tree node with multiple nodes with smaller val ues.Your function accepts two parameters : a reference to a TreeNode pointer representing the root of a binary tree, and an integer "stretching factor" K.Your function should replace each node N with K nodes, each of which stores a data value that is 1 / K of N 's original value, using integer division. The new clones of node N should extend from their parent in the same direction that N extends from its parent. For example, if N is its parent' s left child, the stretched clones of N should also be their parent's left child, and vice versa if N was a right child. The root node is a special case because it has no parent; we will handle this by saying that its stretched clones should extend to the left. Signature: stretch(root *TreeNode, stretchAmount int) 

#include <iostream>

using namespace std;

struct Nodee
{
    int data;
};
struct Node
{
    int data;               //4
    unique_ptr<Node> left;  //8
    unique_ptr<Node> right; //8
};

void stretch_h(unique_ptr<Node> &root, int stretchAmount, int dir)
{
    if (root == nullptr)
        return;
    root->data = root->data / stretchAmount;
    if (dir == 0)
    {
        for (int i = 0; i < stretchAmount - 1; ++i) //s-1
        {
            auto new_node = make_unique<Node>();
            new_node->left = move(root->left);
            root->left = move(new_node);
        }
    }
    else
    {
        for (int i = 0; i < stretchAmount - 1; ++i) //s-1
        {
            auto new_node = make_unique<Node>();
            new_node->left = move(root->left);
            root->left = move(new_node);
        }
    }
    stretch_h(root->left, stretchAmount, dir);
    stretch_h(root->right, stretchAmount, dir);
}
void stretch(unique_ptr<Node> &root, int stretchAmount)
{
    cout << "here" << endl;
    stretch_h(root, stretchAmount, 0);
}

void insert(unique_ptr<Node> &child, int data)
{
    if (child == nullptr)
    {
        auto node = make_unique<Node>();
        node->data = data;
        child = move(node);
    }
}

int main()
{
    //string line = "22 -1 3 100 7 40 -7 6 -9 -30 20 21 19";
    auto root = make_unique<Node>();
    Nodee root1;
    root1.data = 2;
    Nodee root2 = root1;
    root1.data = 3;
    cout << root2.data << endl;

    return 0;

    //auto l1 =
    auto r1 = make_unique<Node>();
    auto r2 = make_unique<Node>();
    auto l3 = make_unique<Node>();
    auto r3 = make_unique<Node>();

    unique_ptr<Node> roott = nullptr;

    root->data = 12;
    insert(root->left, 81);
    insert(root->right, 34);
    insert(root->left->right, 56);
    insert(root->right->left, 19);
    insert(root->right->left, 6);

    // //l1->data = 81;

    // r1->data = 34;
    // r2->data = 56;
    // l3->data = 19;
    // r3->data = 6;

    // //addl(root, l1);
    // //root->left = move(l1);
    // //addr(root, r1);
    // //root->right = move(r1);

    // cout << "bef" << endl;
    // //addr(l1, r2);
    // //l1->right = move(r2);
    // cout << "aft" << endl;

    // r1->left = move(l3);
    // r1->right = move(r3);

    stretch(root, 2);

    return 0;
}
