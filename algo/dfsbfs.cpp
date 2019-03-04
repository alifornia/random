#include <iostream>
#include <vector>

using namespace std;

class Graph
{
  // very flexible design but in programming competitions/interview questions
  // usually there are limits and adj matrix using array or adj list using vector is enough
  // if nodes are not int, a mapping can be used (string to int)
private:
  struct Node
  {
    int data;
    vector<unique_ptr<Node>> neighbours;
  };

public:
  //any methods such as dfs, bfs, dijkstra
};

void addEdge(vector<int> adj[], int u, int v)
{
  adj[u].push_back(v);
  //uncomment below if undirected
  //adj[v].push_back(u);
}

int main()
{
  //0-->1-->2
  // \---->/
  vector<int> adj_lst; // v[0]=1,2 v[1]=2 , v[2]=null
  // adj list for weighted graph: node - weight
  vector<pair<int, int>> adj_lst_w;

  // adj matrix for m[][]=1
  vector<vector<int>> adj_matrix;

  return 0;
}