#include "array_benchmarks.hpp"
#include "benchmark.hpp"
#include "vector_benchmarks.hpp"

template <typename T>
void run_tests() {
    Benchmark<T> out(MICROSECONDS, 999999);
    test_vector<T> tests;

    add_vector_tests<T>(tests);
    add_array_tests<T>(tests);

    out.add_tests(tests);
    out.run_tests();

    std::cout << '\n';
}
