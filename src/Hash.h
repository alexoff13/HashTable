#ifndef HASH_TABLE_HASH_H
#define HASH_TABLE_HASH_H


#include <string>
#include <cstring>

static const unsigned int FNV_PRIME = 16777619u;
static const unsigned int OFFSET_BASIS = 2166136261u;


class Hash {
private:
    unsigned int fnvHash(const std::string str, int table_size);

public:
    int HashFunction1(const std::string str, int table_size);

    unsigned int HashFunction2(int hash1, int step, int table_size);

};


#endif //HASH_TABLE_HASH_H
