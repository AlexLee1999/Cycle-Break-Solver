#include <iostream>
#include <vector>
#include "graph.h"

graph::graph(std::string type, int VerticesNumber)
{
    _type = type;
    _TotalWeight = 0;
    _VerticesNumber = VerticesNumber;
    _NodeList.resize(VerticesNumber);
    _CopyNodeList.resize(VerticesNumber);
    for (int i = 0; i < VerticesNumber; ++i)
    {
        _NodeList[i] = new node(i); // add new node
        _CopyNodeList[i] = _NodeList[i];
    }
}

void graph::AddUndirectedEdge(int id1, int id2, int distance)
{
    _TotalWeight += distance;
    node *Node1 = _NodeList[id1];
    node *Node2 = _NodeList[id2];
    Node1->AddAdjancentNode(Node2, distance);
    Node2->AddAdjancentNode(Node1, distance);
}

void graph::AddDirectedEdge(int id1, int id2, int distance)
{
    node *Node1 = _NodeList[id1];
    node *Node2 = _NodeList[id2];
    Node1->AddAdjancentNode(Node2, distance);
    Node2->AddInNode(Node1, distance);
}

void graph::PrimAlgorithm()
{
    _NodeList[0]->SetKey(0);
    BuildMaxHeap(_NodeList);
    for (int i = 0; i < _VerticesNumber; ++i)
    {
        node *n = extractmax();
        n->SetVisited();
        // std::cout << _NodeList.size();
        for (int i = 0; i < _NodeList.size(); ++i)
        {
            std::cout << _NodeList[i]->_id;
        }
        if (n->_PreviousNode != nullptr)
        {
            // std::vector<node::AdjacentNode> PreviousAdjacentList = n->_PreviousNode->_AdjacentNodeList; // get previous node adjacent list
            for (int j = 0; j < n->_PreviousNode->_AdjacentNodeList.size(); ++j)
            {
                if (n->_PreviousNode->_AdjacentNodeList[j].first->_id == n->_id) // add edge in mst
                {
                    n->_PreviousNode->_AdjacentNodeList[j].second.second = true; // change edge properties
                    _TotalWeight -= n->GetKey();
                    // std::cout << _TotalWeight << std::endl;
                }
            }
            for (int j = 0; j < n->_AdjacentNodeList.size(); ++j)
            {
                if (n->_AdjacentNodeList[j].first->_id == n->_PreviousNode->_id)
                {
                    n->_AdjacentNodeList[j].second.second = true;
                }
            }
        }
        // std::vector<node::AdjacentNode> CurrentNodeAdjacentList = n->_AdjacentNodeList;
        for (int j = 0; j < n->_AdjacentNodeList.size(); ++j)
        {
            if (!n->_AdjacentNodeList[j].first->_isVisited && n->_AdjacentNodeList[j].first->GetKey() < n->_AdjacentNodeList[j].second.first) // if adj not in mst && key < weight
            {
                n->_AdjacentNodeList[j].first->SetKey(n->_AdjacentNodeList[j].second.first);
                IncreaseKey(n->_AdjacentNodeList[j].first);
                n->_AdjacentNodeList[j].first->_PreviousNode = n;
            }
        }
    }
}

void graph::Heapify(int root)
{
    int t = (root - 1) / 2;
    while (t >= 0)
    {
        if (_NodeList[t]->GetKey() < _NodeList[root]->GetKey())
        {
            swap(_NodeList[t], _NodeList[root]);
            root = t;
            t = (root - 1) / 2;
        }
        else
        {
            break;
        }
    }
}

void graph::MaxHeapify(int root)
{
    int t = root;
    int l = 2 * root + 1;
    int r = 2 * root + 2;
    if (l < _NodeList.size() && _NodeList[l]->GetKey() > _NodeList[t]->GetKey())
    {
        t = l;
    }
    if (r < _NodeList.size() && _NodeList[r]->GetKey() > _NodeList[t]->GetKey())
    {
        t = r;
    }
    if (t != root)
    {
        swap(_NodeList[t], _NodeList[root]);
        MaxHeapify(t);
    }
}

void graph::BuildMaxHeap(std::vector<node *> &_nodelists)
{
    int heapSize = _nodelists.size();
    for (int i = heapSize / 2 - 1; i >= 0; i--)
    {
        MaxHeapify(i);
    }
}
node *graph::extractmax()
{
    node *n = _NodeList[0];
    swap(_NodeList[0], _NodeList[_VerticesNumber - 1]);

    std::cout << std::endl;
    _NodeList.pop_back();
    MaxHeapify(0);
    return n;
}

void graph::IncreaseKey(node *x)
{
    for (int i = 0; i < _NodeList.size(); i++)
    {
        if (_NodeList[i] == x)
        {
            Heapify(i);
        }
    }
}

void graph::WriteOutputFile(std::ostream &fout)
{
    fout << _TotalWeight << std::endl;
    for (int i = 0; i < _VerticesNumber; ++i)
    {
        std::vector<node::AdjacentNode> CurrentNodeAdjacentList = _CopyNodeList[i]->_AdjacentNodeList;
        for (int j = 0; j < CurrentNodeAdjacentList.size(); ++j)
        {
            if (CurrentNodeAdjacentList[j].second.second == false)
            {
                if (_CopyNodeList[i]->_id < CurrentNodeAdjacentList[j].first->_id)
                {
                    fout << _CopyNodeList[i]->_id << ' ' << CurrentNodeAdjacentList[j].first->_id << ' ' << CurrentNodeAdjacentList[j].second.first << std::endl;
                }
            }
            else
            {
                continue;
            }
        }
    }
}
void graph::swap(node *&a, node *&b)
{
    node *temp = a;
    a = b;
    b = temp;
}