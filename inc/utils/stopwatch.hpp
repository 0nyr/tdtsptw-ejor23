#pragma once

#include "libs/unordered_dense.hpp"

#include <chrono>
#include <string>
#include <fstream>

using namespace std::string_literals;

class stopwatch {
    using tp = std::chrono::time_point<std::chrono::steady_clock>;
    ankerl::unordered_dense::map<std::string, std::tuple<tp, double, double>> m_; // key -> (time point, lap, global)

    template<bool total = false>
    void display(const std::string &prefix = ""s) {
        for (const auto &[s, x]: m_)
            std::cout << prefix << s << "\t" << std::get<total ? 2 : 1>(x) << std::endl;
    }

public:
    void tic(const std::string &s) {
        std::get<0>(m_[s]) = std::chrono::steady_clock::now();
    }

    void toc(const std::string &s) {
        const auto it = m_.find(s);
        std::get<1>(it->second) += std::chrono::duration_cast<std::chrono::duration<double>>(
                std::chrono::steady_clock::now() - std::get<0>(it->second)).count();
    }

    void display_total(const std::string &prefix = ""s) {
        display<true>(prefix);
    }

    void display_lap(const std::string &prefix = ""s) {
        display<false>(prefix);
    }

    void clear() {
        m_.clear();
    }

    void lap() {
        for (auto &[s, x]: m_) {
            std::get<2>(x) += std::get<1>(x);
            std::get<1>(x) = 0;
        }
    }
};
