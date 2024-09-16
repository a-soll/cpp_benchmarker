#include "array_benchmarks.hpp"
#include "benchmark.hpp"
#include "vector_benchmarks.hpp"

template <typename T>
void run_tests() {
    Benchmark<T> out(MICROSECONDS, 999999);
    test_vector<T> tests;

    tests.push_back({"vector push back", test_vector_push_back<T>}); // add your tests
    tests.push_back({"vector push back (move)", test_vector_push_back_move<T>});

    add_vector_tests<T>(tests);
    add_array_tests<T>(tests);

    out.add_tests(tests);
    out.run_tests();
}
