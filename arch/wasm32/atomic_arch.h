#ifndef __NR_restart_syscall
#include <bits/syscall.h>
#endif

#define a_barrier() syscall(__NR_membarrier)

#define a_ll(p) *p
#define a_sc(p, s) \
    ({ \
        *p = s; \
        1; \
    })

#define a_crash() abort()
