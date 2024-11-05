#include "../include/list_error_handler.h"
#include "../include/list.h"

#include <stdlib.h>

#include "../My_lib/Assert/my_assert.h"
#include "../My_lib/Logger/logging.h"
#include "../My_lib/helpful.h"

const char* EnumToStr (const enum ListError error)
{
    #define CASE_ENUM_(enum_elem)       \
        case enum_elem:                 \
        {                               \
            return #enum_elem;          \
        }

    switch (error)
    {
        CASE_ENUM_ (kDoneList);

        CASE_ENUM_ (kCantCtorList);
        CASE_ENUM_ (kCantDtorList);

        CASE_ENUM_ (kCantPushList);
        CASE_ENUM_ (kCantPopList);

        CASE_ENUM_ (kCantDumpList);

        CASE_ENUM_ (kVerifyListNullPtr);
        CASE_ENUM_ (kVerifyListInvalidZeroElem);
        CASE_ENUM_ (kVerifyListInvalidSize);
        CASE_ENUM_ (kVerifyListInvalidOrderList);
        CASE_ENUM_ (kVerifyListInvalidOrderFree);

        default:
            return "Undefined enum element";
    }

    return "Function didn't completed";

    #undef CASE_ENUM_
}

enum ListError VerifyList (const list_t* const list)
{
    if (list == NULL)
    {
        return kVerifyListNullPtr;
    }

    if ((list->data [0] != 0)
        || ((list->order [0].next == 0) && (list->order [0].previous != 0))
        || ((list->order [0].next != 0) && (list->order [0].previous == 0))
        || ((list->order [0].next == 0) && (list->order [0].previous == 0) && (list->counter != 0)))
    {
        return kVerifyListInvalidZeroElem;
    }

    if (list->size < list->counter)
    {
        return kVerifyListInvalidSize;
    }

    size_t index_element = list->order [0].next;

    while (index_element != 0)
    {
        if ((list->order [index_element].previous == (size_t) - 1)
            || (list->order [index_element].next     != list->order [list->order [index_element].next].previous)
            || (list->order [index_element].previous != list->order [list->order [index_element].previous].next))
        {
            return kVerifyListInvalidOrderList;
        }

        index_element = list->order [index_element].next;
    }

    index_element = list->free;

    while (index_element != 0)
    {
        if (list->order [index_element].previous != (size_t) - 1)
        {
            return kVerifyListInvalidOrderFree;
        }

        index_element = list->order [index_element].next;
    }

    return kDoneList;
}

enum ListError ListDump (const list_t* const list)
{
    FILE* dump_file = fopen ("Dump_file.dot", "w");
    if (dump_file == NULL)
    {
        return kCantDumpList;
    }

    fprintf (dump_file, "digraph\n{\n"
    "\tfontname=\"Helvetica,Arial,sans-serif\";\n"
    "\tnode [fontname=\"Helvetica,Arial,sans-serif\"];\n"
    "\tgraph [rankdir = \"LR\"];\n"
	"\tranksep = 1.5;\n");

//------------------------------------------------------------------------------------------------------------

    fprintf (dump_file, "\n{\n"
                        "rank=max;\n");

    fprintf (dump_file, "\n\t\"node-1\" [\n"
                        "\t\tlabel = \""
                        "<f0> free| "
                        "<f1> %lu\"\n"
                        "\t\tshape = \"record\"\n"
                        "\t];\n",
                        list->free);

    fprintf (dump_file, "\n\t\"node0\" [\n"
                        "\t\tlabel = \""
                        "<f0> index = 0| "
                        "<f1> | "
                        "<f2> Tail = %lu| "
                        "<f3> Head = %lu\"\n"
                        "\t\tshape = \"record\"\n"
                        "\t];\n",
                        list->order [0].next, list->order [0].previous);

    fprintf (dump_file, "}\n");

//------------------------------------------------------------------------------------------------------------

    fprintf (dump_file, "\n{\n"
                        "rank=min;\n");

    for (size_t index = 1; index < list->size; index++)
    {
        fprintf (dump_file, "\t\"node%lu\" [\n"
                            "\t\tlabel = \""
                            "<f0> index = %lu| "
                            "<f1> data = %lu| "
                            "<f2> next = %lu| "
                            "<f3> previous = %lu\"\n"
                            "\t\tshape = \"record\"\n"
                            "\t];\n",
                            index,
                            index,
                            list->data [index],
                            list->order [index].next, list->order [index].previous);
    }

    fprintf (dump_file, "}\n");

//------------------------------------------------------------------------------------------------------------

    for (size_t index = 0; index < list->size - 1; index++)
    {
        fprintf (dump_file, "\t\"node%lu\":f0 -> \"node%lu\":f0 "
                            "[color=\"white\"];\n\n", index, index + 1);
    }

    fprintf (dump_file, "\n");

    for (size_t index = 0; index < list->size; index++)
    {
        fprintf (dump_file, "\t\"node%lu\":f2 -> \"node%lu\":f0 "
                            "[color=\"black\"];\n\n", index, list->order [index].next);
        if (list->order [index].previous != (size_t) -1)
        {
            fprintf (dump_file, "\t\"node%lu\":f3 -> \"node%lu\":f0 "
                                "[color=\"black\"];\n\n", index, list->order [index].previous);
        }
    }

    fprintf (dump_file, "\n\t\"node-1\":f1 -> \"node%lu\":f0 [color=\"green\"];\n", list->free);

    fprintf (dump_file, "}");

    CLOSE_AND_NULL (dump_file);

    return kDoneList;
}