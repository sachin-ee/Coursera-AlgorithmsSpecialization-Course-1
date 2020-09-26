#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <limits.h>

using namespace std;

void removeSelfLoop(vector<int>& v)
{
    v.erase(remove(v.begin()+1, v.end(), v[0]), v.end());
}

void changeAllReference(vector<vector<int>>& v, int node, int merge_to_node, int node_index)
{
    //Change reference of node in all other nodes
    for(size_t i=0; i<v.size(); i++)
    {
        if(v[i][0] != node)
        {
            for(size_t j=1; j<v[i].size(); j++)
                if(v[i][j] == node) v[i][j] = merge_to_node;
        }
    }

    // Remove self loops
    for(size_t i=0; i<v.size(); i++)
    {
        if(v[i][0] == merge_to_node) {
            removeSelfLoop(v[i]);
        }
    }

    // Change links from old node to all other nodes to merge_to_node to all other nodes
    for(size_t k=1; k<v[node_index].size(); k++)
    {
        if(v[node_index][k] != merge_to_node)
        {
            for(size_t l=0; l<v.size(); l++)
                if(v[l][0] == merge_to_node) v[l].push_back(v[node_index][k]);
        }
    }

    //Delete node
    v.erase(v.begin()+node_index);
}

int kargerMinCut(vector<vector<int>>& v) {
    // Pick a node at random
    while(v.size() > 2)
    {
        int node_index = rand() % v.size();
        // Index 0 is head node. So preserve index[0]
        int merge_to_node_index = (rand() % (v[node_index].size()-1))+1;
        changeAllReference(v, v[node_index][0], v[node_index][merge_to_node_index], node_index);
    }

    if(v.size() != 2) cout << "ERROR: Only 2 vectors should remain" << endl;
    if(v[0].size() != v[1].size()) cout << "ERROR: v[0] and v[1] not equal size" << endl;

    return v[0].size()-1;
}

int main() {

    int min_cut=INT_MAX;
    for(int i=0; i<1000; i++)
    {
        vector<vector<int>> v;
        ifstream infile("kargerMinCut.txt");
        string line;

        srand (time(NULL));
        while(getline(infile, line))
        {
            stringstream ss(line);
            int a;
            vector<int> x;
            while(ss >> a)
                x.push_back(a);
            v.push_back(x);
        }

        int x = kargerMinCut(v);
        if(x < min_cut) min_cut=x;
    }
    cout << "Karger min-cuts " << min_cut << endl;

    return 0;
}
