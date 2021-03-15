#include "iostream"
#include "Hash.h"

unsigned int Hash::fnvHash(const std::string str, int table_size) {

    int len_ = str.length();
    int hash = 0;
    for (int i = 0; i < len_; ++i) {
        hash += int(str[i]);
    }
//    const char *str1 = str.c_str();
//    const size_t length = strlen(str1) + 1;
//    unsigned int hash = OFFSET_BASIS;
//    for (size_t i = 0; i < length; ++i) {
//        hash ^= *str1++;
//        hash *= FNV_PRIME;
//    }
    return hash % table_size;

}

int Hash::HashFunction1(const std::string str, int table_size) {
    return fnvHash(str, table_size);
}

unsigned int Hash::HashFunction2(int hash1, int step, int table_size) {
    return (hash1 + (step + step * step) / 2) % table_size;
}
