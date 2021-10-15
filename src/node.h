#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <vector>

class node
{
    friend class graph;
    typedef std::pair<int, bool> edgeProps; //distance, inMst
    typedef std::pair<node *, edgeProps> AdjacentNode; // Node, distance
private:
    std::vector<AdjacentNode> _AdjacentNodeList;
    std::vector<AdjacentNode> _InNodeList; // Only for Directed Graphs
    int _id;
    int _key;
    bool _isVisited;
    node * _PreviousNode;

public:
    node(int);
    ~node() {}
    void AddAdjancentNode(node *, int);
    void AddInNode(node *, int);
    void SetKey(int);    //For Prim's Algorithm
    int  GetKey() const; //For Prim's Algorithm
    void SetVisited();
};

#endif