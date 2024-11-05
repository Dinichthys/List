#include "../include/list_pop.h"
#include "../include/list.h"

#include <stdlib.h>

#include "../My_lib/Assert/my_assert.h"
#include "../My_lib/Logger/logging.h"

enum ListError ListPopAfterIndex (list_t* const list, list_elem_t* const element, size_t index)
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

    if (list->counter + 1 > index)
    {
        list->data [index] = list->data [list->counter + 1];
        list->order [index] = list->order [list->counter + 1];

        list->order [list->order [index].previous].next = index;
        list->order [list->order [index].next].previous = index;

        index = list->counter + 1;
    }

    list->data [index] = 0;
    list->order [index].next = list->free;
    list->order [index].previous = (size_t) -1;

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

    enum ListError result = ListPopAfterIndex (list, element, list->order [0].previous);

    return result;
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

    enum ListError result = ListPopAfterIndex (list, element, list->order [0].next);

    return result;
}
