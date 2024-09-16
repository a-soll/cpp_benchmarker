#include "run_tests.hpp"
#include "test_object.h"
#include <iostream>

int main() {
    // simple SSO object
    run_tests<SingleSSOString>();

    // simple obj with 5 SSO strings
    run_tests<FiveSSOStrings>();
}
