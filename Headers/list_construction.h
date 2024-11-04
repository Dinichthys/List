#ifndef LIST_CONSTRUCTION_H
#define LIST_CONSTRUCTION_H

#include "list.h"

#include <stdlib.h>

#include "../My_lib/helpful.h"

enum ListError ListCtor (list_t* const list, const size_t number_elem);
enum ListError ListDtor (list_t* const list);

#endif // LIST_CONSTRUCTION_H
