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

        CASE_ENUM_ (kVerifyListNullPtr);
        CASE_ENUM_ (kVerifyListInvalidZeroElem);
        CASE_ENUM_ (kVerifyListInvalidSize);
        CASE_ENUM_ (kVerifyListInvalidOrderList);
        CASE_ENUM_ (kVerifyListInvalidOrderFree);

        default:
            return "Undefined enum element";
    }

    return "Function didn't completed";

    #undef CASE_ENUM_
}

enum ListError VerifyList (const list_t* const list)
{
    if (list == NULL)
    {
        return kVerifyListNullPtr;
    }

    if ((list->data [0] != 0)
        || ((list->order [0].next == 0) && (list->order [0].previous != 0))
        || ((list->order [0].next != 0) && (list->order [0].previous == 0))
        || ((list->order [0].next == 0) && (list->order [0].previous == 0) && (list->counter != 0)))
    {
        return kVerifyListInvalidZeroElem;
    }

    if (list->size < list->counter)
    {
        return kVerifyListInvalidSize;
    }

    size_t index_element = list->order [0].next;

    while (index_element != 0)
    {
        if ((list->order [index_element].previous == (size_t) - 1)
            || (list->order [index_element].next     != list->order [list->order [index_element].next].previous)
            || (list->order [index_element].previous != list->order [list->order [index_element].previous].next))
        {
            return kVerifyListInvalidOrderList;
        }

        index_element = list->order [index_element].next;
    }

    index_element = list->free;

    while (index_element != 0)
    {
        if (list->order [index_element].previous != (size_t) - 1)
        {
            return kVerifyListInvalidOrderFree;
        }

        index_element = list->order [index_element].next;
    }

    return kDoneList;
}
