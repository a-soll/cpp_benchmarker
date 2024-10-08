# Tool to help benchmark function runtime

This is a single header cpp benchmarkign tool. Simply include benchmark.hpp in your project.

## Explanation
The benchmarks are broken up into a few components:
```cpp
// vector of each test iteration result
using times = std::vector<uint64_t>;

// alias for test function callback
template <typename T>
using test = std::function<int64_t()>;

// ties string to function
template <typename T>
using test_pair = std::pair<std::string, test<T>>;

template <typename T>
using test_vector = std::vector<test_pair<T>>;
```

`times` is a vector of the test results on each iteration. It's used to calculate the average time the test took.

`test` represents a valid benchmarking function. You must provide a function that returns the time your operation took. It does not matter how you measure the time as long as you return it as `int64_t`.

`test_pair` is a pair of a string and a `test` function. The string is the name of the test you're performing.

`test_vector` is a vector of `test_pair`.

---

```cpp
enum benchmark_unit {
    SECONDS,
    MILLISECONDS,
    MICROSECONDS,
    NANOSECONDS
};
```
`benchmark_unit` represents the supported units of time. It's only used for output, so it should match whatever you're indending to use.

---

## BYOF (bring your own functions)
Right now, the tool only runs functions that are totally provided by you. Your functions must conform to a `test`, which just means you're just providing a function that returns its operation time as an `int64_t`.

The  reason you must measure the time of the operation in your own function is to eliminate any added latency from the function call itself. Function calls, unless truly inlined, can add latency and reduce the accuracy of the results.

## Example usage
Below is an example of how to set up a benchmark. This example will measure the time it takes for an `std::vector` to `push_back()` a provided object.

First, set up the `Benchmark` object. The `Benchmark` object takes the unit of time you intend to measure in (used for the output) as well as the number of times each test should be ran. The template parameter is used for whatever object you indend to test (with or against). In this example, the object is used as the data that the vector test functions will be operating on.

```cpp
template <typename T>
void run_tests() {
    Benchmark<T> bench(MICROSECONDS, 999999); // Set up the benchmark object (unit comes from `benchmark_unit`)

    // add your tests
    bench.add_test({"vector push back", test_vector_push_back<T>});
    bench.add_test({"vector push back (move)", test_vector_push_back_move<T>});

    bench.run_tests(); // run them
}

int main() {
    // assume SingleSSOString is an object that just has a small string member.
    run_tests<SingleSSOString>();

    // output:
    //     SingleSSOString
    // -----------------------------
    // vector push back         174ns
    // vector push back (move)  181ns
}
```

Definitions of the above test functions:

```cpp
// Example benchmark function that conforms to a valid `test`.
template <typename T>
int64_t test_vector_push_back() {
    std::vector<T> objects;
    T o;
    auto start = high_resolution_clock::now();
    objects.push_back(o);
    auto end      = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    return duration.count();
}

template <typename T>
int64_t test_vector_push_back_move() {
    std::vector<T> objects;
    T o;
    auto start = high_resolution_clock::now();
    objects.push_back(std::move(o));
    auto end      = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    return duration.count();
}
```
