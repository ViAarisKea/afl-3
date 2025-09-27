#include "perms.h"

#include <stddef.h>
#include <string.h>


bool check_validity(const char *input) {
    if (input == NULL) {
        return false;
    }
    if (input[0] != 'o' && input[0] != 'u' && input[0] != 'g' && input[0] != 'a') {
        return false;
    }

    if (input[1] != '-' && input[1] != '+') {
        return false;
    }

    if (input[2] != 'r' && input[2] != 'w' && input[2] != 'x') {
        return false;
    }
    return true;
}

void add_perms(uint16_t mask, struct perms_t *perms) {
    perms->bits |= mask;
}

void remove_perms(uint16_t mask, struct perms_t *perms) {
    perms->bits &= ~mask;
}


bool chmod(const char *input, struct perms_t *perms) {
    if (!check_validity(input)) return false;

    bool u_flag = false, g_flag = false, o_flag = false, a_flag = false;
    bool r_flag = false, w_flag = false, x_flag = false;

    switch (input[0]) {
        case 'u': u_flag = true; break;
        case 'g': g_flag = true; break;
        case 'o': o_flag = true; break;
        case 'a': a_flag = true; break;
    }

    const size_t len = strlen(input);
    for (int i = 2; i < len; i++) {
        switch (input[i]) {
            case 'r': r_flag = true; break;
            case 'w': w_flag = true; break;
            case 'x': x_flag = true; break;
        }
    }

    uint16_t mask = 0;
    if (u_flag) {
        if (r_flag) mask |= USER_READ;
        if (w_flag) mask |= USER_WRITE;
        if (x_flag) mask |= USER_EXECUTE;
    }
    if (g_flag) {
        if (r_flag) mask |= GROUP_READ;
        if (w_flag) mask |= GROUP_WRITE;
        if (x_flag) mask |= GROUP_EXECUTE;
    }
    if (o_flag) {
        if (r_flag) mask |= OTHER_READ;
        if (w_flag) mask |= OTHER_WRITE;
        if (x_flag) mask |= OTHER_EXECUTE;
    }
    if (a_flag) {
        if (r_flag) mask |= ALL_READ;
        if (w_flag) mask |= ALL_WRITE;
        if (x_flag) mask |= ALL_EXECUTE;
    }

    switch (input[1]) {
        case '+': add_perms(mask, perms); break;
        case '-': remove_perms(mask, perms); break;
    }

    return true;
}
