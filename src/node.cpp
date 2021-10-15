#include <iostream>
#include "node.h"

node::node(int id)
{
    _id = id;
    _key = INT_MIN;
    _isVisited = false;
    _PreviousNode = nullptr;
}

void node::SetKey(int key)
{
    _key = key;
}

int node::GetKey() const
{
    return _key;
}

void node::SetVisited()
{
    _isVisited = true;
}

void node::AddAdjancentNode(node *AdjNode, int distance)
{
    edgeProps props = edgeProps(distance, false);
    AdjacentNode adjnode(AdjNode, props);
    _AdjacentNodeList.push_back(adjnode);
}

void node::AddInNode(node *AdjNode, int distance)
{
    edgeProps props = edgeProps(distance, false);
    AdjacentNode adjnode(AdjNode, props);
    _InNodeList.push_back(adjnode);
}
