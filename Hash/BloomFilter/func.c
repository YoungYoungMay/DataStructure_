#include <stdio.h>
#include <stdint.h>

uint64_t BKDRHash(const char* str)
{
    uint64_t hash = 0;
    uint64_t ch;
    while(ch = (uint64_t)*str++)
    {
        hash = 65599*hash + ch;
    }
    return hash;
}

uint64_t SDBMHash(const char* str)
{
    uint64_t hash = 0;
    uint64_t ch;
    while(ch = (uint64_t)*str++)
    {
        hash = 131*hash + ch;
    }
    return hash;
}
