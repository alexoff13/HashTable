
#include "Hash.h"

unsigned int Hash::fnvHash(const std::string str, int table_size) {
    const char *str1 = str.c_str();
    const size_t length = strlen(str1) + 1;
    unsigned int hash = OFFSET_BASIS;
    for (size_t i = 0; i < length; ++i) {
        hash ^= *str1++;
        hash *= FNV_PRIME;
    }
    return hash % table_size;
//    return 1;
}

int Hash::HashFunction1(const std::string str, int table_size) {
    return fnvHash(str, table_size);
}

unsigned int Hash::HashFunction2(int hash1, int step, int table_size) {
    return (hash1 + step * 2) % table_size;
}
