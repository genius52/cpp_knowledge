#include <iostream>
#include <string>
using namespace std;

//软件设计六大原则

//1 开闭原则
// 新加的需求不能修改老的代码，接口支持新的扩展需求
class Shape{
public:
    virtual void draw() = 0;
};

class Rect : public Shape{
public:
    virtual void draw(){
        std::cout<<"draw rect"<<std::endl;
    }
};

class Round : public Shape{
public:
    virtual void draw(){
        std::cout<<"draw round"<<std::endl;
    }
};

class Paint{
public:
    void draw_picture(Shape& shape){
        shape.draw();
    }
};

//2 依赖倒置
//抽象工厂
class AbsturctProduct{
public:
    virtual void func(){
        std::cout<< "Absturct Product" << std::endl;
    }

};

class ProductA : public AbsturctProduct{
public:
    ProductA();
    virtual void func(){
        std::cout<< "this is ProductA" << std::endl;
    }
};

class ProductB : public AbsturctProduct{
public:
    ProductB();
    virtual void func(){
        std::cout<< "this is ProductB" << std::endl;
    }
};

class AbstructFactory{
public:
    virtual AbsturctProduct* create_product() = 0;
};

class FactoryA : public AbstructFactory{
public:
    virtual AbsturctProduct* create_product(){
        return new ProductA();
    }
};

class FactoryB : public AbstructFactory{
public:
    virtual AbsturctProduct* create_product(){
        return new ProductB();
    }
};

void craete_product(){
    AbstructFactory* factory = new FactoryB();
    AbsturctProduct* product = factory->create_product();
    product->func();
}


//3 里氏替换
//子类必须能够完全替换父类
class Bird{
public:
    virtual void fly(){
        std::cout<<"Bird can fly"<<std::endl;
    }
};

class Eagle :public Bird{
public:
    virtual void fly(){
        std::cout<<"Eagle can fly"<<std::endl;
    }
};

class Checken : public Bird{
public:
    virtual void fly(){//Wrong !
        std::cout<<"Eagle can fly"<<std::endl;
    }
};

void test_lsp(){

}

//4 接口隔离
class Workable{
public:
    virtual void work() = 0;
};

class Eatable{
public:
    virtual void eat() = 0;
};

class Programmer: public Workable,Eatable{
public:
    virtual void work() override{
        std::cout<<"Programmer is working" << endl;
    }
    virtual void eat() override{
        std::cout<<"Programmer is eating" << endl;
    }
};

class Robot: public Workable{ //Robot can not eat
public:
    virtual void work() override{
        std::cout<<"Robot is working" << endl;
    }
};


//5 迪米特
// (最小知识) 类之间的交互关系
class User_info{ //基本信息
    string name_;
    int age_;
public:
    User_info(string& name,int age){
        name_ = name;
        age_ = age;
    }
    string name(){
        return  name_;
    }

    int age(){
        return age_;
    };
};

class User_storage{ //数据持久化
    User_info* user_info_ = nullptr;
public:
    void add_user(User_info* user){
        user_info_ = user;
    }
    User_info* get_user(){
        return user_info_;
    }
};

class User_display{ //数据展示
public:
    void display(User_info* user_){
        std::cout<<user_->name() << " " << user_->age() << std::endl;
    }
};

//单一职责
//一个类只有一种功能
#include <numeric>
class Order{ //计算总额、持久化数据
    vector<double> sum_;
public:
    double calculate(){
        return std::accumulate(sum_.begin(),sum_.end(),0.0);
    }
    bool saveto_db(){
        return true;
    }
};

class Order_calculate{ // 可以复用在其他场景下
public:
    double calculate(vector<double>& sum){
        return std::accumulate(sum.begin(),sum.end(),0.0);
    }
};

class Order_save{ // 可以复用在其他场景下
public:
    bool saveto_db(){
        return true;
    }
};
