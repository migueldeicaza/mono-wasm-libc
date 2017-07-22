#include "pthread_impl.h"

static int __errno__ = 0;

int *__errno_location(void)
{
	// FIXME-lrz remove once we have threads
	//return &__pthread_self()->errno_val;
	return &__errno__;
}
