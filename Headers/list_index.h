#ifndef LIST_INDEX_H
#define LIST_INDEX_H

#include "list.h"

#include <stdlib.h>

size_t NextIndex (const list_t* const list, const size_t index);
size_t PrevIndex (const list_t* const list, const size_t index);
size_t HeadIndex (const list_t* const list);
size_t TailIndex (const list_t* const list);

#endif // LIST_INDEX_H
