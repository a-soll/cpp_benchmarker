#include "benchmark.hpp"
#include "helper.h"
#include <iostream>

template <typename T>
void test_array_append(times &t) {
    size_t ind             = 0;
    const size_t ARRAY_MAX = 50;
    std::array<T, ARRAY_MAX> objects;

    for (int i = 0; i < num_tests; i++) {
        T o;
        auto start    = high_resolution_clock::now();
        objects[ind]  = o;
        auto end      = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        t.push_back(duration.count());
        if (ind == ARRAY_MAX - 1) {
            ind = 0;
        } else {
            ind++;
        }
    }
}

template <typename T>
void add_array_tests(test_vector<T> &tests) {
    tests.push_back({"array append", test_array_append<T>});
}
