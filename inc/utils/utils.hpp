#ifndef TDTSPTW_UTIL_HPP
#define TDTSPTW_UTIL_HPP

#include "params/constants.hpp"
#include "libs/unordered_dense.hpp"

#include <queue>
#include <fstream>
#include <unistd.h> // hostname
#include <sys/time.h> // CPUTime
#include <sys/resource.h> // CPUTime
#include <vector>
#include <queue>
#include <unordered_map>

inline std::string peak_memory() {
    std::ifstream f("/proc/self/status");
    std::string line;
    while (std::getline(f, line))
        if (line.rfind("VmPeak:", 0) == 0)
            return line;
    return "VmPeak not found in /proc/self/status";
}

inline std::string hostname() {
    char buf[512];
    if (gethostname(buf, 512) == 0) { // success = 0, failure = -1
        return {buf};
    }
    return {};
}

inline void limit_memory_use(unsigned long lim_gb) {
    struct rlimit memlimit;
    unsigned long bytes = lim_gb * (1024 * 1024 * 1024);
    memlimit.rlim_cur = bytes;
    memlimit.rlim_max = bytes;
    setrlimit(RLIMIT_AS, &memlimit);
}

inline std::pair<double, double> CPUTime() {
    rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    return std::make_pair(static_cast<double>(ru.ru_utime.tv_sec) + static_cast<uint>(ru.ru_utime.tv_usec) * 1e-6,
                          static_cast<double>(ru.ru_stime.tv_sec) + static_cast<uint>(ru.ru_stime.tv_usec) * 1e-6);
}

template<class T, class S, class C>
void shrinkToFit(std::priority_queue<T, S, C> &q) {
    struct HackedQueue : private std::priority_queue<T, S, C> {
        static S &Container(std::priority_queue<T, S, C> &q) {
            return q.*&HackedQueue::c;
        }
    };
    HackedQueue::Container(q).shrink_to_fit();
}

template<class T, class S, class C>
void clear(std::priority_queue<T, S, C> &q) {
    struct HackedQueue : private std::priority_queue<T, S, C> {
        static S &Container(std::priority_queue<T, S, C> &q) {
            return q.*&HackedQueue::c;
        }
    };
    HackedQueue::Container(q).clear();
}

#endif //TDTSPTW_UTIL_HPP
