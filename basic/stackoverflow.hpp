#include <exception>
#include <iostream>
using namespace std;

void create_stackoverflow(){
    try{
        std::cout<< "alloc data on stack" << std::endl;
        //create_stackoverflow();
        int p[10 * 1024 * 1024];
        //[ 1024 * 1024] = 3;
    }catch(exception ex){
        std::cout<< ex.what() << std::endl;
    }
}