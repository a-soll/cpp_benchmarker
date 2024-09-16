#include "benchmark.hpp"
#include "helper.h"
#include <iostream>

template <typename T>
int64_t test_array_append() {
    size_t ind             = 0;
    const size_t ARRAY_MAX = 50;
    std::array<T, ARRAY_MAX> objects;
    T o;
    auto start    = high_resolution_clock::now();
    objects[ind]  = o;
    auto end      = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    return duration.count();
}

template <typename T>
void add_array_tests(test_vector<T> &tests) {
    tests.push_back({"array append", test_array_append<T>});
}
