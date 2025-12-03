#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef bool (*HC_LeftRightCompare_Func)(void *pDataLeft, void *pDataRight);

typedef void (*HC_DataDestructor_Func)(void *pData);

#include "hc_collections/singly_linked_list.h"
#include "hc_collections/doubly_linked_list.h"