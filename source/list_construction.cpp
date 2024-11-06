#include "../include/list_construction.h"
#include "../include/list.h"

#include <stdlib.h>
#include <string.h>

#include "../My_lib/Assert/my_assert.h"
#include "../My_lib/Logger/logging.h"
#include "../My_lib/helpful.h"

enum ListError ListCtor (list_t* const list, const size_t number_elem, const size_t elem_size)
{
    ASSERT (list != NULL, "Invalid argument for list [%p] for constructor\n", list);

    LOG (DEBUG,
                "Constructor of the list got argument:\n"
                "| list = %p |\n", list);

    list->counter = 0;

    list->size = number_elem;

    list->elem_size = elem_size;

    list->free = 1;

    list->data = calloc (list->size, list->elem_size * list->size);
    if (list->data == NULL)
    {
        return kCantCtorList;
    }

    list->order = (order_list_t*) calloc (list->size, sizeof (order_list_t));
    if (list->order == NULL)
    {
        FREE_AND_NULL (list->data);
        return kCantCtorList;
    }

    memset (list->data, 0, list->elem_size + list->size);

    for (size_t index_ctor_ = 1; index_ctor_ < number_elem; index_ctor_++)
    {
        list->order [index_ctor_].next = index_ctor_ + 1;
        list->order [index_ctor_].previous = (size_t) -1;
    }

    list->order [0].next = 0;
    list->order [0].previous = 0;
    list->order [number_elem - 1].next = number_elem - 1;

    return kDoneList;
}

enum ListError ListDtor (list_t* const list)
{
    ASSERT (list != NULL, "Invalid argument for list [%p] for destructor\n", list);

    LOG (DEBUG,
                "Destructor of the list got argument:\n"
                "| list = %p |\n",
                list);

    FREE_AND_NULL (list->order);
    FREE_AND_NULL (list->data);

    list->counter = 0;
    list->size = 0;
    list->elem_size = 0;
    list->free = 0;

    return kDoneList;
}
