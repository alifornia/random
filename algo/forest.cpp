#include "iostream"
#include "vector"
#include "set"

//g++ -std=c++11 -stdlib=libc++ forest.cpp
using namespace std;

class Node
{
  public:
    Node(int id) { parent_index = id; }
    int parent_index;
    //data
};

void dfs()
{
}
/*void delete_nodes(vector<Node> *f , const set<int> & to_del){
    for(int i=0; i < (*f).size(); i++){
        cout << f->at(i).parent_index << endl;
    }
} */

void delete_nodes(vector<Node> &f, const set<int> &to_del)
{
    vector<Node>::iterator it = f.begin();
    for (int i = 0; i <= f.size(); i++)
    {
        for (const auto &to_del_id : to_del)
        {
            if (f[i].parent_index == to_del_id)
            {
                //cout << i << endl;
                f.erase(it + i, it + i + 1);
            }
        }
    }
    for (int i = 0; i < f.size(); i++)
    {
        cout << f[i].parent_index << endl;
    }
}

int main()
{
    Node A(-1), B(0), C(1), D(2);
    // A->B->C->D  == del{B} == A, C->D
    // A->B->C , D == del{B} == A, C, D

    const set<int> to_del = {0, 1};
    vector<Node> forest = {A, B, C, D};
    //delete_nodes(&forest, to_del);
    delete_nodes(forest, to_del);

    return 0;
}