#include "perms.h"

#include <stddef.h>
#include <string.h>

// TODO: Den her funktion virker kun for en utrolig begrænset mængde input (u-r)
//
// Den skulle også gerne virke for:
// - u, g, o
// - + og -
// - r, w, x, rw, rx, wx, rwx (eller en anden rækkefølge af dem)
bool chmod(const char *input, struct perms_t *perms) {
    if (input == NULL) {
        return false;
    }
    bool u_flag = false;
    bool g_flag = false;
    bool o_flag = false;
    bool a_flag = false;

    bool add_flag = false;
    bool remove_flag = false;

    bool r_flag = false;
    bool w_flag = false;
    bool x_flag = false;

    switch (input[0]) {
        case 'u':
            u_flag = true;
            break;
        case 'g':
            g_flag = true;
            break;
        case 'o':
            o_flag = true;
            break;
        case 'a':
            a_flag = true;
            break;

    }

    switch (input[1]) {
        case '+':
            add_flag = true;
            break;
        case '-':
            remove_flag = true;
            break;
    }

    const size_t len = strlen(input);
    for (int i = 2; i < len; i++) {
        switch (input[i]) {
            case 'r':
                r_flag = true;
                break;
            case 'w':
                w_flag = true;
                break;
            case 'x':
                x_flag = true;
                break;
        }
    }

    if (u_flag & remove_flag & r_flag) perms->bits &= ~USER_READ;
    if (u_flag & remove_flag & w_flag) perms->bits &= ~USER_WRITE;
    if (u_flag & remove_flag & x_flag) perms->bits &= ~USER_EXECUTE;

    if (g_flag & remove_flag & r_flag) perms->bits &= ~GROUP_READ;
    if (g_flag & remove_flag & w_flag) perms->bits &= ~GROUP_WRITE;
    if (g_flag & remove_flag & x_flag) perms->bits &= ~GROUP_EXECUTE;

    if (o_flag & remove_flag & r_flag) perms->bits &= ~OTHER_READ;
    if (o_flag & remove_flag & w_flag) perms->bits &= ~OTHER_WRITE;
    if (o_flag & remove_flag & x_flag) perms->bits &= ~OTHER_EXECUTE;


    if (u_flag & add_flag & r_flag) perms->bits |= USER_READ;
    if (u_flag & add_flag & w_flag) perms->bits |= USER_WRITE;
    if (u_flag & add_flag & x_flag) perms->bits |= USER_EXECUTE;

    if (g_flag & add_flag & r_flag) perms->bits |= GROUP_READ;
    if (g_flag & add_flag & w_flag) perms->bits |= GROUP_WRITE;
    if (g_flag & add_flag & x_flag) perms->bits |= GROUP_EXECUTE;

    if (o_flag & add_flag & r_flag) perms->bits |= OTHER_READ;
    if (o_flag & add_flag & w_flag) perms->bits |= OTHER_WRITE;
    if (o_flag & add_flag & x_flag) perms->bits |= OTHER_EXECUTE;

    if (a_flag & add_flag & r_flag) perms->bits |= USER_READ | GROUP_READ | OTHER_READ;
    if (a_flag & add_flag & w_flag) perms->bits |= USER_WRITE | GROUP_WRITE | OTHER_WRITE;
    if (a_flag & add_flag & x_flag) perms->bits |= USER_EXECUTE | GROUP_EXECUTE | OTHER_EXECUTE;

    if (a_flag & remove_flag & r_flag) perms->bits = perms->bits & ~USER_READ & ~GROUP_READ & ~OTHER_READ;
    if (a_flag & remove_flag & w_flag) perms->bits = perms->bits & ~USER_WRITE & ~GROUP_WRITE & ~OTHER_WRITE;
    if (a_flag & remove_flag & x_flag) perms->bits = perms->bits & ~USER_EXECUTE & GROUP_EXECUTE & ~OTHER_EXECUTE;

    // Når man AND'er med en maske med 0'er i, slukker man for enkelte bits
    // Når man OR'er med en maske med 1'er i, tænder man for enkelte bits

    // Hvis OTHER_READ er 0b000'000'100
    // så er ~OTHER_READ  0b111'111'011
    //
    // Eksempel:
    // 0644 og o-r giver 0640
    // og når man &'er med den maske, bliver den mindste bit sat til 0, og de resterende bits forbliver som de er.
    //perms->bits &= ~OTHER_READ;
    return true;
}
