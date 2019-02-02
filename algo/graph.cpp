/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

<<<<<<< HEAD
class Node{
public:
    int id;
    Node(int id_):id(id_){}
    vector<Node*> childs;
};

class Graph{
public:
    int v;
    int e;
    Graph():v(0),e(0){}
=======
struct node
{
    int id;
    node *left;
    node *right;
};

class Node
{
  public:
    int id;
    Node(int id_) : id(id_) {}
    vector<Node *> childs;
};

class Graph
{
  public:
    int v;
    int e;
    Graph() : v(0), e(0) {}
>>>>>>> refs/remotes/origin/master
    vector<Node *> roots;
    void BFSi();
    void BFSr();
};

<<<<<<< HEAD
void Graph::BFSi(){
    for(auto & root : roots){
        queue<Node*> q;
        vector<bool> visited(v, false);

        q.push(root);
        visited[root->id]=true;

        while(!q.empty()){
            root = q.front();
            cout << "root: " << root->id << endl;
            q.pop();
            for(auto & child : root->childs){
                cout << "child: " << child->id << endl;
                if(!visited[child->id]){
                    visited[child->id]=true;
=======
void Graph::BFSi()
{
    for (auto &root : roots)
    {
        queue<Node *> q;
        vector<bool> visited(v, false);

        q.push(root);
        visited[root->id] = true;

        while (!q.empty())
        {
            root = q.front();
            cout << "root: " << root->id << endl;
            q.pop();
            for (auto &child : root->childs)
            {
                cout << "child: " << child->id << endl;
                if (!visited[child->id])
                {
                    visited[child->id] = true;
>>>>>>> refs/remotes/origin/master
                    q.push(child);
                }
            }
        }
    }
}
/*

0-1\
| | 4
2-3/

*/

vector<vector<int>> g;

<<<<<<< HEAD
void BFS(vector<vector<int>> &g){

=======
void BFS(vector<vector<int>> &g)
{
>>>>>>> refs/remotes/origin/master
}

int main()
{
    Node node0(0), node1(1), node2(2), node3(3), node4(4);

<<<<<<< HEAD
    node0.childs={&node1, &node2};
    node1.childs={&node0, &node3, &node4};
    node2.childs={&node0, &node3};
    node3.childs={&node1, &node2, &node4};
    node4.childs={&node1, &node3};

    Graph G;
    G.v=5;
    G.e=6;

    G.roots={&node0};
=======
    node0.childs = {&node1, &node2};
    node1.childs = {&node0, &node3, &node4};
    node2.childs = {&node0, &node3};
    node3.childs = {&node1, &node2, &node4};
    node4.childs = {&node1, &node3};

    Graph G;
    G.v = 5;
    G.e = 6;

    G.roots = {&node0};
>>>>>>> refs/remotes/origin/master
    G.BFSi();

    return 0;
}
