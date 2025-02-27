#include <iostream>
#include <exception>
#include "memory_info.hpp"
using namespace std;

bool apply_big_memory() {
    try {
        // 获取系统虚拟内存大小
        size_t maxVirtualMemory = MemoryInfo::getVirtualMemorySize();
        // 尝试分配系统虚拟内存的75%
        size_t allocSize = (maxVirtualMemory * 3) / 4 / sizeof(int);
        
        std::cout << "尝试分配内存: " << (allocSize * sizeof(int) / (1024.0 * 1024 * 1024)) << " GB" << std::endl;
        
        int* p = new int[allocSize];
        if (p != nullptr) {
            std::cout << "内存分配成功!" << std::endl;
            delete[] p;  // 记得释放内存
            return true;
        } else {
            return false;
        }
    } catch (const std::exception& ex) {
        std::cout << "内存分配失败: " << ex.what() << std::endl;
        return false;
    }
}