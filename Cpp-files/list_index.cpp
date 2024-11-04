#include "../Headers/list_index.h"
#include "../Headers/list.h"

#include <stdlib.h>

#include "../My_lib/Assert/my_assert.h"
#include "../My_lib/Logger/logging.h"

size_t NextIndex (const list_t* const list, const size_t index)
{
    ASSERT (list != NULL, "Invalid argument list [%p]\n", list);

    return list->order [index].next;
}

size_t PrevIndex (const list_t* const list, const size_t index)
{
    ASSERT (list != NULL, "Invalid argument list [%p]\n", list);

    return list->order [index].previous;
}

size_t HeadIndex (const list_t* const list)
{
    ASSERT (list != NULL, "Invalid argument list [%p]\n", list);

    return list->order [0].previous;
}

size_t TailIndex (const list_t* const list)
{
    ASSERT (list != NULL, "Invalid argument list [%p]\n", list);

    return list->order [0].next;
}
