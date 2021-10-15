#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "graph.h"

int main(int argc, char *argv[])
{
    std::fstream fin(argv[1]);
    std::fstream fout;
    std::string inFilePath(argv[1]);
    std::string outFilePath = inFilePath.substr(0, inFilePath.size() - 2) + "out";
    fout.open(outFilePath, std::ios::out | std::ios::trunc);
    std::string type;
    fin >> type;
    int VerticesSize;
    fin >> VerticesSize; // get vertices numbers
    graph *myGraph = new graph(type, VerticesSize);
    int EdgeSize;
    fin >> EdgeSize; // get edge numbers
    for (int i = 0; i < EdgeSize; ++i)
    {
        int id1, id2, distance;
        fin >> id1 >> id2 >> distance;
        if (type == "u")
        {
            myGraph->AddUndirectedEdge(id1, id2, distance);
        }
        else if (type == "d")
        {
            myGraph->AddDirectedEdge(id1, id2, distance);
        }
    }
    if (type == "u") //Undirected Graph
    {
        myGraph->PrimAlgorithm();
        myGraph->WriteUndirectedOutputFile(fout);
    }
    else if (type == "d") //Directed Graph
    {
        myGraph->DFSAlgorithm();
    }
    
}