#include <any>
#include <string>
#include <iostream>
using namespace std;

void test_any(){
    //std::any t1 = 37;
    std::string s = "abc";
    std::any t1 = s;
    if( t1.type() == typeid(int)){
        std::cout<< typeid(t1).name() <<endl;
    }else if(t1.type() == typeid(string)){
        std::cout<< typeid(string).name() <<endl;
    }else{
        std::cout<< typeid(t1).name() <<endl;
    }
}