#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#include <vector>

// Object that contains just a string.
class SingleSSOString {
public:
    SingleSSOString()
        : _contents("contents") {}
    SingleSSOString(std::string_view contents)
        : _contents(contents) {}

    inline static const std::string name = "SingleSSOString";

private:
    std::string _contents;
};

class FiveSSOStrings {
public:
    FiveSSOStrings(std::string_view contents)
        : _s1(contents)
        , _s2(contents)
        , _s3(contents)
        , _s4(contents)
        , _s5(contents) {}
    FiveSSOStrings()
        : _s1("sso")
        , _s2("sso")
        , _s3("sso")
        , _s4("sso")
        , _s5("sso") {}

    inline static const std::string name = "FiveSSOStrings";

private:
    std::string _s1;
    std::string _s2;
    std::string _s3;
    std::string _s4;
    std::string _s5;
};

#endif /* TEST_OBJECT_H */
