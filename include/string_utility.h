
#ifndef STRING_UTILITY_H
#define STRING_UTILITY_H

#include <vector>
#include <string>

namespace string_utility
{
    std::vector<std::string> explode(std::string sourceStr, char delimiter);
    std::string getCharsUntil(std::string sourceStr, char delimiter, int startIndex=0);
}

#endif // STRING_UTILITY_H
