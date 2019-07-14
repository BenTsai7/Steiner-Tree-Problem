#include"Solution.h"
Solution::Solution(const int* terminals,int total,Graph* g){
    this->terminals = terminals;
    terminalnum = g->getTerminalnum();
    this->total = total;
    this->g =g;
    mincost=-1;
};
Solution::~Solution(){
    if(nodes!=NULL) delete[] nodes;
};
void Solution::getNeighbor(Solution& s){
    s = (*this);
    s.isCal = false;
    while(true){
        int reverse=rand()%total;
        bool isreverse=false;
        for(int i=0;i<terminalnum;++i){
            if(reverse==terminals[i]) {isreverse=true;break;}
        }
        if(isreverse) continue;//if it's terminal point,choose other points again
        s.nodes[reverse]=!s.nodes[reverse];//reverse
        if(s.nodes[reverse]) ++s.num;
        else --s.num;
        break;
    }
};
void Solution::initialguess(){
    nodes = new bool[total];
    for(int i=0;i<total;++i) nodes[i]=false;
    for(int i=0;i<terminalnum;++i) nodes[terminals[i]]=true;
    num = 0;
    for(int i=0;i<total;++i) {if(nodes[i]) ++num;}
};
Solution& Solution::operator =(const Solution &s){
    terminals=s.terminals;
    mincost = s.mincost;
    num = s.num;
    total = s.total;
    terminalnum = s.terminalnum;
    g = s.g;
    if(nodes!=NULL) delete []nodes;
    nodes = new bool[total];
    for(int i=0;i<total;++i){
        nodes[i]=s.nodes[i];
    }
};
void Solution::print(){
    printf("Solution: ");
    for(int i=0;i<total;++i){
        if(nodes[i]){printf("%d ",i+1);}
    }
    printf("\n");
};
void Solution::vibrate(){
    double randnum;
    for(int i=0;i<total;++i){
        bool isreverse=false;
        for(int j=0;j<terminalnum;++j){
            if(i==terminals[j]) {isreverse=true;break;}
        }
        if(!isreverse){
            randnum = (double)(rand()%10000)/10000;
            if(randnum<=vibrate_rate){
                nodes[i]=!nodes[i];//reverse
                if(nodes[i]) ++num;
                else --num;
            }
        }   
    }
}