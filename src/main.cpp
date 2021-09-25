#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "cb.h"
using namespace std;



int main(int argc, char* argv[]) {
    Graph* graph = new Graph();
    fstream fin(argv[1]);
    fstream fout;
    string inFilePath(argv[1]);
    string outFilePath = inFilePath.substr(0, inFilePath.size() - 2) + "out";
    fout.open(outFilePath, ios::out | ios::trunc);
    string t;
    fin >> t;
    graph->settype(t);
    int v;
    fin >> v;
    graph->setnvertex(v);
    int e;
    fin >> e;
    graph->setnedge(e);
    graph->init();
    if (graph->gettype() == "u") {
        for (int i=0; i < graph->getedge(); i++) {
        int v1, v2, w;
        fin >> v1 >> v2 >> w;
            if (graph->nodelist()[v2] != 0 && graph->nodelist()[v1] != 0) {
                graph->total += w;
                
                pair<pair <Node* ,int> ,bool>* a1=new pair<pair <Node* ,int> ,bool>(pair <Node* ,int>(graph->nodelist()[v1],w) ,false);
                pair<pair <Node* ,int> ,bool>* a2=new pair<pair <Node* ,int> ,bool>(pair <Node* ,int>(graph->nodelist()[v2],w) ,false);

                graph->nodelist()[v2]->setAdj(a1);
                graph->nodelist()[v1]->setAdj(a2);
            }
        }
    }
    else{
        for (int i=0; i<graph->getedge(); i++) {
            int v1, v2, w;
            fin >> v1 >> v2 >> w;
            if(graph->nodelist()[v2]!=0&&graph->nodelist()[v1]!=0){
                pair<pair <Node* ,int> ,bool>* a1=new pair<pair <Node* ,int> ,bool>(pair <Node* ,int>(graph->nodelist()[v1],w) ,false);
                pair<pair <Node* ,int> ,bool>* a2=new pair<pair <Node* ,int> ,bool>(pair <Node* ,int>(graph->nodelist()[v2],w) ,false);
                graph->nodelist()[v1]->setAdj(a2);
                graph->nodelist()[v2]->setInList(a1);
                graph->nodelist()[v1]->setout();
                graph->nodelist()[v2]->setin();
                pair<pair<Node*,Node*>,int>*edge1 =new pair<pair<Node*,Node*>,int>(pair<Node*,Node*>(graph->nodelist()[v1],graph->nodelist()[v2]),w);
                graph->resizeedge();
                graph->setedge(edge1);
            }
        }
    }
        
    
    if (graph->type() == "u") {
        graph->prim(); 
        fout << graph->total << endl;
        graph->checkedge(fout);
    }
    else {
       graph->fas();
       graph->setseq();
       graph->checks();
       //graph->printseq();
        if (graph->getsaves().empty()) {
                fout << 0;
        }
        else {
            int s = 0;
            for (int i=0; i<graph->getsaves().size(); i++) {
            s += graph->getsaves()[i]->second;
            }
            fout << s << endl;
            for (int i=0; i<graph->getsaves().size(); i++) {
                fout<<graph->getsaves()[i]->first.first->id()<<' '<<graph->getsaves()[i]->first.second->id()<<' '<<graph->getsaves()[i]->second<<endl;
            }
        }
    }
    fout.close();
    fin.close();
    return 0;
    
}




