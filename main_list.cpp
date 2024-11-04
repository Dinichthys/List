#include "Headers/list.h"

#include <stdio.h>
#include <stdlib.h>

#include "My_lib/Logger/logging.h"

int main ()
{
    FILE* const error_file = fopen ("My_lib/Logger/error.txt", "w");
    if (error_file == NULL)
    {
        fprintf (stderr, "Can't start logging\n");
        return EXIT_FAILURE;
    }
    set_log_file (error_file);
    set_log_lvl (DEBUG);

    list_t list = {};

    ListError result = kDoneList;

    result = ListCtor (&list, 2000);

    ERROR_HANDLER (result);

    result = ListPushFront (&list, 100);

    ERROR_HANDLER (result);

    result = ListPushBack (&list, 777);

    ERROR_HANDLER (result);

    list_elem_t element = 0;

    result = ListPopAfterIndex (&list, &element, 1);

    ERROR_HANDLER (result);

    fprintf (stderr, "Element = %lu\n", element);

    result = ListPushFront (&list, 100);

    ERROR_HANDLER (result);

    result = ListPushFront (&list, 100);

    ERROR_HANDLER (result);

    result = ListPushFront (&list, 100);

    ERROR_HANDLER (result);

    result = ListPopAfterIndex (&list, &element, 2);

    ERROR_HANDLER (result);

    fprintf (stderr, "Element = %lu\n", element);

    result = ListDtor (&list);

    ERROR_HANDLER (result);

    fclose (error_file);

    return EXIT_SUCCESS;
}
