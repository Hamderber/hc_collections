#include "hc_collections.h"
#include "hc_collections/doubly_linked_list.h"

HC_DoublyLinkedList_t *hc_DLL_create(void)
{
    HC_DoublyLinkedList_t *pNode = calloc(1, sizeof(HC_DoublyLinkedList_t));
    if (!pNode)
        return NULL;

    return pNode;
}

HC_DoublyLinkedList_t *hc_DLL_nodeNew(void *pData)
{
    if (!pData)
        return NULL;

    HC_DoublyLinkedList_t *pNode = malloc(sizeof(HC_DoublyLinkedList_t));
    if (!pNode)
        return NULL;

    pNode->pPrev = NULL;
    pNode->pData = pData;
    pNode->pNext = NULL;

    return pNode;
}

// !pNode->pPrev
bool hc_DLL_nodeIsSentinel(HC_DoublyLinkedList_t *pNode)
{
    // Sentinel nodes will always have no data and no previous node. Doubly linked circular list not supported here.
    return pNode && !pNode->pData && !pNode->pPrev;
}

bool hc_DLL_nodeAdd(HC_DoublyLinkedList_t **ppSentinel, HC_DoublyLinkedList_t *pNode)
{
    if (!ppSentinel || !*ppSentinel || !hc_DLL_nodeIsSentinel(*ppSentinel) || !pNode || hc_DLL_nodeIsSentinel(pNode) || pNode->pPrev)
        return false;

    HC_DoublyLinkedList_t *pCurrent = *ppSentinel;
    while (pCurrent && pCurrent->pNext != NULL)
        pCurrent = pCurrent->pNext;

    pCurrent->pNext = pNode;
    pNode->pPrev = pCurrent;

    return true;
}

bool hc_DLL_dataAdd(HC_DoublyLinkedList_t **ppSentinel, void *pData)
{
    if (!ppSentinel || !*ppSentinel || !pData)
        return false;

    HC_DoublyLinkedList_t *pNode = hc_DLL_nodeNew(pData);
    if (!pNode)
        return false;

    return hc_DLL_nodeAdd(ppSentinel, pNode);
}

bool hc_DLL_nodeInsertAfter(HC_DoublyLinkedList_t *pNode, HC_DoublyLinkedList_t *pAdd)
{
    if (!pNode || hc_DLL_nodeIsSentinel(pNode) || !pAdd || hc_DLL_nodeIsSentinel(pAdd))
        return false;

    HC_DoublyLinkedList_t *pOldNext = pNode->pNext;

    pAdd->pPrev = pNode;
    pAdd->pNext = pOldNext;

    pNode->pNext = pAdd;
    if (pOldNext)
        pOldNext->pPrev = pAdd;

    return true;
}

bool hc_DLL_dataInsertAfter(HC_DoublyLinkedList_t *pNode, void *pData)
{
    if (!pNode || hc_DLL_nodeIsSentinel(pNode) || !pData)
        return false;

    HC_DoublyLinkedList_t *pAdd = hc_DLL_nodeNew(pData);
    if (!pAdd)
        return false;

    return hc_DLL_nodeInsertAfter(pNode, pAdd);
}

bool hc_DLL_nodeDetatch(HC_DoublyLinkedList_t **ppNode)
{
    if (!ppNode || !*ppNode || hc_DLL_nodeIsSentinel(*ppNode) || ((!(*ppNode)->pNext) && !(*ppNode)->pPrev))
        return false;

    HC_DoublyLinkedList_t *pRemove = *ppNode;
    HC_DoublyLinkedList_t *pPrev = pRemove->pPrev;
    HC_DoublyLinkedList_t *pNext = pRemove->pNext;

    if (pPrev)
        pPrev->pNext = pNext;

    if (pNext)
        pNext->pPrev = pPrev;

    pRemove->pNext = NULL;
    pRemove->pPrev = NULL;

    return true;
}

bool hc_DLL_nodeRemove(HC_DoublyLinkedList_t **ppSentinel, HC_DoublyLinkedList_t *pNode)
{
    if (!ppSentinel || !*ppSentinel || !hc_DLL_nodeIsSentinel(*ppSentinel) || !pNode || hc_DLL_nodeIsSentinel(pNode))
        return false;

    HC_DoublyLinkedList_t **ppCurrent = &(*ppSentinel)->pNext;
    while (*ppCurrent && *ppCurrent != pNode)
        ppCurrent = &(*ppCurrent)->pNext;

    if (!*ppCurrent)
        return false;

    return hc_DLL_nodeDetatch(ppCurrent);
}

bool hc_DLL_dataRemove(HC_DoublyLinkedList_t **ppSentinel, void *pData, HC_LeftRightCompare_Func data_equality_func)
{
    if (!ppSentinel || !*ppSentinel || !hc_DLL_nodeIsSentinel(*ppSentinel) || !pData)
        return false;

    HC_DoublyLinkedList_t **ppCurrent = &(*ppSentinel)->pNext;

    while (*ppCurrent && (*ppCurrent)->pData != NULL)
    {
        void *pCurrentData = (*ppCurrent)->pData;

        if ((data_equality_func && data_equality_func(pCurrentData, pData)) || pCurrentData == pData)
            break;

        ppCurrent = &(*ppCurrent)->pNext;
    }

    if (!*ppCurrent)
        return false;

    return hc_DLL_nodeDetatch(ppCurrent);
}

bool hc_DLL_nodeDestroy(HC_DoublyLinkedList_t *pNode, HC_DataDestructor_Func data_destructor_func)
{
    if (!pNode || hc_DLL_nodeIsSentinel(pNode))
        return false;

    if (data_destructor_func && pNode->pData)
        data_destructor_func(pNode->pData);

    free(pNode);
    return true;
}

bool hc_DLL_destroy(HC_DoublyLinkedList_t **ppSentinel, HC_DataDestructor_Func data_destructor_func)
{
    if (!ppSentinel || !*ppSentinel)
        return false;

    if (!hc_DLL_nodeIsSentinel(*ppSentinel))
        return false;

    HC_DoublyLinkedList_t *pNode = *ppSentinel;
    while (pNode)
    {
        HC_DoublyLinkedList_t *pNext = pNode->pNext;

        hc_DLL_nodeDestroy(pNode, data_destructor_func);

        pNode = pNext;
    }

    *ppSentinel = NULL;

    return true;
}