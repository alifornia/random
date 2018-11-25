#include "iostream"
#include "vector"
#include "set"

//g++ -std=c++11 -stdlib=libc++ forest.cpp
using namespace std;

class Node{
    public:
        Node(int id){parent_index=id;}
        int parent_index;
        //data
};

void dfs(){
    
}
/*void delete_nodes(vector<Node> *f , const set<int> & to_del){
    for(int i=0; i < (*f).size(); i++){
        cout << f->at(i).parent_index << endl;
    }
} */

void delete_nodes(vector<Node> &f , const set<int> & to_del){
    for(int i=0; i < f.size(); i++){
        cout << f[i].parent_index << endl;
    }
} 

int main(){
    Node A(-1),B(0),C(1),D(2);
    const set<int> to_del={0,1};
    vector<Node> forest={A,B,C,D};
    //delete_nodes(&forest, to_del);
    delete_nodes(forest, to_del);
    
    return 0;

}