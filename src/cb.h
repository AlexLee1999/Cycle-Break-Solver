#ifndef _CB_H
#define _CB_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Node;
class Graph;



typedef pair<pair<Node* ,int>,bool > adj;
typedef  vector<adj*> adjlist;
typedef pair<pair<Node*,Node*>,int> edge;
typedef vector<edge*> edgelist;
class Node{
    friend class Graph;
    public:
    Node(int id):_id(id),visited(0),_key(-1000),_pre(0),_inweight(0),_outweight(0){
    }
    ~Node(){}
    void setadj(adj* x){
        _adjlist.push_back(x);
        _outweight+=x->first.second;
    }
    adjlist& getadj(){
        return _adjlist;
    }
    adjlist& getinlist(){
        return _inlist;
    }
    int id(){
        return _id;
    }
    void setvisited( ){
        visited=true;
    }
    void setkey(int x){
        _key=x;
    }
    int key(){
        return _key;
    }
    bool isvisited(){
        return visited;
    }
    void setpre(Node* x){
        _pre=x;
    }
    Node* pre(){
        return _pre;
    }
    void setinlist(adj* x){
        _inlist.push_back(x);
        _inweight+=x->first.second;
    }
    void setin(){
        _in++;
    }
    void setout(){
        _out++;
    }
    void minusin(){
        _in--;
    }
    void minusout(){
        _out--;
    }
    int getin(){
        return _in;
    }
    int getout(){
        return _out;
    }
    void minusinweight(int x){
        _inweight-=x;
    }
    void minusoutweight(int x){
        _outweight-=x;
    }
    int& getinweight(){
        return _inweight;
    }
    int& getoutweight(){
        return _outweight;
    }
    void initial(){
        _inweight=0;
        _outweight=0;
    }
    void sets(int x){
        s=x;
    }
    int gets(){
        return s;
    }
    void settrue(int k){
        _adjlist[k]->second=true;
    }
    private:
    adjlist _adjlist;
    int _id;
    bool visited;
    int _key;
    Node* _pre;
    int _in;
    int _out;
    adjlist _inlist;
    int _inweight;
    int _outweight;
    int s;
    
};
class Graph{
    friend class Node;
    public:
    Graph():total(0),count(0){
    }
    ~Graph(){}
    void settype(string x){
        _type=x;
    }
    string& type(){
        return _type;
    }
    void setnedge(int x){
        _edgen=x;
    }
    void setnvertex(int x){
        _vertexn=x;
    }
    string& gettype(){
        return _type;
    }
    void init(){
        _nodelist.resize(_vertexn);
        _nodelists.resize(_vertexn);
        _nodes.resize(_vertexn);
        for(int i=0;i<_vertexn;i++){
            _nodes[i]=(i);
            _nodelist[i]=new Node(i);
            _nodelist[i]->initial();
            _nodelists[i]=_nodelist[i];
        }
    }
    vector<Node*>& nodelist(){
        return _nodelist;
    }
    int getedge(){
        return _edgen;
    }
    int getvertex(){
        return _vertexn;
    }
    void resizeedge(){
        _edgelist.resize(_edgen);
    }
    void setedge(edge* x){
        _edgelist[count]=x;
        ++count;
    }
    vector<int>& node(){
        return _nodes;
    }
    edgelist& getsave(){
        return _saveedge;
    }
    void prim();
    Node* extractmax();
    void checkedge(ostream&);
    void initseq(){
        _seq.resize(_vertexn,-1);
    }
    void fas();
    int hassink(){
        int id=-1;
        for(int i=0;i<_nodes.size();i++){
            if(_nodelist[_nodes[i]]->getout()<=0){
                id=_nodes[i];
            }
        }
        return id;
    }
    int hassource(){
        int id=-1;
        for(int i=0;i<_nodes.size();i++){
            if(_nodelist[_nodes[i]]->getin()<=0){
                id=_nodes[i];
            }
        }
        return id;
    }
    int maxdiff(){
        int temp=-100000;
        int id=0;
        for(int i=0;i<_nodes.size();i++){
            if(_nodelist[_nodes[i]]->getoutweight()-_nodelist[_nodes[i]]->getinweight()>temp){
                temp=_nodelist[_nodes[i]]->getoutweight()-_nodelist[_nodes[i]]->getinweight();
                id=_nodes[i];
            }
        }
        return id;
    }
    void printseq(){
        for(int i=0;i<_seq.size();i++){
            cout<<_seq[i]<<endl;
        }
    }
    void setseq(){
        for(int i=0;i<_seq.size();i++){
            _nodelist[_seq[i]]->sets(i);
        }
    }
    void checks();
    edgelist getsaves(){
        return _save;
    }
    int total;
    void increasekey(Node*);
    void MaxHeapify(int root);
    void swap(Node*&,Node*&);
    void BuildMaxHeap(vector<Node*>&);
    void heapify(int);
    private:
    string _type;
    vector<Node*> _nodelist;
    vector<Node*> _nodelists;
    unsigned int _edgen;
    unsigned int _vertexn;
    edgelist _edgelist;
    edgelist _saveedge;
    vector<int> _seq;
    vector<int> _nodes;
    edgelist _save;
    int count;
    
};
#endif 