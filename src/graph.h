#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <string>
#include "node.h"

class graph
{
private:
    std::vector<node *> _NodeList;
    std::vector<node *> _CopyNodeList;
    int _VerticesNumber;
    std::string _type;
    int _TotalWeight;

public:
    graph(std::string, int);
    ~graph() {}
    // Constructing the Graph
    void AddUndirectedEdge(int, int, int); // node1, node2, distance
    void AddDirectedEdge(int, int, int);   // node1, node2, distance

    //Undirected Graph
    void PrimAlgorithm();

    // For Heap Operations
    void Heapify(int);
    void MaxHeapify(int);
    void BuildMaxHeap();
    node *extractmax();
    void IncreaseKey(node *);

    void DFSAlgorithm();

    // Output 
    void WriteUndirectedOutputFile(std::ostream&);
};
#endif