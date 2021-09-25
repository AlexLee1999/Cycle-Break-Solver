#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "cb.h"
using namespace std;


void
Graph::prim() {
    _nodelist[0]->setKey(0);
    BuildMaxHeap(_nodelists);
    for (int i=0; i<_vertexn; i++) {
        Node* n = extractmax();
        n->setVisited();
        if (n->pre() != 0) {
            for (int k=0; k < n->pre()->getAdj().size(); k++) {
                if (n->pre()->getAdj()[k]->first.first->id() == n->id()) {
                    n->pre()->settrue(k);
                    total -= n->key();
                }
            }
            for (int k=0; k<n->getAdj().size(); k++) {
                if (n->getAdj()[k]->first.first->id() == n->pre()->id()) {
                    n->settrue(k);
                }
            }  
        }
        for (int j=0; j<n->getAdj().size(); j++) {
            if (!n->getAdj()[j]->first.first->isVisited() && n->getAdj()[j]->first.first->key() < n->getAdj()[j]->first.second) {
                (n->getAdj()[j])->first.first->setKey(n->getAdj()[j]->first.second);
                increasekey((n->getAdj()[j])->first.first);
                (n->getAdj()[j])->first.first->setPre(n);
            }
        }
    }
}

Node* 
Graph::extractmax() {
    Node* n = _nodelists[0];
    swap(_nodelists[0],_nodelists[_nodelists.size()-1]);
    _nodelists.pop_back();
    MaxHeapify(0);
    return n;
}

void
Graph::increasekey(Node* x){
for(int i=0;i<_nodelists.size();i++){
    if(_nodelists[i]==x){
        heapify(i);
    }
}
}
void Graph::BuildMaxHeap(vector<Node*>& _nodelists) {
    int heapSize = _nodelists.size(); 
    for(int i=heapSize/2-1;i>=0;i--){
	    MaxHeapify(i);
    }
}
void
Graph::checkedge(ostream& file){
    for(int i=0;i<_vertexn;i++){
        for(int j=0;j<_nodelist[i]->getAdj().size();j++){
            //cout<<_nodelist[i]->id()<<' '<<_nodelist[i]->getAdj()[j].first.first->id()<<' '<<_nodelist[i]->getAdj()[j].second<<endl;
            if(_nodelist[i]->getAdj()[j]->second==false){
                if(_nodelist[i]->id()<_nodelist[i]->getAdj()[j]->first.first->id()){
                    /*pair<Node*,Node*> a1(_nodelist[i],_nodelist[i]->getAdj()[j].first.first);
                    edge b1(a1,_nodelist[i]->getAdj()[j].first.second);
                    _notinlist.push_back(b1);*/
                    file<<_nodelist[i]->id()<<' '<<_nodelist[i]->getAdj()[j]->first.first->id()<<' '<<_nodelist[i]->getAdj()[j]->first.second<<endl;
                }
                else{
                    continue;
                }
            }
        }
    }
}

void
Graph::fas(){
    int id;
    int front=0;
    int back=_vertexn-1;
    initseq();
    while(!_nodes.empty()) {
    if(hassink()!=-1){
        id=hassink();
        if(_nodes.size()==1){
            _seq[back--]=id;
            break;
        }
        _nodes.erase(std::find(_nodes.begin(),_nodes.end(),id));
        _seq[back--]=id;
        for(int i=0;i<_nodelist[id]->getInList().size();i++){
        _nodelist[id]->getInList()[i]->first.first->minusout();
        _nodelist[id]->getInList()[i]->first.first->minusoutweight(_nodelist[id]->getInList()[i]->first.second);
    }  
    }
    if(hassource()!=-1){
        id=hassource();
        
        if(_nodes.size()==1){
            _seq[front++]=id;
            break;
        }
        _nodes.erase(std::find(_nodes.begin(),_nodes.end(),id));
        _seq[front++]=id;
        for(int i=0;i<_nodelist[id]->getAdj().size();i++){
        _nodelist[id]->getAdj()[i]->first.first->minusin();
        _nodelist[id]->getAdj()[i]->first.first->minusinweight(_nodelist[id]->getAdj()[i]->first.second);
    }
    }
    if(hassource()==-1&&hassink()==-1){
        
        id=maxdiff();
        
        if(_nodes.size()==1){
            _seq[front++]=id;
            break;
        }
        _nodes.erase(std::find(_nodes.begin(),_nodes.end(),id));
        _seq[front++]=id;
        for(int i=0;i<_nodelist[id]->getAdj().size();i++){
        _nodelist[id]->getAdj()[i]->first.first->minusin();
        _nodelist[id]->getAdj()[i]->first.first->minusinweight(_nodelist[id]->getAdj()[i]->first.second);
        }
        for(int i=0;i<_nodelist[id]->getInList().size();i++){
        _nodelist[id]->getInList()[i]->first.first->minusout();
        _nodelist[id]->getInList()[i]->first.first->minusoutweight(_nodelist[id]->getInList()[i]->first.second);
        }
    }
}
}

void
Graph::checks(){
    for (int i=0; i<_vertexn; i++) {
        for (int j=0; j<_nodelist[i]->getAdj().size(); j++) {
            if (_nodelist[i]->getAdj()[j]->first.first->gets()<_nodelist[i]->gets()) {
                pair<pair<Node*,Node*> ,int>* e1 = new pair<pair<Node*,Node*> ,int>(pair<Node*,Node*>(_nodelist[i],_nodelist[i]->getAdj()[j]->first.first),_nodelist[i]->getAdj()[j]->first.second); 
                _save.push_back(e1);
            }
        }
    }
}

void 
Graph::MaxHeapify(int root) {
    int t = root;
    int l = 2 * root + 1;
    int r = 2 * root + 2;
    if (l < _nodelists.size() && _nodelists[l]->key() > _nodelists[t]->key()) {
	    t = l;
    }
    if (r < _nodelists.size() && _nodelists[r]->key() > _nodelists[t]->key()) {
	    t = r;
    }
    if (t != root) {
	    swap(_nodelists[t], _nodelists[root]);
	    MaxHeapify(t);
    }
}

void 
Graph::heapify(int root){
    int t = (root - 1) / 2;
    while (t >= 0) {
        if (_nodelists[t]->key() < _nodelists[root]->key()) {
            swap(_nodelists[t],_nodelists[root]);
            root = t;
            t = (root - 1) / 2;
        }
        else {
            break;
        }
    }
}

void 
Graph::swap(Node*& a,Node*&b) {
    Node* temp = a;
    a = b;
    b = temp;
}
