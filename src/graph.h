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
    void AddUndirectedEdge(int, int, int); // node1, node2, distance
    void AddDirectedEdge(int, int, int);   // node1, node2, distance
    void PrimAlgorithm();
    void Heapify(int);
    void MaxHeapify(int);
    void BuildMaxHeap(std::vector<node *> &);
    node *extractmax();
    void IncreaseKey(node *);
    void WriteOutputFile(std::ostream&);
    void swap(node *&, node *&);
};
#endif