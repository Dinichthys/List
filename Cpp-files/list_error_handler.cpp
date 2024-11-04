#include "../Headers/list_error_handler.h"
#include "../Headers/list.h"

#include <stdlib.h>

#include "../My_lib/Assert/my_assert.h"
#include "../My_lib/Logger/logging.h"

const char* EnumToStr (const enum ListError error)
{
    #define CASE_ENUM_(enum_elem)       \
        case enum_elem:                 \
        {                               \
            return #enum_elem;          \
        }

    switch (error)
    {
        CASE_ENUM_ (kDoneList);
        CASE_ENUM_ (kCantCtorList);
        CASE_ENUM_ (kCantDtorList);
        CASE_ENUM_ (kCantPushList);
        CASE_ENUM_ (kCantPopList);
        default:
            return "Undefined enum element";
    }

    return "Function didn't completed";

    #undef CASE_ENUM_
}
