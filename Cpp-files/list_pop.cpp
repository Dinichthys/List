#include "../Headers/list_pop.h"
#include "../Headers/list.h"

#include <stdlib.h>

#include "../My_lib/Assert/my_assert.h"
#include "../My_lib/Logger/logging.h"

enum ListError ListPopAfterIndex (list_t* const list, list_elem_t* const element, const size_t index)
{
    ASSERT (list    != NULL, "Invalid argument list [%p] for pop of index\n", list);
    ASSERT (element != NULL, "Invalid argument element  [%p] for pop of index\n", element);

    LOG (DEBUG,
                "Pop of index of the list got argument:\n"
                "| list = %p | element = %p | index = %lu |\n"
                "| Next = %lu | Previous = %lu |\n",
                list, element, index,
                list->order [index].next, list->order [index].previous);

    if ((list->counter == 0) || (list->order [index].previous == (size_t) -1))
    {
        return kCantPopList;
    }

    list->counter--;

    *element = list->data [index];

    size_t previous_elem_ = list->order [index].previous;
    size_t next_elem_ = list->order [index].next;

    list->order [previous_elem_].next = next_elem_;
    list->order [next_elem_].previous = previous_elem_;

    list->order [index].next = list->free;
    list->order [index].previous = (size_t) - 1;

    list->free = index;

    return kDoneList;
}

enum ListError ListPopFront (list_t* const list, list_elem_t* const element)
{
    ASSERT (list    != NULL, "Invalid argument list [%p] for pop front\n", list);
    ASSERT (element != NULL, "Invalid argument element  [%p] for pop front\n", element);

    LOG (DEBUG,
                "Pop front of the list got argument:\n"
                "| list = %p | element = %p |\n"
                "| Head = %lu | Tail = %lu |\n",
                list, element,
                list->order [0].previous, list->order [0].next);

    if (list->counter == 0)
    {
        return kCantPopList;
    }

    list->counter--;

    const size_t index_head_ = list->order [0].previous;

    *element = list->data [index_head_];

    size_t previous_elem_ = list->order [index_head_].previous;
    size_t next_elem_ = list->order [index_head_].next;

    list->order [previous_elem_].next = next_elem_;
    list->order [next_elem_].previous = previous_elem_;

    list->order [index_head_].next = list->free;
    list->order [index_head_].previous = (size_t) - 1;

    list->free = index_head_;

    return kDoneList;
}

enum ListError ListPopBack (list_t* const list, list_elem_t* const element)
{
    ASSERT (list    != NULL, "Invalid argument list [%p] for pop back\n", list);
    ASSERT (element != NULL, "Invalid argument element  [%p] for pop back\n", element);

    LOG (DEBUG,
                "Pop back of the list got argument:\n"
                "| list = %p | element = %p |\n"
                "| Head = %lu | Tail = %lu |\n",
                list, element,
                list->order [0].previous, list->order [0].next);

    if (list->counter == 0)
    {
        return kCantPopList;
    }

    list->counter--;

    const size_t index_tail_ = list->order [0].previous;

    *element = list->data [index_tail_];

    size_t previous_elem_ = list->order [index_tail_].previous;
    size_t next_elem_ = list->order [index_tail_].next;

    list->order [previous_elem_].next = next_elem_;
    list->order [next_elem_].previous = previous_elem_;

    list->order [index_tail_].next = list->free;
    list->order [index_tail_].previous = (size_t) - 1;

    list->free = index_tail_;

    return kDoneList;
}
