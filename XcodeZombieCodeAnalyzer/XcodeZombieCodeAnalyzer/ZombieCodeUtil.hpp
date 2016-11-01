//
//  CodeCheckUtil.hpp
//  ClangCodeCheckPlugin
//
//  Created by KyleWong on 14/10/2016.
//
//

#ifndef CodeCheckUtil_hpp
#define CodeCheckUtil_hpp
#include <string>
#include<algorithm>
#include <functional>


using namespace std;

static inline bool has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
    str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

static inline string &ltrim(std::string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(),
                               not1(ptr_fun<int, int>(isspace))));
    return s;
}

// trim from end
static inline string &rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(),
                    not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline string &trim(string &s) {
    return ltrim(rtrim(s));
}
#endif /* CodeCheckUtil_hpp */
