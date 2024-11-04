#ifndef MY_ASSERT_H
#define MY_ASSERT_H

#include <stdio.h>
#include <stdlib.h>

#include "../Assert/print_error.h"
#include "../Logger/logging.h"

#define ASSERT(comparison, ...)                                                 \
    do                                                                          \
    {                                                                           \
        if ((comparison) == 0)                                                  \
        {                                                                       \
            fprintf (stderr,"%s:%d (%s)\n", __FILE__, __LINE__, __FUNCTION__);  \
            print_err (stderr, __VA_ARGS__);                                    \
            abort();                                                            \
        };                                                                      \
    }                                                                           \
    while (0)

#endif // MY_ASSERT_H
