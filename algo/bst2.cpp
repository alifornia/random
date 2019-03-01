#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//make a template class
class Node
{
public:
  Node(int data) : data(data) {} //do i need this really?

  int data;
  unique_ptr<Node> right;
  unique_ptr<Node> left;
};

class BST
{
private:
  unique_ptr<Node> root = nullptr;
  void display_helper(const unique_ptr<Node> &root);
  void insert_helper(unique_ptr<Node> &root, int data);
  void remove_helper(unique_ptr<Node> &root, int data);
  unique_ptr<Node> findMin(unique_ptr<Node> &root);

public:
  void display();
  void insert(int data);
  void remove(int data);
};
unique_ptr<Node> BST::findMin(unique_ptr<Node> &root)
{
  if (root == nullptr)
    return nullptr;
  if (root->left == nullptr)
  {
    auto node = make_unique<Node>(root->data); // COMMON MISTAKE WITH UNIQUE PTR
    return move(node);                         //cant return move(root) ---> bug
  }
  return findMin(root->left);
}
void BST::insert(int data)
{
  insert_helper(root, data);
}
void BST::insert_helper(unique_ptr<Node> &root, int data)
{
  if (root == nullptr)
  {
    auto node = make_unique<Node>(data);
    root = move(node);
    return;
  }
  if (data <= root->data)
    insert_helper(root->left, data);
  else if (data > root->data)
    insert_helper(root->right, data);
}
void BST::remove(int data)
{
  remove_helper(root, data);
}
void BST::remove_helper(unique_ptr<Node> &root, int data)
{
  if (root == nullptr) //not found
    return;
  if (data < root->data)
    remove_helper(root->left, data);
  else if (data > root->data)
    remove_helper(root->right, data);
  else //found
  {
    if (root->left == nullptr && root->right == nullptr) //leaf
      root = nullptr;
    else if (root->left == nullptr && root->right != nullptr)
      root = move(root->right);
    else if (root->left != nullptr && root->right == nullptr)
      root = move(root->left);
    else //two childs
    {
      root->data = findMin(root->right)->data;
      remove_helper(root->right, root->data);
    }
  }
}
void BST::display()
{
  display_helper(root);
}
void BST::display_helper(const unique_ptr<Node> &root)
{

  if (root == nullptr) //base
    return;
  display_helper(root->left);
  cout << root->data << " ";
  display_helper(root->right);
}

int main()
{
  string line = "22 -1 3 100 7 40 -7 6 -9 -30 20 21 19";
  int value;
  stringstream ss(line);
  unique_ptr<Node> root;
  BST bst;

  while (ss >> value)
    bst.insert(value);
  bst.display();
  cout << endl;

  bst.remove(-1);
  cout << "seg" << endl;

  bst.display();
  cout << endl;
  return 0;
}