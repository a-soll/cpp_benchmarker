#ifndef HELPER_H
#define HELPER_H

#include <chrono>
#include <ratio>
#include <vector>

using namespace std::chrono;

extern std::vector<int64_t> std_results;

constexpr int num_tests = 9999999;

void print_header(std::string_view obj_name);
void print_avg(std::string_view test_name);
void reset_results();
uint64_t get_avg();

#endif /* HELPER_H */
