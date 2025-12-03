#include "hc_collections.h"
#include "hc_collections/singly_linked_set.h"

HC_SinglyLinkedSet_t *hc_SLS_create(void)
{
    HC_SinglyLinkedSet_t *pNode = calloc(1, sizeof(HC_SinglyLinkedSet_t));
    if (!pNode)
        return NULL;

    return pNode;
}

HC_SinglyLinkedSet_t *hc_SLS_nodeNew(void *pData, HC_HashCode_Func hash_code_func)
{
    if (!pData || !hash_code_func)
        return NULL;

    HC_SinglyLinkedSet_t *pNode = malloc(sizeof(HC_SinglyLinkedSet_t));
    if (!pNode)
        return NULL;

    pNode->pData = pData;
    pNode->pNext = NULL;
    pNode->hashCode = hash_code_func(pData);

    return pNode;
}

bool hc_SLS_nodeIsSentinel(HC_SinglyLinkedSet_t *pNode)
{
    // Sentinel nodes will always have no data and a hashCode of 0
    return pNode && !pNode->pData && pNode->hashCode == 0;
}

bool hc_SLS_nodeAdd(HC_SinglyLinkedSet_t **ppSentinel, HC_SinglyLinkedSet_t *pNode)
{
    if (!ppSentinel || !*ppSentinel || !hc_SLL_nodeIsSentinel(*ppSentinel) || !pNode || hc_SLL_nodeIsSentinel(pNode))
        return false;

    HC_SinglyLinkedSet_t *pCurrent = *ppSentinel;
    while (pCurrent && pCurrent->pNext != NULL)
        pCurrent = pCurrent->pNext;

    pCurrent->pNext = pNode;

    return true;
}

bool hc_SLS_dataAdd(HC_SinglyLinkedSet_t **ppSentinel, void *pData, HC_HashCode_Func hash_code_func)
{
    if (!ppSentinel || !*ppSentinel || !pData || !hash_code_func)
        return false;

    HC_SinglyLinkedSet_t *pNode = hc_SLS_nodeNew(pData, hash_code_func);
    if (!pNode)
        return false;

    return hc_SLS_nodeAdd(ppSentinel, pNode);
}

bool hc_SLS_nodeDestroy(HC_SinglyLinkedSet_t *pNode, HC_DataDestructor_Func data_destructor_func)
{
    if (!pNode || hc_SLS_nodeIsSentinel(pNode))
        return false;

    if (data_destructor_func && pNode->pData)
        data_destructor_func(pNode->pData);

    free(pNode);
    return true;
}

bool hc_SLS_destroy(HC_SinglyLinkedSet_t **ppSentinel, HC_DataDestructor_Func data_destructor_func)
{
    if (!ppSentinel || !*ppSentinel)
        return false;

    if (!hc_SLS_nodeIsSentinel(*ppSentinel))
        return false;

    HC_SinglyLinkedSet_t *pNode = *ppSentinel;
    while (pNode)
    {
        HC_SinglyLinkedSet_t *pNext = pNode->pNext;

        hc_SLS_nodeDestroy(pNode, data_destructor_func);

        pNode = pNext;
    }

    *ppSentinel = NULL;

    return true;
}