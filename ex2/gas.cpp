#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Creating shortcut for an integer pair
typedef  pair<int, int> iPair;

// Structure to represent a graph
struct Graph{
    int V, E;
    vector< pair<int, iPair> > edges;

    // Constructor
    Graph(int V, int E){
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int w){
        edges.push_back({w, {u, v}});
    }

    int kruskalMST();
};

struct DisjointSets{
    int *parent, *rnk;
    int n;

    DisjointSets(int n)
    {
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;

            parent[i] = i;
        }
    }

    int find(int u)
    {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void merge(int x, int y)
    {
        x = find(x), y = find(y);

        if (rnk[x] > rnk[y])
            parent[y] = x;
        else
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};

int Graph::kruskalMST()
{
    int max_weight = 0;

    sort(edges.begin(), edges.end());

    DisjointSets ds(V);

    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;

        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v)
        {
            max_weight = max (max_weight, it->first);            // Update MST weight
            ds.merge(set_u, set_v);
        }
    }

    return max_weight;
}

int main(int argc, char **argv)
{
    string filename = argv[1];
    ifstream text(filename);
    stringstream buffer;
    buffer << text.rdbuf();

    int V, E;                     //V = vertices and E = edges
    buffer >> V >> E;
    Graph g(V, E);
    for(int i=0; i < E; i++){
        int V1, V2, weight;
        buffer >> V1 >> V2 >> weight;
        g.addEdge(V1, V2, weight);
    }

    int max_weight = g.kruskalMST();
    cout << max_weight << endl;
    return 0;
}
