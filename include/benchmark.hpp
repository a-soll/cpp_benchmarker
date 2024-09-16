#ifndef OUTPUT_H
#define OUTPUT_H

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using times = std::vector<uint64_t>;

template <typename T>
using test = std::function<void(times &)>;

template <typename T>
using test_pair = std::pair<std::string, test<T>>;

template <typename T>
using test_vector = std::vector<test_pair<T>>;

enum benchmark_unit { SECONDS, MILLISECONDS, MICROSECONDS, NANOSECONDS };

template <typename T>
class Benchmark {
public:
    Benchmark<T>(benchmark_unit unit, uint64_t num_tests)
        : _num_tests(num_tests) {
        switch (unit) {
        case SECONDS:
            this->_unit = "s";
        case MILLISECONDS:
            this->_unit = "ms";
        case MICROSECONDS:
            this->_unit = "us";
        case NANOSECONDS:
        default:
            this->_unit = "ns";
        }
    }
    void add_tests(test_vector<T> &tests) {
        this->_results.clear();
        this->_max_len = 0;
        this->_output.clear();
        for (const auto i : tests) {
            this->_max_len = std::max<int64_t>(i.first.length(), this->_max_len);
        }
        this->_tests = &tests;
    }

    void run_tests() {
        this->_times.clear();
        std::cout << T::name << '\n';
        std::cout << "-----------------------------\n";
        for (auto &p : *this->_tests) {
            this->_output += p.first;
            for (int i = p.first.length(); i < this->_max_len + 2;
                 i++) { // this can't be the best way
                this->_output += ' ';
            }
            p.second(this->_times);
            this->_output += std::to_string(this->_get_avg());
            std::cout << this->_output << this->_unit << "\n";
            this->_output.clear();
            this->_times.clear();
        }
    }

private:
    std::vector<int64_t> _results;
    times _times;
    test_vector<T> *_tests = nullptr;
    std::string _output;
    int64_t _max_len = 0; // used for formatting output
    std::string _unit;
    uint64_t _num_tests;

    uint64_t _get_avg() {
        uint64_t avg = 0;

        for (auto &i : this->_times) {
            avg += i;
        }
        return avg = avg / this->_times.size();
    }
};

#endif /* OUTPUT_H */
