#include "benchmark.hpp"
#include "helper.h"
#include <iostream>

template <typename T>
void test_vector_push_back(times &t) {
    std::vector<T> objects;
    for (int i = 0; i < num_tests; i++) {
        T o;
        auto start = high_resolution_clock::now();
        objects.push_back(o);
        auto end      = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        t.push_back(duration.count());
    }
}

template <typename T>
void test_vector_emplace_back_no_args(times &t) {
    std::vector<T> objects;
    for (int i = 0; i < num_tests; i++) {
        auto start = high_resolution_clock::now();
        objects.emplace_back();
        auto end      = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        t.push_back(duration.count());
    }
}

template <typename T>
void test_vector_emplace_back_args(times &t) {
    std::vector<T> objects;
    for (int i = 0; i < num_tests; i++) {
        auto start = high_resolution_clock::now();
        objects.emplace_back("contents");
        auto end      = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        t.push_back(duration.count());
    }
}

template <typename T>
void test_vector_push_back_move(times &t) {
    std::vector<T> objects;
    for (int i = 0; i < num_tests; i++) {
        auto start = high_resolution_clock::now();
        T o;
        objects.push_back(std::move(o));
        auto end      = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start);
        t.push_back(duration.count());
    }
}

template <typename T>
void add_vector_tests(test_vector<T> &tests) {
    tests.push_back({"vector push back", test_vector_push_back<T>});
    tests.push_back({"vector push back (move)", test_vector_push_back_move<T>});
    tests.push_back({"vector emplace back (no args)", test_vector_emplace_back_no_args<T>}
    );
    tests.push_back({"vector emplace back (args)", test_vector_emplace_back_args<T>});
}
