#include <cstring>

const char * match(const char * s, char ch) {
    const char* pos = std::strchr(s, ch);
    return pos;
}