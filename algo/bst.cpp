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

class BST
{
  public:
    void insert(unique_ptr<Node> &root, int data)
    {
        if (root == nullptr)
            root = move(create(data)); //avoid creating another copy of obejct READ ON: //http://thbecker.net/articles/rvalue_references/section_01.html
        else if (data < root->data)
            insert(root->left, data);
        else
            insert(root->right, data);
    }
    void remove(unique_ptr<Node> &root, int data)
    {
        if (root == nullptr)
            root = move(create(data)); //avoid creating another copy of obejct READ ON: //http://thbecker.net/articles/rvalue_references/section_01.html
        else if (data < root->data)
            insert(root->left, data);
        else
            insert(root->right, data);
    }
    unique_ptr<Node> search(unique_ptr<Node> &root, int key)
    {
        if (root == nullptr || root->data == key)
            return move(root);
        else if (key < root->data)
            return search(root->left, key);
        else
            return search(root->right, key);
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

  private:
    unique_ptr<Node> create(int data)
    {
        auto node = make_unique<Node>();
        node->data = data;
        return move(node); //https://stackoverflow.com/questions/3413470/what-is-stdmove-and-when-should-it-be-used
    }
};

int main()
{
    string line = "22 -1 3 100 7 40 -7 6 -9 -30 20 21 19";
    int value;
    // getline(cin, line);
    stringstream split(line);

    BST bst;
    unique_ptr<Node> root = nullptr;
    while (split >> value)
        bst.insert(root, value);
    cout << "root: " << root->data << endl;

    bst.display(root);
    cout << endl;

    unique_ptr<Node> term = bst.search(root, 5);
    term ? cout << "found: " << term->data << endl : cout << "not found" << endl;

    return 0;
}

//22 -1 3 100 7 40 -7 6 -9 -30 20 21 19
//1 3 6 8 10 14 13 4 7