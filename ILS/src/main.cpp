#include"ILS.h"
#include<vector>
#include<string>
#include<iostream>
#include<ctime>
std::string filedir("../data/");
std::string files[30] = {"antiwheel5.stp","b01.stp","b02.stp","b03.stp","b04.stp","b05.stp","b06.stp","b07.stp","b08.stp","b09.stp",
"b10.stp","b11.stp","b12.stp","b13.stp","b14.stp","b15.stp","b16.stp","b17.stp","b18.stp","cc3-4p.stp","cc3-4u.stp","cc6-2p.stp",
"cc6-2u.stp","design432.stp","hc6p.stp","hc6u.stp","oddcycle3.stp","oddwheel3.stp","p401.stp","se03.stp"};
int main(){
    Graph g;
    ILS ils;
    for(int i=0;i<30;++i){
        std::string filename = filedir+files[i];
        g.getInput(filename.c_str());
        //g.print();
        ils.setGraph(&g);
        clock_t start,end;
        std::cout<<filename<<" Running"<<std::endl;
        start = clock();
        ils.run();
        std::cout<<"best result:"<<ils.getResult()<<std::endl;
        end = clock();
        std::cout<<"total running time: "<<(double)(end-start)/CLOCKS_PER_SEC<<std::endl;
        std::cout<<"--------------------------"<<std::endl;
        g.clear();
    }
    return 0;
};