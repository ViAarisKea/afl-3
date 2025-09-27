#ifndef AFL_3_CHMOD_PERMS_H
#define AFL_3_CHMOD_PERMS_H
#include <stdint.h>

struct perms_t {
    uint32_t bits;
};

bool chmod(const char *input, struct perms_t *);

#define USER_READ 0400 // 0b100'000'000
#define USER_WRITE 0200 // 0b010'000'000
#define USER_EXECUTE 0100 // 0b001'000'000

#define GROUP_READ 0040 // 0b000'100'000
#define GROUP_WRITE 0020 // 0b000'010'000
#define GROUP_EXECUTE 0010 // 0b000'001'000

#define OTHER_READ 0004
#define OTHER_WRITE 0002
#define OTHER_EXECUTE 0001

#define ALL_READ (USER_READ | GROUP_READ | OTHER_READ)
#define ALL_WRITE (USER_WRITE | GROUP_WRITE | OTHER_WRITE)
#define ALL_EXECUTE (USER_EXECUTE | GROUP_EXECUTE | OTHER_EXECUTE)


#endif //AFL_3_CHMOD_PERMS_H