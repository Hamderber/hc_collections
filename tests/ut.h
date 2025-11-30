#pragma once
#include <stdio.h>
#include <stdbool.h>

static inline int ut_assert(const bool TEST, const char *pDEBUG_MESSAGE)
{
    int result = (int)(!TEST);
    printf("%-72s%s\n", pDEBUG_MESSAGE, TEST ? "PASS" : "FAIL");

    return result;
}