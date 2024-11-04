#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef size_t list_elem_t;

typedef struct order_list
{
    size_t next;

    size_t previous;
} order_list_t;

typedef struct list
{
    list_elem_t* data;

    order_list_t* order;

    size_t counter;

    size_t size;

    size_t free;
} list_t;

enum ListError
{
    kDoneList       = 0,
    kCantCtorList   = 1,
    kCantDtorList   = 2,
    kCantPushList   = 3,
    kCantPopList    = 4,
    kVerifyListNullPtr = 5,
    kVerifyListInvalidZeroElem = 6,
    kVerifyListInvalidSize = 7,
    kVerifyListInvalidOrderList = 8,
    kVerifyListInvalidOrderFree = 9,
};

#include "list_construction.h"
#include "list_push.h"
#include "list_pop.h"
#include "list_index.h"
#include "list_error_handler.h"

#endif // LIST_H
