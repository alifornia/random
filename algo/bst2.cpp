#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

//make a template class
template <typename T>
class Node
{
public:
  Node(const T &data, unique_ptr<Node> left = nullptr, unique_ptr<Node> right = nullptr) : data(data), left(move(left)), right(move(right)) {}

  T data;
  unique_ptr<Node> left;
  unique_ptr<Node> right;
};

template <typename T>
class BST
{
private:
  unique_ptr<Node<T>> root = nullptr;
  void display_helper(const unique_ptr<Node<T>> &root);
  void insert_helper(unique_ptr<Node<T>> &root, T data);
  void remove_helper(unique_ptr<Node<T>> &root, T data);
  bool search_helper(unique_ptr<Node<T>> &root, T data);
  unique_ptr<Node<T>> findMin(unique_ptr<Node<T>> &root);

public:
  void display();
  void insert(T data);
  void remove(T data);
  bool search(T data);
  const BST &operator=(const BST &rhs)
  {
    // this does not work with unique_ptr
    //you must create a new node for each node from rhs and clone its data
    if (this != &rhs)
    {
      auto node = make_unique<Node<T>>(rhs.root->data);
      root = move(node);
    }
    return *this;
  }
};
template <typename T>
unique_ptr<Node<T>> BST<T>::findMin(unique_ptr<Node<T>> &root)
{
  if (root == nullptr)
    return nullptr;
  if (root->left == nullptr)
  {
    auto node = make_unique<Node<T>>(root->data); // COMMON MISTAKE WITH UNIQUE PTR
    return move(node);                            //cant return move(root) ---> bug
  }
  return findMin(root->left);
}
template <typename T>
void BST<T>::insert(T data)
{
  insert_helper(root, data);
}
template <typename T>
void BST<T>::insert_helper(unique_ptr<Node<T>> &root, T data)
{
  if (root == nullptr)
  {
    auto node = make_unique<Node<T>>(data);
    root = move(node);
    return;
  }
  if (data <= root->data)
    insert_helper(root->left, data);
  else if (data > root->data)
    insert_helper(root->right, data);
}
template <typename T>
void BST<T>::remove(T data)
{
  remove_helper(root, data);
}
template <typename T>
void BST<T>::remove_helper(unique_ptr<Node<T>> &root, T data)
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
template <typename T>
bool BST<T>::search(T data)
{
  return search_helper(root, data);
}
template <typename T>
bool BST<T>::search_helper(unique_ptr<Node<T>> &root, T data)
{
  if (root == nullptr)
    return false;
  if (data < root->data)
    return search_helper(root->left, data);
  else if (data > root->data)
    return search_helper(root->right, data);
  else //found
    return true;
}
template <typename T>
void BST<T>::display()
{
  display_helper(root);
}
template <typename T>
void BST<T>::display_helper(const unique_ptr<Node<T>> &root)
{

  if (root == nullptr) //base
    return;
  display_helper(root->left);
  cout << root->data << " ";
  display_helper(root->right);
}

int main()
{
  string line = "22.1 -1 3 100 7 40 -7 6 -9 -30 20 21 19";
  float value;
  stringstream ss(line);
  unique_ptr<Node<float>> root;
  BST<float> bst;

  while (ss >> value)
    bst.insert(value);

  bst.display();
  cout << endl;

  bst.remove(-1);
  bst.display();
  cout << endl;

  if (bst.search(22.1))
    cout << "found" << endl;

  BST<float> bst2;
  bst2 = bst;
  bst2.display();
  cout << endl;

  return 0;
}