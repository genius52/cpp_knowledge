#include <iostream>
#include "basic/typeid.hpp"
#include "basic/oom.hpp"
#include "basic/stackoverflow.hpp"
#include "thread/threadpool.hpp"
#include "newcpp/stdany.hpp"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.


int main() {
    {
        create_stackoverflow();
    }
    {
        test_any();
    }
//    {
//#define MEM_SIZE 320 * 1024 * 1024 * 1024
//            char* addr = (char*) malloc((long)MEM_SIZE);
//            printf("主线程调用malloc后，目前共申请了 32gb 的虚拟内存\n");
//
//            //循环频繁访问虚拟内存
//            int idx = 1;
//            try{
//                while(1) {
//                    printf("开始访问 32gb 大小的虚拟内存...\n");
//                    memset(addr, idx, (long)MEM_SIZE);
//                    idx++;
//                }
//            }catch(std::exception ex){
//                std::cout<< ex.what()<<endl;
//            }
//    }
    {
        //申请太大的内存
        auto ret = apply_big_memory();
        std::cout<< ret<< std::endl;
    }
    {
        //获取子类的数量
        using namespace check_typeid;
        std::unique_ptr<Base> pA = std::make_unique<DeriveA>();
        std::unique_ptr<Base> pB = std::make_unique<DeriveB>();
        std::cout<< Base::getSubclasssize() << std::endl;
    }
    {
        Thread_pool t(4);
        int n = 100;
        std::function<int(int, int)> calc_sum = [](int begin, int end) -> int {
            int sum = 0;
            for (int i = begin; i <= end; i++) {
                sum += i;
            }
            return sum;
        };
        auto result1 = t.enqueue(calc_sum,1,100);
        auto result2 = t.enqueue(calc_sum,1,10000);
        std::cout << result1.get() << std::endl;
        std::cout << result2.get() << std::endl;

    }
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
    // <b>lang</b> variable name to see how CLion can help you rename it.
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        // TIP Press <shortcut actionId="Debug"/> to start debugging your code.
        // We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/>
        // breakpoint for you, but you can always add more by pressing
        // <shortcut actionId="ToggleLineBreakpoint"/>.
        std::cout << "i = " << i << std::endl;
    }

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.