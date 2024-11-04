#include "../Headers/list_push.h"
#include "../Headers/list.h"

#include <stdlib.h>

#include "../My_lib/Assert/my_assert.h"
#include "../My_lib/Logger/logging.h"

enum ListError ListPushAfterIndex (list_t* const list, const list_elem_t element, const size_t index)
{
    ASSERT (list != NULL, "Invalid argument for list [%p] for push after index\n", list);

    LOG (DEBUG,
                "Push after index of the list got argument:\n"
                "| list = %p | element = %p | index = %lu |\n"
                "| Next = %lu | Previous = %lu |\n",
                list, element, index,
                list->order [index].next, list->order [index].previous);

    if ((list->counter + 1 >= list->size) || (list->order [index].previous == 0))
    {
        return kCantPushList;
    }

    list->counter++;

    size_t new_element_index_ = list->free;

    list->free = list->order [list->free].next;

    list->data  [new_element_index_] = element;
    list->order [new_element_index_].next = list->order [index].next;
    list->order [new_element_index_].previous = index;

    list->order [index].next = new_element_index_;

    return kDoneList;
}

enum ListError ListPushFront (list_t* const list, const list_elem_t element)
{
    ASSERT (list != NULL, "Invalid argument for list [%p] for push after head\n", list);

    LOG (DEBUG,
                "Push after head of the list got argument:\n"
                "| list = %p | element = %lu |\n"
                "| Head = %lu | Tail = %lu |\n",
                list, element,
                list->order [0].previous, list->order [0].next);

    if (list->counter + 1 >= list->size)
    {
        return kCantPushList;
    }

    list->counter++;

    size_t new_element_index_ = list->free;

    list->free = list->order [list->free].next;

    list->data  [new_element_index_] = element;
    list->order [new_element_index_].next = 0;
    list->order [new_element_index_].previous = list->order [0].next;

    list->order [list->order [0].previous].next = new_element_index_;
    list->order [0].previous = new_element_index_;
    if (list->counter == 1)
    {
        list->order [0].next = new_element_index_;
    }

    return kDoneList;
}

enum ListError ListPushBack (list_t* const list, const list_elem_t element)
{
    ASSERT (list != NULL, "Invalid argument for list [%p] for push before tail\n", list);

    LOG (DEBUG,
                "Push before tail of the list got argument:\n"
                "| list = %p | element = %lu |\n"
                "| Head = %lu | Tail = %lu |\n",
                list, element,
                list->order [0].previous, list->order [0].next);

    if (list->counter + 1 >= list->size)
    {
        return kCantPushList;
    }

    list->counter++;

    size_t new_element_index_ = list->free;

    list->free = list->order [list->free].next;

    list->data  [new_element_index_] = element;
    list->order [new_element_index_].next = list->order [0].previous;
    list->order [new_element_index_].previous = 0;

    list->order [list->order [0].next].previous = new_element_index_;
    list->order [0].next = new_element_index_;
    if (list->counter == 1)
    {
        list->order [0].previous = new_element_index_;
    }

    return kDoneList;
}

