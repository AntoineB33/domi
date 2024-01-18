#include <string>
#include <algorithm>
#include "case_insensitive_compare.h"

bool caseInsensitiveCompare(const std::string& str1, const std::string& str2) {
    // Transform both strings to lowercase before comparison
    std::string str1Lower = str1;
    std::string str2Lower = str2;
    std::transform(str1Lower.begin(), str1Lower.end(), str1Lower.begin(), ::tolower);
    std::transform(str2Lower.begin(), str2Lower.end(), str2Lower.begin(), ::tolower);

    // Perform the comparison
    return str1Lower == str2Lower;
}