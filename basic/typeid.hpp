#include <unordered_set>


namespace check_typeid{

    class Base{
    public:
        ~Base() = default;
        static void registerSubclass(const std::type_info& type_info){
            set_.insert(type_info.name());
        }
        static size_t getSubclasssize(){
            return set_.size();
        }
    private:
        static std::unordered_set<std::string> set_;
    };
    std::unordered_set<std::string> Base::set_;
    class DeriveA:public Base{
    public:
        DeriveA(){
            Base::registerSubclass(typeid(*this));
        }
    };

    class DeriveB:public Base{
    public:
        DeriveB(){
            Base::registerSubclass(typeid(*this));
        }
    };
}