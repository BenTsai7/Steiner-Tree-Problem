#include <memory>
#include <string>
#include <fstream>
#include <set>
#include <iostream>
#ifndef GRAPH
#define GRAPH
#define INF 2000000000
struct Edge{
    int from;
    int to;
    int weight;
    Edge(int from,int to,int weight){this->from=from;this->to=to;this->weight=weight;}
    Edge(){};
    bool operator< (const Edge& a)const{
        if(from==a.from&&to==a.to) return false;
        else{
            if(weight!=a.weight){
                return weight < a.weight; 
            }
            else{
                if(from!=a.from)
                    return from<a.from;
                else
                    return to<a.to;
            }
        }
    };
};
class Graph{
    private:
        int nodenum;
        int edgenum;
        int terminalnum;
        int** graph=nullptr;
        Edge* edges=nullptr;
        int* terminals;
        bool isread=false;
    public:
        void getGraphCopy(int**& graph);
        void freeGraph(int** graph);
        int getNodenum(){return nodenum;};
        int getEdgenum(){return edgenum;};
        int getTerminalnum(){return terminalnum;};
        int* getTerminalpt(){return terminals;};
        bool getInput(const char* filename);
        void clear();
        ~Graph();
        void getEdges(bool* nodes,std::set<Edge>& set);
        void print();//used to debug
};
#endif