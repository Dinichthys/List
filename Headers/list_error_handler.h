#ifndef LIST_ERROR_HANDLER_H
#define LIST_ERROR_HANDLER_H

#include "list.h"

#define ERROR_HANDLER(result)                                   \
    if (result != kDoneList)                                    \
    {                                                           \
        const char* error = EnumToStr (result);                 \
        fprintf (stderr, " Code error = {%d} \n", result);      \
        fprintf (stderr, " Error is %s \n", error);             \
        fclose (error_file);                                    \
        ListDtor (&list);                                       \
        return EXIT_FAILURE;                                    \
    }

const char* EnumToStr (const enum ListError error);
enum ListError VerifyList (const list_t* const list);

#endif // LIST_ERROR_HANDLER_h
