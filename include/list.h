#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>

typedef size_t list_elem_t;

typedef struct order_list
{
    size_t next;

    size_t previous;
} order_list_t;

typedef struct list
{
    void* data;

    order_list_t* order;

    size_t counter;

    size_t size;

    size_t free;

    size_t elem_size;
} list_t;

enum ListError
{
    kDoneList                   = 0,
    kCantCtorList               = 1,
    kCantDtorList               = 2,
    kCantPushList               = 3,
    kCantPopList                = 4,
    kCantDumpList               = 5,
    kVerifyListNullPtr          = 6,
    kVerifyListInvalidZeroElem  = 7,
    kVerifyListInvalidSize      = 8,
    kVerifyListInvalidOrderList = 9,
    kVerifyListInvalidOrderFree = 10,
};

#include "list_construction.h"
#include "list_push.h"
#include "list_pop.h"
#include "list_index.h"
#include "list_error_handler.h"

#endif // LIST_H_
