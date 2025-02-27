#include <iostream>

#ifdef _WIN32
#include <windows.h>
#elif defined(__APPLE__) && defined(__MACH__)
#include <sys/sysctl.h>
#include <mach/mach.h>
#elif defined(__unix__) || defined(__unix) || defined(unix)
#include <unistd.h>
#include <sys/sysinfo.h>
#endif

class MemoryInfo {
public:
    static size_t getVirtualMemorySize() {
#ifdef _WIN32
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);
        return static_cast<size_t>(memInfo.ullTotalVirtual);
#elif defined(__APPLE__) && defined(__MACH__)
        // 获取物理内存
        int mib[2] = { CTL_HW, HW_MEMSIZE };
        u_int namelen = sizeof(mib) / sizeof(mib[0]);
        uint64_t physicalMemory = 0;
        size_t len = sizeof(physicalMemory);
        
        if (sysctl(mib, namelen, &physicalMemory, &len, NULL, 0) == 0) {
            // 获取交换空间大小
            xsw_usage vmusage;
            size_t size = sizeof(vmusage);
            if (sysctlbyname("vm.swapusage", &vmusage, &size, NULL, 0) == 0) {
                // 返回物理内存加上交换空间的总大小
                return physicalMemory + vmusage.xsu_total;
            }
            return physicalMemory;
        }
#elif defined(__unix__) || defined(__unix) || defined(unix)
        struct sysinfo si;
        if (sysinfo(&si) == 0) {
            // 总虚拟内存 = 交换空间 + 物理内存
            return static_cast<size_t>(si.totalram) * si.mem_unit + 
                   static_cast<size_t>(si.totalswap) * si.mem_unit;
        }
#endif
        return 0;
    }

    static void printMemoryInfo() {
        size_t virtualMemory = getVirtualMemorySize();
        std::cout << "总虚拟内存大小: " << (virtualMemory / (1024.0 * 1024 * 1024)) << " GB" << std::endl;
    }
}; 