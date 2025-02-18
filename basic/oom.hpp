#include <iostream>
#include <exception>
using namespace std;

bool apply_big_memory(){
#define BIGMEM 1LL << 38
    try{
        int* p = new int[BIGMEM];
        if(p != nullptr){
            std::cout<<"success!"<<std::endl;
            for (size_t i = 0; i < BIGMEM; ++i) {
                p[i] = i;
            }
            return true;
        }else{
            return false;
        }
    }catch(std::exception ex){
        std::cout<<ex.what()<<std::endl;
        return false;
    }
}