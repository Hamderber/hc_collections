#pragma once
#include "hc_collections.h"

/// @brief A singly linked set, which contains data and tracks the address of the next element or NULL if the node is at the tail.
/// pData will be NULL only when being used as the set's sentinel node. Node additions will only be allowed when the hashCode value
/// is unique within the set.
typedef struct HC_SinglyLinkedSet_t
{
    void *pData;
    struct HC_SinglyLinkedSet_t *pNext;
    int hashCode;
} HC_SinglyLinkedSet_t;

HC_SinglyLinkedSet_t *hc_SLS_create(void);

HC_SinglyLinkedSet_t *hc_SLS_nodeNew(void *pData, HC_HashCode_Func hash_code_func);

bool hc_SLS_nodeIsSentinel(HC_SinglyLinkedSet_t *pNode);

bool hc_SLS_dataAdd(HC_SinglyLinkedSet_t **ppSentinel, void *pData, HC_HashCode_Func hash_code_func);

bool hc_SLS_nodeDestroy(HC_SinglyLinkedSet_t *pNode, HC_DataDestructor_Func data_destructor_func);

bool hc_SLS_nodeDestroy(HC_SinglyLinkedSet_t *pNode, HC_DataDestructor_Func data_destructor_func);

bool hc_SLS_destroy(HC_SinglyLinkedSet_t **ppSentinel, HC_DataDestructor_Func data_destructor_func);