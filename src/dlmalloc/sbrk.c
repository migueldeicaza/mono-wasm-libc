#include <limits.h>
#include <errno.h>
#include <stdint.h>
#include "syscall.h"

static uintptr_t __brk(uintptr_t newbrk)
{
    return __syscall(SYS_brk, newbrk);
}

#define SBRK_ALIGN 32

void *sbrk(uintptr_t increment)
{
    static uintptr_t s_brk = 0;
    if (s_brk == 0) {
        s_brk = __brk(0);
    }

    uintptr_t start = ((s_brk + SBRK_ALIGN-1) & ~(SBRK_ALIGN-1));
    uintptr_t end = start + increment;

    uintptr_t new_brk = __brk(end);
    if (new_brk == (uintptr_t)-1) {
        return (void *)new_brk;
    }
    else if (new_brk < end) {
        errno = ENOMEM;
        return (void*)-1;
    }

    s_brk = new_brk;
    return (void *)start;
}
